#include "virtualjoystickkeynavigation.h"

VirtualJoystickKeyNavigation::VirtualJoystickKeyNavigation(QObject *parent) :
    KeyNavigation(parent),
    m_up(Qt::Key_Up),
    m_down(Qt::Key_Down),
    m_left(Qt::Key_Left),
    m_right(Qt::Key_Right)
{

}

Qt::Key VirtualJoystickKeyNavigation::up() const
{
    return m_up;
}

void VirtualJoystickKeyNavigation::setUp(Qt::Key up)
{
    if (m_up == up)
        return;

    m_up = up;
    emit upChanged();
}

Qt::Key VirtualJoystickKeyNavigation::down() const
{
    return m_down;
}

void VirtualJoystickKeyNavigation::setDown(Qt::Key down)
{
    if (m_down == down)
        return;

    m_down = down;
    emit downChanged();
}

Qt::Key VirtualJoystickKeyNavigation::left() const
{
    return m_left;
}

void VirtualJoystickKeyNavigation::setLeft(Qt::Key left)
{
    if (m_left == left)
        return;

    m_left = left;
    emit leftChanged();
}

Qt::Key VirtualJoystickKeyNavigation::right() const
{
    return m_right;
}

void VirtualJoystickKeyNavigation::setRight(Qt::Key right)
{
    if (m_right == right)
        return;

    m_right = right;
    emit rightChanged();
}
