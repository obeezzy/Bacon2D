#include "keyinput.h"
#include "keyaction.h"

#include <QKeyEvent>
#include <QDebug>

Q_LOGGING_CATEGORY(keyInput, "bacon2d.core.keyinput", QtWarningMsg);

KeyInput::KeyInput(QQuickItem *parent) :
    QQuickItem(parent)
{
}

QQmlListProperty<KeyAction> KeyInput::keyActions()
{
    return QQmlListProperty<KeyAction>(this, nullptr,
                                       &KeyInput::append_key_action,
                                       &KeyInput::count_key_action,
                                       &KeyInput::at_key_action,
                                       nullptr);
}

bool KeyInput::isPressed(const QString &action)
{
    return m_pressedActions.value(action) == EventType::KeyPress;
}

bool KeyInput::isReleased(const QString &action)
{
    return m_pressedActions.value(action) == EventType::KeyRelease;
}

void KeyInput::keyPressEvent(QKeyEvent *event)
{
    for (auto keyAction : m_keyActions) {
        if (keyAction->key() == event->key() && !event->isAutoRepeat()) {
            m_pressedActions.insert(keyAction->action(), EventType::KeyPress);
            emit actionInvoked(keyAction->action(), EventType::KeyPress);
            return;
        }
    }

    event->ignore();
}

void KeyInput::keyReleaseEvent(QKeyEvent *event)
{
    for (auto keyAction : m_keyActions) {
        if (keyAction->key() == event->key() && !event->isAutoRepeat()) {
            m_pressedActions.insert(keyAction->action(), EventType::KeyRelease);
            emit actionInvoked(keyAction->action(), EventType::KeyRelease);
            return;
        }
    }

    event->ignore();
}

void KeyInput::append_key_action(QQmlListProperty<KeyAction> *list, KeyAction *keyAction)
{
    KeyInput *keyInput = static_cast<KeyInput *>(list->object);
    keyAction->setParent(keyInput);
    keyInput->m_keyActions.append(keyAction);
    keyInput->m_pressedActions.insert(keyAction->action(), EventType::KeyRelease);
}

int KeyInput::count_key_action(QQmlListProperty<KeyAction> *list)
{
    KeyInput *keyInput = static_cast<KeyInput *>(list->object);
    return keyInput->m_keyActions.length();
}

KeyAction *KeyInput::at_key_action(QQmlListProperty<KeyAction> *list, int index)
{
    KeyInput *keyInput = static_cast<KeyInput *>(list->object);
    return keyInput->m_keyActions.at(index);
}
