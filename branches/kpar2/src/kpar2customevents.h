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

#ifndef _KPAR2_CUSTOMEVENTS_H_
#define _KPAR2_CUSTOMEVENTS_H_

#include <qapplication.h>
#include <qevent.h>

class ParHeaders;

typedef enum _Operation{
    noop = 0,
    load = 1,
    verify = 2,
    repair = 3
} Operation;

typedef enum _FinishedStatus{
    info = 0,
    ok = 1,
    warning = 2,
    error = 3
} FinishedStatus;

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
        FileLoaded( const QString &filename, const Operation &op ) : QCustomEvent( QEvent::User + 1 ), f( filename ), m_op( op ){}
        ~FileLoaded(){}
        QString file() const{ return f; }
        Operation operation() const{ return m_op; }

    private:
        QString f;
        Operation m_op;
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
        Finished( const QString &info, const FinishedStatus &status ) : QCustomEvent( QEvent::User + 7 ), i( info ), s( status ){}
        ~Finished(){}
        QString info() const{ return i; }
        FinishedStatus status() const{ return s; }

    private:
        QString i;
        FinishedStatus s;
};

class StatusMessage : public QCustomEvent
{
    public:
        StatusMessage( const QString& message ) : QCustomEvent( QEvent::User + 8 ), m( message ){}
        ~StatusMessage(){}
        QString message() const{ return m; }

    private:
        QString m;
};

class LoadSettings: public QCustomEvent
{
    public:
        LoadSettings() : QCustomEvent( QEvent::User + 9 ){}
        ~LoadSettings(){}
};

#endif // _KPAR2_CUSTOMEVENTS_H_
