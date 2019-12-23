#include "virtualjoystickkeynavigation.h"

VirtualJoystickKeyNavigation::VirtualJoystickKeyNavigation(QObject *parent) :
    KeyNavigation(parent),
    m_upKey(Qt::Key_Up),
    m_downKey(Qt::Key_Down),
    m_leftKey(Qt::Key_Left),
    m_rightKey(Qt::Key_Right)
{

}

Qt::Key VirtualJoystickKeyNavigation::upKey() const
{
    return m_upKey;
}

void VirtualJoystickKeyNavigation::setUpKey(Qt::Key upKey)
{
    if (m_upKey == upKey)
        return;

    m_upKey = upKey;
    emit upKeyChanged();
}

Qt::Key VirtualJoystickKeyNavigation::downKey() const
{
    return m_downKey;
}

void VirtualJoystickKeyNavigation::setDownKey(Qt::Key downKey)
{
    if (m_downKey == downKey)
        return;

    m_downKey = downKey;
    emit downKeyChanged();
}

Qt::Key VirtualJoystickKeyNavigation::leftKey() const
{
    return m_leftKey;
}

void VirtualJoystickKeyNavigation::setLeftKey(Qt::Key leftKey)
{
    if (m_leftKey == leftKey)
        return;

    m_leftKey = leftKey;
    emit leftKeyChanged();
}

Qt::Key VirtualJoystickKeyNavigation::rightKey() const
{
    return m_rightKey;
}

void VirtualJoystickKeyNavigation::setRightKey(Qt::Key rightKey)
{
    if (m_rightKey == rightKey)
        return;

    m_rightKey = rightKey;
    emit rightKeyChanged();
}
