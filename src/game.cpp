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

#include "game.h"
#include "scene.h"
#include "viewport.h"

#include <csignal>
#include <QGuiApplication>
#include <QQuickWindow>
#include <QCursor>
#include <QScreen>
#include <QTimer>
#ifdef Q_OS_ANDROID
#include <QAndroidJniObject>
#include <QtAndroid>
#include <QAndroidJniEnvironment>
#endif

Q_LOGGING_CATEGORY(lcgame, "bacon2d.core.game", QtWarningMsg);

namespace {
void shutdown(int sig)
{
    qCDebug(lcgame) << Q_FUNC_INFO << sig;
    qApp->quit();
}
}

DeviceScreen::DeviceScreen(QObject *parent)
    : QObject(parent)
    , m_landscape(false)
    , m_portrait(false)
    , m_orientation(Qt::PrimaryOrientation)
    , m_requestedOrientation(Qt::PrimaryOrientation)
    , m_alwaysOn(false)
    , m_width(0.0)
    , m_height(0.0)
    , m_availableWidth(0.0)
    , m_availableHeight(0.0)
{
    if (auto game = qobject_cast<Game *>(parent)) {
        if (game->isMobile() && qApp->primaryScreen()) {
            qApp->primaryScreen()->setOrientationUpdateMask(Qt::LandscapeOrientation
                                                            | Qt::InvertedLandscapeOrientation
                                                            | Qt::PortraitOrientation
                                                            | Qt::InvertedPortraitOrientation);
            adjustToOrientationChange();
            connect(qApp->primaryScreen(), &QScreen::orientationChanged,
                    this, &DeviceScreen::adjustToOrientationChange);
        }
    }
}

bool DeviceScreen::isLandscape() const
{
    return m_landscape;
}

bool DeviceScreen::isPortrait() const
{
    return m_portrait;
}

qreal DeviceScreen::width() const
{
    if (qApp->primaryScreen())
        if (qApp->primaryScreen()->isLandscape(m_orientation) != qApp->primaryScreen()->isLandscape(m_requestedOrientation))
            return m_height;

    return m_width;
}

qreal DeviceScreen::height() const
{
    if (qApp->primaryScreen())
        if (qApp->primaryScreen()->isLandscape(m_orientation) != qApp->primaryScreen()->isLandscape(m_requestedOrientation))
            return m_width;

    return m_height;
}

qreal DeviceScreen::availableWidth() const
{
    if (qApp->primaryScreen())
        if (qApp->primaryScreen()->isLandscape(m_orientation) != qApp->primaryScreen()->isLandscape(m_requestedOrientation))
            return m_availableHeight;

    return m_availableWidth;
}

qreal DeviceScreen::availableHeight() const
{
    if (qApp->primaryScreen())
        if (qApp->primaryScreen()->isLandscape(m_orientation) != qApp->primaryScreen()->isLandscape(m_requestedOrientation))
            return m_availableWidth;

    return m_availableHeight;
}

Qt::ScreenOrientation DeviceScreen::orientation() const
{
    return m_requestedOrientation != Qt::PrimaryOrientation ? m_requestedOrientation
                                                            : m_orientation;

}

void DeviceScreen::setOrientation(Qt::ScreenOrientation orientation)
{
    if (m_orientation == orientation)
        return;

    m_orientation = orientation;
    emit orientationChanged();
}

void DeviceScreen::setLandscape(bool landscape)
{
    if (m_landscape == landscape)
        return;

    m_landscape = landscape;
    emit landscapeChanged();
}

void DeviceScreen::setPortrait(bool portrait)
{
    if (m_portrait == portrait)
        return;

    m_portrait = portrait;
    emit portraitChanged();
}

void DeviceScreen::setWidth(qreal width)
{
    if (m_width == width)
        return;

    m_width = width;
    emit widthChanged();
}

void DeviceScreen::setHeight(qreal height)
{
    if (m_height == height)
        return;

    m_height = height;
    emit heightChanged();
}

void DeviceScreen::setAvailableWidth(qreal availableWidth)
{
    if (m_availableWidth == availableWidth)
        return;

    m_availableWidth = availableWidth;
    emit availableWidthChanged();
}

