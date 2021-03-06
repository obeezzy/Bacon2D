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

#ifndef VIEWPORT_H
#define VIEWPORT_H

#include "entity.h"

#include <QPropertyAnimation>
#include <QEasingCurve>
#include <QParallelAnimationGroup>
#include <QQuickItem>
#include <QLoggingCategory>
#include <QDebug>

class Entity;
class QMargins;

class ViewportBounds : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qreal minimum READ minimum NOTIFY minimumChanged)
    Q_PROPERTY(qreal maximum READ maximum NOTIFY maximumChanged)
public:
    explicit ViewportBounds(QObject *parent = nullptr);

    qreal minimum() const;
    void setMinimum(qreal minimum);

    qreal maximum() const;
    void setMaximum(qreal maximum);

    friend QDebug operator<<(QDebug debug, const ViewportBounds &viewportBounds)
    {
        debug.nospace() << "ViewportBounds("
                        << "min=" << viewportBounds.minimum()
                        << ", max=" << viewportBounds.maximum()
                        << ")";

        return debug.space();
    }
signals:
    void minimumChanged();
    void maximumChanged();
private:
    qreal m_minimum;
    qreal m_maximum;
};

class Viewport : public QQuickItem
{
    Q_OBJECT

    Q_PROPERTY(float xOffset READ xOffset WRITE setXOffset NOTIFY xOffsetChanged)
    Q_PROPERTY(float yOffset READ yOffset WRITE setYOffset NOTIFY yOffsetChanged)
    Q_PROPERTY(float contentWidth READ contentWidth WRITE setContentWidth NOTIFY contentWidthChanged)
    Q_PROPERTY(float contentHeight READ contentHeight WRITE setContentHeight NOTIFY contentHeightChanged)
    Q_PROPERTY(int animationDuration READ animationDuration WRITE setAnimationDuration NOTIFY animationDurationChanged)
    Q_PROPERTY(bool atXBeginning READ atXBeginning NOTIFY atXBeginningChanged)
    Q_PROPERTY(bool atXEnd READ atXEnd NOTIFY atXEndChanged)
    Q_PROPERTY(bool atYBeginning READ atYBeginning NOTIFY atYBeginningChanged)
    Q_PROPERTY(bool atYEnd READ atYEnd NOTIFY atYEndChanged)
    Q_PROPERTY(ViewportBounds *xBounds READ xBounds NOTIFY xBoundsChanged)
    Q_PROPERTY(ViewportBounds *yBounds READ yBounds NOTIFY yBoundsChanged)
    Q_PROPERTY(Game* game READ game NOTIFY gameChanged)
public:
    explicit Viewport(QQuickItem *parent = nullptr);

    bool atXBeginning() const;
    bool atXEnd() const;
    bool atYBeginning() const;
    bool atYEnd() const;

    float xOffset();
    void setXOffset(float xOffset);

    float yOffset();
    void setYOffset(float yOffset);

    float contentWidth() const;
    void setContentWidth(const float &contentWidth);

    float contentHeight() const;
    void setContentHeight(const float &contentHeight);

    int animationDuration() const;
    void setAnimationDuration(const int &animationDuration);

    void updateMaxOffsets();

    void setScene(Scene *scene);

    ViewportBounds *xBounds() const;
    ViewportBounds *yBounds() const;

    bool containsEntity(Entity *entity, const QMargins &margins = QMargins());

    Game *game() const;
    void componentComplete() override;

    Q_INVOKABLE void hScroll(float step);
    Q_INVOKABLE void vScroll(float step);
signals:
    void atXBeginningChanged();
    void atXEndChanged();
    void atYBeginningChanged();
    void atYEndChanged();

    void xOffsetChanged();
    void yOffsetChanged();
    void contentWidthChanged();
    void contentHeightChanged();
    void animationDurationChanged();

    void xBoundsChanged();
    void yBoundsChanged();
    void gameChanged();
private:
    void setAtXBeginning(bool atXBeginning);
    void setAtXEnd(bool atXEnd);
    void setAtYBeginning(bool atYBeginning);
    void setAtYEnd(bool atYEnd);

    void onWindowChanged();
    void adjustToOrientationChange();
    void calculateBounds();
    void calculateXLimit();
    void calculateYLimit();
private:
    QEasingCurve m_animationEasingCurve; // TODO expose property?
    bool m_atXBeginning;
    bool m_atXEnd;
    bool m_atYBeginning;
    bool m_atYEnd;
    float m_xOffset;
    float m_yOffset;
    float m_contentWidth;
    float m_contentHeight;
    float m_maxXOffset;
    float m_maxYOffset;
    Scene *m_scene;
    ViewportBounds *m_xBounds;
    ViewportBounds *m_yBounds;

    QParallelAnimationGroup *m_xGroupAnimation;
    QParallelAnimationGroup *m_yGroupAnimation;
    int m_animationDuration;
};

Q_DECLARE_LOGGING_CATEGORY(lcviewport);

#endif // VIEWPORT_H
