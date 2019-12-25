#ifndef VIRTUALJOYSTICKKEYNAVIGATION_H
#define VIRTUALJOYSTICKKEYNAVIGATION_H

#include "keynavigation.h"

class VirtualJoystickKeyNavigation : public KeyNavigation
{
    Q_OBJECT
    Q_PROPERTY(Qt::Key up READ up WRITE setUp NOTIFY upChanged)
    Q_PROPERTY(Qt::Key down READ down WRITE setDown NOTIFY downChanged)
    Q_PROPERTY(Qt::Key left READ left WRITE setLeft NOTIFY leftChanged)
    Q_PROPERTY(Qt::Key right READ right WRITE setRight NOTIFY rightChanged)
public:
    explicit VirtualJoystickKeyNavigation(QObject *parent = nullptr);

    Qt::Key up() const;
    void setUp(Qt::Key up);

    Qt::Key down() const;
    void setDown(Qt::Key down);

    Qt::Key left() const;
    void setLeft(Qt::Key left);

    Qt::Key right() const;
    void setRight(Qt::Key right);
signals:
    void upChanged();
    void downChanged();
    void leftChanged();
    void rightChanged();
private:
    Qt::Key m_up;
    Qt::Key m_down;
    Qt::Key m_left;
    Qt::Key m_right;
};

#endif // VIRTUALJOYSTICKKEYNAVIGATION_H
