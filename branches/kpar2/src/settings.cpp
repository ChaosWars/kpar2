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
#include <KDE/KLocale>
#include <QEvent>
#include "settings.h"
#include "kpar2settings.h"
#include "generalsettingspage.h"

Settings::Settings( QWidget *parent, const char *name, KPar2Settings *config )
 : KConfigDialog( parent, name, config ), m_config( config ), settingsChanged( false )
{
    //Set up settings page
    settingsPage = new GeneralSettingsPage( 0, "SettingsPage" );
    readSettings();
    connect( settingsPage, SIGNAL( autoCheckToggled( bool ) ), this, SLOT( autoCheckToggled( bool ) ) );
    connect( settingsPage, SIGNAL( autoRepairToggled( bool ) ), this, SLOT( autoRepairToggled( bool ) ) );
    connect( this, SIGNAL( cancelClicked() ), this, SLOT( cancelled() ) );
    addPage( settingsPage, i18n( "General Settings" ), "configure" );
}


Settings::~Settings()
{
}

void Settings::showEvent( QShowEvent* )
{
    readSettings();
    /* Since reading the settings can cause dialog settings to change,
     * we must now reset the document's changed status */
    cancelled();
}

void Settings::readSettings()
{
//     settingsPage->setAutoCheck( m_config->autoCheck() );
//     settingsPage->setAutoRepair( m_config->autoRepair() );
}

void Settings::autoCheckToggled( bool )
{
    settingsChanged = true;
    enableButtonApply( true );
}

void Settings::autoRepairToggled( bool )
{
    settingsChanged = true;
    enableButtonApply( true );
}

void Settings::updateSettings()
{
    if( settingsChanged ){
//         m_config->setAutoCheck( settingsPage->autoCheck() );
//         m_config->setAutoRepair( settingsPage->autoRepair() );
        m_config->writeConfig();
        settingsChanged = false;
        emit loadSettings();
    }
}

void Settings::cancelled()
{
    settingsChanged = false;
    enableButtonApply( false );
}

#include "settings.moc"
