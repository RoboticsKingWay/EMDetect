/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QCheckBox *checkCH2;
    QCheckBox *checkCH1;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QComboBox *serialCb;
    QSpacerItem *horizontalSpacer;
    QPushButton *openBt;
    QWidget *widget1;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_5;
    QLineEdit *freqEdit;
    QLabel *label_7;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *sendfreqBt;
    QWidget *widget2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_6;
    QLineEdit *ampEdit;
    QLabel *label_8;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *sendampBt;
    QWidget *widget3;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_9;
    QLineEdit *freqEdit_2;
    QLabel *label_11;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *sendfreqBt_2;
    QWidget *widget4;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_10;
    QLineEdit *ampEdit_2;
    QLabel *label_12;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *sendampBt_2;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(369, 302);
        checkCH2 = new QCheckBox(Widget);
        checkCH2->setObjectName(QString::fromUtf8("checkCH2"));
        checkCH2->setGeometry(QRect(20, 170, 98, 23));
        checkCH1 = new QCheckBox(Widget);
        checkCH1->setObjectName(QString::fromUtf8("checkCH1"));
        checkCH1->setGeometry(QRect(20, 60, 98, 23));
        widget = new QWidget(Widget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(20, 10, 321, 41));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        serialCb = new QComboBox(widget);
        serialCb->setObjectName(QString::fromUtf8("serialCb"));

        horizontalLayout->addWidget(serialCb);

        horizontalSpacer = new QSpacerItem(68, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        openBt = new QPushButton(widget);
        openBt->setObjectName(QString::fromUtf8("openBt"));

        horizontalLayout->addWidget(openBt);

        widget1 = new QWidget(Widget);
        widget1->setObjectName(QString::fromUtf8("widget1"));
        widget1->setGeometry(QRect(20, 90, 321, 31));
        horizontalLayout_2 = new QHBoxLayout(widget1);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_5 = new QLabel(widget1);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_2->addWidget(label_5);

        freqEdit = new QLineEdit(widget1);
        freqEdit->setObjectName(QString::fromUtf8("freqEdit"));
        freqEdit->setMinimumSize(QSize(120, 0));
        freqEdit->setMaximumSize(QSize(120, 16777215));

        horizontalLayout_2->addWidget(freqEdit);

        label_7 = new QLabel(widget1);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        horizontalLayout_2->addWidget(label_7);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        sendfreqBt = new QPushButton(widget1);
        sendfreqBt->setObjectName(QString::fromUtf8("sendfreqBt"));

        horizontalLayout_2->addWidget(sendfreqBt);

        widget2 = new QWidget(Widget);
        widget2->setObjectName(QString::fromUtf8("widget2"));
        widget2->setGeometry(QRect(20, 130, 321, 31));
        horizontalLayout_3 = new QHBoxLayout(widget2);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_6 = new QLabel(widget2);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_3->addWidget(label_6);

        ampEdit = new QLineEdit(widget2);
        ampEdit->setObjectName(QString::fromUtf8("ampEdit"));
        ampEdit->setMinimumSize(QSize(120, 0));
        ampEdit->setMaximumSize(QSize(120, 16777215));

        horizontalLayout_3->addWidget(ampEdit);

        label_8 = new QLabel(widget2);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        horizontalLayout_3->addWidget(label_8);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        sendampBt = new QPushButton(widget2);
        sendampBt->setObjectName(QString::fromUtf8("sendampBt"));

        horizontalLayout_3->addWidget(sendampBt);

        widget3 = new QWidget(Widget);
        widget3->setObjectName(QString::fromUtf8("widget3"));
        widget3->setGeometry(QRect(20, 200, 321, 31));
        horizontalLayout_4 = new QHBoxLayout(widget3);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        label_9 = new QLabel(widget3);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        horizontalLayout_4->addWidget(label_9);

        freqEdit_2 = new QLineEdit(widget3);
        freqEdit_2->setObjectName(QString::fromUtf8("freqEdit_2"));
        freqEdit_2->setMinimumSize(QSize(120, 0));
        freqEdit_2->setMaximumSize(QSize(120, 16777215));

        horizontalLayout_4->addWidget(freqEdit_2);

        label_11 = new QLabel(widget3);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        horizontalLayout_4->addWidget(label_11);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);

        sendfreqBt_2 = new QPushButton(widget3);
        sendfreqBt_2->setObjectName(QString::fromUtf8("sendfreqBt_2"));

        horizontalLayout_4->addWidget(sendfreqBt_2);

        widget4 = new QWidget(Widget);
        widget4->setObjectName(QString::fromUtf8("widget4"));
        widget4->setGeometry(QRect(20, 240, 321, 31));
        horizontalLayout_5 = new QHBoxLayout(widget4);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        label_10 = new QLabel(widget4);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        horizontalLayout_5->addWidget(label_10);

        ampEdit_2 = new QLineEdit(widget4);
        ampEdit_2->setObjectName(QString::fromUtf8("ampEdit_2"));
        ampEdit_2->setMinimumSize(QSize(120, 0));
        ampEdit_2->setMaximumSize(QSize(120, 16777215));

        horizontalLayout_5->addWidget(ampEdit_2);

        label_12 = new QLabel(widget4);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        horizontalLayout_5->addWidget(label_12);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_5);

        sendampBt_2 = new QPushButton(widget4);
        sendampBt_2->setObjectName(QString::fromUtf8("sendampBt_2"));

        horizontalLayout_5->addWidget(sendampBt_2);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "\346\277\200\345\212\261\350\256\276\347\275\256", nullptr));
        checkCH2->setText(QCoreApplication::translate("Widget", "CH2", nullptr));
        checkCH1->setText(QCoreApplication::translate("Widget", "CH1", nullptr));
        label_2->setText(QCoreApplication::translate("Widget", "\344\270\262\345\217\243\345\217\267\357\274\232", nullptr));
        openBt->setText(QCoreApplication::translate("Widget", "\346\211\223\345\274\200", nullptr));
        label_5->setText(QCoreApplication::translate("Widget", "\351\242\221\347\216\207\357\274\232", nullptr));
        label_7->setText(QCoreApplication::translate("Widget", "Hz", nullptr));
        sendfreqBt->setText(QCoreApplication::translate("Widget", "\345\217\221\351\200\201\351\242\221\347\216\207", nullptr));
        label_6->setText(QCoreApplication::translate("Widget", "\345\271\205\345\200\274\357\274\232", nullptr));
        label_8->setText(QCoreApplication::translate("Widget", " V", nullptr));
        sendampBt->setText(QCoreApplication::translate("Widget", "\345\217\221\351\200\201\345\271\205\345\200\274", nullptr));
        label_9->setText(QCoreApplication::translate("Widget", "\351\242\221\347\216\207\357\274\232", nullptr));
        label_11->setText(QCoreApplication::translate("Widget", "Hz", nullptr));
        sendfreqBt_2->setText(QCoreApplication::translate("Widget", "\345\217\221\351\200\201\351\242\221\347\216\207", nullptr));
        label_10->setText(QCoreApplication::translate("Widget", "\345\271\205\345\200\274\357\274\232", nullptr));
        label_12->setText(QCoreApplication::translate("Widget", " V", nullptr));
        sendampBt_2->setText(QCoreApplication::translate("Widget", "\345\217\221\351\200\201\345\271\205\345\200\274", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
