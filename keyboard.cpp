#include "keyboard.h"
#include "ui_keyboard.h"
#include "mainwindow.h"
#include <QDebug>
#include <QMessageBox>
#include <QFile>

bool KeyBoard_Code=false,keyBoard_flag=false;

KeyBoard::KeyBoard(QWidget *parent, QLineEdit *LineEdit) :
    QDialog(parent),
    ui(new Ui::KeyBoard)
{
    ui->setupUi(this);

    this->setWindowTitle( tr("键盘") );
    keyBoard_flag=true;

    ui->label->lower();
    isCap = false;
    outputStr = "";
    lineEdit = LineEdit;
    pageAll = 0;
    curPage = 0;
    current_txt = lineEdit->text();
    QButtonGroup *numGroup = new QButtonGroup();

    numGroup->addButton(ui->num_0_Bt, 0);
    numGroup->addButton(ui->num_1_Bt, 1);
    numGroup->addButton(ui->num_2_Bt, 2);
    numGroup->addButton(ui->num_3_Bt, 3);
    numGroup->addButton(ui->num_4_Bt, 4);
    numGroup->addButton(ui->num_5_Bt, 5);
    numGroup->addButton(ui->num_6_Bt, 6);
    numGroup->addButton(ui->num_7_Bt, 7);
    numGroup->addButton(ui->num_8_Bt, 8);
    numGroup->addButton(ui->num_9_Bt, 9);
    numGroup->addButton(ui->dian, 10);
    connect( numGroup, SIGNAL(buttonClicked(QAbstractButton*)),
            this, SLOT(slot_numClicked(QAbstractButton*)) );

    QButtonGroup *carGroup = new QButtonGroup();
    connect( carGroup, SIGNAL(buttonClicked(QAbstractButton*)),
            this, SLOT(slot_carClicked(QAbstractButton*)) );
    carList = carGroup->buttons();

    QButtonGroup *hanziGroup = new QButtonGroup();
    connect( hanziGroup, SIGNAL(buttonClicked(QAbstractButton*)),
             this, SLOT(slot_hanziBtClicked(QAbstractButton*)));
    zhList = hanziGroup->buttons();
    ui->showLb->setText(lineEdit->text());

    // 加载字库
    //loadziku();

}

KeyBoard::~KeyBoard()
{
    delete ui;
}

/* 加载字库 */
void KeyBoard::loadziku()
{
    // 加载字库文件
    QFile zikuFile(":/ziku1/ziku.dat");
    if ( !zikuFile.open(QIODevice::ReadOnly | QIODevice::Text) )
    {
        QMessageBox::information(this, "键盘字库",
                                 "加载字库文件错误，中文输入不可用！", QMessageBox::Ok);
        //ui->zh_us_Bt->setEnabled(false);
        return;
    }

    QString zikuAll;

    while (true)
    {
        char buf[1024];
        qint64 len = zikuFile.readLine(buf, sizeof(buf));
        if (len <= 0)
        {
            break;
        }
        QString str = QString::fromLocal8Bit(buf);
        zikuAll += str;
    }

    zikuList = zikuAll.split("\n");      //用QString的split函数将字库文件划分成一段一段，每个拼音对应一段字库
    zikuFile.close();
}

/* 查找中文 */
QString KeyBoard::findChinese(QString PinYin)
{
    QStringList lst;
    QString Line;
    QString returnChinese;

    for(int i = 0; i < zikuList.count(); i++)//m_srf.count()QStringList有多少段
    {
        Line = zikuList.at(i);
        if (Line.isEmpty() || PinYin.isEmpty()) continue;

        lst = Line.split(",");
        if (QString::compare(lst.at(0), PinYin, Qt::CaseInsensitive) == 0)
        {
            returnChinese =  lst.at(1);
        }
    }

    // 字符串分割成10个10个一组
    pageList.clear();
    int len = returnChinese.length();
    if (len > 0)
    {
        pageAll = len % 10 == 0 ? len/10 : (len/10) + 1;
        QString str;
        for (int i = 1; i <= len; i++)
        {
            str += returnChinese.at(i-1);
            if (i % 10 == 0 && i != 0)
            {
                pageList << str;
                str = "";
            }
        }

        if (len % 10 != 0)
        {
            pageList << returnChinese.right(len % 10);
        }
    }//if

    return returnChinese;
}

/* 汉字按钮的设置 */
void KeyBoard::setHanziBt()
{

    for (int i = 0; i < 10; i++)
    {
        zhList.at(i)->setText("");
    }

    QString PinYin = ui->showLb->text();
    ui->showLb->raise();
    QString ChineseStr = findChinese(PinYin);

    if (ChineseStr != "")
    {
        int ChineseStrCount = ChineseStr.length();
        // 10字以内汉字个数
        if (ChineseStrCount <= 10)
        {
            for (int i = 0; i < ChineseStrCount; i++)
            {
                ((QPushButton *)zhList.at(i))->setText(ChineseStr.at(i));
            }
            return;
        }

        // 大于十字
        for (int i = 0; i < 10; i++)
        {
            ((QPushButton *)zhList.at(i))->setText(ChineseStr.at(i));
        }
    }//if
}

/* 数字键盘点击 */
void KeyBoard::slot_numClicked(QAbstractButton *bt)
{
    QPushButton *tmpBt = (QPushButton *)bt;
    QString str = lineEdit->text();
    str.append(tmpBt->text());
    lineEdit->setText(str);

    QString str_1 = ui->showLb->text();
    str_1.append(tmpBt->text());
    ui->showLb->setText(str_1);
    ui->showLb->raise();
}

/* 字母键点击 */
void KeyBoard::slot_carClicked(QAbstractButton *bt)
{
    QPushButton *tmp = (QPushButton *)bt;
    QString str_1 = ui->showLb->text();
    str_1.append(tmp->text());
    ui->showLb->setText(str_1);
    ui->showLb->raise();
}

/* 十个中文按钮点击 */
void KeyBoard::slot_hanziBtClicked(QAbstractButton *bt)
{
    QPushButton *tmp = (QPushButton *)bt;
    QString str = lineEdit->text();
    str.append(tmp->text());
    lineEdit->setText(str);
    ui->showLb->setText("");
    ui->showLb->raise();
    for (int i = 0; i < 10; i++)
    {
        zhList.at(i)->setText("");
    }
}

/* 退格键 */
void KeyBoard::on_delBt_clicked()
{
    QString tmp = ui->showLb->text();
    ui->showLb->setText(tmp.left(tmp.length() - 1));
    ui->showLb->raise();
    if (1)
    {
        QString str = lineEdit->text();
        lineEdit->setText(str.left(str.length() - 1));
    }
}

void KeyBoard::on_closeBt_clicked()
{
    KeyBoard_Code=false;
    keyBoard_flag=false;
    delete this;
}

void KeyBoard::on_backBt_clicked()
{
    lineEdit->setText(current_txt);
    KeyBoard_Code=false;
    keyBoard_flag=false;
    delete this;
}

void KeyBoard::on_num_8_Bt_clicked()
{

}
