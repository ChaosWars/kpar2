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
#include "kpar2.h"
#include <kapplication.h>
#include <kaboutdata.h>
#include <kcmdlineargs.h>
#include <klocale.h>

static const char description[] =
    I18N_NOOP( "PAR2 verification and repair application for KDE" );

static const char version[] = "0.3.2";

static KCmdLineOptions options[] =
{
    { "+[URL]", I18N_NOOP( "Document to open" ), 0 },
    KCmdLineLastOption
};

int main(int argc, char **argv)
{
    KAboutData about( "kpar2", I18N_NOOP("KPar2"), version, description, KAboutData::License_GPL,
                      "(C) 2007-2008 Lawrence Lee", 0, "http://kpar2.googlecode.com", "http://code.google.com/p/kpar2/issues/list" );
    about.addAuthor( "Lawrence Lee", 0, "valheru.ashen.shugar@gmail.com" );
    KCmdLineArgs::init( argc, argv, &about );
    KCmdLineArgs::addCmdLineOptions( options );
    KCmdLineArgs::addTempFileOptions();
    KApplication app;

    // see if we are starting with session management
    if ( app.isRestored() ){
        RESTORE( KPar2 );
    }else{
        // no session.. just start up normally
        KCmdLineArgs *args = KCmdLineArgs::parsedArgs();

        if ( args->count() == 0 ){
            KPar2 *widget = new KPar2();
            widget->show();
        }else{
            int i = 0;
            for (; i < args->count(); i++ )
            {
                KPar2 *widget = new KPar2();
                widget->show();
                widget->load( args->url( i ) );
            }
        }
        args->clear();
    }

    return app.exec();
}
