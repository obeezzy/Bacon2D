#include "tiledimage.h"
#include "tmximagelayer.h"

TiledImage::TiledImage(QObject *parent) :
    QObject(parent),
    m_visible(true),
    m_opacity(1.0),
    m_verticalOffset(0.0),
    m_horizontalOffset(0.0),
    m_verticalOffsetValid(false),
    m_horizontalOffsetValid(false)
{

}

QString TiledImage::name() const
{
    return m_name;
}

void TiledImage::setName(const QString &name)
{
    if (m_name == name)
        return;

    m_name = name;
    emit nameChanged();
}

bool TiledImage::isVisible() const
{
    return m_visible;
}

void TiledImage::setVisible(bool visible)
{
    if (m_visible == visible)
        return;

    m_visible = visible;
    emit visibleChanged();
}

qreal TiledImage::opacity() const
{
    return m_opacity;
}

void TiledImage::setOpacity(qreal opacity)
{
    if (m_opacity == opacity)
        return;

    m_opacity = opacity;
    emit opacityChanged();
}

QColor TiledImage::transparentColor() const
{
    return m_transparentColor;
}

void TiledImage::setTransparentColor(QColor transparentColor)
{
    if (m_transparentColor == transparentColor)
        return;

    m_transparentColor = transparentColor;
    emit transparentColorChanged();
}

qreal TiledImage::verticalOffset() const
{
    return m_verticalOffset;
}

void TiledImage::setVerticalOffset(qreal verticalOffset)
{
    if (m_verticalOffset == verticalOffset)
        return;

    m_verticalOffsetValid = true;
    m_verticalOffset = verticalOffset;
    emit verticalOffsetChanged();
}

qreal TiledImage::horizontalOffset() const
{
    return m_horizontalOffset;
}

void TiledImage::setHorizontalOffset(qreal horizontalOffset)
{
    if (m_horizontalOffset == horizontalOffset)
        return;

    m_horizontalOffsetValid = true;
    m_horizontalOffset = horizontalOffset;
    emit horizontalOffsetChanged();
}

QUrl TiledImage::imageUrl() const
{
    return m_imageUrl;
}

QPointF TiledImage::offset() const
{
    return QPointF(m_horizontalOffset, m_verticalOffset);
}

void TiledImage::setTmxImageLayer(const TMXImageLayer &tmxImageLayer)
{
    m_imageUrl = tmxImageLayer.imageUrl();
    if (!m_horizontalOffsetValid)
        m_horizontalOffset = tmxImageLayer.offset().x();
    if (!m_verticalOffsetValid)
        m_verticalOffset = tmxImageLayer.offset().y();
    if (!m_transparentColor.isValid())
        m_transparentColor = tmxImageLayer.transparentColor();
}
