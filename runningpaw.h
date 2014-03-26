#ifndef RUNNINGPAW_H
#define RUNNINGPAW_H

#include "notificationclient.h"
#include "workoutclient.h"

class runningpaw{
public:
    NotificationClient  *notificationclient;
    WorkoutClient       *ExerciseRecorder;

public:
    runningpaw();
};

extern runningpaw theApp;

#endif // RUNNINGPAW_H
