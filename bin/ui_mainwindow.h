/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_version;
    QAction *action_readme;
    QAction *action_outside;
    QAction *action_inside;
    QAction *action_serialSetup;
    QAction *action_thresholdSetup;
    QAction *action_filesave;
    QAction *action_fileperview;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QWidget *widget_up;
    QHBoxLayout *horizontalLayout;
    QWidget *widget_upleft;
    QVBoxLayout *verticalLayout_2;
    QWidget *widget_real_chat_view;
    QWidget *widget_chinnel;
    QHBoxLayout *horizontalLayout_2;
    QCheckBox *checkBox;
    QCheckBox *checkBox_2;
    QCheckBox *checkBox_upline;
    QCheckBox *checkBox_3;
    QSpacerItem *horizontalSpacer;
    QWidget *widget_upright;
    QWidget *widget_down;
    QHBoxLayout *horizontalLayout_3;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QPushButton *pushButton_2;
    QPushButton *pushButton_SerialSetup;
    QPushButton *pushButton;
    QPushButton *pushButton_4;
    QPushButton *pushButton_connect_state;
    QPushButton *pushButton_3;
    QPushButton *pushButton_5;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *label_2;
    QLineEdit *lineEdit;
    QLabel *label;
    QLineEdit *lineEdit_2;
    QComboBox *comboBox;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer_2;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_4;
    QComboBox *comboBox_2;
    QLabel *label_4;
    QComboBox *comboBox_3;
    QLabel *label_5;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_9;
    QLabel *label_13;
    QLabel *label_7;
    QLabel *label_12;
    QLabel *label_6;
    QLabel *label_14;
    QLabel *label_8;
    QLabel *label_15;
    QStatusBar *statusbar;
    QMenuBar *menuBar;
    QMenu *menu_file;
    QMenu *menu_setup;
    QMenu *menu_standar;
    QMenu *menu_software;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1200, 700);
        MainWindow->setMinimumSize(QSize(1200, 700));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/source/title.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setStyleSheet(QString::fromUtf8("/*QMainWindow\n"
"{\n"
"    background-color: #D7D7D7;\n"
"	border: 3px solid #333333;\n"
"}*/"));
        action_version = new QAction(MainWindow);
        action_version->setObjectName(QString::fromUtf8("action_version"));
        action_readme = new QAction(MainWindow);
        action_readme->setObjectName(QString::fromUtf8("action_readme"));
        action_outside = new QAction(MainWindow);
        action_outside->setObjectName(QString::fromUtf8("action_outside"));
        action_inside = new QAction(MainWindow);
        action_inside->setObjectName(QString::fromUtf8("action_inside"));
        action_serialSetup = new QAction(MainWindow);
        action_serialSetup->setObjectName(QString::fromUtf8("action_serialSetup"));
        action_thresholdSetup = new QAction(MainWindow);
        action_thresholdSetup->setObjectName(QString::fromUtf8("action_thresholdSetup"));
        action_filesave = new QAction(MainWindow);
        action_filesave->setObjectName(QString::fromUtf8("action_filesave"));
        action_fileperview = new QAction(MainWindow);
        action_fileperview->setObjectName(QString::fromUtf8("action_fileperview"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        centralwidget->setMinimumSize(QSize(1000, 670));
        centralwidget->setStyleSheet(QString::fromUtf8("/*background-color:#DDDDDD*/"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        widget_up = new QWidget(centralwidget);
        widget_up->setObjectName(QString::fromUtf8("widget_up"));
        widget_up->setMinimumSize(QSize(920, 0));
        widget_up->setAutoFillBackground(false);
        horizontalLayout = new QHBoxLayout(widget_up);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        widget_upleft = new QWidget(widget_up);
        widget_upleft->setObjectName(QString::fromUtf8("widget_upleft"));
        widget_upleft->setMinimumSize(QSize(460, 0));
        verticalLayout_2 = new QVBoxLayout(widget_upleft);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        widget_real_chat_view = new QWidget(widget_upleft);
        widget_real_chat_view->setObjectName(QString::fromUtf8("widget_real_chat_view"));

        verticalLayout_2->addWidget(widget_real_chat_view);

        widget_chinnel = new QWidget(widget_upleft);
        widget_chinnel->setObjectName(QString::fromUtf8("widget_chinnel"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget_chinnel->sizePolicy().hasHeightForWidth());
        widget_chinnel->setSizePolicy(sizePolicy);
        widget_chinnel->setMinimumSize(QSize(0, 40));
        QFont font;
        font.setPointSize(12);
        widget_chinnel->setFont(font);
        widget_chinnel->setAutoFillBackground(false);
        widget_chinnel->setStyleSheet(QString::fromUtf8("\n"
"/*background-color: white;*/"));
        horizontalLayout_2 = new QHBoxLayout(widget_chinnel);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        checkBox = new QCheckBox(widget_chinnel);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));

        horizontalLayout_2->addWidget(checkBox);

        checkBox_2 = new QCheckBox(widget_chinnel);
        checkBox_2->setObjectName(QString::fromUtf8("checkBox_2"));

        horizontalLayout_2->addWidget(checkBox_2);

        checkBox_upline = new QCheckBox(widget_chinnel);
        checkBox_upline->setObjectName(QString::fromUtf8("checkBox_upline"));

        horizontalLayout_2->addWidget(checkBox_upline);

        checkBox_3 = new QCheckBox(widget_chinnel);
        checkBox_3->setObjectName(QString::fromUtf8("checkBox_3"));

        horizontalLayout_2->addWidget(checkBox_3);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout_2->addWidget(widget_chinnel);


        horizontalLayout->addWidget(widget_upleft);

        widget_upright = new QWidget(widget_up);
        widget_upright->setObjectName(QString::fromUtf8("widget_upright"));
        widget_upright->setMinimumSize(QSize(500, 0));

        horizontalLayout->addWidget(widget_upright);


        verticalLayout->addWidget(widget_up);

        widget_down = new QWidget(centralwidget);
        widget_down->setObjectName(QString::fromUtf8("widget_down"));
        widget_down->setMinimumSize(QSize(780, 100));
        widget_down->setMaximumSize(QSize(16777215, 150));
        widget_down->setStyleSheet(QString::fromUtf8("background-color:#DFDFDF"));
        horizontalLayout_3 = new QHBoxLayout(widget_down);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        groupBox_2 = new QGroupBox(widget_down);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setMinimumSize(QSize(260, 120));
        groupBox_2->setMaximumSize(QSize(300, 120));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setSizeConstraint(QLayout::SetDefaultConstraint);
        gridLayout_2->setContentsMargins(-1, 2, -1, 2);
        pushButton_2 = new QPushButton(groupBox_2);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setFont(font);
        pushButton_2->setAutoDefault(false);

        gridLayout_2->addWidget(pushButton_2, 1, 1, 1, 1);

        pushButton_SerialSetup = new QPushButton(groupBox_2);
        pushButton_SerialSetup->setObjectName(QString::fromUtf8("pushButton_SerialSetup"));
        pushButton_SerialSetup->setFont(font);
        pushButton_SerialSetup->setStyleSheet(QString::fromUtf8("/*QPushButton {\n"
"				border: 4px outset gray;\n"
"                   border-radius: 3px;\n"
"}*/"));
        pushButton_SerialSetup->setFlat(false);

        gridLayout_2->addWidget(pushButton_SerialSetup, 0, 1, 1, 1);

        pushButton = new QPushButton(groupBox_2);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setFont(font);

        gridLayout_2->addWidget(pushButton, 1, 0, 1, 1);

        pushButton_4 = new QPushButton(groupBox_2);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setFont(font);

        gridLayout_2->addWidget(pushButton_4, 3, 1, 1, 1);

        pushButton_connect_state = new QPushButton(groupBox_2);
        pushButton_connect_state->setObjectName(QString::fromUtf8("pushButton_connect_state"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/source/serial_close.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_connect_state->setIcon(icon1);
        pushButton_connect_state->setFlat(true);

        gridLayout_2->addWidget(pushButton_connect_state, 0, 0, 1, 1);

        pushButton_3 = new QPushButton(groupBox_2);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setFont(font);

        gridLayout_2->addWidget(pushButton_3, 3, 0, 1, 1);

        pushButton_5 = new QPushButton(groupBox_2);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));

        gridLayout_2->addWidget(pushButton_5, 2, 1, 1, 1);


        horizontalLayout_3->addWidget(groupBox_2);

        groupBox = new QGroupBox(widget_down);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setMinimumSize(QSize(240, 120));
        groupBox->setMaximumSize(QSize(280, 120));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(-1, 2, 9, 2);
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font);

        gridLayout->addWidget(label_2, 1, 1, 1, 1);

        lineEdit = new QLineEdit(groupBox);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setStyleSheet(QString::fromUtf8("background-color:#DDDDD"));

        gridLayout->addWidget(lineEdit, 0, 2, 1, 1);

        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setFont(font);

        gridLayout->addWidget(label, 0, 1, 1, 1);

        lineEdit_2 = new QLineEdit(groupBox);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setStyleSheet(QString::fromUtf8("background-color:#DDDDD"));

        gridLayout->addWidget(lineEdit_2, 1, 2, 1, 1);

        comboBox = new QComboBox(groupBox);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setStyleSheet(QString::fromUtf8("background-color:#DDDDD"));

        gridLayout->addWidget(comboBox, 2, 2, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFont(font);

        gridLayout->addWidget(label_3, 2, 1, 1, 1);


        horizontalLayout_3->addWidget(groupBox);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        groupBox_4 = new QGroupBox(widget_down);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setFont(font);
        groupBox_4->setAutoFillBackground(false);
        gridLayout_4 = new QGridLayout(groupBox_4);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_4->setContentsMargins(9, 2, -1, 2);
        comboBox_2 = new QComboBox(groupBox_4);
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));
        comboBox_2->setFont(font);
        comboBox_2->setStyleSheet(QString::fromUtf8("background-color:#DDDDD"));

        gridLayout_4->addWidget(comboBox_2, 0, 1, 1, 1);

        label_4 = new QLabel(groupBox_4);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setFont(font);

        gridLayout_4->addWidget(label_4, 2, 0, 1, 1);

        comboBox_3 = new QComboBox(groupBox_4);
        comboBox_3->setObjectName(QString::fromUtf8("comboBox_3"));
        comboBox_3->setFont(font);
        comboBox_3->setStyleSheet(QString::fromUtf8("background-color:#DDDDD"));

        gridLayout_4->addWidget(comboBox_3, 0, 3, 1, 1);

        label_5 = new QLabel(groupBox_4);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_4->addWidget(label_5, 2, 1, 1, 1);

        label_10 = new QLabel(groupBox_4);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setFont(font);

        gridLayout_4->addWidget(label_10, 0, 0, 1, 1);

        label_11 = new QLabel(groupBox_4);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setFont(font);

        gridLayout_4->addWidget(label_11, 0, 2, 1, 1);

        label_9 = new QLabel(groupBox_4);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setFont(font);

        gridLayout_4->addWidget(label_9, 2, 2, 1, 1);

        label_13 = new QLabel(groupBox_4);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        gridLayout_4->addWidget(label_13, 4, 1, 1, 1);

        label_7 = new QLabel(groupBox_4);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setFont(font);

        gridLayout_4->addWidget(label_7, 4, 0, 1, 1);

        label_12 = new QLabel(groupBox_4);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        gridLayout_4->addWidget(label_12, 2, 3, 1, 1);

        label_6 = new QLabel(groupBox_4);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setFont(font);

        gridLayout_4->addWidget(label_6, 3, 0, 1, 1);

        label_14 = new QLabel(groupBox_4);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        gridLayout_4->addWidget(label_14, 3, 1, 1, 1);

        label_8 = new QLabel(groupBox_4);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setFont(font);

        gridLayout_4->addWidget(label_8, 3, 2, 1, 1);

        label_15 = new QLabel(groupBox_4);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        gridLayout_4->addWidget(label_15, 3, 3, 1, 1);


        horizontalLayout_3->addWidget(groupBox_4);


        verticalLayout->addWidget(widget_down);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1200, 26));
        menuBar->setFont(font);
        menu_file = new QMenu(menuBar);
        menu_file->setObjectName(QString::fromUtf8("menu_file"));
        menu_file->setFont(font);
        menu_setup = new QMenu(menuBar);
        menu_setup->setObjectName(QString::fromUtf8("menu_setup"));
        menu_setup->setFont(font);
        menu_standar = new QMenu(menuBar);
        menu_standar->setObjectName(QString::fromUtf8("menu_standar"));
        menu_standar->setFont(font);
        menu_software = new QMenu(menuBar);
        menu_software->setObjectName(QString::fromUtf8("menu_software"));
        menu_software->setFont(font);
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menu_file->menuAction());
        menuBar->addAction(menu_setup->menuAction());
        menuBar->addAction(menu_standar->menuAction());
        menuBar->addAction(menu_software->menuAction());
        menu_file->addAction(action_filesave);
        menu_file->addAction(action_fileperview);
        menu_setup->addAction(action_serialSetup);
        menu_setup->addAction(action_thresholdSetup);
        menu_standar->addAction(action_outside);
        menu_standar->addAction(action_inside);
        menu_software->addAction(action_version);
        menu_software->addAction(action_readme);

        retranslateUi(MainWindow);

        pushButton_2->setDefault(false);
        pushButton_SerialSetup->setDefault(false);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "2\351\200\232\351\201\223\346\277\200\345\212\261\347\243\201\346\243\200\346\265\213\350\275\257\344\273\266", nullptr));
        action_version->setText(QCoreApplication::translate("MainWindow", "\350\275\257\344\273\266\347\211\210\346\234\254", nullptr));
        action_readme->setText(QCoreApplication::translate("MainWindow", "\350\275\257\344\273\266\350\257\264\346\230\216", nullptr));
        action_outside->setText(QCoreApplication::translate("MainWindow", "\350\241\250\351\235\242\347\274\272\351\231\267", nullptr));
        action_inside->setText(QCoreApplication::translate("MainWindow", "\345\206\205\351\203\250\347\274\272\351\231\267", nullptr));
        action_serialSetup->setText(QCoreApplication::translate("MainWindow", "\344\270\262\345\217\243\350\256\276\347\275\256", nullptr));
        action_thresholdSetup->setText(QCoreApplication::translate("MainWindow", "\351\230\210\345\200\274\350\256\276\347\275\256", nullptr));
        action_filesave->setText(QCoreApplication::translate("MainWindow", "\346\225\260\346\215\256\345\217\246\345\255\230\344\270\272", nullptr));
        action_fileperview->setText(QCoreApplication::translate("MainWindow", "\346\225\260\346\215\256\351\242\204\350\247\210", nullptr));
        checkBox->setText(QCoreApplication::translate("MainWindow", "\351\200\232\351\201\2231", nullptr));
        checkBox_2->setText(QCoreApplication::translate("MainWindow", "\351\200\232\351\201\2232", nullptr));
        checkBox_upline->setText(QCoreApplication::translate("MainWindow", "\344\270\212\351\230\210\345\200\274\347\272\277", nullptr));
        checkBox_3->setText(QCoreApplication::translate("MainWindow", "\344\270\213\351\230\210\345\200\274\347\272\277", nullptr));
        groupBox_2->setTitle(QString());
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "\344\277\235\345\255\230", nullptr));
        pushButton_SerialSetup->setText(QCoreApplication::translate("MainWindow", "\344\270\262\345\217\243", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "\345\274\200\345\247\213", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "\346\225\260\346\215\256\351\242\204\350\247\210", nullptr));
        pushButton_connect_state->setText(QString());
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "\346\225\260\346\215\256\345\244\204\347\220\206", nullptr));
        pushButton_5->setText(QCoreApplication::translate("MainWindow", "\347\211\271\345\276\201\345\214\272\345\237\237", nullptr));
        groupBox->setTitle(QString());
        label_2->setText(QCoreApplication::translate("MainWindow", "\346\265\213\351\207\217\351\225\277\345\272\246", nullptr));
        lineEdit->setText(QString());
        label->setText(QCoreApplication::translate("MainWindow", "\344\277\235\345\255\230\346\240\207\347\255\276", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\347\201\265\346\225\217\345\272\246", nullptr));
        groupBox_4->setTitle(QString());
        label_4->setText(QCoreApplication::translate("MainWindow", "\347\272\277\346\200\247\346\213\237\345\220\210\345\207\275\346\225\260\357\274\232", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "\347\274\272\351\231\267\347\261\273\345\236\213", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "\347\274\272\351\231\267\347\274\226\345\217\267", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "\347\274\272\351\231\267\345\275\223\351\207\217\357\274\232", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "\347\274\272\351\231\267\345\256\275\346\267\261\346\257\224\357\274\232", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "\347\274\272\351\231\267\346\225\260\351\207\217\357\274\232", nullptr));
        label_14->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "\347\274\272\351\231\267\345\271\205\345\200\274\357\274\232", nullptr));
        label_15->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        menu_file->setTitle(QCoreApplication::translate("MainWindow", "\346\226\207\344\273\266", nullptr));
        menu_setup->setTitle(QCoreApplication::translate("MainWindow", "\350\256\276\347\275\256", nullptr));
        menu_standar->setTitle(QCoreApplication::translate("MainWindow", "\346\240\207\345\256\232", nullptr));
        menu_software->setTitle(QCoreApplication::translate("MainWindow", "\345\205\263\344\272\216", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
