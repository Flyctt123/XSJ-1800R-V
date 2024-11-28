#include "mainwindow.h"
#include <qdesktopwidget.h>
#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsProxyWidget>

#define Screen_Overturn 0//屏幕旋转

#if (Screen_Overturn==0)
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    CEventFilter *m_pEventFilter = CEventFilter::getInstance();//息屏检测

    w.setFixedSize(480,272);
    QDesktopWidget *desktop = QApplication::desktop();
    w.move((desktop->width() - w.width())/ 2, (desktop->height() - w.height()) /2);
    w.installEventFilter(m_pEventFilter);
    w.show();

    return a.exec();
}

# else
//屏幕旋转180°
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    QGraphicsScene *scene = new QGraphicsScene;
    QGraphicsProxyWidget *w1 = scene->addWidget(&w);
    w1->setRotation(180);  //旋转180,  参数可选0,90,180,270
    QGraphicsView *view = new QGraphicsView(scene);
    view->setWindowFlags(Qt::FramelessWindowHint);
    view->centerOn(0,0);
    view->resize(480,272); //显示器尺寸
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->show();
    return a.exec();
}
#endif
