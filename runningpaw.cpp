#include "runningpaw.h"

runningpaw::runningpaw()
{
    notificationclient = 0;
    ExerciseRecorder = 0;
    facebookclient = 0;
}

runningpaw::~runningpaw()
{
    if( notificationclient != 0)
        delete notificationclient;

    if( ExerciseRecorder != 0 )
        delete ExerciseRecorder;

    if( facebookclient != 0 )
        delete facebookclient;
}
