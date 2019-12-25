#include "gesturepadkeynavigation.h"

GesturePadKeyNavigation::GesturePadKeyNavigation(QObject *parent)
    : KeyNavigation(parent)
    , m_swipeUp(Qt::Key_Launch0)
    , m_swipeDown(Qt::Key_Launch1)
    , m_swipeLeft(Qt::Key_Launch2)
    , m_swipeRight(Qt::Key_Launch3)
    , m_tap(Qt::Key_Launch4)
    , m_doubleTap(Qt::Key_Launch5)
    , m_tripleTap(Qt::Key_Launch6)
    , m_tapAndHold(Qt::Key_Launch7)
{

}

Qt::Key GesturePadKeyNavigation::swipeUp() const
{
    return m_swipeUp;
}

void GesturePadKeyNavigation::setSwipeUp(Qt::Key swipeUp)
{
    if (m_swipeUp == swipeUp)
        return;

    m_swipeUp = swipeUp;
    emit swipeUpChanged();
}

Qt::Key GesturePadKeyNavigation::swipeDown() const
{
    return m_swipeDown;
}

void GesturePadKeyNavigation::setSwipeDown(Qt::Key swipeDown)
{
    if (m_swipeDown == swipeDown)
        return;

    m_swipeDown = swipeDown;
    emit swipeDownChanged();
}

Qt::Key GesturePadKeyNavigation::swipeLeft() const
{
    return m_swipeLeft;
}

void GesturePadKeyNavigation::setSwipeLeft(Qt::Key swipeLeft)
{
    if (m_swipeLeft == swipeLeft)
        return;

    m_swipeLeft = swipeLeft;
    emit swipeLeftChanged();
}

Qt::Key GesturePadKeyNavigation::swipeRight() const
{
    return m_swipeRight;
}

void GesturePadKeyNavigation::setSwipeRight(Qt::Key swipeRight)
{
    if (m_swipeRight == swipeRight)
        return;

    m_swipeRight = swipeRight;
    emit swipeRightChanged();
}

Qt::Key GesturePadKeyNavigation::tap() const
{
    return m_tap;
}

void GesturePadKeyNavigation::setTap(Qt::Key tap)
{
    if (m_tap == tap)
        return;

    m_tap = tap;
    emit tapChanged();
}

Qt::Key GesturePadKeyNavigation::doubleTap() const
{
    return m_doubleTap;
}

void GesturePadKeyNavigation::setDoubleTap(Qt::Key doubleTap)
{
    if (m_doubleTap == doubleTap)
        return;

    m_doubleTap = doubleTap;
    emit doubleTapChanged();
}

Qt::Key GesturePadKeyNavigation::tripleTap() const
{
    return m_tripleTap;
}

void GesturePadKeyNavigation::setTripleTap(Qt::Key tripleTap)
{
    if (m_tripleTap == tripleTap)
        return;

    m_tripleTap = tripleTap;
    emit tripleTapChanged();
}

Qt::Key GesturePadKeyNavigation::tapAndHold() const
{
    return m_tapAndHold;
}

void GesturePadKeyNavigation::setTapAndHold(Qt::Key tapAndHold)
{
    if (m_tapAndHold == tapAndHold)
        return;

    m_tapAndHold = tapAndHold;
    emit tapAndHoldChanged();
}