void DeviceScreen::setAvailableHeight(qreal availableHeight)
{
    if (m_availableHeight == availableHeight)
        return;

    m_availableHeight = availableHeight;
    emit availableHeightChanged();
}

Qt::ScreenOrientation DeviceScreen::requestedOrientation() const
{
    return m_requestedOrientation;
}

void DeviceScreen::setRequestedOrientation(Qt::ScreenOrientation requestedOrientation)
{
    if (m_requestedOrientation == requestedOrientation)
        return;

    m_requestedOrientation = requestedOrientation;
#ifdef Q_OS_ANDROID
    Bacon2DAndroid::changeOrientation(requestedOrientation);
    adjustToOrientationChange();
#endif
    emit requestedOrientationChanged();
}

bool DeviceScreen::alwaysOn() const
{
    return m_alwaysOn;
}

void DeviceScreen::setAlwaysOn(bool alwaysOn)
{
    if (m_alwaysOn == alwaysOn)
        return;

    m_alwaysOn = alwaysOn;
#ifdef Q_OS_ANDROID
    DeviceScreen::Bacon2DAndroid::keepScreenOn(alwaysOn);
#endif
    emit alwaysOnChanged();
}

void DeviceScreen::adjustToOrientationChange()
{
    if (qApp->primaryScreen()) {
        setWidth(qApp->primaryScreen()->geometry().width());
        setHeight(qApp->primaryScreen()->geometry().height());
        setAvailableWidth(qApp->primaryScreen()->availableGeometry().width());
        setAvailableHeight(qApp->primaryScreen()->availableGeometry().height());
        setLandscape(qApp->primaryScreen()->isLandscape(orientation()));
        setPortrait(qApp->primaryScreen()->isPortrait(orientation()));
        setOrientation(qApp->primaryScreen()->orientation());
    }
}

void DeviceScreen::Bacon2DAndroid::changeOrientation(Qt::ScreenOrientation orientation)
{
#ifdef Q_OS_ANDROID
    QAndroidJniObject activity = QtAndroid::androidActivity();
    if (activity.isValid()) {
        switch (orientation) {
        case Qt::LandscapeOrientation:
        case Qt::InvertedLandscapeOrientation:
            activity.callMethod<void>("setRequestedOrientation", "(I)V", SCREEN_ORIENTATION_LANDSCAPE);
            break;
        case Qt::PortraitOrientation:
        case Qt::InvertedPortraitOrientation:
            activity.callMethod<void>("setRequestedOrientation", "(I)V", SCREEN_ORIENTATION_PORTRAIT);
            break;
        default:
            activity.callMethod<void>("setRequestedOrientation", "(I)V", SCREEN_ORIENTATION_UNSPECIFIED);
            break;
        }
    }
#endif
}

void DeviceScreen::Bacon2DAndroid::keepScreenOn(bool on)
{
#ifdef Q_OS_ANDROID
    QtAndroid::runOnAndroidThread([on]{
        QAndroidJniObject activity = QtAndroid::androidActivity();
        if (activity.isValid()) {
            QAndroidJniObject window = activity.callObjectMethod("getWindow", "()Landroid/view/Window;");
            if (window.isValid()) {
                const int FLAG_KEEP_SCREEN_ON = 128;
                if (on)
                    window.callMethod<void>("addFlags", "(I)V", FLAG_KEEP_SCREEN_ON);
                else
                    window.callMethod<void>("clearFlags", "(I)V", FLAG_KEEP_SCREEN_ON);
            }
        }
        QAndroidJniEnvironment env;
        if (env->ExceptionCheck())
            env->ExceptionClear();
    });
#endif
}


