#ifndef TILEDMAP_H
#define TILEDMAP_H

#include <QObject>
#include <QColor>
#include <QVariant>

class QQuickItem;
class TMXMap;

class TiledMap : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQuickItem *background READ background WRITE setBackground NOTIFY backgroundChanged)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor NOTIFY backgroundColorChanged)
    Q_PROPERTY(bool backgroundVisible READ backgroundVisible WRITE setBackgroundVisible NOTIFY backgroundVisibleChanged)
public:
    explicit TiledMap(QObject *parent = nullptr);

    QQuickItem *background() const;
    void setBackground(QQuickItem *background);

    QColor backgroundColor() const;
    void setBackgroundColor(const QColor &backgroundColor);

    bool backgroundVisible() const;
    void setBackgroundVisible(bool backgroundVisible);

    Q_INVOKABLE QVariant getProperty(const QString &name, const QVariant &defaultValue = QVariant()) const;
    void setTmxMap(TMXMap *tmxMap);
signals:
    void backgroundChanged();
    void backgroundColorChanged();
    void backgroundVisibleChanged();
private:
    TMXMap *m_tmxMap;
    QQuickItem *m_background;
    QColor m_backgroundColor;
    bool m_backgroundVisible;
};

#endif // TILEDMAP_H
