/***************************************************************************
                         kthumb.h  -  description
                            -------------------
   begin                : Fri Nov 22 2002
   copyright            : (C) 2002 by Jason Wood
   email                : jasonwood@blueyonder.co.uk
***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef KTHUMB_H
#define KTHUMB_H

#include <QPixmap>
#include <QFile>
#include <QThread>
#include <QMutex>
#include <QDomElement>

#include <KUrl>

#include <mlt++/Mlt.h>


/**KRender encapsulates the client side of the interface to a renderer.
From Kdenlive's point of view, you treat the KRender object as the
renderer, and simply use it as if it was local. Calls are asyncrhonous -
you send a call out, and then receive the return value through the
relevant signal that get's emitted once the call completes.
  *@author Jason Wood
  */


namespace Mlt
{
class Miracle;
class Consumer;
class Producer;
class Frame;
class Profile;
};

class ClipManager;



class MyThread : public QThread
{
    Q_OBJECT
public:
    virtual void run();
    void init(QObject *parent, KUrl url, QString target, double frame, double frameLength, int frequency, int channels, int arrayWidth);
    bool isWorking();
    bool stop_me;

private:
    QFile f;
    KUrl m_url;
    double m_frame;
    double m_frameLength;
    int m_frequency;
    int m_channels;
    int m_arrayWidth;
    bool m_isWorking;
    QObject *m_parent;

signals:
    void audioThumbProgress(const int);
    void audioThumbOver();
};

class KThumb: public QObject
{
Q_OBJECT public:


    KThumb(ClipManager *clipManager, KUrl url, const QString &id, const QString &hash, QObject * parent = 0, const char *name = 0);
    ~KThumb();
    void setProducer(Mlt::Producer *producer);
    void askForAudioThumbs(const QString &id);
    bool hasProducer() const;
    void clearProducer();
    void updateThumbUrl(const QString &hash);

public slots:
    void extractImage(int frame, int frame2);
    QPixmap extractImage(int frame, int width, int height);
    void updateClipUrl(KUrl url, const QString &hash);
    static QPixmap getImage(KUrl url, int width, int height);
//    static QPixmap getImage(QDomElement xml, int frame, int width, int height);
    /* void getImage(KUrl url, int frame, int width, int height);
     void getThumbs(KUrl url, int startframe, int endframe, int width, int height);*/
    void stopAudioThumbs();
    void removeAudioThumb();
    void getAudioThumbs(int channel, double frame, double frameLength, int arrayWidth);
    static QPixmap getImage(KUrl url, int frame, int width, int height);
    static QPixmap getFrame(Mlt::Producer *producer, int framepos, int width, int height);

private slots:
    void slotAudioThumbProgress(const int progress);
    void slotAudioThumbOver();

private:
    MyThread audioThumbProducer;
    KUrl m_url;
    QString m_thumbFile;
    double m_dar;
    Mlt::Producer *m_producer;
    ClipManager *m_clipManager;
    QString m_id;
    int m_mainFrame;

signals:
    void thumbReady(int, QPixmap);
    void mainThumbReady(const QString &, QPixmap);
    void audioThumbReady(QMap <int, QMap <int, QByteArray> >);
};

#endif
