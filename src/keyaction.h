#ifndef KEYACTION_H
#define KEYACTION_H

#include <QObject>

class KeyAction : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString action READ action WRITE setAction NOTIFY actionChanged)
    Q_PROPERTY(Qt::Key key READ key WRITE setKey NOTIFY keyChanged)
public:
    explicit KeyAction(QObject *parent = nullptr);

    QString action() const;
    void setAction(const QString &action);

    Qt::Key key() const;
    void setKey(Qt::Key key);
signals:
    void actionChanged();
    void keyChanged();
private:
    QString m_action;
    Qt::Key m_key;
};

#endif // KEYACTION_H
