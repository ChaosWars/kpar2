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

#include <libpar2/parheaders.h>
#include <qpixmap.h>
#include <kstatusbar.h>
#include <kparts/mainwindow.h>
#include <kiconloader.h>
#include "kpar2customevents.h"

static QPixmap ok( KGlobal::iconLoader()->loadIcon( "button_ok.png", KIcon::Toolbar ) );
static QPixmap damaged( KGlobal::iconLoader()->loadIcon( "button_cancel.png", KIcon::Toolbar ) );
static QPixmap missing( KGlobal::iconLoader()->loadIcon( "messagebox_critical.png", KIcon::Toolbar ) );
static QPixmap info( KGlobal::iconLoader()->loadIcon( "info.png", KIcon::Toolbar ) );

void KPar2GUI::init()
{
    FileDisplay->setSortColumn( -1 );
    connect( CheckParityButton, SIGNAL( clicked() ), this, SIGNAL( checkParity() ) );
    connect( RepairFilesButton, SIGNAL( clicked() ), this, SIGNAL( repairFiles() ) );
    connect( this, SIGNAL( fileProgress( int ) ), CurrentFileProgress, SLOT( setValue( int ) ) );
    connect( this, SIGNAL( totalFileProgress( int ) ), TotalFileProgress, SLOT( setValue( int ) ) );
}

void KPar2GUI::customEvent( QCustomEvent *e )
{
        if( e->type() ==  QEvent::User ){
            HeaderInfo *he = ( HeaderInfo* )e;
            QListViewItem *i = new QListViewItem( FileDisplay, FileDisplay->lastItem() );
            i->setMultiLinesEnabled( true );

            i->setText( 0, "There are " + QString::number( he->headers()->recoverable_files ) + \
                            " recoverable files and " +  QString::number( he->headers()->other_files ) + \
                            " other files.\n" + "The block size used was " + \
                            QString::number( he->headers()->block_size ) + "\nThere are a total of " + \
                            QString::number( he->headers()->data_blocks ) + " data blocks.\n" + \
                            "The total size of the data files is " + \
                            QString::number( abs( he->headers()->data_size ) ) + " bytes." );

            i->setPixmap( 1, info );
            FileDisplay->ensureItemVisible( i );
        }else if( e->type() ==  QEvent::User + 1 ){
            FileLoaded *fe = ( FileLoaded* )e;
            FileDisplay->ensureItemVisible( new QListViewItem( FileDisplay, FileDisplay->lastItem(), fe->file() ) );
        }else if( e->type() ==  QEvent::User + 2 ){
            FileProgress *fe = ( FileProgress* )e;

            if( fe->progress() < 0 ){
                CurrentFileProgress->setValue( 0 );
                CurrentFileProgress->setEnabled( false );
            }else{

                if( !CurrentFileProgress->isEnabled() )
                    CurrentFileProgress->setEnabled( true );

                CurrentFileProgress->setValue( fe->progress() );
            }
        }else if( e->type() ==  QEvent::User + 3 ){
            TotalProgress *fe = ( TotalProgress* )e;

            if( fe->progress() < 0 ){
                TotalFileProgress->setValue( 0 );
                TotalFileProgress->setEnabled( false );
            }else{

                if( !TotalFileProgress->isEnabled() )
                    TotalFileProgress->setEnabled( true );

                TotalFileProgress->setValue( fe->progress() );

            }

        }else if( e->type() ==  QEvent::User + 4 ){
            EnableCheckParity *ee = ( EnableCheckParity* )e;
            CheckParityButton->setEnabled( ee->enable() );
        }else if( e->type() ==  QEvent::User + 5 ){
            EnableRepair *ee = ( EnableRepair* )e;
            RepairFilesButton->setEnabled( ee->enable() );
        }else if( e->type() ==  QEvent::User + 6 ){
            Done *de = ( Done* )e;

            if( de->info() == "Found" ){
                FileDisplay->lastItem()->setPixmap( 1, ok );
            }else if( de->info() == "Damaged" ){
                FileDisplay->lastItem()->setPixmap( 1, damaged );
            }else{ //Missing
                FileDisplay->ensureItemVisible( new QListViewItem( FileDisplay, FileDisplay->lastItem(), de->info() ) );
                FileDisplay->lastItem()->setPixmap( 1, missing );
            }

        }else if( e->type() ==  QEvent::User + 7 ){
            Finished *fe = ( Finished* )e;
            FileDisplay->ensureItemVisible( new QListViewItem( FileDisplay, FileDisplay->lastItem(), fe->info() ) );
        }else if( e->type() ==  QEvent::User + 8 ){
            StatusMessage *m = ( StatusMessage* )e;
            static_cast< KParts::MainWindow* >( parent() )->statusBar()->message( m->message() );
        }
}

KListView* KPar2GUI::gui()
{
	return FileDisplay;
}
