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
#include <kiconloader.h>
#include <klocale.h>
#include <kstatusbar.h>
#include <kparts/mainwindow.h>
#include <qpixmap.h>
#include "kpar2customevents.h"

static QPixmap p_info( KGlobal::iconLoader()->loadIcon( "info.png", KIcon::Toolbar ) );
static QPixmap p_ok( KGlobal::iconLoader()->loadIcon( "ok.png", KIcon::Toolbar ) );
static QPixmap p_damaged( KGlobal::iconLoader()->loadIcon( "cancel.png", KIcon::Toolbar ) );
static QPixmap p_error( KGlobal::iconLoader()->loadIcon( "messagebox_critical.png", KIcon::Toolbar ) );
static QPixmap p_warning( KGlobal::iconLoader()->loadIcon( "messagebox_warning.png", KIcon::Toolbar ) );

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

            i->setText( 0, i18n( "There are " + QString::number( he->headers()->recoverable_files ) + \
                                " recoverable files and " +  QString::number( he->headers()->other_files ) + \
                                " other files.\n" + "The block size used was " + \
                                QString::number( he->headers()->block_size ) + "\nThere are a total of " + \
                                QString::number( he->headers()->data_blocks ) + " data blocks.\n" + \
                                "The total size of the data files is " + \
                                QString::number( abs( he->headers()->data_size ) ) + " bytes." ) );

            i->setPixmap( 1, p_info );
            FileDisplay->ensureItemVisible( i );
        }else if( e->type() ==  QEvent::User + 1 ){
            FileLoaded *fe = ( FileLoaded* )e;
            QListViewItem *i = new QListViewItem( FileDisplay, FileDisplay->lastItem(), fe->file() );

            if( fe->operation() == load ){
                i->setPixmap( 1, p_info );
            }

            FileDisplay->ensureItemVisible( i );
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

            if( de->info() == i18n( "Found" ) ){
                FileDisplay->lastItem()->setPixmap( 1, p_ok );
            }else if( de->info() == i18n( "Damaged" ) ){
                FileDisplay->lastItem()->setPixmap( 1, p_damaged );
            }else{ //Missing
                FileDisplay->ensureItemVisible( new QListViewItem( FileDisplay, FileDisplay->lastItem(), de->info() ) );
                FileDisplay->lastItem()->setPixmap( 1, p_error );
            }

        }else if( e->type() ==  QEvent::User + 7 ){
            Finished *fe = ( Finished* )e;
            QListViewItem *i = new QListViewItem( FileDisplay, FileDisplay->lastItem(), fe->info() );
            i->setMultiLinesEnabled( true );
            FileDisplay->ensureItemVisible( i );
            FinishedStatus s = fe->status();

            switch( s ){
                case info:
                    i->setPixmap( 1, p_info );
                    break;
                case ok:
                    i->setPixmap( 1, p_ok );
                    break;
                case warning:
                    i->setPixmap( 1, p_warning );
                    break;
                case error:
                    i->setPixmap( 1, p_error );
                    break;
                default:
                    break;
            }

        }else if( e->type() ==  QEvent::User + 8 ){
            StatusMessage *m = ( StatusMessage* )e;
            static_cast< KParts::MainWindow* >( parent() )->statusBar()->message( m->message() );
        }
}

KListView* KPar2GUI::gui()
{
	return FileDisplay;
}
