//
// Created by xiabi on 2020/10/31.
//

#ifndef SIXGOD_MAIN_H
#define SIXGOD_MAIN_H

#define CAMERALESS
//#define THREAD0TEST
//#define THREAD1TEST
#define ALLTEST
#define THREAD0OUT
#define THREAD1OUT
#define THREAD0FEEDBACK
#define NUM_THREADS 1

#define PointPerCycle 4000 //每周期点云点数量
static const char* device="/dev/spidev0.1";
class GodState_t{
public:
    int t;
    double X;
    double Y;
    double Xai;
    double P[2][2];
    double K[2];
    double bias;
};
class HistoryLinkedList_t{
public:
    HistoryLinkedList_t* next;
    int t;
    short v_PWM=1000;
    short delta_PWM=1380;
    double ax=0;
    double ay=0;
    double omegaz;
};
void* thread0(void* arg);
void* thread1(void* arg);
//以下 异常返回0，否则其他

/// Fuse the input sensor and control information.
/// Output the new estimation of position
///
/// \param Data         The current sensor and control measurement.
/// \param My_GodState  The current state of AGV
/// \return 0 for a success, -1 otherwise.
int My_KalmanFilter(HistoryLinkedList_t &Data,GodState_t& My_GodState);

/// Stop the thread 0 for 10ms second, make sure
/// the interval of each operation is the same.
/// \return 0 for a success, -1 otherwise.
int GodSleep();

/// Comunicate with the lower level board,
/// update its' control and grab the sensor information from it.
/// \param History      The current sensor and control measurement.
/// \return 0 for a success, -1 otherwise.
int GodUpdate(HistoryLinkedList_t &History);

/// Interface of Control, for now, a simple
/// pid is implemented for demo.
/// \param mGodState    The current state of AGV
/// \param mHistoryLinkedList  The current sensor and control measurement.
/// \return 0 for a success, -1 otherwise.
int Control(const GodState_t &mGodState, HistoryLinkedList_t &mHistoryLinkedList);
#endif //SIXGOD_MAIN_H
