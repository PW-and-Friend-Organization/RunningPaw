#ifndef USERPROFILE_H
#define USERPROFILE_H

class UserProfile{
public:
    QString sUserName;
    QString sPassword;
    int     nLoginStatus; // 1-Login, 0-Logout
    int     nExpGain;
    int     nTotalDistance;
    int     nTotalTimeInSec;
    double  dAverageSpeed;

public:
    UserProfile(){
        sUserName = "";
        sPassword = "";
        nLoginStatus = 0;
        nExpGain = 0;
        nTotalDistance = 0;
        nTotalTimeInSec = 0;
        dAverageSpeed = 0;
    }
};

#endif // USERPROFILE_H
