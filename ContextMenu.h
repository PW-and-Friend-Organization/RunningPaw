#ifndef CONTEXTMENU_H
#define CONTEXTMENU_H

#include <QObject>
#include <QDebug>

class ContextMenu : public QObject
{
    Q_OBJECT

    // to expose property for ListView
    Q_PROPERTY(QString menu_name READ menu_name)
    Q_PROPERTY(QString menu_param READ menu_param)

public:
    QString m_sMenuName;
    QString m_sMenuParam;

public:
    ContextMenu(QObject *parent=0)
        : QObject(parent)
    {
    }

    ContextMenu(QString sMenuName, QString sMenuParam)
    {
        m_sMenuName = sMenuName;
        m_sMenuParam = sMenuParam;
    }

    ~ContextMenu(){}

    // For QML to call this as a method
    Q_INVOKABLE bool postMessage(QString msg) {
         qDebug() << "Called the C++ method with" << msg;
         return true;
     }

    QString menu_name()
    {
        return m_sMenuName;
    }

    QString menu_param()
    {
        return m_sMenuParam;
    }

};

#endif // CONTEXTMENU_H
