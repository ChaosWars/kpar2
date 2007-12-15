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
#include <klocale.h>
#include <qgroupbox.h>
#include <qcheckbox.h>
#include <qlayout.h>
#include "settings.h"
#include "kpar2settings.h"
#include "generalsettings.h"

Settings::Settings( QWidget *parent, const char *name, KPar2Settings *config )
 : KConfigDialog( parent, name, config ), settingsChanged( false )
{
    m_config = config;
    //Set up settings page
    settingsPage = new QWidget( 0, "SettingsPage" );
    settingsPageLayout = new QVBoxLayout( settingsPage );
    generalSettings = new GeneralSettings( settingsPage );
    settingsPageLayout->addWidget( generalSettings );
    generalSettings->setAutoCheck( m_config->autoCheck() );
    generalSettings->setAutoRepair( m_config->autoRepair() );
    connect( generalSettings, SIGNAL( autoCheckToggled( bool ) ), this, SLOT( autoCheckToggled( bool ) ) );
    connect( generalSettings, SIGNAL( autoRepairToggled( bool ) ), this, SLOT( autoRepairToggled( bool ) ) );
    addPage( settingsPage, i18n( "General Settings" ), "configure" );
}


Settings::~Settings()
{
}

void Settings::autoCheckToggled( bool )
{
    settingsChanged = true;
    enableButton( Apply, true );
}

void Settings::autoRepairToggled( bool )
{
    settingsChanged = true;
    enableButton( Apply, true );
}

void Settings::updateSettings()
{
    if( settingsChanged ){
        m_config->setAutoCheck( generalSettings->autoCheck() );
        m_config->setAutoRepair( generalSettings->autoRepair() );
        m_config->writeConfig();
        settingsChanged = false;
        emit loadSettings();
    }
}

#include "settings.moc"
