#include "buttonpadkeynavigation.h"

ButtonPadKeyNavigation::ButtonPadKeyNavigation(QObject *parent)
    : KeyNavigation(parent)
    , m_buttonL1(Qt::Key_F35)
    , m_buttonL2(Qt::Key_F34)
    , m_buttonL3(Qt::Key_F33)
    , m_buttonR1(Qt::Key_F32)
    , m_buttonR2(Qt::Key_F31)
    , m_buttonR3(Qt::Key_F30)
    , m_buttonA(Qt::Key_F29)
    , m_buttonB(Qt::Key_F28)
    , m_buttonCenter(Qt::Key_F27)
    , m_buttonDown(Qt::Key_F26)
    , m_buttonGuide(Qt::Key_F25)
    , m_buttonLeft(Qt::Key_F24)
    , m_buttonRight(Qt::Key_F23)
    , m_buttonSelect(Qt::Key_F22)
    , m_buttonStart(Qt::Key_F21)
    , m_buttonUp(Qt::Key_F20)
    , m_buttonX(Qt::Key_F19)
    , m_buttonY(Qt::Key_F18)
{

}

Qt::Key ButtonPadKeyNavigation::buttonL1() const
{
    return m_buttonL1;
}

void ButtonPadKeyNavigation::setButtonL1(Qt::Key buttonL1)
{
    if (m_buttonL1 == buttonL1)
        return;

    m_buttonL1 = buttonL1;
    emit buttonL1Changed();
}

Qt::Key ButtonPadKeyNavigation::buttonL2() const
{
    return m_buttonL2;
}

void ButtonPadKeyNavigation::setButtonL2(Qt::Key buttonL2)
{
    if (m_buttonL2 == buttonL2)
        return;

    m_buttonL2 = buttonL2;
    emit buttonL2Changed();
}

Qt::Key ButtonPadKeyNavigation::buttonL3() const
{
    return m_buttonL3;
}

void ButtonPadKeyNavigation::setButtonL3(Qt::Key buttonL3)
{
    if (m_buttonL3 == buttonL3)
        return;

    m_buttonL3 = buttonL3;
    emit buttonL3Changed();
}

Qt::Key ButtonPadKeyNavigation::buttonR1() const
{
    return m_buttonR1;
}

void ButtonPadKeyNavigation::setButtonR1(Qt::Key buttonR1)
{
    if (m_buttonR1 == buttonR1)
        return;

    m_buttonR1 = buttonR1;
    emit buttonR1Changed();
}

Qt::Key ButtonPadKeyNavigation::buttonR2() const
{
    return m_buttonR2;
}

void ButtonPadKeyNavigation::setButtonR2(Qt::Key buttonR2)
{
    if (m_buttonR2 == buttonR2)
        return;

    m_buttonR2 = buttonR2;
    emit buttonR2Changed();
}

Qt::Key ButtonPadKeyNavigation::buttonR3() const
{
    return m_buttonR3;
}

void ButtonPadKeyNavigation::setButtonR3(Qt::Key buttonR3)
{
    if (m_buttonR3 == buttonR3)
        return;

    m_buttonR3 = buttonR3;
    emit buttonR3Changed();
}

Qt::Key ButtonPadKeyNavigation::buttonA() const
{
    return m_buttonA;
}

void ButtonPadKeyNavigation::setButtonA(Qt::Key buttonA)
{
    if (m_buttonA == buttonA)
        return;

    m_buttonA = buttonA;
    emit buttonAChanged();
}

Qt::Key ButtonPadKeyNavigation::buttonB() const
{
    return m_buttonB;
}

void ButtonPadKeyNavigation::setButtonB(Qt::Key buttonB)
{
    if (m_buttonB == buttonB)
        return;

    m_buttonB = buttonB;
    emit buttonBChanged();
}

Qt::Key ButtonPadKeyNavigation::buttonCenter() const
{
    return m_buttonCenter;
}

void ButtonPadKeyNavigation::setButtonCenter(Qt::Key buttonCenter)
{
    if (m_buttonCenter == buttonCenter)
        return;

    m_buttonCenter = buttonCenter;
    emit buttonCenterChanged();
}

Qt::Key ButtonPadKeyNavigation::buttonDown() const
{
    return m_buttonDown;
}

void ButtonPadKeyNavigation::setButtonDown(Qt::Key buttonDown)
{
    if (m_buttonDown == buttonDown)
        return;

    m_buttonDown = buttonDown;
    emit buttonDownChanged();
}

Qt::Key ButtonPadKeyNavigation::buttonGuide() const
{
    return m_buttonGuide;
}

void ButtonPadKeyNavigation::setButtonGuide(Qt::Key buttonGuide)
{
    if (m_buttonGuide == buttonGuide)
        return;

    m_buttonGuide = buttonGuide;
    emit buttonGuideChanged();
}

Qt::Key ButtonPadKeyNavigation::buttonLeft() const
{
    return m_buttonLeft;
}

void ButtonPadKeyNavigation::setButtonLeft(Qt::Key buttonLeft)
{
    if (m_buttonLeft == buttonLeft)
        return;

    m_buttonLeft = buttonLeft;
    emit buttonLeftChanged();
}

Qt::Key ButtonPadKeyNavigation::buttonRight() const
{
    return m_buttonRight;
}

void ButtonPadKeyNavigation::setButtonRight(Qt::Key buttonRight)
{
    if (m_buttonRight == buttonRight)
        return;

    m_buttonRight = buttonRight;
    emit buttonRightChanged();
}

Qt::Key ButtonPadKeyNavigation::buttonSelect() const
{
    return m_buttonSelect;
}

void ButtonPadKeyNavigation::setButtonSelect(Qt::Key buttonSelect)
{
    if (m_buttonSelect == buttonSelect)
        return;

    m_buttonSelect = buttonSelect;
    emit buttonSelectChanged();
}

Qt::Key ButtonPadKeyNavigation::buttonStart() const
{
    return m_buttonStart;
}

void ButtonPadKeyNavigation::setButtonStart(Qt::Key buttonStart)
{
    if (m_buttonStart == buttonStart)
        return;

    m_buttonStart = buttonStart;
    emit buttonStartChanged();
}

Qt::Key ButtonPadKeyNavigation::buttonUp() const
{
    return m_buttonUp;
}

void ButtonPadKeyNavigation::setButtonUp(Qt::Key buttonUp)
{
    if (m_buttonUp == buttonUp)
        return;

    m_buttonUp = buttonUp;
    emit buttonUpChanged();
}

Qt::Key ButtonPadKeyNavigation::buttonX() const
{
    return m_buttonX;
}

void ButtonPadKeyNavigation::setButtonX(Qt::Key buttonX)
{
    if (m_buttonX == buttonX)
        return;

    m_buttonX = buttonX;
    emit buttonXChanged();
}

Qt::Key ButtonPadKeyNavigation::buttonY() const
{
    return m_buttonY;
}

void ButtonPadKeyNavigation::setButtonY(Qt::Key buttonY)
{
    if (m_buttonY == buttonY)
        return;

    m_buttonY = buttonY;
    emit buttonYChanged();
}
