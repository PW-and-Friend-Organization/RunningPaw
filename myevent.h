#ifndef MYEVENT_H
#define MYEVENT_H

#include <QObject>

class MyEvent : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int pick_count READ pick_count WRITE setPick_count NOTIFY pick_countChanged)

public:
    explicit MyEvent(QObject *parent = 0);

    Q_INVOKABLE void start();
    Q_INVOKABLE void stop();
    Q_INVOKABLE void finalizePickCount();

    void startRandomAnimalTimer();
    void startRandomPickUpTimer();

    int     m_nPickCount;
    int     pick_count() const;
    void    setPick_count(const int &a);

    QString AnimalSoundPath[8];

signals:
    void pick_countChanged();

public slots:
    void AnimalEvent();
    void PickUpEvent();
};

#endif // MYEVENT_H
