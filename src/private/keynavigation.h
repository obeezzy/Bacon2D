#ifndef KEYNAVIGATION_H
#define KEYNAVIGATION_H

#include <QObject>

class KeyNavigation : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool active READ active WRITE setActive NOTIFY activeChanged)
public:
    explicit KeyNavigation(QObject *parent = nullptr);
    virtual ~KeyNavigation() = default;

    bool active() const;
    void setActive(bool active);
signals:
    void activeChanged();
private:
    bool m_active;
};

#endif // KEYNAVIGATION_H
