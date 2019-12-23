#include "keyeventforwarder.h"
#include <QCoreApplication>
#include <QQmlEngine>
#include <QQmlApplicationEngine>
#include <QKeyEvent>
#include <QDebug>

KeyEventForwarder::KeyEventForwarder(QObject *parent) :
    QObject(parent)
{
}

KeyEventForwarder::~KeyEventForwarder()
{
    releaseAllKeys();
}

void KeyEventForwarder::pressKey(Qt::Key key)
{
    auto engine = qobject_cast<QQmlApplicationEngine *>(qmlEngine(this));
    if (engine) {
        QCoreApplication::postEvent(engine->rootObjects().first(),
                                    new QKeyEvent(QEvent::KeyPress, key, Qt::NoModifier));
        m_pressedKeys.insert(key, QEvent::KeyPress);
    }
}

void KeyEventForwarder::releaseKey(Qt::Key key)
{
    auto engine = qobject_cast<QQmlApplicationEngine *>(qmlEngine(this));
    if (engine && m_pressedKeys.value(key) == QEvent::KeyPress) {
        QCoreApplication::postEvent(engine->rootObjects().first(),
                                    new QKeyEvent(QEvent::KeyRelease, key, Qt::NoModifier));
        m_pressedKeys.insert(key, QEvent::KeyRelease);
    }
}

void KeyEventForwarder::releaseAllKeys()
{
    if (m_pressedKeys.isEmpty())
        return;

    QMapIterator<Qt::Key, QEvent::Type> i(m_pressedKeys);
    while (i.hasNext()) {
        i.next();
        if (i.value() == QEvent::KeyPress)
            releaseKey(i.key());
    }
}

bool KeyEventForwarder::isPressed(Qt::Key key) const
{
    return m_pressedKeys.value(key) == QEvent::KeyPress;
}

bool KeyEventForwarder::isReleased(Qt::Key key) const
{
    return m_pressedKeys.value(key) == QEvent::KeyRelease;
}
