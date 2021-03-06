/**
 * The MIT License (MIT)
 *
 * Copyright (C) 2017 Bacon2D Project
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#ifndef TMXIMAGELAYER_H
#define TMXIMAGELAYER_H

#include "tmxlayer.h"
#include <QPixmap>
#include <QUrl>

#include <libtiled/imagelayer.h>

class TMXImageLayer : public TMXLayer
{
    Q_OBJECT

public:
    explicit TMXImageLayer(Tiled::ImageLayer *imageLayer, QObject *parent = nullptr)
        : TMXLayer(imageLayer, parent), m_imageLayer(imageLayer) {}

    explicit TMXImageLayer(const TMXLayer &layer, QObject *parent = nullptr)
        : TMXLayer(layer.layer()->asImageLayer(), parent), m_imageLayer(layer.layer()->asImageLayer()) {}

    Tiled::ImageLayer *tiledImageLayer() const { return m_imageLayer; }
    QPixmap image() const { return m_imageLayer->image(); }
    QUrl imageUrl() const { return m_imageLayer->imageSource(); }
    QColor transparentColor() const { return m_imageLayer->transparentColor(); }
private:
    Tiled::ImageLayer *m_imageLayer;
};

#endif // TMXIMAGELAYER_H
