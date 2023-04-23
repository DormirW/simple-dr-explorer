#ifndef STATE_H
#define STATE_H

#include <QMainWindow>

class State
{
public:
    State();
    QImage im;
    double hrate,wrate,angle,srate;
    bool iss,isr,ish,isw,isi,ise;
    int mirrortype;
    ushort lowerbound,upperbound;
    QString fname;//文件路径
};

#endif // STATE_H
