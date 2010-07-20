/***************************************************************************
 *   Copyright (C) 2010 by Simon Andreas Eugster (simon.eu@gmail.com)      *
 *   This file is part of kdenlive. See www.kdenlive.org.                  *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#ifndef WAVEFORMGENERATOR_H
#define WAVEFORMGENERATOR_H

#include <QObject>
#include <QImage>
#include <QSize>

class WaveformGenerator : public QObject
{
    Q_OBJECT

public:
    WaveformGenerator();
    ~WaveformGenerator();

    QImage calculateWaveform(const QSize &waveformSize, const QImage &image, const bool &drawAxis, const uint &accelFactor = 1);

signals:
    void signalCalculationFinished(QImage image, const uint &ms);

};

#endif // WAVEFORMGENERATOR_H
