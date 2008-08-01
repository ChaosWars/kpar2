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

#include <KDE/KParts/ReadOnlyPart>

class QWidget;
class QPainter;
class KUrl;
class KAction;
class KPar2Gui;
class KAboutData;
class KPar2Thread;
class KPar2Settings;
class Settings;

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
         * 
         * @param parentWidget 
         * @param parent 
         * @param args 
         */
        KPar2Part( QWidget* parentWidget,
                   QObject* parent,
                   const QStringList &args = QStringList() );
        virtual ~KPar2Part();
        static KAboutData* createAboutData();

    public Q_SLOTS:
        void loadSettings();

    protected:
        /**
         * This must be implemented by each part
         */
        virtual bool openFile();
        virtual bool openUrl( const KUrl & url );

    protected Q_SLOTS:
        void fileOpen();
        void optionsConfigure();

//     Q_SIGNALS:
//         void loadPAR2Files( const QString& file );

    private:
        QWidget *m_widget;
//         KPar2Thread *kpar2thread;
        KPar2Gui *m_gui;
        bool autoCheck, autoRepair;
};

#endif // _KPAR2PART_H_
