#include <QtGui/QGuiApplication>
#include "qtquick2applicationviewer.h"
#include <qqmlcontext.h>
#include <QDebug>
#include "workoutclient.h"
#include "ContextMenu.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QtQuick2ApplicationViewer viewer;

    // Connect myModel Value to QML ListView myModel
    QList<QObject*> ContextList;
    ContextList.append(new ContextMenu("HOME", "home.qml"));
    ContextList.append(new ContextMenu("INVENTORY", "inventory.qml"));
    ContextList.append(new ContextMenu("EXERCISE", "exercise.qml"));
    ContextList.append(new ContextMenu("ABOUT", "about.qml"));
    ContextList.append(new ContextMenu("LOGOUT", "logout.qml"));

    // ExerciseRecorder
    WorkoutClient oExerciseRecorder;

    QQmlContext *ctxt = viewer.rootContext();
    ctxt->setContextProperty("ContextMenuList", QVariant::fromValue(ContextList));
    ctxt->setContextProperty("ExerciseRecorder", &oExerciseRecorder);

    viewer.setMainQmlFile(QStringLiteral("qml/RunningPaw/splash.qml"));
    viewer.showExpanded();

    return app.exec();
}