/*!
  \qmltype Game
  \inqmlmodule Bacon2D
  \inherits Item
  \brief The root element containing one or more Scene.

  The Game component is the root game component which
  contains one or more Scene components.  Only one
  Scene will be set as currentScene.

  Example usage:
  \qml
   import QtQuick 2.0
   import Bacon2D 1.0

   Game {
       id: game
       width: 800
       height: 600

       Scene {
           id: scene
           width: 300
           height: 300
       }
   }
   \endqml
*/
Game::Game(QQuickWindow *parent)
    : QQuickWindow(parent)
    , m_ups(30)
    , m_timerId(0)
    , m_state(Bacon2D::State::Active)
    , m_deviceScreen(new DeviceScreen(this))
    , m_enterScene(nullptr)
    , m_exitScene(nullptr)
{
    setVisible(true);
    m_gameTime.start();
    m_timerId = startTimer(1000 / m_ups);

    if (QCoreApplication::instance()) {
        connect(qApp, &QGuiApplication::applicationStateChanged,
                this, &Game::onApplicationStateChanged);

        std::signal(SIGTERM, shutdown);
        std::signal(SIGINT, shutdown);
#ifndef WIN32 // SIGHUP and SIGKILL are not available on windows
        std::signal(SIGHUP, shutdown);
        std::signal(SIGKILL, shutdown);
#endif
    }
}

/*!
  \qmlproperty string Game::gameName
  \brief Name of the game, required if using Settings
*/
QString Game::gameName()
{
    return QCoreApplication::applicationName();
}

void Game::setGameName(const QString& gameName)
{
    // applicationName is needed for QSettings to create path to file
    QCoreApplication::setApplicationName(gameName);
    // Set the organizationName to match the applicationName, it's redundant
    // but creates path that plays well accross platforms
    QCoreApplication::setOrganizationName(gameName);
    Q_EMIT gameNameChanged();
}

void Game::onApplicationStateChanged(Qt::ApplicationState state)
{
    if (m_state != Bacon2D::State::Paused && state != Qt::ApplicationActive)
        this->setGameState(Bacon2D::State::Suspended);
    else if (m_state != Bacon2D::State::Paused && state == Qt::ApplicationActive)
        this->setGameState(Bacon2D::State::Running);
}

/*!
  \qmlproperty Bacon2D.State Game::gameState
  \brief This property holds the current gameState.
  \sa {http://doc.qt.io/qt-5/qt.html#ApplicationState-enum} {Qt.ApplicationState}
  \table
  \header
    \li {2, 1} This enum type is used to specify the current state of the game.


  \header
    \li State
    \li Description
  \row
    \li Bacon2D.Active
    \li Game is active and the currentScene is not running
  \row
    \li Bacon2D.Inactive
    \li Game is inactive
  \row
    \li Bacon2D.Running
    \li Game is active and the currentScene is running
  \row
    \li Bacon2D.Paused
    \li Game is paused by user request.
  \row
    \li Bacon2D.Suspended
    \li Game is suspended, usually means the platform has stopped the process or the game is no longer focused.
  \endtable
*/
void Game::setGameState(const Bacon2D::State &state)
{
    if (state == m_state || !currentScene())
        return;

    m_state = state;

    if (m_state == Bacon2D::State::Running)
        currentScene()->setRunning(true);
    else
        currentScene()->setRunning(false);

    emit gameStateChanged();
}

bool Game::isMobile() const
{
#ifdef Q_OS_ANDROID
    return true;
#else
    return false;
#endif
}

DeviceScreen *Game::deviceScreen() const
{
    return m_deviceScreen;
}

qreal Game::devicePixelRatio() const
{
    return QQuickWindow::devicePixelRatio();
}
/*!
  \qmlproperty Scene Game::currentScene
  \brief The current Scene
*/
Scene *Game::currentScene() const
{
    if(m_sceneStack.isEmpty())
        return nullptr;
    return m_sceneStack.top();
}

