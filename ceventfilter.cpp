#include "ceventfilter.h"
#include <QDebug>
#include <QEvent>

CEventFilter::CEventFilter(QObject *parent) :
    QObject(parent)
{
    m_timeOutMSec = 60000 * 5;
    m_eventTimer = new QTimer;
    m_eventTimer->setInterval(m_timeOutMSec);
    connect(m_eventTimer, SIGNAL(timeout()), this, SLOT(onTimerTimeOut()));

    m_eventTimer->start(m_timeOutMSec);
}

CEventFilter::~CEventFilter()
{
    delete m_eventTimer;
}


bool CEventFilter::eventFilter(QObject *ob, QEvent *e)
{
    if(e->type()==QEvent::MouseMove||e->type()==QEvent::MouseButtonPress
            ||e->type()==QEvent::MouseButtonRelease)//  判断如果是鼠标移动事件
    {
        if(m_eventTimer->isActive())
        {
            m_eventTimer->stop();
            m_eventTimer->start();
        }
        if(lowPower_flag == true)
        {
            lowPower_flag = false;
#ifdef ARM
            system("echo 0 > /sys/class/leds/user-lcd/brightness");//亮屏
#else
            qDebug()<<"lowPower off";
#endif
        }
    }

    return QObject::eventFilter(ob,e);
}

void CEventFilter::onTimerTimeOut()
{
    lowPower_flag = true;
#ifdef ARM
        system("echo 1 > /sys/class/leds/user-lcd/brightness");//息屏
#else
        qDebug()<<"lowPower on";
#endif
}

CEventFilter *CEventFilter::m_instance = NULL;
CEventFilter *CEventFilter::getInstance()
{
    if ( m_instance == NULL )
    {
        m_instance = new CEventFilter;
    }

    return m_instance;
}
