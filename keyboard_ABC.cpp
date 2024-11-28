#include "keyboard_ABC.h"
#include "ui_keyboard_ABC.h"
#include "mainwindow.h"
#include <QDebug>
#include <QMessageBox>
#include <QFile>

bool KeyBoard_ABC_Code=false,keyBoard_ABC_flag=false;

KeyBoard_ABC::KeyBoard_ABC(QWidget *parent, QLineEdit *LineEdit) :
    QDialog(parent),
    ui(new Ui::KeyBoard_ABC)
{
    ui->setupUi(this);

    this->setWindowTitle( tr("键盘") );
    keyBoard_ABC_flag=true;
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
    connect( numGroup, SIGNAL(buttonClicked(QAbstractButton*)),
            this, SLOT(slot_numClicked(QAbstractButton*)) );

    QButtonGroup *carGroup = new QButtonGroup();
    carGroup->addButton(ui->q_Bt, 1);
    carGroup->addButton(ui->w_Bt, 2);
    carGroup->addButton(ui->e_Bt, 3);
    carGroup->addButton(ui->r_Bt, 4);
    carGroup->addButton(ui->t_Bt, 5);
    carGroup->addButton(ui->y_Bt, 6);
    carGroup->addButton(ui->u_Bt, 7);
    carGroup->addButton(ui->i_Bt, 8);
    carGroup->addButton(ui->o_Bt, 9);
    carGroup->addButton(ui->p_Bt, 10);
    carGroup->addButton(ui->a_Bt, 11);
    carGroup->addButton(ui->s_Bt, 12);
    carGroup->addButton(ui->d_Bt, 13);
    carGroup->addButton(ui->f_Bt, 14);
    carGroup->addButton(ui->g_Bt, 15);
    carGroup->addButton(ui->h_Bt, 16);
    carGroup->addButton(ui->j_Bt, 17);
    carGroup->addButton(ui->k_Bt, 18);
    carGroup->addButton(ui->l_Bt, 19);
    carGroup->addButton(ui->z_Bt, 20);
    carGroup->addButton(ui->x_Bt, 21);
    carGroup->addButton(ui->c_Bt, 22);
    carGroup->addButton(ui->v_Bt, 23);
    carGroup->addButton(ui->b_Bt, 24);
    carGroup->addButton(ui->n_Bt, 25);
    carGroup->addButton(ui->m_Bt, 26);
    carGroup->addButton(ui->Bt_hengxian, 27);
    carGroup->addButton(ui->Bt_dian, 28);
    connect( carGroup, SIGNAL(buttonClicked(QAbstractButton*)),
            this, SLOT(slot_carClicked(QAbstractButton*)) );
    carList = carGroup->buttons();

    QButtonGroup *hanziGroup = new QButtonGroup();
    connect( hanziGroup, SIGNAL(buttonClicked(QAbstractButton*)),
             this, SLOT(slot_hanziBtClicked(QAbstractButton*)));
    zhList = hanziGroup->buttons();
    ui->showLb->setText(lineEdit->text());
}

KeyBoard_ABC::~KeyBoard_ABC()
{
    delete ui;
}

/* 加载字库 */
void KeyBoard_ABC::loadziku()
{

}

/* 查找中文 */
QString KeyBoard_ABC::findChinese(QString PinYin)
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
void KeyBoard_ABC::setHanziBt()
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

/* 大小写转换 */
void KeyBoard_ABC::on_caps_Bt_clicked()
{
    if (isCap == false) // 小写状态
    {
        for (int i = 0; i < carList.size(); i++)
        {
            QString upper = carList.at(i)->text().toUpper();
            carList.at(i)->setText(upper);
        }
        isCap = true;
        return;
    }
    else // 大写状态
    {
        for (int i = 0; i < carList.size(); i++)
        {
            QString lower = carList.at(i)->text().toLower();
            carList.at(i)->setText(lower);
        }
        isCap = false;
        return;
    }
}


/* 数字键盘点击 */
void KeyBoard_ABC::slot_numClicked(QAbstractButton *bt)
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
void KeyBoard_ABC::slot_carClicked(QAbstractButton *bt)
{
    QPushButton *tmp = (QPushButton *)bt;
    QString str_1 = ui->showLb->text();
    str_1.append(tmp->text());
    ui->showLb->setText(str_1);
    ui->showLb->raise();
    if (1)
    {
        QString str_2 = lineEdit->text();
        str_2.append(tmp->text());
        lineEdit->setText(str_2);
    }
}

/* 十个中文按钮点击 */
void KeyBoard_ABC::slot_hanziBtClicked(QAbstractButton *bt)
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
void KeyBoard_ABC::on_delBt_clicked()
{
    QString tmp = ui->showLb->text();
    ui->showLb->setText(tmp.left(tmp.length() - 1));

    if (1)
    {
        QString str = lineEdit->text();
        lineEdit->setText(str.left(str.length() - 1));
    }
}

void KeyBoard_ABC::on_closeBt_clicked()
{
    KeyBoard_ABC_Code=false;
    keyBoard_ABC_flag=false;
    delete this;
}

void KeyBoard_ABC::on_backBt_clicked()
{
    lineEdit->setText(current_txt);
    KeyBoard_ABC_Code=false;
    keyBoard_ABC_flag=false;
    delete this;
}
