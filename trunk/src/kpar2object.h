/***************************************************************************
 *   Copyright (C) 2007 by Lawrence Lee   *
 *   valheru@facticius.net   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 3 of the License, or     *
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

#include <qobject.h>

class KPar2GUI;
class ParHeaders;
class Par2Repairer;
class CommandLine;

class KPar2Object : public QObject
{
    Q_OBJECT

    public:
        KPar2Object( KPar2GUI *gui );
        ~KPar2Object();

    public slots:
        void loadPAR2Files( const QString& par2file );
        void checkParity();
        void repairFiles();

    signals:
        void headerInfo( ParHeaders *headers );
        void fileLoaded( const QString& filename );
        void fileProgress( int progress );
        void totalProgress( int progress );
        void enableCheckParity( bool enabled );
        void enableRepair( bool enabled );
        void done( const QString& info );

    private:
        int total_files;
        int processed_files;
        QString par2file;
        CommandLine *cmdline;
        Par2Repairer *par2repairer;
        void signal_filename( std::string str );
        void signal_progress( double value );
        void signal_headers( ParHeaders* headers );
        void signal_done( std::string filename, int blocks_available, int blocks_total );
};

#endif // _KPAR2OBJECT_H_