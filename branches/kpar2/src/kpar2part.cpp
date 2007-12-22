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
// #include "kpar2thread.h"
#include "kpar2part.h"
#include "kpar2gui.h"
#include "kpar2settings.h"
#include "settings.h"
#include <KDE/KParts/MainWindow>
#include <KDE/KStatusBar>
#include <KDE/KAction>
#include <KDE/KStandardAction>
#include <KDE/KFileDialog>
#include <KDE/KGlobal>
#include <KDE/KLocale>
#include <KDE/KIO/NetAccess>
#include <QFile>

//Factory Code
typedef KParts::GenericFactory< KPar2Part > KPar2PartFactory;
K_EXPORT_COMPONENT_FACTORY( kpar2part /*library name*/, KPar2PartFactory )

    KPar2Part::KPar2Part( QWidget* parentWidget,
                          QObject* parent,
                          const QStringList& args = QStringList() )
    : KParts::ReadOnlyPart(parent, name), parent( parentWidget )
{
    // we need an instance
    setInstance( KPar2PartFactory::instance() );

    // this should be your custom internal widget
    m_widget = new KPar2GUI( parentWidget );

    // notify the part that this is our internal widget
    setWidget( m_widget );

    // create our actions
    KStandardAction::open( this, SLOT( fileOpen() ), actionCollection() )->setText( i18n( "&Open PAR2 File" ) );

    // Set up the PAR2 thread
//     kpar2thread = new KPar2Thread( m_widget );

    configureAction = new KAction( KIcon( "configure" ), i18n( "&amp;Configure KPar2" ), actionCollection() );
    actionCollection()->addAction( "configure_settings", configureAction );
    connect( configureAction, SIGNAL( triggered( bool ) ), this, SLOT( configureSettings() ) );

    config = KPar2Settings::self();
    readSettings();

    // set our XML-UI resource file
    setXMLFile( "kpar2/kpar2part.rc" );

}

KPar2Part::~KPar2Part()
{
    kpar2thread->terminate();
    static_cast< KParts::MainWindow* >( parent )->statusBar()->message( "" );
    saveSettings();
}

bool KPar2Part::openFile()
{
    return false;
}

bool KPar2Part::openUrl( const KUrl & url )
{
    QString m_file( KIO::NetAccess::mostLocalURL( url, 0 ).path() );
    emit setWindowCaption( url.prettyURL() );
    return true;
}

void KPar2Part::fileOpen()
{
    // this slot is called whenever the File->Open menu is selected,
    // the Open shortcut is pressed (usually CTRL+O) or the Open toolbar
    // button is clicked
    KUrl file_name = KFileDialog::getOpenURL( QString::null, "*.par2 *.PAR2 | PAR2 Files" );

    if( !file_name.isEmpty() ){
        openUrl( file_name );
    }
}

void KPar2Part::configureSettings()
{
    if( KConfigDialog::showDialog( "settings" ) )
        return;

    settings = new Settings( m_widget, "settings", config );
    connect( settings, SIGNAL( settingsChanged() ), this, SLOT( readSettings() ) );
    connect( settings, SIGNAL( loadSettings() ), kpar2thread, SLOT( readSettings() ) );
    settings->show();
}

void KPar2Part::saveSettings()
{
    config->writeConfig();
}

void KPar2Part::readSettings()
{
}

#include "kpar2part.moc"
