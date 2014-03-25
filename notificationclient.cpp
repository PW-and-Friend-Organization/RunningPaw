/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the QtAndroidExtras module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "notificationclient.h"

#include <QtAndroidExtras/QAndroidJniObject>
#include <QtAndroidExtras/QAndroidJniEnvironment>
#include <QDebug>

static void myQtDebug(JNIEnv *, jclass /*clazz*/, jstring s)
{
    QAndroidJniObject javaRetObj = (QAndroidJniObject)s;

    QString javastring = javaRetObj.toString();

    qDebug()<< javastring;
}

static void jni_QtFacebookLogin(JNIEnv *, jclass /*clazz*/, jstring s)
{
    QAndroidJniObject javaRetObj = (QAndroidJniObject)s;

    QString accessToken = javaRetObj.toString();

    qDebug()<< accessToken;
}

//void registerNativeMethods() {
//    JNINativeMethod methods[] = {
//        {"vowelBought", "(C)V", (void *)vowelBought},
//        {"qtDebug", "(Ljava/lang/String;)V", (void *)myQtDebug}
//    };

//    QAndroidJniObject javaClass("com/appli/test/TMain");
//    QAndroidJniEnvironment env;
//    jclass objectClass = env->GetObjectClass(javaClass.object<jobject>());
//    env->RegisterNatives(objectClass,
//                         methods,
//                         sizeof(methods) / sizeof(methods[0]));
//}

static JNINativeMethod methods[] = {
    {"qtDebug", "(Ljava/lang/String;)V", (void *)myQtDebug},
    {"qtFacebookLogin", "(Ljava/lang/String;)V", (void *)jni_QtFacebookLogin}
};

static JNINativeMethod methods2[] = {
    {"qtDebug", "(Ljava/lang/String;)V", (void *)myQtDebug}
};

jint JNICALL JNI_OnLoad(JavaVM *vm, void *)
{
    JNIEnv *env;
    if (vm->GetEnv(reinterpret_cast<void **>(&env), JNI_VERSION_1_4) != JNI_OK)
        return JNI_FALSE;

    jclass clazz = env->FindClass("com/appli/test/TMain");
    if (env->RegisterNatives(clazz, methods, sizeof(methods) / sizeof(methods[0])) < 0)
        return JNI_FALSE;

    clazz = env->FindClass("com/appli/test/TFacebook");
    if (env->RegisterNatives(clazz, methods2, sizeof(methods2) / sizeof(methods2[0])) < 0)
        return JNI_FALSE;

    return JNI_VERSION_1_4;
}

NotificationClient::NotificationClient(QObject *parent)
    : QObject(parent)
{
    connect(this, SIGNAL(notificationChanged()), this, SLOT(updateAndroidNotification()));
    connect(this, SIGNAL(loginFlagChanged()), this, SLOT(facebookLogin()));
}

void NotificationClient::setNotification(const QString &notification)
{
    if (m_notification == notification)
        return;

    m_notification = notification;
    emit notificationChanged();
}

QString NotificationClient::notification() const
{
    return m_notification;
}

void NotificationClient::setLoginFlag(const QString &loginFlag)
{
    if (m_loginFlag == loginFlag)
        return;

    m_loginFlag = loginFlag;
    emit loginFlagChanged();
}

QString NotificationClient::loginFlag() const
{
    return m_loginFlag;
}

void NotificationClient::updateAndroidNotification()
{
//    QAndroidJniObject javaNotification = QAndroidJniObject::fromString(m_notification);
//    QAndroidJniObject::callStaticMethod<void>("org/qtproject/example/notification/NotificationClient",
//                                       "notify",
//                                       "(Ljava/lang/String;)V",
//                                       javaNotification.object<jstring>());
}

void NotificationClient::facebookLogin()
{
    QAndroidJniObject::callStaticMethod<void>("com.appli.test.TMain", "startFacebook");
}