void Game::setCurrentScene(Scene *currentScene)
{
    if (!currentScene)
        return;
    if (!m_sceneStack.isEmpty() && currentScene == m_sceneStack.top())
        return;
    if (m_sceneStack.isEmpty()) {
        pushScene(currentScene);
        return;
    }

    const int stackLevel = m_sceneStack.size();

    //we need to check the the currentScene is already on the stack
    //and remove it to put on top
    if (m_sceneStack.contains(currentScene)){
        const int index = m_sceneStack.indexOf(currentScene);
        m_sceneStack.remove(index);
        //fix Scene Z in case of pushing a scene in the middle of
        //the stack to the top
        for(int i = index; i < stackLevel -1; i++){
            m_sceneStack.at(i)->setZ(i);
        }
    }

    m_exitScene = m_sceneStack.pop();

    m_sceneStack.push(currentScene);
    currentScene->setZ(m_sceneStack.size());

    if (stackLevel != m_sceneStack.size())
        emit stackLevelChanged();

    if (currentScene->viewport())
        currentScene->viewport()->setZ(m_sceneStack.size());

    deactivateScene(m_exitScene);

    attachScene(currentScene);

    triggerExitAnimation(m_exitScene);
    if (!triggerEnterAnimation(currentScene)) {
        activateScene(currentScene);
        if (m_exitScene)
            m_exitScene->setVisible(false);
        m_exitScene = nullptr;
    }
}

/*!
  \qmlproperty int Game::stackLevel
  \brief Indicates how many Scenes are stacked in the scene stack
*/
int Game::stackLevel() const
{
    return m_sceneStack.size();
}

/*!
    \qmlmethod void Game::pushScene(Scene *scene)

    Suspends the execution of the running scene, while add a new Scene to the Scene stack.
    If the Scene has the enterAnimation property set, the push will be animated. \warning Pushing
    scenes already on stack will remove it from the current position and place it on top of the stack.

\sa popScene
*/
void Game::pushScene(Scene *scene)
{
    if (!scene)
        return;
    if (!m_sceneStack.isEmpty() && scene == m_sceneStack.top())
        return;

    const int stackLevel = m_sceneStack.size();

    //we need to check the the currentScene is already on the stack
    //and remove it to put on top
    if (m_sceneStack.contains(scene)) {
        const int index = m_sceneStack.indexOf(scene);
        m_sceneStack.remove(index);
        //fix Scene Z in case of pushing a scene in the middle of
        //the stack to the top
        for (int i = index; i < stackLevel - 1; i++){
            m_sceneStack.at(i)->setZ(i);
            if (m_sceneStack.at(i)->viewport()){
                m_sceneStack.at(i)->viewport()->setZ(i);
            }
        }
    }

    Scene *topScene = nullptr;

    if (!m_sceneStack.isEmpty()) {
        topScene = m_sceneStack.top();
        deactivateScene(topScene);
        m_exitScene = topScene;
    }

    m_sceneStack.push(scene);
    if (stackLevel != m_sceneStack.size())
        emit stackLevelChanged();

    scene->setZ(m_sceneStack.size());

    if (scene->viewport())
        scene->viewport()->setZ(m_sceneStack.size());

    attachScene(scene);

    if (!triggerEnterAnimation(scene)) {
        activateScene(scene);
        if(topScene)
            topScene->setVisible(false);
    }
}

/*!
    \qmlmethod Scene* Game::popScene()
    \brief Suspends and remove the top Scene from the scene stack.
    Suspends and remove the current Scene from stack. If exitAnimation property
the exit will be animated. When there is no scene on stack, it will do nothing.

\sa pushScene
*/
Scene* Game::popScene()
{
    if (m_sceneStack.isEmpty())
        return nullptr;

    Scene *topScene = m_sceneStack.pop();

    emit stackLevelChanged();

    if (topScene) {
        deactivateScene(topScene);

        if (!m_sceneStack.isEmpty())
            attachScene(m_sceneStack.top());
        if (!triggerExitAnimation(topScene)) {
            if(!m_sceneStack.isEmpty())
                activateScene(m_sceneStack.top());
            else
                emit currentSceneChanged();

            topScene->setVisible(false);
        }
    }
    return topScene;
}

/*!
  \qmlproperty int Game::ups
  \brief This property holds the number of times update is called per second.

    Updates per second can be used to control the speed of the game
    loop.  The default is 30.
 */
int Game::ups() const
{
    return m_ups;
}

void Game::setUps(const int &ups)
{
    if (m_ups == ups)
        return;

    m_ups = ups;

    killTimer(m_timerId);
    m_gameTime.restart();
    m_timerId = startTimer(1000 / m_ups);

    emit upsChanged();
}

