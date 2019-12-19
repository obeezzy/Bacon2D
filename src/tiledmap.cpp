#include "tiledmap.h"
#include "tmxmap.h"

TiledMap::TiledMap(QObject *parent) :
    QObject(parent),
    m_tmxMap(nullptr),
    m_background(nullptr),
    m_backgroundColor(Qt::transparent),
    m_backgroundVisible(false)
{

}

/*!
 * \qmlproperty Item TiledScene::background
 * \brief This property allows you to override the TMX image layer set in the TMX file. Note that the
 * background set takes the dimensions of the scene automatically.
 * \return
 */

QQuickItem *TiledMap::background() const
{
    return m_background;
}

void TiledMap::setBackground(QQuickItem *background)
{
    if (m_background == background)
        return;

    m_background = background;
    emit backgroundChanged();
}

QColor TiledMap::backgroundColor() const
{
    return m_backgroundColor;
}

void TiledMap::setBackgroundColor(const QColor &backgroundColor)
{
    if (m_backgroundColor == backgroundColor)
        return;

    m_backgroundColor = backgroundColor;
    emit backgroundColorChanged();
}

bool TiledMap::backgroundVisible() const
{
    return m_backgroundVisible;
}

void TiledMap::setBackgroundVisible(bool backgroundVisible)
{
    if (m_backgroundVisible == backgroundVisible)
        return;

    m_backgroundVisible = backgroundVisible;
    emit backgroundVisibleChanged();
}

QVariant TiledMap::getProperty(const QString &name, const QVariant &defaultValue) const
{
    if (m_tmxMap)
        return m_tmxMap->properties().value(name, defaultValue);

    return defaultValue;
}

void TiledMap::setTmxMap(TMXMap *tmxMap)
{
    m_tmxMap = tmxMap;
    if (m_tmxMap)
        setBackgroundColor(m_tmxMap->backgroundColor());
}
