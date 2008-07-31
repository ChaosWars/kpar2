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
#include <KDE/KLocalizedString>
#include <KDE/KAboutData>
#include <KDE/KCmdLineArgs>
#include <KDE/KApplication>
#include <KDE/KIcon>
#include "kpar2.h"

static const char description[] ="A PAR2  verification and repair application for KDE";

static const char version[] = "0.4.0";

int main(int argc, char **argv)
{
    KCmdLineOptions options;
    options.add( "+files", ki18n( "Documents to open. You can list multiple files here." ) );
    KAboutData about( "kpar2", QByteArray(), ki18n( "KPar2" ), version, ki18n( description ),
                      KAboutData::License_GPL, ki18n( "(C) 2007 Lawrence Lee" ), ki18n(""),
                      "http://kpar2.googlecode.com", "valheru.ashen.shugar@gmail.net" );
    about.addAuthor( ki18n( "Lawrence Lee" ), ki18n( "Lead programmer" ), "valheru@facticius.net", "www.facticius.net" );
    KCmdLineArgs::init( argc, argv, &about );
    KCmdLineArgs::addCmdLineOptions( options );
    KApplication app;
    KCmdLineArgs *args = KCmdLineArgs::parsedArgs();

    if ( args->count() == 0 ){
        KPar2 *widget = new KPar2();
        widget->show();
    }else{

        for (int i = 0; i < args->count(); i++ )
        {
            KPar2 *widget = new KPar2();
            widget->show();
            widget->load( args->url( i ) );
        }

    }
    args->clear();
    return app.exec();
}
