#ifndef GESTUREPADKEYNAVIGATION_H
#define GESTUREPADKEYNAVIGATION_H

#include "private/keynavigation.h"

class GesturePadKeyNavigation : public KeyNavigation
{
    Q_OBJECT
    Q_PROPERTY(Qt::Key swipeUp READ swipeUp WRITE setSwipeUp NOTIFY swipeUpChanged)
    Q_PROPERTY(Qt::Key swipeDown READ swipeDown WRITE setSwipeDown NOTIFY swipeDownChanged)
    Q_PROPERTY(Qt::Key swipeLeft READ swipeLeft WRITE setSwipeLeft NOTIFY swipeLeftChanged)
    Q_PROPERTY(Qt::Key swipeRight READ swipeRight WRITE setSwipeRight NOTIFY swipeRightChanged)
    Q_PROPERTY(Qt::Key tap READ tap WRITE setTap NOTIFY tapChanged)
    Q_PROPERTY(Qt::Key doubleTap READ doubleTap WRITE setDoubleTap NOTIFY doubleTapChanged)
    Q_PROPERTY(Qt::Key tripleTap READ tripleTap WRITE setTripleTap NOTIFY tripleTapChanged)
    Q_PROPERTY(Qt::Key tapAndHold READ tapAndHold WRITE setTapAndHold NOTIFY tapAndHoldChanged)
public:
    explicit GesturePadKeyNavigation(QObject *parent = nullptr);

    Qt::Key swipeUp() const;
    void setSwipeUp(Qt::Key swipeUp);

    Qt::Key swipeDown() const;
    void setSwipeDown(Qt::Key swipeDown);

    Qt::Key swipeLeft() const;
    void setSwipeLeft(Qt::Key swipeLeft);

    Qt::Key swipeRight() const;
    void setSwipeRight(Qt::Key swipeRight);

    Qt::Key tap() const;
    void setTap(Qt::Key singleTap);

    Qt::Key doubleTap() const;
    void setDoubleTap(Qt::Key doubleTap);

    Qt::Key tripleTap() const;
    void setTripleTap(Qt::Key tripleTap);

    Qt::Key tapAndHold() const;
    void setTapAndHold(Qt::Key tapAndHold);
signals:
    void swipeUpChanged();
    void swipeDownChanged();
    void swipeLeftChanged();
    void swipeRightChanged();
    void tapChanged();
    void doubleTapChanged();
    void tripleTapChanged();
    void tapAndHoldChanged();
private:
    Qt::Key m_swipeUp;
    Qt::Key m_swipeDown;
    Qt::Key m_swipeLeft;
    Qt::Key m_swipeRight;
    Qt::Key m_tap;
    Qt::Key m_doubleTap;
    Qt::Key m_tripleTap;
    Qt::Key m_tapAndHold;
};

#endif // GESTUREPADKEYNAVIGATION_H
