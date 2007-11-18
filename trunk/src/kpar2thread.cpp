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

#include "kpar2thread.h"
#include "kpar2object.h"
#include "kpar2gui.h"

KPar2Thread::KPar2Thread( KPar2GUI *gui )
{
    _gui = gui;
    operation = KPar2Thread::noop;
    connect( gui, SIGNAL( checkParity() ), this, SLOT( checkParity() ) );
    connect( gui, SIGNAL( repairFiles() ), this, SLOT( repairFiles() ) );
}

KPar2Thread::~KPar2Thread()
{
}

void KPar2Thread::run()
{
    if( !obj )
        obj = new KPar2Object( _gui );

    switch( operation ){
        case KPar2Thread::load:
            obj->loadPAR2Files( par2file );
            break;
        case KPar2Thread::verify:
            obj->checkParity();
            break;
        case KPar2Thread::repair:
            obj->repairFiles();
            break;
        default:
            break;
    }

}

void KPar2Thread::loadPAR2Files( const QString& file )
{
    if( !running() ){
        operation = KPar2Thread::load;
        par2file = file;
        start();
    }
}

void KPar2Thread::checkParity()
{
    if( !running() ){
        operation = KPar2Thread::verify;
        start();
    }
}

void KPar2Thread::repairFiles()
{
    if( !running() ){
        operation = KPar2Thread::repair;
        start();
    }
}

#include "kpar2thread.moc"
