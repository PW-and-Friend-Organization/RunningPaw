#include "myevent.h"
#include "runningpaw.h"
#include <QTimer>
#include <QTime>
#include <QMediaPlayer>

QTimer  *pAnimalNearByTimer;
QTimer  *pItemFoundTimer;

int multiplier = 1000;

MyEvent::MyEvent(QObject *parent) :
    QObject(parent)
{
    AnimalSoundPath[0] = "Sound/cat_meow.mp3";
    AnimalSoundPath[1] = "Sound/cat_meow_002.mp3";
    AnimalSoundPath[2] = "Sound/cat_meow_003.mp3";
    AnimalSoundPath[3] = "Sound/Dog_walking.mp3";
    AnimalSoundPath[4] = "Sound/dogs_barking.mp3";
    AnimalSoundPath[5] = "Sound/dog_german_shepherd_dog_barking_inside_kennel.mp3";
    AnimalSoundPath[6] = "Sound/tiger_siberian_tiger_single_growl_and_snarl.mp3";
    AnimalSoundPath[7] = "Sound/wild_cat_hissing_with_single_swat.mp3";

    pAnimalNearByTimer = new QTimer;
    pItemFoundTimer = new QTimer;

    connect(pAnimalNearByTimer, SIGNAL(timeout()), this, SLOT(AnimalEvent()));
    connect(pItemFoundTimer, SIGNAL(timeout()), this, SLOT(PickUpEvent()));
}

void MyEvent::start()
{
    setPick_count(0);

    pAnimalNearByTimer->start(30*multiplier);
    pItemFoundTimer->start(45*multiplier);
}

void MyEvent::stop()
{
    pAnimalNearByTimer->stop();
    pItemFoundTimer->stop();
}

void MyEvent::finalizePickCount()
{
    theApp.facebookclient->setFound(theApp.facebookclient->m_nFound + m_nPickCount);

    QString sID = theApp.facebookclient->m_sId;
    QString sName = theApp.facebookclient->m_sName;
    int nFound = theApp.facebookclient->m_nFound;
    int nLogin = theApp.notificationclient->loginFlag().toInt();

    theApp.pLocalDB->UpdateUser( sID, sName, nFound, nLogin );
}

void MyEvent::startRandomAnimalTimer()
{
    int low = 15;
    int high = 45;

    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());

    int nNum = qrand()%((high + 1) - low) + low;

    pAnimalNearByTimer->start(nNum*multiplier);
}

void MyEvent::startRandomPickUpTimer()
{
    int low = 120;
    int high = 240;

    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());

    int nNum = qrand()%((high + 1) - low) + low;

    pItemFoundTimer->start(nNum*multiplier);
}


int MyEvent::pick_count() const
{
    return m_nPickCount;
}
void MyEvent::setPick_count(const int &a)
{
    if( a != m_nPickCount){
        m_nPickCount = a;
        emit pick_countChanged();
    }
}

void MyEvent::AnimalEvent()
{  
    int low = 0;
    int high = 7;

    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());

    int nNum = qrand()%((high + 1) - low) + low;

//    QMediaPlayer *player = new QMediaPlayer;

//    player->setMedia(QUrl::fromLocalFile(AnimalSoundPath[nNum]));
//    player->setVolume(50);
//    player->play();

    theApp.notificationclient->androidPlayMusic(nNum);

    pAnimalNearByTimer->stop();
    startRandomAnimalTimer();
}

void MyEvent::PickUpEvent()
{
//    QMediaPlayer *player = new QMediaPlayer;

//    player->setMedia(QUrl::fromLocalFile("Sound/casino_slot_machine_bell_or_alarm_ring_win_jackpot_loops_.mp3"));
//    player->setVolume(50);
//    player->play();

    theApp.notificationclient->androidPlayMusic(8);
    int pick = m_nPickCount;
    pick++;
    setPick_count(pick);

    pItemFoundTimer->stop();
    startRandomPickUpTimer();
}
