#ifndef EXERCISERECORDER_H
#define EXERCISERECORDER_H

#include <QObject>
#include <QtPositioning/QGeoPositionInfo>
#include <QtPositioning/QGeoPositionInfoSource>
#include <QGeoCoordinate>
#include <QTime>
#include <QTimer>
#include <QDebug>

class ExerciseRecorder : public QObject
{
    Q_OBJECT

    Q_PROPERTY(double longitude READ longitude WRITE setLongitude NOTIFY longitudeChanged)
    Q_PROPERTY(double latitude READ latitude WRITE setLatitude NOTIFY latitudeChanged)
    Q_PROPERTY(QString elapedTimeFormatted READ elapedTimeFormatted WRITE setElapedTimeFormatted NOTIFY elapedTimeFormattedChanged)

    // exercise score property
    Q_PROPERTY(double distance READ distance WRITE setDistance NOTIFY distanceChanged)
    Q_PROPERTY(int exp_gain READ exp_gain WRITE setExp_gain NOTIFY exp_gainChanged)

private:
    // attribute that will be expose to QML
    double  m_dLongitude;
    double  m_dLatitude;
    double  m_dDistance;
    int     m_nExpGain;
    QString m_sElapedTimeFormatted;

public:
    void setLongitude(const double &a)
    {
        if( a != m_dLongitude){
            m_dLongitude = a;
            emit longitudeChanged();
        }
    }
    double longitude() const {
        return m_dLongitude;
    }

    void setLatitude(const double &a)
    {
        if( a != m_dLatitude){
            m_dLatitude = a;
            emit latitudeChanged();
        }
    }
    double latitude() const {
        return m_dLatitude;
    }

    void setElapedTimeFormatted(const QString &a)
    {
        if( a != m_sElapedTimeFormatted){
            m_sElapedTimeFormatted = a;
            emit elapedTimeFormattedChanged();
        }
    }
    QString elapedTimeFormatted() const {
        return m_sElapedTimeFormatted;
    }

    void setDistance(const double &a)
    {
        if( a != m_dDistance){
            m_dDistance = a;
            emit distanceChanged();
        }
    }
    double distance() const {
        return m_dDistance;
    }

    void setExp_gain(const int &a)
    {
        if( a != m_nExpGain){
            m_nExpGain = a;
            emit exp_gainChanged();
        }
    }
    int exp_gain() const {
        return m_nExpGain;
    }

public:
    // Local attributes
    QGeoPositionInfoSource *pGeoPositionInfoSource;
    QGeoCoordinate          currentCoordinate;
    QGeoCoordinate          previousCoordinate;

    QTimer  *pTimer;
    QTime   startTime;
    QTime   endTime;
    QTime   recordingTime;

public:
    ExerciseRecorder()
    {
        pGeoPositionInfoSource = QGeoPositionInfoSource::createDefaultSource(0);
        if (pGeoPositionInfoSource) {
            qDebug() << "connect positionUpdated...";

            connect(pGeoPositionInfoSource, SIGNAL(positionUpdated(QGeoPositionInfo)),
                    this, SLOT(PositioningUpdate(QGeoPositionInfo)));
        }

        pTimer = new QTimer(this);
        connect(pTimer, SIGNAL(timeout()), this, SLOT(StopwatchUpdate()));
    }

    Q_INVOKABLE void start()
    {
        qDebug() << "ExcerciseRecorder is starting";

        m_dDistance = 0;
        m_nExpGain = 0;

        startPositioning();
        startStopwatch();
        return;
    }

    Q_INVOKABLE void stop()
    {
        qDebug() << "ExcerciseRecorder has stop";

        stopPositioning();
        stopStopwatch();

        setExp_gain(((recordingTime.elapsed()/1000)*m_dDistance)/10);

        return;
    }

    //
    // this consist of all the function that will be started when user click play
    //
    void startStopwatch()
    {
        startTime = QTime::currentTime();
        recordingTime.start();
        pTimer->start(1000);
    }

    void startPositioning()
    {
        qDebug() << "startPositioning...";

        if( pGeoPositionInfoSource )
            pGeoPositionInfoSource->startUpdates();
    }

    //
    // this consist of all the function that will be stop when user click stop
    //
    void stopStopwatch()
    {
        endTime = QTime::currentTime();
        pTimer->stop();
    }

    void stopPositioning()
    {
        qDebug() << "stopPositioning...";

        if( pGeoPositionInfoSource )
            pGeoPositionInfoSource->stopUpdates();
    }


public slots:
    void StopwatchUpdate()
    {
        qDebug() << "Stopwatch update";

        QTime tempTime(0,0,0,0);
        tempTime = tempTime.addMSecs(recordingTime.elapsed());

        QString sElaps = tempTime.toString(QString("hh:mm:ss"));
        qDebug("Time elapsed: %d ms", recordingTime.elapsed());

        setElapedTimeFormatted( sElaps ); //QString("%1 ms").arg(recordingTime.elapsed());
    }

    void PositioningUpdate(const QGeoPositionInfo &info)
    {
        qDebug() << "Position updated:" << info;

        currentCoordinate = info.coordinate();

        setLatitude(currentCoordinate.latitude());
        setLongitude(currentCoordinate.longitude());

        if( previousCoordinate.isValid() )
        {
            setDistance( m_dDistance += currentCoordinate.distanceTo(previousCoordinate) );
        }
        previousCoordinate = currentCoordinate;
    }

signals:
    void longitudeChanged();
    void latitudeChanged();
    void elapedTimeFormattedChanged();
    void exp_gainChanged();
    void distanceChanged();
};


#endif // EXERCISERECORDER_H
