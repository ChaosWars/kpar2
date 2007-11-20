/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you want to add, delete, or rename functions or slots, use
** Qt Designer to update this file, preserving your code.
**
** You should not define a constructor or destructor in this file.
** Instead, write your code in functions called init() and destroy().
** These will automatically be called by the form's constructor and
** destructor.
*****************************************************************************/

#include <parheaders.h>
#include <qpixmap.h>
#include <qimage.h>
#include "kpar2customevents.h"
#include "kpar2guisettings.h"
#include "kpar2gui_images.h"

void KPar2GUI::init()
{
    FileDisplay->setSortColumn( -1 );
    connect( CheckParityButton, SIGNAL( clicked() ), this, SIGNAL( checkParity() ) );
    connect( RepairFilesButton, SIGNAL( clicked() ), this, SIGNAL( repairFiles() ) );
    connect( this, SIGNAL( fileProgress( int ) ), CurrentFileProgress, SLOT( setValue( int ) ) );
    connect( this, SIGNAL( totalFileProgress( int ) ), TotalFileProgress, SLOT( setValue( int ) ) );
    readConfig();
}

void KPar2GUI::destroy()
{
    saveSettings();
}

void KPar2GUI::customEvent( QCustomEvent *e )
{
        if( e->type() ==  QEvent::User ){
            HeaderInfo *he = ( HeaderInfo* )e;
            new QListViewItem( FileDisplay, FileDisplay->lastItem(), "There are " + QString::number( he->headers()->recoverable_files ) + " recoverable files and " +  QString::number( he->headers()->other_files ) + " other files." );
            new QListViewItem( FileDisplay, FileDisplay->lastItem(), "The block size used was " + QString::number( he->headers()->block_size ) );
            new QListViewItem( FileDisplay, FileDisplay->lastItem(), "There are a total of " + QString::number( he->headers()->data_blocks ) + " data blocks." );
            new QListViewItem( FileDisplay, FileDisplay->lastItem(), "The total size of the data files is " + QString::number( he->headers()->data_size ) + " bytes." );
        }else if( e->type() ==  QEvent::User + 1 ){
            FileLoaded *fe = ( FileLoaded* )e;
            new QListViewItem( FileDisplay, FileDisplay->lastItem(), fe->file() );
        }else if( e->type() ==  QEvent::User + 2 ){
            FileProgress *fe = ( FileProgress* )e;
            CurrentFileProgress->setValue( fe->progress() );
        }else if( e->type() ==  QEvent::User + 3 ){
            TotalProgress *fe = ( TotalProgress* )e;
            TotalFileProgress->setValue( fe->progress() );
        }else if( e->type() ==  QEvent::User + 4 ){
            EnableCheckParity *ee = ( EnableCheckParity* )e;
            CheckParityButton->setEnabled( ee->enable() );
        }else if( e->type() ==  QEvent::User + 5 ){
            EnableRepair *ee = ( EnableRepair* )e;
            RepairFilesButton->setEnabled( ee->enable() );
        }else if( e->type() ==  QEvent::User + 6 ){
            Done *de = ( Done* )e;

            if( de->info() == "Found" ){
//                 FileDisplay->lastItem()->setText( 1, "Found" );
                FileDisplay->lastItem()->setPixmap( 1, QPixmap( QImage( image_0_data ) ) );
            }else if( de->info() == "Damaged" ){
//                 FileDisplay->lastItem()->setText( 1, "Damaged" );
                FileDisplay->lastItem()->setPixmap( 1, QPixmap( QImage ( "reload" ) ) );
            }else{ //Missing
                new QListViewItem( FileDisplay, FileDisplay->lastItem(), de->info() );
//                 FileDisplay->lastItem()->setText( 1, "Missing" );
                FileDisplay->lastItem()->setPixmap( 1, QPixmap( QImage ( "cancel" ) ) );
            }

        }else if( e->type() ==  QEvent::User + 7 ){
            Finished *fe = ( Finished* )e;
            new QListViewItem( FileDisplay, FileDisplay->lastItem(), fe->info() );
        }
}

void KPar2GUI::saveSettings()
{
    KPar2GUISettings::self()->setAutoCheck( kcfg_AutoCheck->isChecked() );
    KPar2GUISettings::self()->setAutoRepair( kcfg_AutoRepair->isChecked() );
    KPar2GUISettings::self()->writeConfig();
}

void KPar2GUI::readConfig()
{
    kcfg_AutoCheck->setChecked( KPar2GUISettings::self()->autoCheck() );
    kcfg_AutoRepair->setChecked( KPar2GUISettings::self()->autoRepair() );
}

bool KPar2GUI::autoCheck()
{
    return kcfg_AutoCheck->isChecked();
}

bool KPar2GUI::autoRepair()
{
    return kcfg_AutoRepair->isChecked();
}
