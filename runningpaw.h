#ifndef RUNNINGPAW_H
#define RUNNINGPAW_H

#include "notificationclient.h"
#include "workoutclient.h"
#include "facebookclient.h"
#include "localdb.h"
#include "myevent.h"

class runningpaw{
public:
    NotificationClient  *notificationclient;
    WorkoutClient       *ExerciseRecorder;
    FacebookClient      *facebookclient;
    LocalDB             *pLocalDB;
    MyEvent             *pMyEvent;

public:
    runningpaw();
    ~runningpaw();
};

extern runningpaw theApp;

#endif // RUNNINGPAW_H
