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
#ifndef SETTINGS_H
#define SETTINGS_H

#include <kconfigdialog.h>

class KPar2Settings;
class QVBoxLayout;
class GeneralSettings;

/**
	@author Lawrence Lee <valheru@facticius.net>
*/
class Settings : public KConfigDialog
{
    Q_OBJECT

    public:
        Settings( QWidget *parent = 0, const char *name = 0, KPar2Settings *config = 0 );
        ~Settings();

    protected slots:
        virtual void updateSettings();

    private:
        KPar2Settings *m_config;
        QWidget *settingsPage;
        QVBoxLayout *settingsPageLayout;
        GeneralSettings *generalSettings;
        bool settingsChanged;

    private slots:
        void autoCheckToggled( bool on );
        void autoRepairToggled( bool on );

    signals:
        void loadSettings();
};

#endif
