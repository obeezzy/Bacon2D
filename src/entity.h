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

#ifndef ENTITY_H
#define ENTITY_H

#include <QtGlobal>
#include <QTime>
#include <QQuickItem>
#include <QLoggingCategory>

class Game;
class Scene;
class Entity;
class Viewport;
class Behavior;

class ViewportTracker : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool enabled READ isEnabled WRITE setEnabled NOTIFY enabledChanged)
    Q_PROPERTY(int leftMargin READ leftMargin WRITE setLeftMargin NOTIFY leftMarginChanged)
    Q_PROPERTY(int rightMargin READ rightMargin WRITE setRightMargin NOTIFY rightMarginChanged)
    Q_PROPERTY(int topMargin READ topMargin WRITE setTopMargin NOTIFY topMarginChanged)
    Q_PROPERTY(int bottomMargin READ bottomMargin WRITE setBottomMargin NOTIFY bottomMarginChanged)
    Q_PROPERTY(bool withinViewport READ withinViewport NOTIFY withinViewportChanged)
public:
    explicit ViewportTracker(QObject *parent = nullptr);

    bool isEnabled() const;
    void setEnabled(bool enabled);

    int leftMargin() const;
    void setLeftMargin(int leftMargin);

    int rightMargin() const;
    void setRightMargin(int rightMargin);

    int topMargin() const;
    void setTopMargin(int topMargin);

    int bottomMargin() const;
    void setBottomMargin(int bottomMargin);

    bool withinViewport() const;

    void startTracking();
    void stopTracking();
signals:
    void enabledChanged();
    void viewportEntered();
    void viewportExited();
    void withinViewportChanged();
    void leftMarginChanged();
    void rightMarginChanged();
    void topMarginChanged();
    void bottomMarginChanged();
private:
    void onEnabledChanged();
    void trackPosition();
    void setWithinViewport(bool withinViewport);
private:
    bool m_enabled;
    Scene *m_scene;
    Entity *m_entity;
    Viewport *m_viewport;
    bool m_withinViewport;
    int m_leftMargin;
    int m_rightMargin;
    int m_topMargin;
    int m_bottomMargin;
};

class Entity : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QString entityId READ entityId NOTIFY entityIdChanged)
    Q_PROPERTY(QString entityType READ entityType WRITE setEntityType NOTIFY entityTypeChanged)
    Q_PROPERTY(int updateInterval READ updateInterval WRITE setUpdateInterval NOTIFY updateIntervalChanged)
    Q_PROPERTY(Game *game READ game NOTIFY gameChanged)
    Q_PROPERTY(Scene *scene READ scene NOTIFY sceneChanged)
    Q_PROPERTY(Behavior *behavior READ behavior WRITE setBehavior NOTIFY behaviorChanged)
    Q_PROPERTY(ViewportTracker* viewportTracker READ viewportTracker NOTIFY viewportTrackerChanged)
public:
    explicit Entity(Scene *parent = nullptr);
    virtual ~Entity() = default;

    QString entityId() const;
    void setEntityId(const QString &);

    QString entityType() const;
    void setEntityType(const QString &);

    int updateInterval() const;
    void setUpdateInterval(const int &updateInterval);

    Scene *scene() const;
    void setScene(Scene *scene);

    Game *game() const;

    Behavior *behavior() const;
    void setBehavior(Behavior *behavior);

    ViewportTracker *viewportTracker() const;

    virtual void update(const int &delta);
signals:
    void updateIntervalChanged();
    void behaviorChanged();
    void gameChanged();
    void sceneChanged();
    void entityIdChanged();
    void entityTypeChanged();
    void viewportTrackerChanged();
protected:
    virtual void componentComplete();
    virtual void itemChange(ItemChange change, const ItemChangeData &data);
    void initializeEntities(QQuickItem *parent);
private:
    QString m_entityId;
    QString m_entityType;
    int m_updateInterval;
    QTime m_updateTime;
    Scene *m_scene;
    Behavior *m_behavior;
    ViewportTracker *m_viewportTracker;
};

Q_DECLARE_LOGGING_CATEGORY(entity);

#endif // ENTITY_H
