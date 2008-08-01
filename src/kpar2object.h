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

#ifndef _KPAR2OBJECT_H_
#define _KPAR2OBJECT_H_

#include <sigc++/trackable.h>
#include <qobject.h>
#include "kpar2customevents.h"

class CommandLine;
class KPar2GUI;
class QCustomEvent;
class ParHeaders;
class Par2Repairer;

class KPar2Object : public QObject, public sigc::trackable
{
    Q_OBJECT

    public:
        KPar2Object( KPar2GUI *gui );
        ~KPar2Object();
        bool loadPAR2Files( const QString& par2file );
        bool checkParity( const QString& par2file );
        bool repairFiles( const QString& par2file );

    public slots:
        void loadSettings();

    protected:
        void customEvent( QCustomEvent *e );

    private:
        KPar2GUI *m_gui;
        Par2Repairer *par2repairer;
        CommandLine *cmdline;
        Operation operation;
        bool autoCheck;
        bool autoRepair;
        int total_files;
        int processed_files;
        int files_damaged;
        int files_missing;
        void signal_filename( std::string str );
        void signal_progress( double value );
        void signal_headers( ParHeaders* headers );
        void signal_done( std::string filename, int blocks_available, int blocks_total );
};

#endif // _KPAR2OBJECT_H_
