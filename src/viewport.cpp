/**
 * The MIT License (MIT)
 *
 * Copyright (C) 2012 by INdT
 * Copyright (C) 2014 Bacon2D Project
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
 * @author Rodrigo Goncalves de Oliveira <rodrigo.goncalves@openbossa.org>
 * @author Roger Felipe Zanoni da Silva <roger.zanoni@openbossa.org>
 */

#include "viewport.h"
#include "scene.h"
#include "game.h"

#include <QMargins>

Q_LOGGING_CATEGORY(lcviewport, "bacon2d.core.viewport", QtWarningMsg);

ViewportBounds::ViewportBounds(QObject *parent) :
    QObject(parent),
    m_minimum(0.0),
    m_maximum(0.0)
{

}

qreal ViewportBounds::minimum() const
{
    return m_minimum;
}

void ViewportBounds::setMinimum(qreal minimum)
{
    if (m_minimum == minimum)
        return;

    m_minimum = minimum;
    emit minimumChanged();
}

qreal ViewportBounds::maximum() const
{
    return m_maximum;
}

void ViewportBounds::setMaximum(qreal maximum)
{
    if (m_maximum == maximum)
        return;

    m_maximum = maximum;
    emit maximumChanged();
}

/*!
  \qmltype Viewport
  \inqmlmodule Bacon2D
  \brief The visible portion of a larger \l Scene.

   The Viewport is the visible area of a larger \l Scene and can be scrolled
   horizontally or vertically showing different parts of the larger \l Scene.
*/
Viewport::Viewport(QQuickItem *parent)
    : QQuickItem(parent)
    , m_animationEasingCurve(QEasingCurve::Linear)
    , m_atXBeginning(false)
    , m_atXEnd(false)
    , m_atYBeginning(false)
    , m_atYEnd(false)
    , m_xOffset(0.0f)
    , m_yOffset(0.0f)
    , m_contentWidth(0.0f)
    , m_contentHeight(0.0f)
    , m_maxXOffset(0.0f)
    , m_maxYOffset(0.0f)
    , m_scene(nullptr)
    , m_animationDuration(100)
    , m_xBounds(new ViewportBounds(this))
    , m_yBounds(new ViewportBounds(this))
{
    m_xGroupAnimation = new QParallelAnimationGroup(this);
    m_yGroupAnimation = new QParallelAnimationGroup(this);

    connect(this, &Viewport::xChanged, this, &Viewport::calculateXLimit);
    connect(this, &Viewport::yChanged, this, &Viewport::calculateYLimit);
    connect(this, &Viewport::windowChanged, this, &Viewport::onWindowChanged);
}

bool Viewport::atXBeginning() const
{
    return m_atXBeginning;
}

bool Viewport::atXEnd() const
{
    return m_atXEnd;
}

bool Viewport::atYBeginning() const
{
    return m_atYBeginning;
}

bool Viewport::atYEnd() const
{
    return m_atYEnd;
}

/*!
  \qmlproperty float Viewport::xOffset
  \brief This property holds the horizontal offset of the Viewport's x property from the
   Scene's x property.
*/
float Viewport::xOffset()
{
    return m_xOffset;
}

