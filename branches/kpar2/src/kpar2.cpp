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
#include <KDE/KFileDialog>
#include <KDE/KConfig>
#include <KDE/KUrl>
#include <KDE/KEditToolBar>
#include <KDE/KAction>
#include <KDE/KStandardAction>
#include <KDE/KActionCollection>
#include <KDE/KPluginLoader>
#include <KDE/KPluginFactory>
#include <KDE/KMessageBox>
#include <KDE/KStatusBar>
#include <KDE/KLocale>

KPar2::KPar2()
{
    // set the shell's ui resource file
    setXMLFile("kpar2/kpar2.rc");

    // then, setup our actions
    setupActions();

    KPluginLoader loader( "kpar2part" );
    KPluginFactory *factory = loader.factory();

    if ( factory ){
        // now that the Part is loaded, we cast it to a Part to get
        // our hands on it
        m_part = factory->create< KParts::ReadOnlyPart >();

        if( m_part ){
            // tell the KParts::MainWindow that this is indeed the main widget
            setCentralWidget( m_part->widget() );

            // and integrate the part's GUI with the shell's
            createGUI( m_part );
        }
    }
    else
    {
        // if we couldn't find our Part, we exit since the Shell by
        // itself can't do anything useful
        KMessageBox::error( this, i18n( "Could not find our part." ) );
        kapp->quit();
        // we return here, cause kapp->quit() only means "exit the
        // next time we enter the event loop...
        return;
    }

    // apply the saved mainwindow settings, if any, and ask the mainwindow
    // to automatically save settings if changed: window size, toolbar
    // position, icon size, etc.
    setAutoSaveSettings();
}

KPar2::~KPar2()
{
}

void KPar2::load( const KUrl& url )
{
    m_part->openUrl( url );
}

void KPar2::setupActions()
{
    setStandardToolBarMenuEnabled( true );
    createStandardStatusBarAction();
    KStandardAction::quit( kapp, SLOT( quit() ), actionCollection() );
    KStandardAction::keyBindings( this, SLOT( optionsConfigureKeys()), actionCollection() );
    KStandardAction::configureToolbars( this, SLOT( optionsConfigureToolbars()), actionCollection() );
}

void KPar2::saveProperties( KConfigGroup& )
{
    // the 'config' object points to the session managed
    // config file.  anything you write here will be available
    // later when this app is restored
}

void KPar2::readProperties( const KConfigGroup& )
{
    // the 'config' object points to the session managed
    // config file.  this function is automatically called whenever
    // the app is being restored.  read in here whatever you wrote
    // in 'saveProperties'
}

void KPar2::optionsConfigureKeys()
{
//     KKeyDialog::configure(actionCollection());
}

void KPar2::optionsConfigureToolbars()
{
//     saveMainWindowSettings( KGlobal::config(), autoSaveGroup() );

    // use the standard toolbar editor
    KEditToolBar dlg(factory());
    connect( &dlg, SIGNAL( newToolbarConfig() ), this, SLOT( applyNewToolbarConfig() ) );
    dlg.exec();
}

void KPar2::applyNewToolbarConfig()
{
//     applyMainWindowSettings(KGlobal::config(), autoSaveGroup());
}

#include "kpar2.moc"
