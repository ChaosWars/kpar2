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

#ifndef _KPAR2PART_H_
#define _KPAR2PART_H_

#ifdef COMPILE_FOR_KDE4

#include <KDE/KParts/Part>
#include <KDE/KParts/Factory>

#else

#include <kparts/part.h>
#include <kparts/factory.h>

#endif

class QWidget;
class QPainter;
class KURL;
class KPar2GUI;
class KPar2Thread;

/**
 * This is a "Part".  It that does all the real work in a KPart
 * application.
 *
 * @short Main Part
 * @author Lawrence Lee <valher@facticius.net>
 * @version 0.3
 */
class KPar2Part : public KParts::ReadOnlyPart
{
    Q_OBJECT
    public:
    /**
     * Default constructor
     */
        KPar2Part( QWidget *parentWidget, const char *widgetName,
                      QObject *parent, const char *name );

    /**
         * Destructor
     */
        virtual ~KPar2Part();

    protected:
    /**
     * This must be implemented by each part
     */
        virtual bool openFile();
        virtual bool openURL( const KURL & url );

    protected slots:
        void fileOpen();

    signals:
        void loadPAR2Files( const QString& file );

    private:
        KPar2Thread *kpar2thread;
        KPar2GUI *m_widget;
};

class KInstance;
class KAboutData;

class KPar2PartFactory : public KParts::Factory
{
    Q_OBJECT
    public:
        KPar2PartFactory();
        virtual ~KPar2PartFactory();
        virtual KParts::Part* createPartObject( QWidget *parentWidget, const char *widgetName,
                                                QObject *parent, const char *name,
                                                const char *classname, const QStringList &args );
        static KInstance* instance();

    private:
        static KInstance* s_instance;
        static KAboutData* s_about;
};

#endif // _KPAR2PART_H_
