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

/**
 * @class KPar2 kpar2.h
 * @mainpage KPar2 is a PAR2 verification and repair application for KDE
 */
#ifndef _KPAR2_H_
#define _KPAR2_H_

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <kparts/mainwindow.h>
#include <kparts/factory.h>

class KConfig;

/**
 * This is the application "Shell".  It has a menubar, toolbar, and
 * statusbar but relies on the "Part" to do all the real work.
 *
 * @short Application Shell
 * @author Lawrence Lee <valheru.ashen.shugar@gmail.com>
 * @version 0.3.2
 */
class KPar2 : public KParts::MainWindow
{
    Q_OBJECT

    public:
        KPar2();
        virtual ~KPar2();

        /**
        * Use this method to load whatever file/URL you have
        */
        void load(const KURL& url);

    protected:
        /**
         * This method is called when it is time for the app to save its
         * properties for session management purposes.
         */
        void saveProperties(KConfig *);

        /**
         * This method is called when this app is restored.  The KConfig
         * object points to the session management config file that was saved
         * with @ref saveProperties
         */
        void readProperties(KConfig *);

    private slots:
        void optionsConfigureKeys();
        void optionsConfigureToolbars();
        void applyNewToolbarConfig();

    private:
        KParts::ReadOnlyPart *m_part;
        void setupAccel();
        void setupActions();
};

#endif // _KPAR2_H_
