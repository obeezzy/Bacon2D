#ifndef KEYEVENTFORWARDER_H
#define KEYEVENTFORWARDER_H

#include <QObject>
#include <QKeyEvent>

class KeyEventForwarder : public QObject
{
    Q_OBJECT
public:
    explicit KeyEventForwarder(QObject *parent = nullptr);
    ~KeyEventForwarder();

    Q_INVOKABLE void pressKey(Qt::Key key);
    Q_INVOKABLE void releaseKey(Qt::Key key);
    Q_INVOKABLE void releaseAllKeys();
    Q_INVOKABLE bool isPressed(Qt::Key key) const;
    Q_INVOKABLE bool isReleased(Qt::Key key) const;
private:
    QMap<Qt::Key, QEvent::Type> m_pressedKeys;
};

#endif // KEYEVENTFORWARDER_H
