/********************************************************************************
** Form generated from reading UI file 'keyboard_ABC.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_KEYBOARD_ABC_H
#define UI_KEYBOARD_ABC_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_KeyBoard_ABC
{
public:
    QLabel *label;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QPushButton *e_Bt;
    QPushButton *num_9_Bt;
    QPushButton *num_4_Bt;
    QPushButton *k_Bt;
    QPushButton *f_Bt;
    QPushButton *y_Bt;
    QPushButton *h_Bt;
    QPushButton *q_Bt;
    QPushButton *num_6_Bt;
    QPushButton *g_Bt;
    QPushButton *i_Bt;
    QPushButton *num_1_Bt;
    QPushButton *s_Bt;
    QPushButton *w_Bt;
    QPushButton *l_Bt;
    QPushButton *Bt_dian;
    QPushButton *u_Bt;
    QPushButton *a_Bt;
    QPushButton *d_Bt;
    QPushButton *num_0_Bt;
    QPushButton *num_5_Bt;
    QPushButton *num_8_Bt;
    QPushButton *o_Bt;
    QPushButton *num_7_Bt;
    QPushButton *j_Bt;
    QPushButton *r_Bt;
    QPushButton *num_3_Bt;
    QPushButton *p_Bt;
    QPushButton *t_Bt;
    QPushButton *num_2_Bt;
    QPushButton *Bt_hengxian;
    QPushButton *delBt;
    QPushButton *closeBt;
    QPushButton *caps_Bt;
    QPushButton *z_Bt;
    QPushButton *x_Bt;
    QPushButton *c_Bt;
    QPushButton *v_Bt;
    QPushButton *b_Bt;
    QPushButton *n_Bt;
    QPushButton *m_Bt;
    QPushButton *spaceBt;
    QLabel *showLb;
    QPushButton *backBt;

    void setupUi(QDialog *KeyBoard_ABC)
    {
        if (KeyBoard_ABC->objectName().isEmpty())
            KeyBoard_ABC->setObjectName(QString::fromUtf8("KeyBoard_ABC"));
        KeyBoard_ABC->setEnabled(true);
        KeyBoard_ABC->resize(681, 408);
        KeyBoard_ABC->setStyleSheet(QString::fromUtf8(""));
        label = new QLabel(KeyBoard_ABC);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(1, 1, 476, 150));
        QFont font;
        font.setPointSize(10);
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 62, 91);"));
        layoutWidget = new QWidget(KeyBoard_ABC);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 461, 131));
        layoutWidget->setFont(font);
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setHorizontalSpacing(3);
        gridLayout->setVerticalSpacing(1);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        e_Bt = new QPushButton(layoutWidget);
        e_Bt->setObjectName(QString::fromUtf8("e_Bt"));
        e_Bt->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(e_Bt->sizePolicy().hasHeightForWidth());
        e_Bt->setSizePolicy(sizePolicy);
        QFont font1;
        font1.setFamily(QString::fromUtf8("Times New Roman"));
        font1.setPointSize(10);
        e_Bt->setFont(font1);

        gridLayout->addWidget(e_Bt, 1, 2, 1, 1);

        num_9_Bt = new QPushButton(layoutWidget);
        num_9_Bt->setObjectName(QString::fromUtf8("num_9_Bt"));
        num_9_Bt->setEnabled(true);
        sizePolicy.setHeightForWidth(num_9_Bt->sizePolicy().hasHeightForWidth());
        num_9_Bt->setSizePolicy(sizePolicy);
        num_9_Bt->setFont(font1);

        gridLayout->addWidget(num_9_Bt, 3, 12, 1, 1);

        num_4_Bt = new QPushButton(layoutWidget);
        num_4_Bt->setObjectName(QString::fromUtf8("num_4_Bt"));
        num_4_Bt->setEnabled(true);
        sizePolicy.setHeightForWidth(num_4_Bt->sizePolicy().hasHeightForWidth());
        num_4_Bt->setSizePolicy(sizePolicy);
        num_4_Bt->setFont(font1);

        gridLayout->addWidget(num_4_Bt, 2, 10, 1, 1);

        k_Bt = new QPushButton(layoutWidget);
        k_Bt->setObjectName(QString::fromUtf8("k_Bt"));
        k_Bt->setEnabled(true);
        sizePolicy.setHeightForWidth(k_Bt->sizePolicy().hasHeightForWidth());
        k_Bt->setSizePolicy(sizePolicy);
        k_Bt->setFont(font1);

        gridLayout->addWidget(k_Bt, 2, 8, 1, 1);

        f_Bt = new QPushButton(layoutWidget);
        f_Bt->setObjectName(QString::fromUtf8("f_Bt"));
        f_Bt->setEnabled(true);
        sizePolicy.setHeightForWidth(f_Bt->sizePolicy().hasHeightForWidth());
        f_Bt->setSizePolicy(sizePolicy);
        f_Bt->setFont(font1);

        gridLayout->addWidget(f_Bt, 2, 4, 1, 1);

        y_Bt = new QPushButton(layoutWidget);
        y_Bt->setObjectName(QString::fromUtf8("y_Bt"));
        y_Bt->setEnabled(true);
        sizePolicy.setHeightForWidth(y_Bt->sizePolicy().hasHeightForWidth());
        y_Bt->setSizePolicy(sizePolicy);
        y_Bt->setFont(font1);

        gridLayout->addWidget(y_Bt, 1, 5, 1, 1);

        h_Bt = new QPushButton(layoutWidget);
        h_Bt->setObjectName(QString::fromUtf8("h_Bt"));
        h_Bt->setEnabled(true);
        sizePolicy.setHeightForWidth(h_Bt->sizePolicy().hasHeightForWidth());
        h_Bt->setSizePolicy(sizePolicy);
        h_Bt->setFont(font1);

        gridLayout->addWidget(h_Bt, 2, 6, 1, 1);

        q_Bt = new QPushButton(layoutWidget);
        q_Bt->setObjectName(QString::fromUtf8("q_Bt"));
        q_Bt->setEnabled(true);
        sizePolicy.setHeightForWidth(q_Bt->sizePolicy().hasHeightForWidth());
        q_Bt->setSizePolicy(sizePolicy);
        q_Bt->setFont(font1);

        gridLayout->addWidget(q_Bt, 1, 0, 1, 1);

        num_6_Bt = new QPushButton(layoutWidget);
        num_6_Bt->setObjectName(QString::fromUtf8("num_6_Bt"));
        num_6_Bt->setEnabled(true);
        sizePolicy.setHeightForWidth(num_6_Bt->sizePolicy().hasHeightForWidth());
        num_6_Bt->setSizePolicy(sizePolicy);
        num_6_Bt->setFont(font1);

        gridLayout->addWidget(num_6_Bt, 2, 12, 1, 1);

        g_Bt = new QPushButton(layoutWidget);
        g_Bt->setObjectName(QString::fromUtf8("g_Bt"));
        g_Bt->setEnabled(true);
        sizePolicy.setHeightForWidth(g_Bt->sizePolicy().hasHeightForWidth());
        g_Bt->setSizePolicy(sizePolicy);
        g_Bt->setFont(font1);

        gridLayout->addWidget(g_Bt, 2, 5, 1, 1);

        i_Bt = new QPushButton(layoutWidget);
        i_Bt->setObjectName(QString::fromUtf8("i_Bt"));
        i_Bt->setEnabled(true);
        sizePolicy.setHeightForWidth(i_Bt->sizePolicy().hasHeightForWidth());
        i_Bt->setSizePolicy(sizePolicy);
        i_Bt->setFont(font1);

        gridLayout->addWidget(i_Bt, 1, 7, 1, 1);

        num_1_Bt = new QPushButton(layoutWidget);
        num_1_Bt->setObjectName(QString::fromUtf8("num_1_Bt"));
        num_1_Bt->setEnabled(true);
        sizePolicy.setHeightForWidth(num_1_Bt->sizePolicy().hasHeightForWidth());
        num_1_Bt->setSizePolicy(sizePolicy);
        num_1_Bt->setFont(font1);

        gridLayout->addWidget(num_1_Bt, 1, 10, 1, 1);

        s_Bt = new QPushButton(layoutWidget);
        s_Bt->setObjectName(QString::fromUtf8("s_Bt"));
        s_Bt->setEnabled(true);
        sizePolicy.setHeightForWidth(s_Bt->sizePolicy().hasHeightForWidth());
        s_Bt->setSizePolicy(sizePolicy);
        s_Bt->setFont(font1);

        gridLayout->addWidget(s_Bt, 2, 2, 1, 1);

        w_Bt = new QPushButton(layoutWidget);
        w_Bt->setObjectName(QString::fromUtf8("w_Bt"));
        w_Bt->setEnabled(true);
        sizePolicy.setHeightForWidth(w_Bt->sizePolicy().hasHeightForWidth());
        w_Bt->setSizePolicy(sizePolicy);
        w_Bt->setFont(font1);

        gridLayout->addWidget(w_Bt, 1, 1, 1, 1);

        l_Bt = new QPushButton(layoutWidget);
        l_Bt->setObjectName(QString::fromUtf8("l_Bt"));
        l_Bt->setEnabled(true);
        sizePolicy.setHeightForWidth(l_Bt->sizePolicy().hasHeightForWidth());
        l_Bt->setSizePolicy(sizePolicy);
        l_Bt->setFont(font1);

        gridLayout->addWidget(l_Bt, 2, 9, 1, 1);

        Bt_dian = new QPushButton(layoutWidget);
        Bt_dian->setObjectName(QString::fromUtf8("Bt_dian"));
        Bt_dian->setEnabled(true);
        sizePolicy.setHeightForWidth(Bt_dian->sizePolicy().hasHeightForWidth());
        Bt_dian->setSizePolicy(sizePolicy);
        Bt_dian->setFont(font1);

        gridLayout->addWidget(Bt_dian, 0, 11, 1, 1);

        u_Bt = new QPushButton(layoutWidget);
        u_Bt->setObjectName(QString::fromUtf8("u_Bt"));
        u_Bt->setEnabled(true);
        sizePolicy.setHeightForWidth(u_Bt->sizePolicy().hasHeightForWidth());
        u_Bt->setSizePolicy(sizePolicy);
        u_Bt->setFont(font1);

        gridLayout->addWidget(u_Bt, 1, 6, 1, 1);

        a_Bt = new QPushButton(layoutWidget);
        a_Bt->setObjectName(QString::fromUtf8("a_Bt"));
        a_Bt->setEnabled(true);
        sizePolicy.setHeightForWidth(a_Bt->sizePolicy().hasHeightForWidth());
        a_Bt->setSizePolicy(sizePolicy);
        a_Bt->setFont(font1);

        gridLayout->addWidget(a_Bt, 2, 1, 1, 1);

        d_Bt = new QPushButton(layoutWidget);
        d_Bt->setObjectName(QString::fromUtf8("d_Bt"));
        d_Bt->setEnabled(true);
        sizePolicy.setHeightForWidth(d_Bt->sizePolicy().hasHeightForWidth());
        d_Bt->setSizePolicy(sizePolicy);
        d_Bt->setFont(font1);

        gridLayout->addWidget(d_Bt, 2, 3, 1, 1);

        num_0_Bt = new QPushButton(layoutWidget);
        num_0_Bt->setObjectName(QString::fromUtf8("num_0_Bt"));
        num_0_Bt->setEnabled(true);
        sizePolicy.setHeightForWidth(num_0_Bt->sizePolicy().hasHeightForWidth());
        num_0_Bt->setSizePolicy(sizePolicy);
        num_0_Bt->setFont(font1);

        gridLayout->addWidget(num_0_Bt, 0, 12, 1, 1);

        num_5_Bt = new QPushButton(layoutWidget);
        num_5_Bt->setObjectName(QString::fromUtf8("num_5_Bt"));
        num_5_Bt->setEnabled(true);
        sizePolicy.setHeightForWidth(num_5_Bt->sizePolicy().hasHeightForWidth());
        num_5_Bt->setSizePolicy(sizePolicy);
        num_5_Bt->setFont(font1);

        gridLayout->addWidget(num_5_Bt, 2, 11, 1, 1);

        num_8_Bt = new QPushButton(layoutWidget);
        num_8_Bt->setObjectName(QString::fromUtf8("num_8_Bt"));
        num_8_Bt->setEnabled(true);
        sizePolicy.setHeightForWidth(num_8_Bt->sizePolicy().hasHeightForWidth());
        num_8_Bt->setSizePolicy(sizePolicy);
        num_8_Bt->setFont(font1);

        gridLayout->addWidget(num_8_Bt, 3, 11, 1, 1);

        o_Bt = new QPushButton(layoutWidget);
        o_Bt->setObjectName(QString::fromUtf8("o_Bt"));
        o_Bt->setEnabled(true);
        sizePolicy.setHeightForWidth(o_Bt->sizePolicy().hasHeightForWidth());
        o_Bt->setSizePolicy(sizePolicy);
        o_Bt->setFont(font1);

        gridLayout->addWidget(o_Bt, 1, 8, 1, 1);

        num_7_Bt = new QPushButton(layoutWidget);
        num_7_Bt->setObjectName(QString::fromUtf8("num_7_Bt"));
        num_7_Bt->setEnabled(true);
        sizePolicy.setHeightForWidth(num_7_Bt->sizePolicy().hasHeightForWidth());
        num_7_Bt->setSizePolicy(sizePolicy);
        num_7_Bt->setFont(font1);

        gridLayout->addWidget(num_7_Bt, 3, 10, 1, 1);

        j_Bt = new QPushButton(layoutWidget);
        j_Bt->setObjectName(QString::fromUtf8("j_Bt"));
        j_Bt->setEnabled(true);
        sizePolicy.setHeightForWidth(j_Bt->sizePolicy().hasHeightForWidth());
        j_Bt->setSizePolicy(sizePolicy);
        j_Bt->setFont(font1);

        gridLayout->addWidget(j_Bt, 2, 7, 1, 1);

        r_Bt = new QPushButton(layoutWidget);
        r_Bt->setObjectName(QString::fromUtf8("r_Bt"));
        r_Bt->setEnabled(true);
        sizePolicy.setHeightForWidth(r_Bt->sizePolicy().hasHeightForWidth());
        r_Bt->setSizePolicy(sizePolicy);
        r_Bt->setFont(font1);

        gridLayout->addWidget(r_Bt, 1, 3, 1, 1);

        num_3_Bt = new QPushButton(layoutWidget);
        num_3_Bt->setObjectName(QString::fromUtf8("num_3_Bt"));
        num_3_Bt->setEnabled(true);
        sizePolicy.setHeightForWidth(num_3_Bt->sizePolicy().hasHeightForWidth());
        num_3_Bt->setSizePolicy(sizePolicy);
        num_3_Bt->setFont(font1);

        gridLayout->addWidget(num_3_Bt, 1, 12, 1, 1);

        p_Bt = new QPushButton(layoutWidget);
        p_Bt->setObjectName(QString::fromUtf8("p_Bt"));
        p_Bt->setEnabled(true);
        sizePolicy.setHeightForWidth(p_Bt->sizePolicy().hasHeightForWidth());
        p_Bt->setSizePolicy(sizePolicy);
        p_Bt->setFont(font1);

        gridLayout->addWidget(p_Bt, 1, 9, 1, 1);

        t_Bt = new QPushButton(layoutWidget);
        t_Bt->setObjectName(QString::fromUtf8("t_Bt"));
        t_Bt->setEnabled(true);
        sizePolicy.setHeightForWidth(t_Bt->sizePolicy().hasHeightForWidth());
        t_Bt->setSizePolicy(sizePolicy);
        t_Bt->setFont(font1);

        gridLayout->addWidget(t_Bt, 1, 4, 1, 1);

        num_2_Bt = new QPushButton(layoutWidget);
        num_2_Bt->setObjectName(QString::fromUtf8("num_2_Bt"));
        num_2_Bt->setEnabled(true);
        sizePolicy.setHeightForWidth(num_2_Bt->sizePolicy().hasHeightForWidth());
        num_2_Bt->setSizePolicy(sizePolicy);
        num_2_Bt->setFont(font1);

        gridLayout->addWidget(num_2_Bt, 1, 11, 1, 1);

        Bt_hengxian = new QPushButton(layoutWidget);
        Bt_hengxian->setObjectName(QString::fromUtf8("Bt_hengxian"));
        Bt_hengxian->setEnabled(true);
        sizePolicy.setHeightForWidth(Bt_hengxian->sizePolicy().hasHeightForWidth());
        Bt_hengxian->setSizePolicy(sizePolicy);
        Bt_hengxian->setFont(font1);

        gridLayout->addWidget(Bt_hengxian, 2, 0, 1, 1);

        delBt = new QPushButton(layoutWidget);
        delBt->setObjectName(QString::fromUtf8("delBt"));
        delBt->setEnabled(true);
        sizePolicy.setHeightForWidth(delBt->sizePolicy().hasHeightForWidth());
        delBt->setSizePolicy(sizePolicy);
        QFont font2;
        font2.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font2.setPointSize(10);
        delBt->setFont(font2);

        gridLayout->addWidget(delBt, 0, 9, 1, 2);

        closeBt = new QPushButton(layoutWidget);
        closeBt->setObjectName(QString::fromUtf8("closeBt"));
        closeBt->setEnabled(true);
        sizePolicy.setHeightForWidth(closeBt->sizePolicy().hasHeightForWidth());
        closeBt->setSizePolicy(sizePolicy);
        closeBt->setFont(font2);

        gridLayout->addWidget(closeBt, 0, 7, 1, 2);

        caps_Bt = new QPushButton(layoutWidget);
        caps_Bt->setObjectName(QString::fromUtf8("caps_Bt"));
        caps_Bt->setEnabled(true);
        sizePolicy.setHeightForWidth(caps_Bt->sizePolicy().hasHeightForWidth());
        caps_Bt->setSizePolicy(sizePolicy);
        QFont font3;
        font3.setFamily(QString::fromUtf8("Times New Roman"));
        font3.setPointSize(8);
        font3.setBold(false);
        font3.setWeight(50);
        caps_Bt->setFont(font3);

        gridLayout->addWidget(caps_Bt, 3, 0, 1, 1);

        z_Bt = new QPushButton(layoutWidget);
        z_Bt->setObjectName(QString::fromUtf8("z_Bt"));
        z_Bt->setEnabled(true);
        sizePolicy.setHeightForWidth(z_Bt->sizePolicy().hasHeightForWidth());
        z_Bt->setSizePolicy(sizePolicy);
        z_Bt->setFont(font1);

        gridLayout->addWidget(z_Bt, 3, 1, 1, 1);

        x_Bt = new QPushButton(layoutWidget);
        x_Bt->setObjectName(QString::fromUtf8("x_Bt"));
        x_Bt->setEnabled(true);
        sizePolicy.setHeightForWidth(x_Bt->sizePolicy().hasHeightForWidth());
        x_Bt->setSizePolicy(sizePolicy);
        x_Bt->setFont(font1);

        gridLayout->addWidget(x_Bt, 3, 2, 1, 1);

        c_Bt = new QPushButton(layoutWidget);
        c_Bt->setObjectName(QString::fromUtf8("c_Bt"));
        c_Bt->setEnabled(true);
        sizePolicy.setHeightForWidth(c_Bt->sizePolicy().hasHeightForWidth());
        c_Bt->setSizePolicy(sizePolicy);
        c_Bt->setFont(font1);

        gridLayout->addWidget(c_Bt, 3, 3, 1, 1);

        v_Bt = new QPushButton(layoutWidget);
        v_Bt->setObjectName(QString::fromUtf8("v_Bt"));
        v_Bt->setEnabled(true);
        sizePolicy.setHeightForWidth(v_Bt->sizePolicy().hasHeightForWidth());
        v_Bt->setSizePolicy(sizePolicy);
        v_Bt->setFont(font1);

        gridLayout->addWidget(v_Bt, 3, 4, 1, 1);

        b_Bt = new QPushButton(layoutWidget);
        b_Bt->setObjectName(QString::fromUtf8("b_Bt"));
        b_Bt->setEnabled(true);
        sizePolicy.setHeightForWidth(b_Bt->sizePolicy().hasHeightForWidth());
        b_Bt->setSizePolicy(sizePolicy);
        b_Bt->setFont(font1);

        gridLayout->addWidget(b_Bt, 3, 5, 1, 1);

        n_Bt = new QPushButton(layoutWidget);
        n_Bt->setObjectName(QString::fromUtf8("n_Bt"));
        n_Bt->setEnabled(true);
        sizePolicy.setHeightForWidth(n_Bt->sizePolicy().hasHeightForWidth());
        n_Bt->setSizePolicy(sizePolicy);
        n_Bt->setFont(font1);

        gridLayout->addWidget(n_Bt, 3, 6, 1, 1);

        m_Bt = new QPushButton(layoutWidget);
        m_Bt->setObjectName(QString::fromUtf8("m_Bt"));
        m_Bt->setEnabled(true);
        sizePolicy.setHeightForWidth(m_Bt->sizePolicy().hasHeightForWidth());
        m_Bt->setSizePolicy(sizePolicy);
        m_Bt->setFont(font1);

        gridLayout->addWidget(m_Bt, 3, 7, 1, 1);

        spaceBt = new QPushButton(layoutWidget);
        spaceBt->setObjectName(QString::fromUtf8("spaceBt"));
        spaceBt->setEnabled(true);
        sizePolicy.setHeightForWidth(spaceBt->sizePolicy().hasHeightForWidth());
        spaceBt->setSizePolicy(sizePolicy);
        spaceBt->setFont(font2);

        gridLayout->addWidget(spaceBt, 3, 8, 1, 2);

        showLb = new QLabel(layoutWidget);
        showLb->setObjectName(QString::fromUtf8("showLb"));
        showLb->setEnabled(true);
        showLb->setFont(font1);
        showLb->setStyleSheet(QString::fromUtf8("background-color: rgb(211, 211, 211);\n"
"color: rgb(4, 4, 4);"));
        showLb->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(showLb, 0, 0, 1, 5);

        backBt = new QPushButton(layoutWidget);
        backBt->setObjectName(QString::fromUtf8("backBt"));
        backBt->setEnabled(true);
        sizePolicy.setHeightForWidth(backBt->sizePolicy().hasHeightForWidth());
        backBt->setSizePolicy(sizePolicy);
        backBt->setFont(font2);

        gridLayout->addWidget(backBt, 0, 5, 1, 2);


        retranslateUi(KeyBoard_ABC);

        QMetaObject::connectSlotsByName(KeyBoard_ABC);
    } // setupUi

    void retranslateUi(QDialog *KeyBoard_ABC)
    {
        KeyBoard_ABC->setWindowTitle(QApplication::translate("KeyBoard_ABC", "Dialog", nullptr));
        label->setText(QString());
        e_Bt->setText(QApplication::translate("KeyBoard_ABC", "e", nullptr));
        num_9_Bt->setText(QApplication::translate("KeyBoard_ABC", "9", nullptr));
        num_4_Bt->setText(QApplication::translate("KeyBoard_ABC", "4", nullptr));
        k_Bt->setText(QApplication::translate("KeyBoard_ABC", "k", nullptr));
        f_Bt->setText(QApplication::translate("KeyBoard_ABC", "f", nullptr));
        y_Bt->setText(QApplication::translate("KeyBoard_ABC", "y", nullptr));
        h_Bt->setText(QApplication::translate("KeyBoard_ABC", "h", nullptr));
        q_Bt->setText(QApplication::translate("KeyBoard_ABC", "q", nullptr));
        num_6_Bt->setText(QApplication::translate("KeyBoard_ABC", "6", nullptr));
        g_Bt->setText(QApplication::translate("KeyBoard_ABC", "g", nullptr));
        i_Bt->setText(QApplication::translate("KeyBoard_ABC", "i", nullptr));
        num_1_Bt->setText(QApplication::translate("KeyBoard_ABC", "1", nullptr));
        s_Bt->setText(QApplication::translate("KeyBoard_ABC", "s", nullptr));
        w_Bt->setText(QApplication::translate("KeyBoard_ABC", "w", nullptr));
        l_Bt->setText(QApplication::translate("KeyBoard_ABC", "l", nullptr));
        Bt_dian->setText(QApplication::translate("KeyBoard_ABC", ".", nullptr));
        u_Bt->setText(QApplication::translate("KeyBoard_ABC", "u", nullptr));
        a_Bt->setText(QApplication::translate("KeyBoard_ABC", "a", nullptr));
        d_Bt->setText(QApplication::translate("KeyBoard_ABC", "d", nullptr));
        num_0_Bt->setText(QApplication::translate("KeyBoard_ABC", "0", nullptr));
        num_5_Bt->setText(QApplication::translate("KeyBoard_ABC", "5", nullptr));
        num_8_Bt->setText(QApplication::translate("KeyBoard_ABC", "8", nullptr));
        o_Bt->setText(QApplication::translate("KeyBoard_ABC", "o", nullptr));
        num_7_Bt->setText(QApplication::translate("KeyBoard_ABC", "7", nullptr));
        j_Bt->setText(QApplication::translate("KeyBoard_ABC", "j", nullptr));
        r_Bt->setText(QApplication::translate("KeyBoard_ABC", "r", nullptr));
        num_3_Bt->setText(QApplication::translate("KeyBoard_ABC", "3", nullptr));
        p_Bt->setText(QApplication::translate("KeyBoard_ABC", "p", nullptr));
        t_Bt->setText(QApplication::translate("KeyBoard_ABC", "t", nullptr));
        num_2_Bt->setText(QApplication::translate("KeyBoard_ABC", "2", nullptr));
        Bt_hengxian->setText(QApplication::translate("KeyBoard_ABC", "-", nullptr));
        delBt->setText(QApplication::translate("KeyBoard_ABC", "\345\210\240\351\231\244", nullptr));
        closeBt->setText(QApplication::translate("KeyBoard_ABC", "\347\241\256\345\256\232", nullptr));
        caps_Bt->setText(QApplication::translate("KeyBoard_ABC", "Caps", nullptr));
        z_Bt->setText(QApplication::translate("KeyBoard_ABC", "z", nullptr));
        x_Bt->setText(QApplication::translate("KeyBoard_ABC", "x", nullptr));
        c_Bt->setText(QApplication::translate("KeyBoard_ABC", "c", nullptr));
        v_Bt->setText(QApplication::translate("KeyBoard_ABC", "v", nullptr));
        b_Bt->setText(QApplication::translate("KeyBoard_ABC", "b", nullptr));
        n_Bt->setText(QApplication::translate("KeyBoard_ABC", "n", nullptr));
        m_Bt->setText(QApplication::translate("KeyBoard_ABC", "m", nullptr));
        spaceBt->setText(QApplication::translate("KeyBoard_ABC", "\347\251\272\346\240\274", nullptr));
        showLb->setText(QString());
        backBt->setText(QApplication::translate("KeyBoard_ABC", "\350\277\224\345\233\236", nullptr));
    } // retranslateUi

};

namespace Ui {
    class KeyBoard_ABC: public Ui_KeyBoard_ABC {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_KEYBOARD_ABC_H
