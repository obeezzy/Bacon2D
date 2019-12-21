#include <QGuiApplication>
#include <QQmlApplicationEngine>
#ifdef Q_OS_ANDROID
#include <QAndroidJniObject>
#include <QtAndroid>
#include <QAndroidJniEnvironment>
#endif

#ifdef Q_OS_ANDROID
void switchToHorizontalOrientation()
{
    QAndroidJniObject activity = QtAndroid::androidActivity();
    if (activity.isValid()) {
        const int HORIZONTAL_ORIENTATION = 0;
        activity.callMethod<void>("setRequestedOrientation", "(I)V", HORIZONTAL_ORIENTATION);
    }
}

void keepScreenOn()
{
    QtAndroid::runOnAndroidThread([]{
        QAndroidJniObject activity = QtAndroid::androidActivity();
        if (activity.isValid()) {
            QAndroidJniObject window = activity.callObjectMethod("getWindow", "()Landroid/view/Window;");
            if (window.isValid()) {
                const int FLAG_KEEP_SCREEN_ON = 128;
                window.callMethod<void>("addFlags", "(I)V", FLAG_KEEP_SCREEN_ON);
            }
        }
        QAndroidJniEnvironment env;
        if (env->ExceptionCheck())
            env->ExceptionClear();
    });
}
#endif

int main(int argc, char *argv[])
{
#ifdef Q_OS_ANDROID
    switchToHorizontalOrientation();
    keepScreenOn();
#endif
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
