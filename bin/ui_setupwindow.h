/********************************************************************************
** Form generated from reading UI file 'setupwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETUPWINDOW_H
#define UI_SETUPWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SetupWindow
{
public:
    QWidget *tab_setup_serial;
    QGridLayout *gridLayout_9;
    QWidget *widget_3;
    QGridLayout *gridLayout_3;
    QWidget *widget;
    QGridLayout *gridLayout_2;
    QLabel *label;
    QComboBox *comboBox;
    QLabel *label_2;
    QComboBox *comboBox_2;
    QLabel *label_3;
    QComboBox *comboBox_3;
    QLabel *label_4;
    QComboBox *comboBox_4;
    QSpacerItem *horizontalSpacer_2;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton_sure;
    QPushButton *pushButton_cancel;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer;
    QWidget *tab_setup_threshold;
    QGridLayout *gridLayout_8;
    QWidget *widget_7;
    QGridLayout *gridLayout_4;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_6;
    QPushButton *pushButton_downlinede;
    QLineEdit *lineEdit_downlineto;
    QLabel *label_downlineto;
    QPushButton *pushButton_downlinesure;
    QPushButton *pushButton_downlineplus;
    QPushButton *pushButton_downlinereset;
    QSpacerItem *horizontalSpacer_4;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_5;
    QLabel *label_uplineto;
    QLineEdit *lineEdit_uplineto;
    QPushButton *pushButton_uplineplus;
    QPushButton *pushButton_uplinesure;
    QPushButton *pushButton_uplinede;
    QPushButton *pushButton_uplinereset;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *verticalSpacer_2;
    QWidget *tab_setup_ip;
    QWidget *widget_4;
    QGridLayout *gridLayout_7;
    QWidget *widget_6;
    QGridLayout *gridLayout;
    QLabel *label_5;
    QLineEdit *lineEdit;
    QLabel *label_6;
    QLineEdit *lineEdit_2;
    QSpacerItem *horizontalSpacer_5;
    QWidget *widget_5;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QSpacerItem *horizontalSpacer_6;
    QSpacerItem *verticalSpacer_3;

    void setupUi(QTabWidget *SetupWindow)
    {
        if (SetupWindow->objectName().isEmpty())
            SetupWindow->setObjectName(QString::fromUtf8("SetupWindow"));
        SetupWindow->resize(436, 432);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(SetupWindow->sizePolicy().hasHeightForWidth());
        SetupWindow->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(12);
        SetupWindow->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/source/title.png"), QSize(), QIcon::Normal, QIcon::Off);
        SetupWindow->setWindowIcon(icon);
        tab_setup_serial = new QWidget();
        tab_setup_serial->setObjectName(QString::fromUtf8("tab_setup_serial"));
        gridLayout_9 = new QGridLayout(tab_setup_serial);
        gridLayout_9->setObjectName(QString::fromUtf8("gridLayout_9"));
        widget_3 = new QWidget(tab_setup_serial);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        widget_3->setFont(font);
        gridLayout_3 = new QGridLayout(widget_3);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        widget = new QWidget(widget_3);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setMinimumSize(QSize(200, 200));
        gridLayout_2 = new QGridLayout(widget);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        comboBox = new QComboBox(widget);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        gridLayout_2->addWidget(comboBox, 0, 1, 1, 1);

        label_2 = new QLabel(widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_2->addWidget(label_2, 1, 0, 1, 1);

        comboBox_2 = new QComboBox(widget);
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));

        gridLayout_2->addWidget(comboBox_2, 1, 1, 1, 1);

        label_3 = new QLabel(widget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_2->addWidget(label_3, 2, 0, 1, 1);

        comboBox_3 = new QComboBox(widget);
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->setObjectName(QString::fromUtf8("comboBox_3"));

        gridLayout_2->addWidget(comboBox_3, 2, 1, 1, 1);

        label_4 = new QLabel(widget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_2->addWidget(label_4, 3, 0, 1, 1);

        comboBox_4 = new QComboBox(widget);
        comboBox_4->addItem(QString());
        comboBox_4->addItem(QString());
        comboBox_4->addItem(QString());
        comboBox_4->setObjectName(QString::fromUtf8("comboBox_4"));

        gridLayout_2->addWidget(comboBox_4, 3, 1, 1, 1);


        gridLayout_3->addWidget(widget, 0, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(158, 28, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_2, 0, 1, 1, 1);

        widget_2 = new QWidget(widget_3);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        widget_2->setMinimumSize(QSize(200, 100));
        widget_2->setMaximumSize(QSize(16777215, 200));
        horizontalLayout_2 = new QHBoxLayout(widget_2);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        pushButton_sure = new QPushButton(widget_2);
        pushButton_sure->setObjectName(QString::fromUtf8("pushButton_sure"));

        horizontalLayout_2->addWidget(pushButton_sure);

        pushButton_cancel = new QPushButton(widget_2);
        pushButton_cancel->setObjectName(QString::fromUtf8("pushButton_cancel"));

        horizontalLayout_2->addWidget(pushButton_cancel);


        gridLayout_3->addWidget(widget_2, 1, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(158, 18, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer, 1, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 48, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer, 2, 0, 1, 1);


        gridLayout_9->addWidget(widget_3, 0, 0, 1, 1);

        SetupWindow->addTab(tab_setup_serial, QString());
        tab_setup_threshold = new QWidget();
        tab_setup_threshold->setObjectName(QString::fromUtf8("tab_setup_threshold"));
        gridLayout_8 = new QGridLayout(tab_setup_threshold);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        widget_7 = new QWidget(tab_setup_threshold);
        widget_7->setObjectName(QString::fromUtf8("widget_7"));
        gridLayout_4 = new QGridLayout(widget_7);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        groupBox_2 = new QGroupBox(widget_7);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setMinimumSize(QSize(200, 150));
        gridLayout_6 = new QGridLayout(groupBox_2);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        pushButton_downlinede = new QPushButton(groupBox_2);
        pushButton_downlinede->setObjectName(QString::fromUtf8("pushButton_downlinede"));

        gridLayout_6->addWidget(pushButton_downlinede, 1, 0, 1, 1);

        lineEdit_downlineto = new QLineEdit(groupBox_2);
        lineEdit_downlineto->setObjectName(QString::fromUtf8("lineEdit_downlineto"));
        lineEdit_downlineto->setStyleSheet(QString::fromUtf8(""));

        gridLayout_6->addWidget(lineEdit_downlineto, 0, 2, 1, 1);

        label_downlineto = new QLabel(groupBox_2);
        label_downlineto->setObjectName(QString::fromUtf8("label_downlineto"));

        gridLayout_6->addWidget(label_downlineto, 0, 1, 1, 1);

        pushButton_downlinesure = new QPushButton(groupBox_2);
        pushButton_downlinesure->setObjectName(QString::fromUtf8("pushButton_downlinesure"));

        gridLayout_6->addWidget(pushButton_downlinesure, 1, 1, 1, 1);

        pushButton_downlineplus = new QPushButton(groupBox_2);
        pushButton_downlineplus->setObjectName(QString::fromUtf8("pushButton_downlineplus"));

        gridLayout_6->addWidget(pushButton_downlineplus, 0, 0, 1, 1);

        pushButton_downlinereset = new QPushButton(groupBox_2);
        pushButton_downlinereset->setObjectName(QString::fromUtf8("pushButton_downlinereset"));

        gridLayout_6->addWidget(pushButton_downlinereset, 1, 2, 1, 1);


        gridLayout_4->addWidget(groupBox_2, 1, 0, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_4, 1, 1, 1, 1);

        groupBox = new QGroupBox(widget_7);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setMinimumSize(QSize(200, 150));
        gridLayout_5 = new QGridLayout(groupBox);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        label_uplineto = new QLabel(groupBox);
        label_uplineto->setObjectName(QString::fromUtf8("label_uplineto"));
        label_uplineto->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_5->addWidget(label_uplineto, 0, 1, 1, 1);

        lineEdit_uplineto = new QLineEdit(groupBox);
        lineEdit_uplineto->setObjectName(QString::fromUtf8("lineEdit_uplineto"));
        lineEdit_uplineto->setStyleSheet(QString::fromUtf8(""));

        gridLayout_5->addWidget(lineEdit_uplineto, 0, 2, 1, 1);

        pushButton_uplineplus = new QPushButton(groupBox);
        pushButton_uplineplus->setObjectName(QString::fromUtf8("pushButton_uplineplus"));

        gridLayout_5->addWidget(pushButton_uplineplus, 0, 0, 1, 1);

        pushButton_uplinesure = new QPushButton(groupBox);
        pushButton_uplinesure->setObjectName(QString::fromUtf8("pushButton_uplinesure"));

        gridLayout_5->addWidget(pushButton_uplinesure, 1, 1, 1, 1);

        pushButton_uplinede = new QPushButton(groupBox);
        pushButton_uplinede->setObjectName(QString::fromUtf8("pushButton_uplinede"));

        gridLayout_5->addWidget(pushButton_uplinede, 1, 0, 1, 1);

        pushButton_uplinereset = new QPushButton(groupBox);
        pushButton_uplinereset->setObjectName(QString::fromUtf8("pushButton_uplinereset"));

        gridLayout_5->addWidget(pushButton_uplinereset, 1, 2, 1, 1);


        gridLayout_4->addWidget(groupBox, 0, 0, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_3, 0, 1, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_4->addItem(verticalSpacer_2, 2, 0, 1, 1);


        gridLayout_8->addWidget(widget_7, 0, 0, 1, 1);

        SetupWindow->addTab(tab_setup_threshold, QString());
        tab_setup_ip = new QWidget();
        tab_setup_ip->setObjectName(QString::fromUtf8("tab_setup_ip"));
        widget_4 = new QWidget(tab_setup_ip);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        widget_4->setGeometry(QRect(20, 30, 371, 361));
        gridLayout_7 = new QGridLayout(widget_4);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        widget_6 = new QWidget(widget_4);
        widget_6->setObjectName(QString::fromUtf8("widget_6"));
        widget_6->setMinimumSize(QSize(200, 120));
        gridLayout = new QGridLayout(widget_6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_5 = new QLabel(widget_6);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 0, 0, 1, 1);

        lineEdit = new QLineEdit(widget_6);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        gridLayout->addWidget(lineEdit, 0, 1, 1, 1);

        label_6 = new QLabel(widget_6);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 1, 0, 1, 1);

        lineEdit_2 = new QLineEdit(widget_6);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));

        gridLayout->addWidget(lineEdit_2, 1, 1, 1, 1);


        gridLayout_7->addWidget(widget_6, 0, 0, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(144, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_7->addItem(horizontalSpacer_5, 0, 1, 1, 1);

        widget_5 = new QWidget(widget_4);
        widget_5->setObjectName(QString::fromUtf8("widget_5"));
        widget_5->setMinimumSize(QSize(150, 120));
        pushButton_3 = new QPushButton(widget_5);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(10, 20, 80, 24));
        pushButton_4 = new QPushButton(widget_5);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setGeometry(QRect(120, 20, 80, 24));

        gridLayout_7->addWidget(widget_5, 1, 0, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(144, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_7->addItem(horizontalSpacer_6, 1, 1, 1, 1);

        verticalSpacer_3 = new QSpacerItem(18, 88, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_7->addItem(verticalSpacer_3, 2, 0, 1, 1);

        SetupWindow->addTab(tab_setup_ip, QString());

        retranslateUi(SetupWindow);

        SetupWindow->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(SetupWindow);
    } // setupUi

    void retranslateUi(QTabWidget *SetupWindow)
    {
        SetupWindow->setWindowTitle(QCoreApplication::translate("SetupWindow", "\345\217\202\346\225\260\350\256\276\347\275\256", nullptr));
        label->setText(QCoreApplication::translate("SetupWindow", "\347\253\257\345\217\243", nullptr));
        label_2->setText(QCoreApplication::translate("SetupWindow", "\346\263\242\347\211\271\347\216\207", nullptr));
        comboBox_2->setItemText(0, QCoreApplication::translate("SetupWindow", "115200", nullptr));
        comboBox_2->setItemText(1, QCoreApplication::translate("SetupWindow", "9600", nullptr));
        comboBox_2->setItemText(2, QCoreApplication::translate("SetupWindow", "57600", nullptr));
        comboBox_2->setItemText(3, QCoreApplication::translate("SetupWindow", "256000", nullptr));
        comboBox_2->setItemText(4, QCoreApplication::translate("SetupWindow", "460800", nullptr));

        label_3->setText(QCoreApplication::translate("SetupWindow", "\346\225\260\346\215\256\344\275\215", nullptr));
        comboBox_3->setItemText(0, QCoreApplication::translate("SetupWindow", "8", nullptr));
        comboBox_3->setItemText(1, QCoreApplication::translate("SetupWindow", "5", nullptr));
        comboBox_3->setItemText(2, QCoreApplication::translate("SetupWindow", "6", nullptr));
        comboBox_3->setItemText(3, QCoreApplication::translate("SetupWindow", "7", nullptr));

        label_4->setText(QCoreApplication::translate("SetupWindow", "\345\201\234\346\255\242\344\275\215", nullptr));
        comboBox_4->setItemText(0, QCoreApplication::translate("SetupWindow", "1", nullptr));
        comboBox_4->setItemText(1, QCoreApplication::translate("SetupWindow", "2", nullptr));
        comboBox_4->setItemText(2, QCoreApplication::translate("SetupWindow", "3", nullptr));

        pushButton_sure->setText(QCoreApplication::translate("SetupWindow", "\347\241\256\350\256\244", nullptr));
        pushButton_cancel->setText(QCoreApplication::translate("SetupWindow", "\345\217\226\346\266\210", nullptr));
        SetupWindow->setTabText(SetupWindow->indexOf(tab_setup_serial), QCoreApplication::translate("SetupWindow", "\344\270\262\345\217\243\350\256\276\347\275\256", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("SetupWindow", "\344\270\213\351\230\210\345\200\274\347\272\277\350\256\276\347\275\256", nullptr));
        pushButton_downlinede->setText(QCoreApplication::translate("SetupWindow", "\344\270\213\347\247\273 -", nullptr));
        label_downlineto->setText(QCoreApplication::translate("SetupWindow", "\347\247\273\345\212\250\344\275\215\347\275\256\350\207\263", nullptr));
        pushButton_downlinesure->setText(QCoreApplication::translate("SetupWindow", "\347\247\273\344\275\215", nullptr));
        pushButton_downlineplus->setText(QCoreApplication::translate("SetupWindow", "\344\270\212\347\247\273 +", nullptr));
        pushButton_downlinereset->setText(QCoreApplication::translate("SetupWindow", "\345\244\215\344\275\215", nullptr));
        groupBox->setTitle(QCoreApplication::translate("SetupWindow", "\344\270\212\351\230\210\345\200\274\347\272\277\350\256\276\347\275\256", nullptr));
        label_uplineto->setText(QCoreApplication::translate("SetupWindow", "\347\247\273\345\212\250\344\275\215\347\275\256\350\207\263", nullptr));
        pushButton_uplineplus->setText(QCoreApplication::translate("SetupWindow", "\344\270\212\347\247\273 +", nullptr));
        pushButton_uplinesure->setText(QCoreApplication::translate("SetupWindow", "\347\247\273\344\275\215", nullptr));
        pushButton_uplinede->setText(QCoreApplication::translate("SetupWindow", "\344\270\213\347\247\273 -", nullptr));
        pushButton_uplinereset->setText(QCoreApplication::translate("SetupWindow", "\345\244\215\344\275\215", nullptr));
        SetupWindow->setTabText(SetupWindow->indexOf(tab_setup_threshold), QCoreApplication::translate("SetupWindow", "\351\230\210\345\200\274\350\256\276\347\275\256", nullptr));
        label_5->setText(QCoreApplication::translate("SetupWindow", "\347\253\257\345\217\243", nullptr));
        label_6->setText(QCoreApplication::translate("SetupWindow", "\345\234\260\345\235\200", nullptr));
        pushButton_3->setText(QCoreApplication::translate("SetupWindow", "\347\241\256\350\256\244", nullptr));
        pushButton_4->setText(QCoreApplication::translate("SetupWindow", "\345\217\226\346\266\210", nullptr));
        SetupWindow->setTabText(SetupWindow->indexOf(tab_setup_ip), QCoreApplication::translate("SetupWindow", "\347\275\221\347\273\234\350\256\276\347\275\256", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SetupWindow: public Ui_SetupWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETUPWINDOW_H
