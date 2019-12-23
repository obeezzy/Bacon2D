#include "keynavigation.h"

KeyNavigation::KeyNavigation(QObject *parent) :
    QObject(parent),
    m_active(true)
{

}

bool KeyNavigation::active() const
{
    return m_active;
}

void KeyNavigation::setActive(bool active)
{
    if (m_active == active)
        return;

    m_active == active;
    emit activeChanged();
}
