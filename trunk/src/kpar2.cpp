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

#ifdef COMPILE_FOR_KDE4

#include <KDE/KFileDialog>
#include <KDE/KConfig>
#include <KDE/KUrl>
#include <KDE/KEditToolbar>
#include <KDe/KAction>
#include <KDE/KStdAction>
#include <KDe/KLibLoader>
#include <KDE/KMessageBox>
#include <KDE/KStatusBar>
#include <KDE/KLocale>

#else

#include <kkeydialog.h>
#include <kfiledialog.h>
#include <kconfig.h>
#include <kurl.h>
#include <kedittoolbar.h>
#include <kaction.h>
#include <kstdaction.h>
#include <klibloader.h>
#include <kmessagebox.h>
#include <kstatusbar.h>
#include <klocale.h>

#endif

KPar2::KPar2()
    : KParts::MainWindow( 0L, "KPar2" )
{
    // set the shell's ui resource file
    setXMLFile("kpar2_shell.rc");

    // then, setup our actions
    setupActions();

    // and a status bar
//     statusBar()->show();

    // this routine will find and load our Part.  it finds the Part by
    // name which is a bad idea usually.. but it's alright in this
    // case since our Part is made for this Shell
    KLibFactory *factory = KLibLoader::self()->factory("libkpar2part");
    if ( factory ){
        // now that the Part is loaded, we cast it to a Part to get
        // our hands on it
        m_part = static_cast<KParts::ReadOnlyPart *>(factory->create(this,
                "kpar2_part", "KParts::ReadOnlyPart" ));

        if( m_part ){
            // tell the KParts::MainWindow that this is indeed the main widget
            setCentralWidget(m_part->widget());

            // and integrate the part's GUI with the shell's
            createGUI(m_part);
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

void KPar2::load( const KURL& url )
{
    m_part->openURL( url );
}

void KPar2::setupActions()
{
    setStandardToolBarMenuEnabled( true );
    createStandardStatusBarAction();
    KStdAction::quit( kapp, SLOT( quit() ), actionCollection() );
    KStdAction::keyBindings( this, SLOT( optionsConfigureKeys()), actionCollection() );
    KStdAction::configureToolbars( this, SLOT( optionsConfigureToolbars()), actionCollection() );
}

void KPar2::saveProperties( KConfig* )
{
    // the 'config' object points to the session managed
    // config file.  anything you write here will be available
    // later when this app is restored
}

void KPar2::readProperties( KConfig* )
{
    // the 'config' object points to the session managed
    // config file.  this function is automatically called whenever
    // the app is being restored.  read in here whatever you wrote
    // in 'saveProperties'
}

void KPar2::optionsConfigureKeys()
{
    KKeyDialog::configure(actionCollection());
}

void KPar2::optionsConfigureToolbars()
{
#if defined(KDE_MAKE_VERSION)
# if KDE_VERSION >= KDE_MAKE_VERSION(3,1,0)
    saveMainWindowSettings( KGlobal::config(), autoSaveGroup() );
# else
    saveMainWindowSettings( KGlobal::config() );
# endif
#else
    saveMainWindowSettings( KGlobal::config() );
#endif

    // use the standard toolbar editor
    KEditToolbar dlg(factory());
    connect( &dlg, SIGNAL( newToolbarConfig() ), this, SLOT( applyNewToolbarConfig() ) );
    dlg.exec();
}

void KPar2::applyNewToolbarConfig()
{
#if defined(KDE_MAKE_VERSION)
# if KDE_VERSION >= KDE_MAKE_VERSION(3,1,0)
    applyMainWindowSettings(KGlobal::config(), autoSaveGroup());
# else
    applyMainWindowSettings(KGlobal::config());
# endif
#else
    applyMainWindowSettings(KGlobal::config());
#endif
}

#include "kpar2.moc"
