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

#include <par2cmdline.h>
#include <par2repairer.h>
#include "kpar2object.h"
#include "kpar2gui.h"

KPar2Object::KPar2Object( KPar2GUI *gui )
{
    total_files = processed_files = 0;
    par2repairer = new Par2Repairer();
    cmdline = new CommandLine();
    par2repairer->sig_filename.
            connect( sigc::mem_fun( *this, &KPar2Object::signal_filename ) );
    par2repairer->sig_progress.
            connect( sigc::mem_fun( *this,&KPar2Object::signal_progress ) );
    par2repairer->sig_headers.
            connect( sigc::mem_fun( *this,&KPar2Object::signal_headers ) );
    par2repairer->sig_done.
            connect( sigc::mem_fun( *this,&KPar2Object::signal_done ) );
    connect( this, SIGNAL( headerInfo( ParHeaders* ) ), gui, SLOT( appendHeaderInfo( ParHeaders* ) ) );
    connect( this, SIGNAL( fileLoaded( const QString& ) ), gui, SLOT( fileLoaded( const QString& ) ) );
    connect( this, SIGNAL( fileProgress( int ) ), gui, SIGNAL( fileProgress( int ) ) );
    connect( this, SIGNAL( totalProgress( int ) ), gui, SIGNAL( totalFileProgress( int ) ) );
    connect( this, SIGNAL( enableCheckParity( bool ) ), gui, SLOT( enableCheckParity( bool ) ) );
    connect( this, SIGNAL( enableRepair( bool ) ), gui, SLOT( enableRepair( bool ) ) );
//     connect( this, SIGNAL( done( const QString& ) ), gui, SLOT( done( const QString& ) ) );
}

KPar2Object::~KPar2Object()
{
    delete par2repairer;
    delete cmdline;
}

void KPar2Object::loadPAR2Files( const QString& par2file )
{
    const char *program = "par2verify";
    char *argv[] = {const_cast<char*>( program ), const_cast<char*>( par2file.latin1() )};
    cmdline->Parse( 2, argv );
    if( par2repairer->PreProcess( *cmdline ) == eSuccess )
        emit( enableCheckParity( true ) );
    else
        emit( enableCheckParity( false ) );

    emit( fileProgress( 0.00 ) );
}

void KPar2Object::checkParity()
{
    const char *program = "par2verify";
    char *argv[] = {const_cast<char*>( program ), const_cast<char*>( par2file.latin1() )};
    cmdline->Parse( 2, argv );

    if( par2repairer->Process( *cmdline, false ) == eRepairPossible )
        emit( enableRepair( true ) );
    else
        emit( enableRepair( false ) );
}

void KPar2Object::repairFiles()
{
    const char *program = "par2repair";
    char *argv[] = {const_cast<char*>( program ), const_cast<char*>( par2file.latin1() )};
    cmdline->Parse( 2, argv );

    if( par2repairer->Process( *cmdline, true ) == eSuccess )
        emit( enableRepair( false ) );
}

void KPar2Object::signal_filename( std::string str )
{
    emit( fileLoaded( QString( str ) ) );
}

void KPar2Object::signal_progress( double value )
{
    emit( fileProgress( static_cast<int>( value/10.0 ) ) );
}

void KPar2Object::signal_headers( ParHeaders* headers )
{
    emit( headerInfo( headers ) );
}

void KPar2Object::signal_done( std::string filename, int blocks_available, int blocks_total )
{
    emit( done( QString( "%1 : %2 blocks available of a total of %3 blocks" ).arg( filename ).arg( blocks_available ).arg( blocks_total ) ) );
}

#include "kpar2object.moc"