void Game::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event)

    update();
}

void Game::update()
{
    if (m_sceneStack.isEmpty())
        return;

    Scene *currentScene = m_sceneStack.top();
    int elapsedTime = m_gameTime.restart();

    if (currentScene && currentScene->running())
        currentScene->update(elapsedTime);
}

/*!
  \qmlproperty QPointF Game::mouse
  \brief The point in the plane of the mouse pointer
*/
QPointF Game::mouse()
{
    return mapFromGlobal(QCursor::pos());
}

void Game::attachScene(Scene *scene)
{
    if (!scene)
        return;

    Viewport *viewport = scene->viewport();
    if (viewport) {
        viewport->setParent(contentItem());
        viewport->setParentItem(contentItem());
        viewport->setScene(scene);
    } else {
        scene->setParent(this);
        scene->setParentItem(contentItem());
    }

    scene->setVisible(true);
    scene->setRunning(false);
    scene->setEnabled(false);
    scene->setFocus(false, Qt::OtherFocusReason);
}

void Game::activateScene(Scene *scene)
{
    if (!scene){
        return;
    }
    scene->setRunning(true);
    scene->setEnabled(true);
    scene->setFocus(true, Qt::OtherFocusReason);
    emit currentSceneChanged();
}

void Game::deactivateScene(Scene *scene)
{
    if (!scene)
        return;

    scene->setRunning(false);
    scene->setEnabled(false);
    scene->setFocus(false, Qt::OtherFocusReason);
}

bool Game::triggerEnterAnimation(Scene *scene)
{
    QObject *enterAnimation = scene->enterAnimation();

    if (!enterAnimation)
        return false;

    m_enterScene = scene;
    const QMetaObject *meta = enterAnimation->metaObject();

    int propIndex = meta->indexOfProperty("running");

    QMetaMethod enterSignal = meta->property(propIndex).notifySignal();

    connect(enterAnimation, enterSignal,
            this, getMetaMethod(this, "handleEnterAnimationRunningChanged(bool)"));

    getMetaMethod(enterAnimation, "start()")
            .invoke(enterAnimation, Qt::AutoConnection);
    return true;
}

void Game::handleEnterAnimationRunningChanged(bool running)
{
    if (running)
        return;

    disconnect(sender(), nullptr, this, SLOT(handleEnterAnimationRunningChanged(bool)));

    activateScene(m_enterScene);
    m_enterScene = nullptr;

    if (m_exitScene)
        m_exitScene->setVisible(false);
}

bool Game::triggerExitAnimation(Scene *scene)
{
    QObject *exitAnimation = scene->exitAnimation();

    if (!exitAnimation)
        return false;

    m_exitScene = scene;
    const QMetaObject *meta = exitAnimation->metaObject();

    const int propIndex = meta->indexOfProperty("running");

    QMetaMethod signal  = meta->property(propIndex).notifySignal();

    connect(exitAnimation, signal,
            this, getMetaMethod(this, "handleExitAnimationRunningChanged(bool)"));

    getMetaMethod(exitAnimation, "start()").invoke(exitAnimation, Qt::AutoConnection);

    return true;
}

void Game::handleExitAnimationRunningChanged(bool running)
{
    if (running)
        return;
    disconnect(sender(), nullptr, this, SLOT(handleExitAnimationRunningChanged(bool)));

    if (m_exitScene) {
        if(m_exitScene->viewport())
            m_exitScene->viewport()->setVisible(false);

        m_exitScene->setVisible(false);
    }
    m_exitScene = nullptr;

    if (!m_sceneStack.isEmpty()) {
        if (!m_sceneStack.top()->running())
            activateScene(m_sceneStack.top());
    } else {
        emit currentSceneChanged();
    }
}

QMetaMethod Game::getMetaMethod(QObject *object, QString methodSignature) const
{
    const int methodIndex = object->metaObject()->indexOfMethod(QMetaObject::normalizedSignature(methodSignature.toLocal8Bit()));

    if (!object || methodIndex == -1)
        return QMetaMethod();

    return object->metaObject()->method(methodIndex);
}
