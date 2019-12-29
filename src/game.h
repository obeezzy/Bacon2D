/**
 * The MIT License (MIT)
 *
 * Copyright (C) 2012 by INdT
 * Copyright (C) 2014 Bacon2D Project
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * @author Rodrigo Goncalves de Oliveira <rodrigo.goncalves@openbossa.org>
 * @author Roger Felipe Zanoni da Silva <roger.zanoni@openbossa.org>
 */

#ifndef GAME_H
#define GAME_H

#include "enums.h"

#include <QQuickWindow>
#include <QTime>
#include <QtGlobal>
#include <QStack>
#include <QLoggingCategory>
#include <QQuickItem>

class Scene;
class Viewport;

class DeviceScreen : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool landscape READ isLandscape NOTIFY landscapeChanged)
    Q_PROPERTY(bool portrait READ isPortrait NOTIFY portraitChanged)
    Q_PROPERTY(bool alwaysOn READ alwaysOn WRITE setAlwaysOn NOTIFY alwaysOnChanged)
    Q_PROPERTY(qreal width READ width WRITE setWidth NOTIFY widthChanged)
    Q_PROPERTY(qreal height READ height WRITE setHeight NOTIFY heightChanged)
    Q_PROPERTY(qreal availableWidth READ availableWidth WRITE setAvailableWidth NOTIFY availableWidthChanged)
    Q_PROPERTY(qreal availableHeight READ availableHeight WRITE setAvailableHeight NOTIFY availableHeightChanged)
    Q_PROPERTY(Qt::ScreenOrientation orientation READ orientation NOTIFY orientationChanged)
    Q_PROPERTY(Qt::ScreenOrientation requestedOrientation READ requestedOrientation WRITE setRequestedOrientation NOTIFY requestedOrientationChanged)
public:
    explicit DeviceScreen(QObject *parent = nullptr);

    bool isLandscape() const;
    bool isPortrait() const;

    qreal width() const;
    qreal height() const;

    qreal availableWidth() const;
    qreal availableHeight() const;

    Qt::ScreenOrientation orientation() const;
    Qt::ScreenOrientation requestedOrientation() const;
    void setRequestedOrientation(Qt::ScreenOrientation requestedOrientation);

    bool alwaysOn() const;
    void setAlwaysOn(bool alwaysOn);

    void adjustToOrientationChange();

    class Bacon2DAndroid {
    public:
        static inline const int SCREEN_ORIENTATION_UNSPECIFIED = -1;
        static inline const int SCREEN_ORIENTATION_LANDSCAPE = 0;
        static inline const int SCREEN_ORIENTATION_PORTRAIT = 1;
        static void changeOrientation(Qt::ScreenOrientation orientation);
        static void keepScreenOn(bool on);
    };
signals:
    void orientationChanged();
    void requestedOrientationChanged();
    void alwaysOnChanged();
    void landscapeChanged();
    void portraitChanged();
    void widthChanged();
    void heightChanged();
    void availableWidthChanged();
    void availableHeightChanged();
private:
    void setOrientation(Qt::ScreenOrientation orientation);
    void setLandscape(bool landscape);
    void setPortrait(bool portrait);
    void setWidth(qreal width);
    void setHeight(qreal height);
    void setAvailableWidth(qreal availableWidth);
    void setAvailableHeight(qreal availableHeight);
private:
    bool m_landscape;
    bool m_portrait;
    Qt::ScreenOrientation m_orientation;
    Qt::ScreenOrientation m_requestedOrientation;
    bool m_alwaysOn;
    qreal m_width;
    qreal m_height;
    qreal m_availableWidth;
    qreal m_availableHeight;
};

/*!
  \class Game
 */
class Game : public QQuickWindow
{
    Q_OBJECT
    Q_PROPERTY(Scene *currentScene READ currentScene WRITE setCurrentScene NOTIFY currentSceneChanged)
    Q_PROPERTY(int ups READ ups WRITE setUps NOTIFY upsChanged)
    Q_PROPERTY(QPointF mouse READ mouse)
    Q_PROPERTY(QString gameName READ gameName WRITE setGameName NOTIFY gameNameChanged)
    Q_PROPERTY(Bacon2D::State gameState READ gameState WRITE setGameState NOTIFY gameStateChanged)
    Q_PROPERTY(int stackLevel READ stackLevel NOTIFY stackLevelChanged)
    Q_PROPERTY(bool isMobile READ isMobile CONSTANT)
    Q_PROPERTY(DeviceScreen* deviceScreen READ deviceScreen NOTIFY deviceScreenChanged)
    Q_PROPERTY(qreal devicePixelRatio READ devicePixelRatio CONSTANT)
public:
    explicit Game(QQuickWindow *parent = nullptr);
    virtual ~Game() override = default;

    Scene *currentScene() const;
    void setCurrentScene(Scene *currentScene);

    int stackLevel() const;
    Q_INVOKABLE void pushScene(Scene* scene);
    Q_INVOKABLE Scene* popScene();

    int ups() const;
    void setUps(const int &ups);

    QPointF mouse();

    QString gameName();
    void setGameName(const QString& gameName);

    Bacon2D::State gameState() const { return m_state; }
    void setGameState(const Bacon2D::State &state);

    bool isMobile() const;
    DeviceScreen *deviceScreen() const;
    qreal devicePixelRatio() const;
protected:
    void timerEvent(QTimerEvent *event) override;
    void update();
signals:
    void currentSceneChanged();
    void upsChanged();
    void gameNameChanged();
    void gameStateChanged();
    void stackLevelChanged();
    void deviceScreenChanged();
private:
    QTime m_gameTime;
    int m_ups;
    int m_timerId;
    Bacon2D::State m_state;
    DeviceScreen *m_deviceScreen;

    //for handling scene transition
    Scene *m_enterScene;
    Scene *m_exitScene;
    QStack<Scene*> m_sceneStack;

    QMetaMethod getMetaMethod(QObject *object, QString methodSignature) const;

    void attachScene(Scene *scene);
    void activateScene(Scene *scene);
    void deactivateScene(Scene *scene);
    bool triggerExitAnimation(Scene *scene);
    bool triggerEnterAnimation(Scene *scene);
private slots:
    void handleEnterAnimationRunningChanged(bool running);
    void handleExitAnimationRunningChanged(bool running);
    void onApplicationStateChanged(Qt::ApplicationState state);
};

Q_DECLARE_LOGGING_CATEGORY(game);

#endif // GAME_H
