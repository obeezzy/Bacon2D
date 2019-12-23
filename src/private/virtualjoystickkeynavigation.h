#ifndef VIRTUALJOYSTICKKEYNAVIGATION_H
#define VIRTUALJOYSTICKKEYNAVIGATION_H

#include "keynavigation.h"

class VirtualJoystickKeyNavigation : public KeyNavigation
{
    Q_OBJECT
    Q_PROPERTY(Qt::Key upKey READ upKey WRITE setUpKey NOTIFY upKeyChanged)
    Q_PROPERTY(Qt::Key downKey READ downKey WRITE setDownKey NOTIFY downKeyChanged)
    Q_PROPERTY(Qt::Key leftKey READ leftKey WRITE setLeftKey NOTIFY leftKeyChanged)
    Q_PROPERTY(Qt::Key rightKey READ rightKey WRITE setRightKey NOTIFY rightKeyChanged)
public:
    explicit VirtualJoystickKeyNavigation(QObject *parent = nullptr);

    Qt::Key upKey() const;
    void setUpKey(Qt::Key upKey);

    Qt::Key downKey() const;
    void setDownKey(Qt::Key downKey);

    Qt::Key leftKey() const;
    void setLeftKey(Qt::Key leftKey);

    Qt::Key rightKey() const;
    void setRightKey(Qt::Key rightKey);
signals:
    void upKeyChanged();
    void downKeyChanged();
    void leftKeyChanged();
    void rightKeyChanged();
private:
    Qt::Key m_upKey;
    Qt::Key m_downKey;
    Qt::Key m_leftKey;
    Qt::Key m_rightKey;
};

#endif // VIRTUALJOYSTICKKEYNAVIGATION_H
