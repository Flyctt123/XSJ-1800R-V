#ifndef CEVENTFILTER_H
#define CEVENTFILTER_H

#include <QObject>
#include <QTimer>
#include "mainwindow.h"

class CEventFilter : public QObject
{
    Q_OBJECT
protected:
    explicit CEventFilter(QObject *parent = 0);
    ~CEventFilter();
    static CEventFilter *m_instance;
    virtual bool eventFilter(QObject *ob, QEvent *e);

public:
    static CEventFilter *getInstance();
    bool lowPower_flag = false;

public slots:
    void onTimerTimeOut();

private:
    int m_timeOutMSec;
    QTimer *m_eventTimer;
};

#endif // CEVENTFILTER_H
