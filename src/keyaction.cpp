#include "keyaction.h"

KeyAction::KeyAction(QObject *parent) : QObject(parent)
{

}

QString KeyAction::action() const
{
    return m_action;
}

void KeyAction::setAction(const QString &action)
{
    if (m_action == action)
        return;

    m_action = action;
    emit actionChanged();
}

Qt::Key KeyAction::key() const
{
    return m_key;
}

void KeyAction::setKey(Qt::Key key)
{
    if (m_key == key)
        return;

    m_key = key;
    emit keyChanged();
}
