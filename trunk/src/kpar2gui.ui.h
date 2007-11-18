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

void KPar2GUI::init()
{
    connect( CheckParityButton, SIGNAL( clicked() ), this, SIGNAL( checkParity() ) );
    connect( RepairFilesButton, SIGNAL( clicked() ), this, SIGNAL( repairFiles() ) );
    connect( this, SIGNAL( fileProgress( int ) ), CurrentFileProgress, SLOT( setValue( int ) ) );
    connect( this, SIGNAL( totalFileProgress( int ) ), TotalFileProgress, SLOT( setValue( int ) ) );
}

void KPar2GUI::appendHeaderInfo( ParHeaders *headers )
{
    FileDisplay->append( "There are " + QString::number( headers->recoverable_files ) + " recoverable files and " +  QString::number( headers->other_files ) + " other files." );
    FileDisplay->append( "The block size used was " + QString::number( headers->block_size ) );
    FileDisplay->append( "There are a total of " + QString::number( headers->data_blocks ) + " data blocks." );
    FileDisplay->append( "The total size of the data files is " + QString::number( headers->data_size ) + " bytes" );
    FileDisplay->append("\n");
}

void KPar2GUI::fileLoaded( const QString& filename )
{
    FileDisplay->append( filename );
}

void KPar2GUI::enableRepair( bool enable )
{
    RepairFilesButton->setEnabled( enable );
}

void KPar2GUI::enableCheckParity( bool enable )
{
    CheckParityButton->setEnabled( enable );
}

void KPar2GUI::done( const QString& info )
{
    FileDisplay->append( info );
}

void KPar2GUI::clearFileDisplay()
{
    FileDisplay->clear();
}
