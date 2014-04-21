#include "workoutclient.h"

#include <QtPositioning/QGeoPositionInfo>
#include <QtPositioning/QGeoPositionInfoSource>
#include <QtPositioning/QGeoCoordinate>
#include <QTime>
#include <QTimer>
#include <QDebug>

//
// Shared Attributes
//
QGeoPositionInfoSource *pGeoPositionInfoSource;
QGeoCoordinate          currentCoordinate;
QGeoCoordinate          previousCoordinate;

QTimer  *pTimer;
QTime   startTime;
QTime   endTime;
QTime   recordingTime;

WorkoutClient::WorkoutClient()
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
WorkoutClient::~WorkoutClient()
{
}

double WorkoutClient::longitude() const
{
    return m_dLongitude;
}
void WorkoutClient::setLongitude(const double &a)
{
    if( a != m_dLongitude){
        m_dLongitude = a;
        emit longitudeChanged();
    }
}

double WorkoutClient::latitude() const
{
    return m_dLatitude;
}
void WorkoutClient::setLatitude(const double &a)
{
    if( a != m_dLatitude){
        m_dLatitude = a;
        emit latitudeChanged();
    }
}

double WorkoutClient::distance() const
{
    return m_dDistance;
}
void WorkoutClient::setDistance(const double &a)
{
    if( a != m_dDistance){
        m_dDistance = a;
        emit distanceChanged();
    }
}

int WorkoutClient::exp_gain() const
{
    return m_nExpGain;
}
void WorkoutClient::setExp_gain(const int &a)
{
    if( a != m_nExpGain){
        m_nExpGain = a;
        emit exp_gainChanged();
    }
}

QString WorkoutClient::elapedTimeFormatted() const
{
    return m_sElapedTimeFormatted;
}
void WorkoutClient::setElapedTimeFormatted(const QString &a)
{
    if( a != m_sElapedTimeFormatted){
        m_sElapedTimeFormatted = a;
        emit elapedTimeFormattedChanged();
    }
}

void WorkoutClient::start()
{
    qDebug() << "ExcerciseRecorder is starting";

    m_dDistance = 0;
    m_nExpGain = 0;

    //startPositioning();
    startStopwatch();
    return;
}
void WorkoutClient::stop()
{
    qDebug() << "ExcerciseRecorder has stop";

    //stopPositioning();
    stopStopwatch();

    setExp_gain(((recordingTime.elapsed()/1000)*m_dDistance)/10);

    return;
}

void WorkoutClient::startStopwatch()
{
    startTime = QTime::currentTime();
    recordingTime.start();
    pTimer->start(1000);
}
void WorkoutClient::startPositioning()
{
    qDebug() << "startPositioning...";

    if( pGeoPositionInfoSource )
        pGeoPositionInfoSource->startUpdates();
}

void WorkoutClient::stopStopwatch()
{
    endTime = QTime::currentTime();
    pTimer->stop();
}
void WorkoutClient::stopPositioning()
{
    qDebug() << "stopPositioning...";

    if( pGeoPositionInfoSource )
        pGeoPositionInfoSource->stopUpdates();
}

void WorkoutClient::StopwatchUpdate()
{
    qDebug() << "Stopwatch update";

    QTime tempTime(0,0,0,0);
    tempTime = tempTime.addMSecs(recordingTime.elapsed());

    QString sElaps = tempTime.toString(QString("hh:mm:ss"));
    qDebug("Time elapsed: %d ms", recordingTime.elapsed());

    setElapedTimeFormatted( sElaps ); //QString("%1 ms").arg(recordingTime.elapsed());
}
void WorkoutClient::PositioningUpdate(const QGeoPositionInfo &info)
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