void Viewport::setXOffset(float xOffset)
{
    xOffset = qBound<float>(0.0f, xOffset, m_maxXOffset);

    // TODO create a heuristic function to calculate the animation duration
    // when m_animationDuration < 0, according to this delta
    // (bigger delta -> bigger animation duration)
    //qreal delta = qAbs(m_xOffset - xOffset);

    if (m_xOffset != xOffset) {
        m_xOffset = xOffset;

        if (m_scene) {
            m_xGroupAnimation->clear();

            QPropertyAnimation *xAnim = new QPropertyAnimation(m_scene, "x");
            xAnim->setDuration(m_animationDuration); // TODO set duration according the offset value
            xAnim->setEasingCurve(m_animationEasingCurve);
            xAnim->setStartValue(m_scene->x());
            xAnim->setEndValue(-m_xOffset);
            m_xGroupAnimation->addAnimation(xAnim);

            /* TODO: Fix this according to current layer scheme
            QPropertyAnimation *xLayerAnimation = new QPropertyAnimation(m_scene->gameLayers(), "xOffset"); // TODO
            xLayerAnimation->setDuration(m_animationDuration); // TODO
            xLayerAnimation->setEasingCurve(m_animationEasingCurve);
            xLayerAnimation->setStartValue(m_scene->gameLayers()->xOffset());
            xLayerAnimation->setEndValue(m_xOffset);
            m_xGroupAnimation->addAnimation(xLayerAnimation);
            */

            m_xGroupAnimation->start();
        }

        emit xOffsetChanged();
    }
}

/*!
  \qmlproperty float Viewport::yOffset
  \brief This property holds the vertical offset of the Viewport's y property from the
   Scene's y property.
*/
float Viewport::yOffset()
{
    return m_yOffset;
}

void Viewport::setYOffset(float yOffset)
{
    yOffset = qBound<float>(0.0f, yOffset, m_maxYOffset);

    if (m_yOffset != yOffset) {
        m_yOffset = yOffset;

        if (m_scene) {
            m_yGroupAnimation->clear();

            QPropertyAnimation *yAnim = new QPropertyAnimation(m_scene, "y");
            yAnim->setDuration(m_animationDuration); // TODO set duration according the offset value
            yAnim->setEasingCurve(m_animationEasingCurve);
            yAnim->setStartValue(m_scene->y());
            yAnim->setEndValue(-m_yOffset);
            m_yGroupAnimation->addAnimation(yAnim);

            /* TODO: Fix this according to current layer scheme
            QPropertyAnimation *yLayerAnimation = new QPropertyAnimation(m_scene->gameLayers(), "yOffset"); // TODO
            yLayerAnimation->setDuration(m_animationDuration); // TODO
            yLayerAnimation->setEasingCurve(m_animationEasingCurve);
            yLayerAnimation->setStartValue(m_scene->gameLayers()->yOffset());
            yLayerAnimation->setEndValue(m_yOffset);
            m_yGroupAnimation->addAnimation(yLayerAnimation);
            */

            m_yGroupAnimation->start();
        }

        emit yOffsetChanged();
    }
}

/*!
  \qmlmethod Viewport::hScroll(float step)
  \brief Scroll the Viewport horizontally by \a step
*/
void Viewport::hScroll(float step)
{
    setXOffset(step);
}

/*!
  \qmlmethod Viewport::vScroll(float step)
  \brief Scroll the Viewport vertically by \a step
*/
void Viewport::vScroll(float step)
{
    setYOffset(step);
}

void Viewport::setAtXBeginning(bool atXBeginning)
{
    if (m_atXBeginning == atXBeginning)
        return;

    m_atXBeginning = atXBeginning;
    emit atXBeginningChanged();
}

void Viewport::setAtXEnd(bool atXEnd)
{
    if (m_atXEnd == atXEnd)
        return;

    m_atXEnd = atXEnd;
    emit atXEndChanged();
}

void Viewport::setAtYBeginning(bool atYBeginning)
{
    if (m_atYBeginning == atYBeginning)
        return;

    m_atYBeginning = atYBeginning;
    emit atYBeginningChanged();
}

void Viewport::setAtYEnd(bool atYEnd)
{
    if (m_atYEnd == atYEnd)
        return;

    m_atYEnd = atYEnd;
    emit atYEndChanged();
}

void Viewport::onWindowChanged()
{
    if (!game())
        return;

    if (!game()->isMobile()) {
        setImplicitWidth(game()->width());
        setImplicitHeight(game()->height());
        calculateBounds();
    }

    emit gameChanged();
}

