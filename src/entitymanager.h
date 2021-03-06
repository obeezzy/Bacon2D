#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <QObject>
#include <QHash>
#include <QQuickItem>
#include <QLoggingCategory>

class QQmlComponent;
class Entity;
class Scene;

class EntityManager : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(Scene* parentScene READ parentScene WRITE setParentScene NOTIFY parentSceneChanged)
    Q_PROPERTY(int entityCount READ entityCount NOTIFY entityCountChanged)
public:
    explicit EntityManager(QQuickItem *parent = nullptr);

    Q_INVOKABLE Entity *createEntity(const QVariant &);
    Q_INVOKABLE Entity *findEntity(const QString &entityType, const QVariantMap &properties);
    Q_INVOKABLE Entity *getEntity(const QString &entityId);
    Q_INVOKABLE QList<Entity *> getEntities(const QString &entityType = QString());
    Q_INVOKABLE void destroyEntity(const QString &entityId);
    Q_INVOKABLE int getEntityCount(const QString &entityType = QString());
    Q_INVOKABLE void destroyAllEntities(const QString &entityType = QString());

    int entityCount() const;

    Scene *parentScene() const;
    void setParentScene(Scene *);

    void componentComplete();
signals:
    void parentSceneChanged();
    void entityCountChanged();
private:
    Scene *m_parentScene;
};

Q_DECLARE_LOGGING_CATEGORY(entityManager);

#endif // ENTITYMANAGER_H
