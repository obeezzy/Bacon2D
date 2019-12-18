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

#ifndef TMXMAP_H
#define TMXMAP_H

#include "tmximagelayer.h"
#include "tmxobject.h"
#include "tmxobjectlayer.h"
#include "tmxtilelayer.h"
#include "tmxlayer.h"
#include "tmxobjectgroup.h"
#include "tmxtileset.h"

#include <libtiled/map.h>
#include <libtiled/objectgroup.h>

class TMXMap : public TMXObject
{
    Q_OBJECT

public:
    explicit TMXMap(std::unique_ptr<Tiled::Map> tiledMap, QObject *parent = nullptr)
        : TMXObject(tiledMap.get(), parent), m_tiledMap(std::move(tiledMap)) {}

    Tiled::Map *tiledMap() const { return m_tiledMap.get(); }

    int width() const { return m_tiledMap->width(); }
    void setWidth(int width) { m_tiledMap->setWidth(width); }

    int height() const { return m_tiledMap->height(); }
    void setHeight(int height) { m_tiledMap->setHeight(height); }

    int tileWidth() const { return m_tiledMap->tileWidth(); }
    int tileHeight() const { return m_tiledMap->tileHeight(); }
    QSize tileSize() const { return m_tiledMap->tileSize(); }

    QColor backgroundColor() const { return m_tiledMap->backgroundColor(); }

    QList<TMXLayer> layers() const {
        QList<TMXLayer> allLayers;
        for (Tiled::Layer *layer : m_tiledMap->layers())
            allLayers.append(TMXLayer(layer));

        return allLayers;
    }

    QList<TMXObjectGroup> objectGroups() const {
        QList<TMXObjectGroup> allObjectGroups;
        for (auto it = m_tiledMap->objectGroups().begin(); it != m_tiledMap->objectGroups().end();  ++it)
            allObjectGroups.append(TMXObjectGroup(it->asObjectGroup()));

        return allObjectGroups;
    }

    QList<TMXTileLayer> tileLayers() const {
        QList<TMXTileLayer> allTileLayers;
        for (auto it = m_tiledMap->tileLayers().begin(); it != m_tiledMap->tileLayers().end();  ++it)
            allTileLayers.append(TMXTileLayer(it->asTileLayer()));

        return allTileLayers;
    }

    QList<TMXTileset> tilesets() const {
        QList<TMXTileset> allTilesets;
        for (Tiled::SharedTileset tileset : m_tiledMap->tilesets())
            allTilesets.append(TMXTileset(tileset.data()));

        return allTilesets;
    }

private:
    std::unique_ptr<Tiled::Map> m_tiledMap;
    QList<TMXTileset> m_tilesets;
};

#endif // TMXMAP_H
