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

#include "entity.h"
#include "scene.h"
#include "game.h"
#include "behavior.h"
#include "animatedsprite.h"
#include "sprite.h"
#include "box2dbody.h"
#include "entitymanager.h"
#include "viewport.h"

#include <QMargins>

Q_LOGGING_CATEGORY(lcentity, "bacon2d.core.entity", QtWarningMsg);

ViewportTracker::ViewportTracker(QObject *parent)
    : QObject(parent)
    , m_enabled(false)
    , m_scene(nullptr)
    , m_entity(nullptr)
    , m_viewport(nullptr)
    , m_withinViewport(false)
    , m_leftMargin(0)
    , m_rightMargin(0)
    , m_topMargin(0)
    , m_bottomMargin(0)
{
    connect(this, &ViewportTracker::enabledChanged,
            this, &ViewportTracker::onEnabledChanged);
}

bool ViewportTracker::isEnabled() const
{
    return m_enabled;
}

void ViewportTracker::setEnabled(bool enabled)
{
    if (m_enabled == enabled)
        return;

    m_enabled = enabled;
    emit enabledChanged();
}

int ViewportTracker::leftMargin() const
{
    return m_leftMargin;
}

void ViewportTracker::setLeftMargin(int leftMargin)
{
    if (m_leftMargin == leftMargin)
        return;

    m_leftMargin = leftMargin;
    emit leftMarginChanged();
}

int ViewportTracker::rightMargin() const
{
    return m_rightMargin;
}

void ViewportTracker::setRightMargin(int rightMargin)
{
    if (m_rightMargin == rightMargin)
        return;

    m_rightMargin = rightMargin;
    emit rightMarginChanged();
}

int ViewportTracker::topMargin() const
{
    return m_topMargin;
}

void ViewportTracker::setTopMargin(int topMargin)
{
    if (m_topMargin == topMargin)
        return;

    m_topMargin = topMargin;
    emit topMarginChanged();
}

int ViewportTracker::bottomMargin() const
{
    return m_bottomMargin;
}

void ViewportTracker::setBottomMargin(int bottomMargin)
{
    if (m_bottomMargin == bottomMargin)
        return;

    m_bottomMargin = bottomMargin;
    emit bottomMarginChanged();
}

bool ViewportTracker::withinViewport() const
{
    return m_withinViewport;
}

void ViewportTracker::setWithinViewport(bool withinViewport)
{
    if (m_withinViewport == withinViewport)
        return;

    m_withinViewport = withinViewport;

    if (withinViewport)
        emit viewportEntered();
    else
        emit viewportExited();

    emit withinViewportChanged();
}

void ViewportTracker::startTracking()
{
    if (m_entity)
        return;

    if (auto entity = qobject_cast<Entity *>(parent())) {
        if (entity->scene() && entity->scene()->viewport()) {
            m_entity = entity;
            m_viewport = entity->scene()->viewport();

            connect(entity, &Entity::xChanged,
                    this, &ViewportTracker::trackPosition);
            connect(entity, &Entity::yChanged,
                    this, &ViewportTracker::trackPosition);
            connect(entity, &Entity::widthChanged,
                    this, &ViewportTracker::trackPosition);
            connect(entity, &Entity::heightChanged,
                    this, &ViewportTracker::trackPosition);

            connect(entity->scene()->viewport(), &Viewport::xChanged,
                    this, &ViewportTracker::trackPosition);
            connect(entity->scene()->viewport(), &Viewport::yChanged,
                    this, &ViewportTracker::trackPosition);
            connect(entity->scene()->viewport(), &Viewport::widthChanged,
                    this, &ViewportTracker::trackPosition);
            connect(entity->scene()->viewport(), &Viewport::heightChanged,
                    this, &ViewportTracker::trackPosition);

            blockSignals(true);
            trackPosition();
            blockSignals(false);
        }
    }
}

void ViewportTracker::stopTracking()
{
    if (m_entity && m_viewport) {
        if (m_entity->scene() && m_entity->scene()->viewport()) {
            disconnect(m_entity, &Entity::xChanged,
                       this, &ViewportTracker::trackPosition);
            disconnect(m_entity, &Entity::yChanged,
                       this, &ViewportTracker::trackPosition);
            disconnect(m_entity, &Entity::widthChanged,
                       this, &ViewportTracker::trackPosition);
            disconnect(m_entity, &Entity::heightChanged,
                       this, &ViewportTracker::trackPosition);

            disconnect(m_entity->scene()->viewport(), &Viewport::xChanged,
                       this, &ViewportTracker::trackPosition);
            disconnect(m_entity->scene()->viewport(), &Viewport::yChanged,
                       this, &ViewportTracker::trackPosition);
            disconnect(m_entity->scene()->viewport(), &Viewport::widthChanged,
                       this, &ViewportTracker::trackPosition);
            disconnect(m_entity->scene()->viewport(), &Viewport::heightChanged,
                       this, &ViewportTracker::trackPosition);

            m_entity = nullptr;
            m_viewport = nullptr;
        }
    }
}

void ViewportTracker::onEnabledChanged()
{
    if (m_enabled)
        startTracking();
    else
        stopTracking();
}

void ViewportTracker::trackPosition()
{
    if (!m_entity || !m_viewport || !m_entity->scene())
        return;

    setWithinViewport(m_viewport->containsEntity(m_entity,
                      QMargins(m_leftMargin, m_topMargin, m_rightMargin, m_bottomMargin)));
}

