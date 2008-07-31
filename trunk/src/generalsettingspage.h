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
#ifndef GENERAL_SETTINGS_PAGE
#define GENERAL_SETTINGS_PAGE

#include "ui_generalsettingspage.h"

class GeneralSettingsPage : public QWidget, public Ui::GeneralSettingsPage
{
    public:
        GeneralSettingsPage();
        ~GeneralSettingsPage();
        Qt::CheckState autoCheck() const;
        Qt::CheckState autoRepair() const;
        void setAutoCheck( const Qt::CheckState checkState );
        void setAutoRepair( const Qt::CheckState checkState );
};

#endif // GENERAL_SETTINGS_PAGE