# Add more folders to ship with the application, here
folder_01.source = qml/RunningPaw
folder_01.target = qml
DEPLOYMENTFOLDERS = folder_01

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

QT += multimedia positioning sql quick androidextras network core gui

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android-sources

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp \
    workoutclient.cpp \
    notificationclient.cpp \
    runningpaw.cpp \
    facebookclient.cpp \
    localdb.cpp \
    myevent.cpp

# Installation path
# target.path =

# Please do not modify the following two lines. Required for deployment.
include(qtquick2applicationviewer/qtquick2applicationviewer.pri)
qtcAddDeployment()

HEADERS += \
    ContextMenu.h \
    workoutclient.h \
    notificationclient.h \
    runningpaw.h \
    facebookclient.h \
    localdb.h \
    myevent.h

OTHER_FILES += \
    android-sources/AndroidManifest.xml \
    android-sources/src/com/blueorbitz/digicfc2/TMain.java \
    android-sources/src/com/blueorbitz/digicfc2/TFacebook.java
