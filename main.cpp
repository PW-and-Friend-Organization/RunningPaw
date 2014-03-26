#include <QtGui/QGuiApplication>
#include "qtquick2applicationviewer.h"
#include <qqmlcontext.h>
#include <QDebug>
#include "runningpaw.h"
#include "workoutclient.h"
#include "ContextMenu.h"
#include "notificationclient.h"

runningpaw theApp;

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QtQuick2ApplicationViewer viewer;

    theApp.ExerciseRecorder = new WorkoutClient;
    theApp.notificationclient = new NotificationClient;

    // Connect myModel Value to QML ListView myModel
    QList<QObject*> ContextList;
    ContextList.append(new ContextMenu("HOME", "home.qml"));
    ContextList.append(new ContextMenu("INVENTORY", "inventory.qml"));
    ContextList.append(new ContextMenu("EXERCISE", "exercise.qml"));
    ContextList.append(new ContextMenu("ABOUT", "about.qml"));
    ContextList.append(new ContextMenu("LOGOUT", "logout.qml"));

    QQmlContext *ctxt = viewer.rootContext();
    ctxt->setContextProperty("ContextMenuList", QVariant::fromValue(ContextList));
    ctxt->setContextProperty("ExerciseRecorder", theApp.ExerciseRecorder);

    // JNI notification and facebook connect
    ctxt->setContextProperty(QLatin1String("notificationClient"), theApp.notificationclient);

    viewer.setMainQmlFile(QStringLiteral("qml/RunningPaw/splash.qml"));
    viewer.showExpanded();

    return app.exec();
}
