/********************************************************************************
** Form generated from reading UI file 'keyboard.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_KEYBOARD_H
#define UI_KEYBOARD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_KeyBoard
{
public:
    QLabel *label;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QPushButton *closeBt;
    QPushButton *num_7_Bt;
    QPushButton *num_8_Bt;
    QPushButton *num_9_Bt;
    QPushButton *delBt;
    QPushButton *num_4_Bt;
    QPushButton *num_5_Bt;
    QPushButton *num_6_Bt;
    QPushButton *dian;
    QPushButton *num_1_Bt;
    QPushButton *num_2_Bt;
    QPushButton *num_3_Bt;
    QPushButton *num_0_Bt;
    QLabel *showLb;
    QPushButton *backBt;

    void setupUi(QDialog *KeyBoard)
    {
        if (KeyBoard->objectName().isEmpty())
            KeyBoard->setObjectName(QString::fromUtf8("KeyBoard"));
        KeyBoard->setEnabled(true);
        KeyBoard->resize(545, 254);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(KeyBoard->sizePolicy().hasHeightForWidth());
        KeyBoard->setSizePolicy(sizePolicy);
        KeyBoard->setStyleSheet(QString::fromUtf8(""));
        label = new QLabel(KeyBoard);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(0, 0, 180, 140));
        QFont font;
        font.setPointSize(15);
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 35, 53);\n"
"color: rgb(67, 135, 203);"));
        label->setFrameShape(QFrame::Box);
        layoutWidget = new QWidget(KeyBoard);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 161, 121));
        layoutWidget->setFont(font);
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setSpacing(2);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        closeBt = new QPushButton(layoutWidget);
        closeBt->setObjectName(QString::fromUtf8("closeBt"));
        closeBt->setEnabled(true);
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(closeBt->sizePolicy().hasHeightForWidth());
        closeBt->setSizePolicy(sizePolicy1);
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font1.setPointSize(9);
        closeBt->setFont(font1);

        gridLayout->addWidget(closeBt, 0, 3, 1, 1);

        num_7_Bt = new QPushButton(layoutWidget);
        num_7_Bt->setObjectName(QString::fromUtf8("num_7_Bt"));
        num_7_Bt->setEnabled(true);
        sizePolicy1.setHeightForWidth(num_7_Bt->sizePolicy().hasHeightForWidth());
        num_7_Bt->setSizePolicy(sizePolicy1);
        QFont font2;
        font2.setFamily(QString::fromUtf8("Times New Roman"));
        font2.setPointSize(15);
        num_7_Bt->setFont(font2);

        gridLayout->addWidget(num_7_Bt, 1, 0, 1, 1);

        num_8_Bt = new QPushButton(layoutWidget);
        num_8_Bt->setObjectName(QString::fromUtf8("num_8_Bt"));
        num_8_Bt->setEnabled(true);
        sizePolicy1.setHeightForWidth(num_8_Bt->sizePolicy().hasHeightForWidth());
        num_8_Bt->setSizePolicy(sizePolicy1);
        num_8_Bt->setFont(font2);

        gridLayout->addWidget(num_8_Bt, 1, 1, 1, 1);

        num_9_Bt = new QPushButton(layoutWidget);
        num_9_Bt->setObjectName(QString::fromUtf8("num_9_Bt"));
        num_9_Bt->setEnabled(true);
        sizePolicy1.setHeightForWidth(num_9_Bt->sizePolicy().hasHeightForWidth());
        num_9_Bt->setSizePolicy(sizePolicy1);
        num_9_Bt->setFont(font2);

        gridLayout->addWidget(num_9_Bt, 1, 2, 1, 1);

        delBt = new QPushButton(layoutWidget);
        delBt->setObjectName(QString::fromUtf8("delBt"));
        delBt->setEnabled(true);
        sizePolicy1.setHeightForWidth(delBt->sizePolicy().hasHeightForWidth());
        delBt->setSizePolicy(sizePolicy1);
        delBt->setFont(font1);

        gridLayout->addWidget(delBt, 1, 3, 1, 1);

        num_4_Bt = new QPushButton(layoutWidget);
        num_4_Bt->setObjectName(QString::fromUtf8("num_4_Bt"));
        num_4_Bt->setEnabled(true);
        sizePolicy1.setHeightForWidth(num_4_Bt->sizePolicy().hasHeightForWidth());
        num_4_Bt->setSizePolicy(sizePolicy1);
        num_4_Bt->setFont(font2);

        gridLayout->addWidget(num_4_Bt, 2, 0, 1, 1);

        num_5_Bt = new QPushButton(layoutWidget);
        num_5_Bt->setObjectName(QString::fromUtf8("num_5_Bt"));
        num_5_Bt->setEnabled(true);
        sizePolicy1.setHeightForWidth(num_5_Bt->sizePolicy().hasHeightForWidth());
        num_5_Bt->setSizePolicy(sizePolicy1);
        num_5_Bt->setFont(font2);

        gridLayout->addWidget(num_5_Bt, 2, 1, 1, 1);

        num_6_Bt = new QPushButton(layoutWidget);
        num_6_Bt->setObjectName(QString::fromUtf8("num_6_Bt"));
        num_6_Bt->setEnabled(true);
        sizePolicy1.setHeightForWidth(num_6_Bt->sizePolicy().hasHeightForWidth());
        num_6_Bt->setSizePolicy(sizePolicy1);
        num_6_Bt->setFont(font2);

        gridLayout->addWidget(num_6_Bt, 2, 2, 1, 1);

        dian = new QPushButton(layoutWidget);
        dian->setObjectName(QString::fromUtf8("dian"));
        sizePolicy1.setHeightForWidth(dian->sizePolicy().hasHeightForWidth());
        dian->setSizePolicy(sizePolicy1);
        dian->setFont(font2);

        gridLayout->addWidget(dian, 2, 3, 1, 1);

        num_1_Bt = new QPushButton(layoutWidget);
        num_1_Bt->setObjectName(QString::fromUtf8("num_1_Bt"));
        num_1_Bt->setEnabled(true);
        sizePolicy1.setHeightForWidth(num_1_Bt->sizePolicy().hasHeightForWidth());
        num_1_Bt->setSizePolicy(sizePolicy1);
        num_1_Bt->setFont(font2);

        gridLayout->addWidget(num_1_Bt, 3, 0, 1, 1);

        num_2_Bt = new QPushButton(layoutWidget);
        num_2_Bt->setObjectName(QString::fromUtf8("num_2_Bt"));
        num_2_Bt->setEnabled(true);
        sizePolicy1.setHeightForWidth(num_2_Bt->sizePolicy().hasHeightForWidth());
        num_2_Bt->setSizePolicy(sizePolicy1);
        num_2_Bt->setFont(font2);

        gridLayout->addWidget(num_2_Bt, 3, 1, 1, 1);

        num_3_Bt = new QPushButton(layoutWidget);
        num_3_Bt->setObjectName(QString::fromUtf8("num_3_Bt"));
        num_3_Bt->setEnabled(true);
        sizePolicy1.setHeightForWidth(num_3_Bt->sizePolicy().hasHeightForWidth());
        num_3_Bt->setSizePolicy(sizePolicy1);
        num_3_Bt->setFont(font2);

        gridLayout->addWidget(num_3_Bt, 3, 2, 1, 1);

        num_0_Bt = new QPushButton(layoutWidget);
        num_0_Bt->setObjectName(QString::fromUtf8("num_0_Bt"));
        num_0_Bt->setEnabled(true);
        sizePolicy1.setHeightForWidth(num_0_Bt->sizePolicy().hasHeightForWidth());
        num_0_Bt->setSizePolicy(sizePolicy1);
        num_0_Bt->setFont(font2);

        gridLayout->addWidget(num_0_Bt, 3, 3, 1, 1);

        showLb = new QLabel(layoutWidget);
        showLb->setObjectName(QString::fromUtf8("showLb"));
        showLb->setEnabled(true);
        showLb->setFont(font2);
        showLb->setStyleSheet(QString::fromUtf8("color: rgb(4, 4, 4);\n"
"background-color: rgb(217, 217, 217);"));
        showLb->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(showLb, 0, 0, 1, 2);

        backBt = new QPushButton(layoutWidget);
        backBt->setObjectName(QString::fromUtf8("backBt"));
        backBt->setEnabled(true);
        sizePolicy1.setHeightForWidth(backBt->sizePolicy().hasHeightForWidth());
        backBt->setSizePolicy(sizePolicy1);
        backBt->setFont(font1);

        gridLayout->addWidget(backBt, 0, 2, 1, 1);


        retranslateUi(KeyBoard);

        QMetaObject::connectSlotsByName(KeyBoard);
    } // setupUi

    void retranslateUi(QDialog *KeyBoard)
    {
        KeyBoard->setWindowTitle(QApplication::translate("KeyBoard", "Dialog", nullptr));
        label->setText(QString());
        closeBt->setText(QApplication::translate("KeyBoard", "\347\241\256\345\256\232", nullptr));
        num_7_Bt->setText(QApplication::translate("KeyBoard", "7", nullptr));
        num_8_Bt->setText(QApplication::translate("KeyBoard", "8", nullptr));
        num_9_Bt->setText(QApplication::translate("KeyBoard", "9", nullptr));
        delBt->setText(QApplication::translate("KeyBoard", "\345\210\240\351\231\244", nullptr));
        num_4_Bt->setText(QApplication::translate("KeyBoard", "4", nullptr));
        num_5_Bt->setText(QApplication::translate("KeyBoard", "5", nullptr));
        num_6_Bt->setText(QApplication::translate("KeyBoard", "6", nullptr));
        dian->setText(QApplication::translate("KeyBoard", ".", nullptr));
        num_1_Bt->setText(QApplication::translate("KeyBoard", "1", nullptr));
        num_2_Bt->setText(QApplication::translate("KeyBoard", "2", nullptr));
        num_3_Bt->setText(QApplication::translate("KeyBoard", "3", nullptr));
        num_0_Bt->setText(QApplication::translate("KeyBoard", "0", nullptr));
        showLb->setText(QString());
        backBt->setText(QApplication::translate("KeyBoard", "\350\277\224\345\233\236", nullptr));
    } // retranslateUi

};

namespace Ui {
    class KeyBoard: public Ui_KeyBoard {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_KEYBOARD_H
