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
#include "kpar2customevents.h"

void KPar2GUI::init()
{
    connect( CheckParityButton, SIGNAL( clicked() ), this, SIGNAL( checkParity() ) );
    connect( RepairFilesButton, SIGNAL( clicked() ), this, SIGNAL( repairFiles() ) );
    connect( this, SIGNAL( fileProgress( int ) ), CurrentFileProgress, SLOT( setValue( int ) ) );
    connect( this, SIGNAL( totalFileProgress( int ) ), TotalFileProgress, SLOT( setValue( int ) ) );
}

void KPar2GUI::customEvent( QCustomEvent *e )
{
        if( e->type() ==  QEvent::User ){
            HeaderInfo *he = ( HeaderInfo* )e;
            FileDisplay->append( "There are " + QString::number( he->headers()->recoverable_files ) + " recoverable files and " +  QString::number( he->headers()->other_files ) + " other files." );
            FileDisplay->append( "The block size used was " + QString::number( he->headers()->block_size ) );
            FileDisplay->append( "There are a total of " + QString::number( he->headers()->data_blocks ) + " data blocks." );
            FileDisplay->append( "The total size of the data files is " + QString::number( he->headers()->data_size ) + " bytes" );
            FileDisplay->append("\n");
        }else if( e->type() ==  QEvent::User + 1 ){
            FileLoaded *fe = ( FileLoaded* )e;
            FileDisplay->append( fe->file() );
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
            FileDisplay->append( de->info() );
        }
}
