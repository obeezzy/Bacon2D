#ifndef KEYINPUT_H
#define KEYINPUT_H

#include <QQuickItem>
#include <QQmlListProperty>
#include <QEvent>

class KeyAction;

class KeyInput : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<KeyAction> keyActions READ keyActions)
    Q_CLASSINFO("DefaultProperty", "keyActions")
public:
    enum class EventType {
        KeyPress,
        KeyRelease
    }; Q_ENUM(EventType)

    explicit KeyInput(QQuickItem *parent = nullptr);

    QQmlListProperty<KeyAction> keyActions();
    Q_INVOKABLE bool isPressed(const QString &action);
    Q_INVOKABLE bool isReleased(const QString &action);
protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
signals:
    void actionInvoked(const QString &action, EventType eventType);
private:
    static void append_key_action(QQmlListProperty<KeyAction> *list, KeyAction *keyAction);
    static int count_key_action(QQmlListProperty<KeyAction> *list);
    static KeyAction *at_key_action(QQmlListProperty<KeyAction> *list, int index);
private:
    QList<KeyAction *> m_keyActions;
    QMap<QString, EventType> m_pressedActions;
};

#endif // KEYINPUT_H
