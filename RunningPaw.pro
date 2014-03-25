# Add more folders to ship with the application, here
folder_01.source = qml/RunningPaw
folder_01.target = qml
DEPLOYMENTFOLDERS = folder_01

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

QT += positioning sql quick androidextras

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android-sources

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp \
    workoutclient.cpp \
    notificationclient.cpp

# Installation path
# target.path =

# Please do not modify the following two lines. Required for deployment.
include(qtquick2applicationviewer/qtquick2applicationviewer.pri)
qtcAddDeployment()

HEADERS += \
    ContextMenu.h \
    workoutclient.h \
    notificationclient.h

OTHER_FILES += \
    android-sources/AndroidManifest.xml \
    android-sources/src/com/appli/test/TMain.java \
    android-sources/src/com/appli/test/TFacebook.java
