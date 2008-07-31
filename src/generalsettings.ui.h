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

void GeneralSettings::init()
{
	connect( m_autoCheck, SIGNAL( toggled( bool ) ), this, SIGNAL( autoCheckToggled( bool ) ) );
	connect( m_autoRepair, SIGNAL( toggled( bool ) ), this, SIGNAL( autoRepairToggled( bool ) ) );
}

bool GeneralSettings::autoCheck()
{
	return m_autoCheck->isChecked();
}

bool GeneralSettings::autoRepair()
{
	return m_autoRepair->isChecked();
}

void GeneralSettings::setAutoCheck( bool checked )
{
	m_autoCheck->setChecked( checked );
}

void GeneralSettings::setAutoRepair( bool checked )
{
	m_autoRepair->setChecked( checked );
}