/*!
  \qmltype Entity
  \inqmlmodule Bacon2D
  \inherits Item
  \brief Entity is the base for any component used in your game.

   Each Entity gets updated from the \l Scene on each step of the
   game loop.  The Entity can include a Behavior, which gets run on each
   update.  You can also change the updateInterval so your Behavior
   doesn't get run on each update of the Entity, reducing
   processing time.

   If physics are enabled in the \l Scene, Entities will become part of the
   scene's \l Box2D physics world.  Box2D uses the term "body" for all items
   participating in the physics world.  Your entities are bodies to Box2D, so
   whenever you see the term body used in the documentation, remember in
   Bacon2D it's an Entity.

   You can apply forces, torques, and impulses to entities. An Entity can
   be static, kinematic, or dynamic.

   Bodies (Entities) are the backbone for fixtures (shapes).  Bodies carry
   fixtures and move them around in the world.  Entites are always rigid bodies
   in Box2D.  That means that two fixtures attached to the same rigid body
   never move relative to each other and fixtures attached to the same
   entity don’t collide.

   Fixtures have collision geometry and density. Normally, entities acquire
   their mass properties from the fixtures. However, you can override the
   mass properties after an entity is constructed.
*/
Entity::Entity(Scene *parent)
    : QQuickItem(parent)
    , m_updateInterval(0)
    , m_scene(nullptr)
    , m_behavior(nullptr)
    , m_viewportTracker(new ViewportTracker(this))
{
    connect(this, &Entity::windowChanged, this, &Entity::gameChanged);
}

QString Entity::entityId() const
{
    return m_entityId;
}

void Entity::setEntityId(const QString &entityId)
{
    if (m_entityId == entityId)
        return;

    m_entityId = entityId;
    emit entityIdChanged();
}

QString Entity::entityType() const
{
    return m_entityType;
}

void Entity::setEntityType(const QString &entityType)
{
    if (m_entityType == entityType)
        return;

    m_entityType = entityType;
    emit entityTypeChanged();
}

void Entity::initializeEntities(QQuickItem *parent)
{
    if (!m_scene)
        return;

    for (auto item : parent->childItems()) {
        if (Entity *entity = dynamic_cast<Entity *>(item))
            entity->setScene(m_scene);
        if (AnimatedSprite *animatedSprite = dynamic_cast<AnimatedSprite *>(item))
            animatedSprite->setEntity(this);
        initializeEntities(item);
    }
}

void Entity::componentComplete()
{
    QQuickItem::componentComplete();

    setScene(qobject_cast<Scene *>(parentItem()));
    if (m_scene && m_scene->physics() && m_scene->world()) {
        for (Box2DBody *body : this->findChildren<Box2DBody *>(QString(), Qt::FindDirectChildrenOnly)) {
            body->setTarget(this);
            body->setWorld(m_scene->world());
        }
    }

    if (m_viewportTracker->isEnabled())
        m_viewportTracker->startTracking();

    initializeEntities(this);
}

void Entity::itemChange(ItemChange change, const ItemChangeData &data)
{
    if (!m_scene)
        return;

    if (isComponentComplete() && change == ItemChildAddedChange) {
        QQuickItem *child = data.item;
        if (Entity *entity = dynamic_cast<Entity *>(child))
            entity->setScene(m_scene);
        if (AnimatedSprite *sprite = dynamic_cast<AnimatedSprite *>(child))
            sprite->setEntity(this);

        initializeEntities(child);
    }

    QQuickItem::itemChange(change, data);
}

void Entity::update(const int &delta)
{
    if ((m_updateInterval && m_updateTime.elapsed() >= m_updateInterval)
            || !m_updateInterval) {
        m_updateTime.restart();
        if (m_behavior) {
            m_behavior->setDelta(delta);
            m_behavior->setTarget(this);
            m_behavior->update(delta);
            m_behavior->setTarget(nullptr);
        }
    }

    for (QQuickItem *child : childItems())
        if (Entity *item = dynamic_cast<Entity *>(child))
            item->update(delta);
}

/*!
  \qmlproperty int Entity::updateInterval
  \brief This property holds the interval in milliseconds between
   execution of the Behavior.
*/
int Entity::updateInterval() const
{
    return m_updateInterval;
}

void Entity::setUpdateInterval(const int &updateInterval)
{
    if (m_updateInterval == updateInterval)
        return;

    m_updateInterval = updateInterval;

    emit updateIntervalChanged();

    m_updateTime.restart();
}

Scene *Entity::scene() const
{
    return m_scene;
}

void Entity::setScene(Scene *scene)
{
    if (m_scene == scene)
        return;
    m_scene = scene;
    initializeEntities(this);
    emit sceneChanged();
}

Game *Entity::game() const
{
    return qobject_cast<Game *>(window());
}

/*!
  \qmlproperty Behavior Entity::behavior
  \brief This property holds the \l Behavior to be run on on
   each \l updateInterval
*/
Behavior *Entity::behavior() const
{
    return m_behavior;
}

void Entity::setBehavior(Behavior *behavior)
{
    if (m_behavior == behavior)
        return;

    m_behavior = behavior;

    emit behaviorChanged();
}

ViewportTracker *Entity::viewportTracker() const
{
    return m_viewportTracker;
}
