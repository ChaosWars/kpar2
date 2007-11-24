/***************************************************************************
 *   Copyright (C) 2007 by Lawrence Lee   *
 *   valheru@facticius.net   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include <libpar2/par2cmdline.h>
#include <libpar2/par2repairer.h>
#include <klistview.h>
#include "kpar2object.h"
#include "kpar2gui.h"
#include "kpar2customevents.h"

KPar2Object::KPar2Object( KPar2GUI *gui )
{
    _gui = gui;
    operation = noop;
    total_files = 0;
    processed_files = 0;
    files_damaged = 0;
    files_missing = 0;
    par2repairer = NULL;
    cmdline = NULL;
}

KPar2Object::~KPar2Object()
{
    delete par2repairer;
    delete cmdline;
}

bool KPar2Object::loadPAR2Files( const QString& par2file )
{
    _gui->gui()->clear();
    bool result = false;

    if( !par2file.isEmpty() ){
        StatusMessage *m = new StatusMessage( "Loading PAR2 files..." );
        QApplication::postEvent( _gui, m );

        total_files = 0;
        processed_files = 0;

        FileProgress *f1 = new FileProgress( 0 );
        QApplication::postEvent( _gui, f1 );

        TotalProgress *t = new TotalProgress( 0 );
        QApplication::postEvent( _gui, t );

        operation = load;
        const char *program = "par2verify";
        char *argv[] = { const_cast<char*>( program ), const_cast<char*>( par2file.latin1() ) };

        if( cmdline == NULL ){
            cmdline = new CommandLine();
        }else{
            delete cmdline;
            cmdline = new CommandLine();
        }

        if( par2repairer == NULL ){
            par2repairer = new Par2Repairer();
        }else{
            delete par2repairer;
            par2repairer = new Par2Repairer();
        }

        par2repairer->sig_filename.connect( sigc::mem_fun( *this, &KPar2Object::signal_filename ) );
        par2repairer->sig_progress.connect( sigc::mem_fun( *this, &KPar2Object::signal_progress ) );
        par2repairer->sig_headers.connect( sigc::mem_fun( *this, &KPar2Object::signal_headers ) );
        par2repairer->sig_done.connect( sigc::mem_fun( *this, &KPar2Object::signal_done ) );

        cmdline->Parse( 2, argv );

        if( par2repairer->PreProcess( *cmdline ) == eSuccess ){
            result = true;

            if( !_gui->autoCheck() ){
                EnableCheckParity *c = new EnableCheckParity( true );
                QApplication::postEvent( _gui, c );
            }

        }else{

            if( !_gui->autoCheck() ){
                EnableCheckParity *c = new EnableCheckParity( false );
                QApplication::postEvent( _gui, c );
            }

        }

        FileProgress *f2 = new FileProgress( 0 );
        QApplication::postEvent( _gui, f2 );

    }else{
        qDebug( "Empty string passed as file to load, aborting!" );
    }

    return result;
}

bool KPar2Object::checkParity( const QString& par2file )
{
    bool result = false;

    if( !par2file.isEmpty() ){
        StatusMessage *m = new StatusMessage( "Checking parity..." );
        QApplication::postEvent( _gui, m );

        EnableCheckParity *c = new EnableCheckParity( false );
        QApplication::postEvent( _gui, c );
        operation = verify;
        const char *program = "par2verify";
        char *argv[] = {const_cast<char*>( program ), const_cast<char*>( par2file.latin1() )};
        cmdline->Parse( 2, argv );

        if( par2repairer->Process( *cmdline, false ) == eRepairPossible ){
            result = true;

            Finished *f1 = new Finished( QString( "%1 files are damaged." ).arg( files_damaged ) );
            QApplication::postEvent( _gui, f1 );

            Finished *f2 = new Finished( QString( "%1 files are missing." ).arg( files_missing ) );
            QApplication::postEvent( _gui, f2 );

            Finished *f3 = new Finished( "Repair is possible." );
            QApplication::postEvent( _gui, f3 );

            if( !_gui->autoRepair() ){
                EnableRepair *e = new EnableRepair( true );
                QApplication::postEvent( _gui, e );
            }

        }else{

            if( files_missing + files_damaged == 0 ){
                Finished *f = new Finished( QString( "All files are correct, repair is not required." ) );
                QApplication::postEvent( _gui, f );
            }else{
                Finished *f1 = new Finished( QString( "%1 files are damaged." ).arg( files_damaged ) );
                QApplication::postEvent( _gui, f1 );

                Finished *f2 = new Finished( QString( "%1 files are missing." ).arg( files_missing ) );
                QApplication::postEvent( _gui, f2 );

                Finished *f3 = new Finished( QString( "Repair not possible!" ) );
                QApplication::postEvent( _gui, f3 );
            }

            EnableRepair *e = new EnableRepair( false );
            QApplication::postEvent( _gui, e );
        }

        processed_files = 0;

    }else{
        qDebug( "Empty string passed as file to load, aborting!" );
    }

    return result;

}

bool KPar2Object::repairFiles( const QString& par2file )
{
    bool result = false;

    if( !par2file.isEmpty() ){
        StatusMessage *m = new StatusMessage( "Repairing..." );
        QApplication::postEvent( _gui, m );

        FileProgress *f1 = new FileProgress( 0 );
        QApplication::postEvent( _gui, f1 );

        TotalProgress *t = new TotalProgress( 0 );
        QApplication::postEvent( _gui, t );

        EnableRepair *e = new EnableRepair( false );
        QApplication::postEvent( _gui, e );

        operation = repair;
        const char *program = "par2repair";
        char *argv[] = {const_cast<char*>( program ), const_cast<char*>( par2file.latin1() )};
        cmdline->Parse( 2, argv );

        if( par2repairer->Process( *cmdline, true ) == eSuccess ){
            result = true;
            files_damaged = 0;
            files_missing = 0;
        }

    }else{
        qDebug( "Empty string passed as file to load, aborting!" );
    }

    return result;
}

void KPar2Object::signal_filename( std::string str )
{
    FileLoaded *e = new FileLoaded( str );
    QApplication::postEvent( _gui, e );
}

void KPar2Object::signal_progress( double value )
{
    double current_progress = value/10.0;
    FileProgress *e = new FileProgress( static_cast<int>( current_progress ) );
    QApplication::postEvent( _gui, e );
}

void KPar2Object::signal_headers( ParHeaders* headers )
{
    total_files = headers->recoverable_files;
    HeaderInfo *e = new HeaderInfo( headers );
    QApplication::postEvent( _gui, e );
}

void KPar2Object::signal_done( std::string filename, int blocks_available, int blocks_total )
{
    processed_files++;
    int data = blocks_total - blocks_available;

    if( operation == verify ){

        if( total_files > 0 ){
            int progress = static_cast<int>( ( static_cast<double>( processed_files )/ static_cast<double>( total_files ) ) * 100.00 );
            TotalProgress *e = new TotalProgress( progress );
            QApplication::postEvent( _gui, e );
        }

    }else if( operation == repair ){

        if( total_files > 0 ){
            int progress = static_cast<int>( ( static_cast<double>( processed_files )/ static_cast<double>( files_damaged + files_missing ) ) * 100.00 );
            TotalProgress *e = new TotalProgress( progress );
            QApplication::postEvent( _gui, e );
        }

    }

    if( data == 0 ){
        Done *e = new Done( QString( "Found" ) );
        QApplication::postEvent( _gui, e );
    }else if( data < blocks_total ){
        files_damaged++;
        Done *e = new Done( QString( "Damaged" ) );
        QApplication::postEvent( _gui, e );
    }else if( data == blocks_total ){
        files_missing++;
        Done *e = new Done( QString( filename ) );
        QApplication::postEvent( _gui, e );
    }

}

#include "kpar2object.moc"
