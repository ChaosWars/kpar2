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

#ifndef _KPAR2THREAD_H_
#define _KPAR2THREAD_H_

#include "kpar2object.h"
#include <qobject.h>
#include <qthread.h>

class KPar2GUI;
class KPar2Object;

class KPar2Thread : public QObject, public QThread
{
    Q_OBJECT

    public:
        KPar2Thread( KPar2GUI *gui );
        ~KPar2Thread();

    public slots:
        void loadPAR2Files( const QString& par2file );
        void checkParity();
        void repairFiles();
        void loadSettings();

    protected:
        void run();

    private:
        bool autoCheck;
        bool autoRepair;
        KPar2GUI *m_gui;
        KPar2Object *obj;
        QString par2file;
        Operation operation;
};

#endif // _KPAR2THREAD_H_
