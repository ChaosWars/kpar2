/***************************************************************************
 *   Copyright (C) 2007 by Lawrence Lee   *
 *   valheru@facticius.net   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
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
#include "kpar2gui.h"
#include "kpar2thread.h"
#include "kpar2settings.h"

KPar2Thread::KPar2Thread( KPar2GUI *gui )
{
    obj = NULL;
    m_gui = gui;
    config = KPar2Settings::self();
    operation = noop;
    autoCheck = config->autoCheck();
    autoRepair = config->autoRepair();
    connect( gui, SIGNAL( checkParity() ), this, SLOT( checkParity() ) );
    connect( gui, SIGNAL( repairFiles() ), this, SLOT( repairFiles() ) );
}

KPar2Thread::~KPar2Thread()
{
    delete obj;
}

void KPar2Thread::run()
{
    if( obj == NULL )
        obj = new KPar2Object( m_gui );

    switch( operation ){
        case load:
            if( obj->loadPAR2Files( par2file ) ){

                if( autoCheck ){

                    if( obj->checkParity( par2file ) ){

                        if( autoRepair ){
                            obj->repairFiles( par2file );
                        }

                    }

                }

            }
            break;
        case verify:
            if( obj->checkParity( par2file ) ){

                if( autoRepair ){
                    obj->repairFiles( par2file );
                }

            }
            break;
        case repair:
            obj->repairFiles( par2file );
            break;
        default:
            break;
    }

}

void KPar2Thread::loadPAR2Files( const QString& file )
{
    if( !running() ){
        operation = load;
        par2file = file;
        start();
    }
}

void KPar2Thread::checkParity()
{
    if( !running() ){
        operation = verify;
        start();
    }
}

void KPar2Thread::repairFiles()
{
    if( !running() ){
        operation = repair;
        start();
    }
}

#include "kpar2thread.moc"
