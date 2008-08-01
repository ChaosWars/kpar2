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

#include <kconfigdialog.h>
#include <kfiledialog.h>
#include <kglobal.h>
#include <klocale.h>
#include <kstatusbar.h>
#include <kstdaction.h>
#include <kio/netaccess.h>
#include <kparts/mainwindow.h>
#include <qfile.h>
#include <qlayout.h>
#include "generalsettingspage.h"
#include "kpar2gui.h"
#include "kpar2part.h"
#include "kpar2settings.h"
#include "kpar2thread.h"

KPar2Part::KPar2Part( QWidget *parentWidget, const char* /*widgetName*/,
                              QObject *parent, const char *name )
    : KParts::ReadOnlyPart( parent, name ), parent( parentWidget )
{
    // we need an instance
    setInstance( KPar2PartFactory::instance() );
    // this should be your custom internal widget
    m_widget = new KPar2GUI( parentWidget );
    // create our actions
    KStdAction::open( this, SLOT( fileOpen() ), actionCollection() );
    KStdAction::preferences( this, SLOT( optionsConfigure() ), actionCollection() );
    // Set up the PAR2 thread
    kpar2thread = new KPar2Thread( m_widget );
    // notify the part that this is our internal widget
    setWidget( m_widget );
    // set our XML-UI resource file
    setXMLFile( "kpar2part.rc" );
}

KPar2Part::~KPar2Part()
{
    kpar2thread->terminate();
    static_cast< KParts::MainWindow* >( parent )->statusBar()->message( "" );
}

bool KPar2Part::openFile()
{
    // m_file is always local so we can use QFile on it
    QFile file( m_file );
    kpar2thread->loadPAR2Files( m_file.latin1() );
    return true;
}

bool KPar2Part::openURL( const KURL & url )
{
    emit setWindowCaption( url.prettyURL() );
    m_file = KIO::NetAccess::mostLocalURL( url, 0 ).path();
    return openFile();
}

void KPar2Part::fileOpen()
{
    // this slot is called whenever the File->Open menu is selected,
    // the Open shortcut is pressed (usually CTRL+O) or the Open toolbar
    // button is clicked
    KURL file_name = KFileDialog::getOpenURL( QString::null, "*.par2 *.PAR2 | PAR2 Files" );

    if( !file_name.isEmpty() ){
        openURL( file_name );
    }
}

void KPar2Part::optionsConfigure()
{
    if( KConfigDialog::showDialog( "settings" ) )
        return;

    KConfigDialog *configDialog = new KConfigDialog( m_widget, "settings", KPar2Settings::self() );
    QWidget *generalSettingsWidget = new QWidget();
    QHBoxLayout *layout = new QHBoxLayout( generalSettingsWidget );
    layout->addWidget( new GeneralSettingsPage( generalSettingsWidget ) );
    configDialog->addPage( generalSettingsWidget, i18n( "General Settings" ), "configure" );
    connect( configDialog, SIGNAL( settingsChanged() ), kpar2thread, SLOT( loadSettings() ) );
    configDialog->show();
}

// It's usually safe to leave the factory code alone.. with the
// notable exception of the KAboutData data
#include <kaboutdata.h>
#include <klocale.h>

KInstance*  KPar2PartFactory::s_instance = 0L;
KAboutData* KPar2PartFactory::s_about = 0L;

KPar2PartFactory::KPar2PartFactory() : KParts::Factory()
{
}

KPar2PartFactory::~KPar2PartFactory()
{
    delete s_instance;
    delete s_about;

    s_instance = 0L;
}

KParts::Part* KPar2PartFactory::createPartObject( QWidget *parentWidget, const char *widgetName,
                                                  QObject *parent, const char *name,
                                                  const char* /*classname*/, const QStringList& /*args*/ )
{
    // Create an instance of our Part
    KPar2Part* obj = new KPar2Part( parentWidget, widgetName, parent, name );
    return obj;
}

KInstance* KPar2PartFactory::instance()
{
    if( !s_instance )
    {
        s_about = new KAboutData( "kpar2", I18N_NOOP("KPar2"), "0.3.2" );
        s_about->addAuthor( "Lawrence Lee", 0, "valher.ashen.shugar@gmail.com" );
        s_instance = new KInstance(s_about);
    }
    return s_instance;
}

extern "C"
{
    void* init_libkpar2part()
    {
        KGlobal::locale()->insertCatalogue( "kpar2" );
        return new KPar2PartFactory;
    }
};

#include "kpar2part.moc"