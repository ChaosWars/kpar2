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

#ifndef _KPAR2_CUSTOMEVENTS_H_
#define _KPAR2_CUSTOMEVENTS_H_

#include <qapplication.h>
#include <qevent.h>

class HeaderInfo : public QCustomEvent
{
    public:
        HeaderInfo( ParHeaders *headers ) : QCustomEvent( QEvent::User ), _headers( headers ){}
        ~HeaderInfo(){}
        ParHeaders *headers(){ return _headers; }

    private:
        ParHeaders *_headers;
};

class FileLoaded : public QCustomEvent
{
    public:
        FileLoaded( const QString& filename ) : QCustomEvent( QEvent::User + 1 ), f( filename ){}
        ~FileLoaded(){}
        QString file() const{ return f; }

    private:
        QString f;
};

class FileProgress : public QCustomEvent
{
    public:
        FileProgress( int progress ) : QCustomEvent( QEvent::User + 2 ), p( progress ){}
        ~FileProgress(){}
        int progress() const{ return p; }

    private:
        int p;
};

class TotalProgress : public QCustomEvent
{
    public:
        TotalProgress( int progress ) : QCustomEvent( QEvent::User + 3 ), p( progress){}
        ~TotalProgress(){}
        int progress() const{ return p; }

    private:
        int p;
};

class EnableCheckParity : public QCustomEvent
{
    public:
        EnableCheckParity( bool enabled ) : QCustomEvent( QEvent::User + 4 ), e( enabled ){}
        ~EnableCheckParity(){}
        bool enable() const{ return e; }

    private:
        bool e;
};

class EnableRepair : public QCustomEvent
{
    public:
        EnableRepair( bool enabled ) : QCustomEvent( QEvent::User + 5 ), e( enabled ){}
        ~EnableRepair(){}
        bool enable() const{ return e; }

    private:
        bool e;
};

class Done : public QCustomEvent
{
    public:
        Done( const QString& info ) : QCustomEvent( QEvent::User + 6 ), i( info ){}
        ~Done(){}
        QString info() const{ return i; }

    private:
        QString i;
};

class Finished : public QCustomEvent
{
    public:
        Finished( const QString& info ) : QCustomEvent( QEvent::User + 7 ), i( info ){}
        ~Finished(){}
        QString info() const{ return i; }

    private:
        QString i;
};

#endif // _KPAR2_CUSTOMEVENTS_H_
