#ifndef WORKOUTCLIENT_H
#define WORKOUTCLIENT_H

#include <QObject>
#include <QtPositioning/QGeoPositionInfo>

class WorkoutClient : public QObject
{
    Q_OBJECT

    Q_PROPERTY(double longitude READ longitude WRITE setLongitude NOTIFY longitudeChanged)
    Q_PROPERTY(double latitude READ latitude WRITE setLatitude NOTIFY latitudeChanged)
    Q_PROPERTY(QString elapedTimeFormatted READ elapedTimeFormatted WRITE setElapedTimeFormatted NOTIFY elapedTimeFormattedChanged)

    // exercise score property
    Q_PROPERTY(double distance READ distance WRITE setDistance NOTIFY distanceChanged)
    Q_PROPERTY(int exp_gain READ exp_gain WRITE setExp_gain NOTIFY exp_gainChanged)

public:
    WorkoutClient();
    ~WorkoutClient();

    //
    // Property binding
    //

    double  m_dLongitude;
    double  longitude() const;
    void    setLongitude(const double &a);

    double  m_dLatitude;
    double  latitude() const;
    void    setLatitude(const double &a);

    double  m_dDistance;
    double  distance() const;
    void    setDistance(const double &a);

    int     m_nExpGain;
    int     exp_gain() const;
    void    setExp_gain(const int &a);

    QString m_sElapedTimeFormatted;
    QString elapedTimeFormatted() const;
    void    setElapedTimeFormatted(const QString &a);

    Q_INVOKABLE void start();
    Q_INVOKABLE void stop();

    //
    // Property binding End
    //

    //
    // this consist of all the function that will be started when user click play
    //
    void startStopwatch();
    void startPositioning();

    //
    // this consist of all the function that will be stop when user click stop
    //
    void stopStopwatch();
    void stopPositioning();

signals:
    void longitudeChanged();
    void latitudeChanged();
    void elapedTimeFormattedChanged();
    void exp_gainChanged();
    void distanceChanged();

public slots:
    void StopwatchUpdate();
    void PositioningUpdate(const QGeoPositionInfo &info);
};

#endif // WORKOUTCLIENT_H
