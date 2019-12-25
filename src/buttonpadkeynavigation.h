#ifndef BUTTONPADKEYNAVIGATION_H
#define BUTTONPADKEYNAVIGATION_H

#include "keynavigation.h"

class ButtonPadKeyNavigation : public KeyNavigation
{
    Q_OBJECT
    Q_PROPERTY(Qt::Key buttonL1 READ buttonL1 WRITE setButtonL1 NOTIFY buttonL1Changed)
    Q_PROPERTY(Qt::Key buttonL2 READ buttonL2 WRITE setButtonL2 NOTIFY buttonL2Changed)
    Q_PROPERTY(Qt::Key buttonL3 READ buttonL3 WRITE setButtonL3 NOTIFY buttonL3Changed)
    Q_PROPERTY(Qt::Key buttonR1 READ buttonR1 WRITE setButtonR1 NOTIFY buttonR1Changed)
    Q_PROPERTY(Qt::Key buttonR2 READ buttonR2 WRITE setButtonR2 NOTIFY buttonR2Changed)
    Q_PROPERTY(Qt::Key buttonR3 READ buttonR3 WRITE setButtonR3 NOTIFY buttonR3Changed)
    Q_PROPERTY(Qt::Key buttonA READ buttonA WRITE setButtonA NOTIFY buttonAChanged)
    Q_PROPERTY(Qt::Key buttonB READ buttonB WRITE setButtonB NOTIFY buttonBChanged)
    Q_PROPERTY(Qt::Key buttonCenter READ buttonCenter WRITE setButtonCenter NOTIFY buttonCenterChanged)
    Q_PROPERTY(Qt::Key buttonDown READ buttonDown WRITE setButtonDown NOTIFY buttonDownChanged)
    Q_PROPERTY(Qt::Key buttonGuide READ buttonGuide WRITE setButtonGuide NOTIFY buttonGuideChanged)
    Q_PROPERTY(Qt::Key buttonLeft READ buttonLeft WRITE setButtonLeft NOTIFY buttonLeftChanged)
    Q_PROPERTY(Qt::Key buttonRight READ buttonRight WRITE setButtonRight NOTIFY buttonRightChanged)
    Q_PROPERTY(Qt::Key buttonSelect READ buttonSelect WRITE setButtonSelect NOTIFY buttonSelectChanged)
    Q_PROPERTY(Qt::Key buttonStart READ buttonStart WRITE setButtonStart NOTIFY buttonStartChanged)
    Q_PROPERTY(Qt::Key buttonUp READ buttonUp WRITE setButtonUp NOTIFY buttonUpChanged)
    Q_PROPERTY(Qt::Key buttonX READ buttonX WRITE setButtonX NOTIFY buttonXChanged)
    Q_PROPERTY(Qt::Key buttonY READ buttonY WRITE setButtonY NOTIFY buttonYChanged)
public:
    explicit ButtonPadKeyNavigation(QObject *parent = nullptr);

    Qt::Key buttonL1() const;
    void setButtonL1(Qt::Key buttonL1);

    Qt::Key buttonL2() const;
    void setButtonL2(Qt::Key buttonL2);

    Qt::Key buttonL3() const;
    void setButtonL3(Qt::Key buttonL3);

    Qt::Key buttonR1() const;
    void setButtonR1(Qt::Key buttonR1);

    Qt::Key buttonR2() const;
    void setButtonR2(Qt::Key buttonR2);

    Qt::Key buttonR3() const;
    void setButtonR3(Qt::Key buttonR3);

    Qt::Key buttonA() const;
    void setButtonA(Qt::Key buttonA);

    Qt::Key buttonB() const;
    void setButtonB(Qt::Key buttonB);

    Qt::Key buttonCenter() const;
    void setButtonCenter(Qt::Key buttonCenter);

    Qt::Key buttonDown() const;
    void setButtonDown(Qt::Key buttonDown);

    Qt::Key buttonGuide() const;
    void setButtonGuide(Qt::Key buttonGuide);

    Qt::Key buttonLeft() const;
    void setButtonLeft(Qt::Key buttonLeft);

    Qt::Key buttonRight() const;
    void setButtonRight(Qt::Key buttonRight);

    Qt::Key buttonSelect() const;
    void setButtonSelect(Qt::Key buttonSelect);

    Qt::Key buttonStart() const;
    void setButtonStart(Qt::Key buttonStart);

    Qt::Key buttonUp() const;
    void setButtonUp(Qt::Key buttonUp);

    Qt::Key buttonX() const;
    void setButtonX(Qt::Key buttonX);

    Qt::Key buttonY() const;
    void setButtonY(Qt::Key buttonY);
signals:
    void buttonL1Changed();
    void buttonL2Changed();
    void buttonL3Changed();
    void buttonR1Changed();
    void buttonR2Changed();
    void buttonR3Changed();
    void buttonAChanged();
    void buttonBChanged();
    void buttonCenterChanged();
    void buttonDownChanged();
    void buttonGuideChanged();
    void buttonLeftChanged();
    void buttonRightChanged();
    void buttonSelectChanged();
    void buttonStartChanged();
    void buttonUpChanged();
    void buttonXChanged();
    void buttonYChanged();
private:
    Qt::Key m_buttonL1;
    Qt::Key m_buttonL2;
    Qt::Key m_buttonL3;
    Qt::Key m_buttonR1;
    Qt::Key m_buttonR2;
    Qt::Key m_buttonR3;
    Qt::Key m_buttonA;
    Qt::Key m_buttonB;
    Qt::Key m_buttonCenter;
    Qt::Key m_buttonDown;
    Qt::Key m_buttonGuide;
    Qt::Key m_buttonLeft;
    Qt::Key m_buttonRight;
    Qt::Key m_buttonSelect;
    Qt::Key m_buttonStart;
    Qt::Key m_buttonUp;
    Qt::Key m_buttonX;
    Qt::Key m_buttonY;
};

#endif // BUTTONPADKEYNAVIGATION_H