void Viewport::adjustToOrientationChange()
{
    if (!game() || !game()->isMobile() || !game()->deviceScreen())
        return;

    setImplicitWidth(game()->deviceScreen()->width());
    setImplicitHeight(game()->deviceScreen()->height());
    calculateBounds();
}

void Viewport::calculateBounds()
{
    if (!m_scene || !game() || !game()->deviceScreen())
        return;

    const qreal widthDiff = implicitWidth() - m_scene->width();
    const qreal heightDiff = implicitHeight() - m_scene->height();
    const qreal minX = widthDiff < 0.0 ? widthDiff : 0.0;
    const qreal maxX = widthDiff > 0.0 ? widthDiff : 0.0;
    const qreal minY = heightDiff < 0.0 ? heightDiff : 0.0;
    const qreal maxY = heightDiff > 0.0 ? heightDiff : 0.0;

    m_xBounds->setMinimum(minX);
    m_xBounds->setMaximum(maxX);

    m_yBounds->setMinimum(minY);
    m_yBounds->setMaximum(maxY);

    calculateXLimit();
    calculateYLimit();
}

void Viewport::calculateXLimit()
{
    setAtXBeginning(x() >= m_xBounds->maximum());
    setAtXEnd(x() <= m_xBounds->minimum());
}

void Viewport::calculateYLimit()
{
    setAtYBeginning(y() >= m_yBounds->maximum());
    setAtYEnd(y() <= m_yBounds->minimum());
}

float Viewport::contentWidth() const
{
    return m_contentWidth;
}

void Viewport::setContentWidth(const float &contentWidth)
{
    if (m_contentWidth != contentWidth) {
        m_contentWidth = contentWidth;

        emit contentWidthChanged();
    }
}

float Viewport::contentHeight() const
{
    return m_contentHeight;
}

void Viewport::setContentHeight(const float &contentHeight)
{
    if (m_contentHeight != contentHeight) {
        m_contentHeight = contentHeight;

        emit contentHeightChanged();
    }
}

/*!
  \qmlproperty int Viewport::animationDuration
  \brief Viewport scrolling uses an animation, the animationDuration
   property sets the duration in milliseconds of that animation.  You can
   change this duration for smooth panning of the Viewport.  The default
   is 100ms.
*/
int Viewport::animationDuration() const
{
    return m_animationDuration;
}

void Viewport::setAnimationDuration(const int &animationDuration)
{
    if (m_animationDuration != animationDuration) {
        m_animationDuration = animationDuration;

        emit animationDurationChanged();
    }
}

void Viewport::setScene(Scene *scene)
{
    m_scene = scene;
    scene->setParentItem(this);
    setContentWidth(static_cast<float>(scene->width()));
    setContentHeight(static_cast<float>(scene->height()));
    setVisible(true);
    updateMaxOffsets();
    calculateBounds();
}

ViewportBounds *Viewport::xBounds() const
{
    return m_xBounds;
}

ViewportBounds *Viewport::yBounds() const
{
    return m_yBounds;
}

bool Viewport::containsEntity(Entity *entity, const QMargins &margins)
{
    if (entity) {
        if ((entity->x() + entity->width() > qAbs(x()) + margins.left()
                && entity->y() + entity->height() > qAbs(y()) + margins.top())
                && (entity->x() < qAbs(x()) + width() - margins.right()
                && entity->y() < qAbs(y()) + height()) - margins.bottom())
            return true;
    }

    return false;
}

Game *Viewport::game() const
{
    return qobject_cast<Game *>(window());
}

void Viewport::componentComplete()
{
    QQuickItem::componentComplete();
    adjustToOrientationChange();

    if (game() && game()->isMobile() && game()->deviceScreen()) {
        connect(game()->deviceScreen(), &DeviceScreen::orientationChanged,
                this, &Viewport::adjustToOrientationChange);
    }
}

void Viewport::updateMaxOffsets()
{
    m_maxXOffset = m_contentWidth - static_cast<float>(width());
    m_maxYOffset = m_contentHeight - static_cast<float>(height());
}
