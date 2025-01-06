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
    QAction *action_fit_circle;
    QAction *action_filter;
    QAction *action_magstimulate;
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
    QPushButton *pushButton_connect_state;
    QPushButton *pushButton_5;
    QPushButton *pushButton;
    QPushButton *pushButton_3;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *label_2;
    QLineEdit *lineEdit_scan_length;
    QLabel *label_3;
    QComboBox *comboBox;
    QSpacerItem *horizontalSpacer_2;
    QGroupBox *groupBox_result_outside;
    QGridLayout *gridLayout_3;
    QLabel *label_func;
    QLabel *label_standar_function;
    QLabel *label_7;
    QLabel *label_detection_xy;
    QLabel *label_6;
    QLabel *label_detection_length;
    QGroupBox *groupBox_result_inside;
    QGridLayout *gridLayout_4;
    QLabel *label_detection_fuzhi;
    QLabel *label_db_equal;
    QLabel *label_8;
    QLabel *label_9;
    QComboBox *comboBox_2;
    QStatusBar *statusbar;
    QMenuBar *menuBar;
    QMenu *menu_file;
    QMenu *menu_setup;
    QMenu *menu_standar;
    QMenu *menu_software;
    QMenu *menu_magsetup;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1200, 700);
        MainWindow->setMinimumSize(QSize(1200, 700));
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(0, 0, 0, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        QBrush brush2(QColor(255, 255, 255, 128));
        brush2.setStyle(Qt::SolidPattern);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Active, QPalette::PlaceholderText, brush2);
#endif
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush2);
#endif
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush2);
#endif
        MainWindow->setPalette(palette);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/source/title.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setAutoFillBackground(true);
        MainWindow->setStyleSheet(QString::fromUtf8(""));
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
        action_fit_circle = new QAction(MainWindow);
        action_fit_circle->setObjectName(QString::fromUtf8("action_fit_circle"));
        action_filter = new QAction(MainWindow);
        action_filter->setObjectName(QString::fromUtf8("action_filter"));
        action_magstimulate = new QAction(MainWindow);
        action_magstimulate->setObjectName(QString::fromUtf8("action_magstimulate"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        centralwidget->setMinimumSize(QSize(1000, 670));
        centralwidget->setStyleSheet(QString::fromUtf8("QWidget{\n"
"background-color:white\n"
"}"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        widget_up = new QWidget(centralwidget);
        widget_up->setObjectName(QString::fromUtf8("widget_up"));
        widget_up->setMinimumSize(QSize(920, 0));
        widget_up->setAutoFillBackground(false);
        widget_up->setStyleSheet(QString::fromUtf8(""));
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
        widget_chinnel->setStyleSheet(QString::fromUtf8(""));
        horizontalLayout_2 = new QHBoxLayout(widget_chinnel);
        horizontalLayout_2->setSpacing(3);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(-1, 5, 5, 3);
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
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush1);
        palette1.setBrush(QPalette::Active, QPalette::Button, brush);
        palette1.setBrush(QPalette::Active, QPalette::Text, brush1);
        palette1.setBrush(QPalette::Active, QPalette::ButtonText, brush1);
        palette1.setBrush(QPalette::Active, QPalette::Base, brush);
        palette1.setBrush(QPalette::Active, QPalette::Window, brush);
        QBrush brush3(QColor(0, 0, 0, 128));
        brush3.setStyle(Qt::SolidPattern);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette1.setBrush(QPalette::Active, QPalette::PlaceholderText, brush3);
#endif
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Text, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::ButtonText, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Window, brush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette1.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush3);
#endif
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Button, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::Window, brush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette1.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush3);
#endif
        widget_down->setPalette(palette1);
        widget_down->setStyleSheet(QString::fromUtf8(""));
        horizontalLayout_3 = new QHBoxLayout(widget_down);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        groupBox_2 = new QGroupBox(widget_down);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setMinimumSize(QSize(260, 120));
        groupBox_2->setMaximumSize(QSize(360, 120));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        pushButton_connect_state = new QPushButton(groupBox_2);
        pushButton_connect_state->setObjectName(QString::fromUtf8("pushButton_connect_state"));
        pushButton_connect_state->setStyleSheet(QString::fromUtf8(""));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/source/serial_close.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_connect_state->setIcon(icon1);
        pushButton_connect_state->setFlat(true);

        gridLayout_2->addWidget(pushButton_connect_state, 0, 0, 1, 1);

        pushButton_5 = new QPushButton(groupBox_2);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        pushButton_5->setFont(font);
        pushButton_5->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"        border: 3px outset gray;\n"
"        background-color: #D8D8D8;\n"
"         color: black;\n"
"        }\n"
" QPushButton:disabled {\n"
"         background-color: #F1F1F1;\n"
"         color: white;\n"
"        }\n"
" QPushButton:pressed {\n"
"        border: 1px inset gray;\n"
"         background-color: #11FF11;\n"
"         color: white;\n"
"        }\n"
"    QPushButton:hover {\n"
"         background-color: #13B3B3;\n"
"        }"));
        pushButton_5->setAutoDefault(true);
        pushButton_5->setFlat(false);

        gridLayout_2->addWidget(pushButton_5, 1, 0, 1, 1);

        pushButton = new QPushButton(groupBox_2);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setFont(font);
        pushButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"        border: 3px outset gray;\n"
"        background-color: #D8D8D8;\n"
"         color: black;\n"
"        }\n"
" QPushButton:disabled {\n"
"         background-color: #F1F1F1;\n"
"         color: white;\n"
"        }\n"
" QPushButton:pressed {\n"
"        border: 1px inset gray;\n"
"         background-color: #11FF11;\n"
"         color: white;\n"
"        }\n"
"    QPushButton:hover {\n"
"         background-color: #13B3B3;\n"
"        }"));
        pushButton->setAutoDefault(true);

        gridLayout_2->addWidget(pushButton, 0, 1, 1, 1);

        pushButton_3 = new QPushButton(groupBox_2);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setFont(font);
        pushButton_3->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"        border: 3px outset gray;\n"
"        background-color: #D8D8D8;\n"
"         color: black;\n"
"        }\n"
" QPushButton:disabled {\n"
"         background-color: #F1F1F1;\n"
"         color: white;\n"
"        }\n"
" QPushButton:pressed {\n"
"        border: 1px inset gray;\n"
"         background-color: #11FF11;\n"
"         color: white;\n"
"        }\n"
"    QPushButton:hover {\n"
"         background-color: #13B3B3;\n"
"        }"));

        gridLayout_2->addWidget(pushButton_3, 1, 1, 1, 1);


        horizontalLayout_3->addWidget(groupBox_2);

        groupBox = new QGroupBox(widget_down);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setMinimumSize(QSize(220, 120));
        groupBox->setMaximumSize(QSize(350, 120));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setSpacing(2);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(2, 4, 2, 4);
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font);

        gridLayout->addWidget(label_2, 2, 0, 1, 1);

        lineEdit_scan_length = new QLineEdit(groupBox);
        lineEdit_scan_length->setObjectName(QString::fromUtf8("lineEdit_scan_length"));
        lineEdit_scan_length->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(lineEdit_scan_length, 2, 1, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFont(font);

        gridLayout->addWidget(label_3, 3, 0, 1, 1);

        comboBox = new QComboBox(groupBox);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setMinimumSize(QSize(80, 26));
        comboBox->setFont(font);
        comboBox->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(comboBox, 3, 1, 1, 1);


        horizontalLayout_3->addWidget(groupBox);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        groupBox_result_outside = new QGroupBox(widget_down);
        groupBox_result_outside->setObjectName(QString::fromUtf8("groupBox_result_outside"));
        gridLayout_3 = new QGridLayout(groupBox_result_outside);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        label_func = new QLabel(groupBox_result_outside);
        label_func->setObjectName(QString::fromUtf8("label_func"));
        label_func->setFont(font);

        gridLayout_3->addWidget(label_func, 0, 0, 1, 2);

        label_standar_function = new QLabel(groupBox_result_outside);
        label_standar_function->setObjectName(QString::fromUtf8("label_standar_function"));

        gridLayout_3->addWidget(label_standar_function, 1, 0, 1, 3);

        label_7 = new QLabel(groupBox_result_outside);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setFont(font);

        gridLayout_3->addWidget(label_7, 2, 0, 1, 1);

        label_detection_xy = new QLabel(groupBox_result_outside);
        label_detection_xy->setObjectName(QString::fromUtf8("label_detection_xy"));

        gridLayout_3->addWidget(label_detection_xy, 2, 1, 1, 1);

        label_6 = new QLabel(groupBox_result_outside);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setFont(font);

        gridLayout_3->addWidget(label_6, 2, 2, 1, 1);

        label_detection_length = new QLabel(groupBox_result_outside);
        label_detection_length->setObjectName(QString::fromUtf8("label_detection_length"));

        gridLayout_3->addWidget(label_detection_length, 2, 3, 1, 1);


        horizontalLayout_3->addWidget(groupBox_result_outside);

        groupBox_result_inside = new QGroupBox(widget_down);
        groupBox_result_inside->setObjectName(QString::fromUtf8("groupBox_result_inside"));
        QFont font1;
        font1.setPointSize(9);
        groupBox_result_inside->setFont(font1);
        groupBox_result_inside->setAutoFillBackground(false);
        gridLayout_4 = new QGridLayout(groupBox_result_inside);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_4->setContentsMargins(9, 2, -1, 2);
        label_detection_fuzhi = new QLabel(groupBox_result_inside);
        label_detection_fuzhi->setObjectName(QString::fromUtf8("label_detection_fuzhi"));

        gridLayout_4->addWidget(label_detection_fuzhi, 2, 2, 1, 1);

        label_db_equal = new QLabel(groupBox_result_inside);
        label_db_equal->setObjectName(QString::fromUtf8("label_db_equal"));

        gridLayout_4->addWidget(label_db_equal, 1, 2, 1, 1);

        label_8 = new QLabel(groupBox_result_inside);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setFont(font);

        gridLayout_4->addWidget(label_8, 2, 1, 1, 1);

        label_9 = new QLabel(groupBox_result_inside);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setFont(font);

        gridLayout_4->addWidget(label_9, 1, 1, 1, 1);

        comboBox_2 = new QComboBox(groupBox_result_inside);
        comboBox_2->addItem(QString());
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));
        comboBox_2->setFont(font);
        comboBox_2->setStyleSheet(QString::fromUtf8(""));

        gridLayout_4->addWidget(comboBox_2, 0, 1, 1, 1);


        horizontalLayout_3->addWidget(groupBox_result_inside);


        verticalLayout->addWidget(widget_down);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1200, 26));
        menuBar->setFont(font);
        menuBar->setStyleSheet(QString::fromUtf8("QMenu{\n"
"	color:black\n"
"}"));
        menu_file = new QMenu(menuBar);
        menu_file->setObjectName(QString::fromUtf8("menu_file"));
        menu_file->setFont(font);
        menu_file->setStyleSheet(QString::fromUtf8("    QMenu:hover {\n"
"         background-color: #13B3B3;\n"
"        }"));
        menu_setup = new QMenu(menuBar);
        menu_setup->setObjectName(QString::fromUtf8("menu_setup"));
        menu_setup->setFont(font);
        menu_setup->setStyleSheet(QString::fromUtf8("    QMenu:hover {\n"
"         background-color: #13B3B3;\n"
"        }"));
        menu_standar = new QMenu(menuBar);
        menu_standar->setObjectName(QString::fromUtf8("menu_standar"));
        menu_standar->setFont(font);
        menu_standar->setStyleSheet(QString::fromUtf8("    QMenu:hover {\n"
"         background-color: #13B3B3;\n"
"        }"));
        menu_software = new QMenu(menuBar);
        menu_software->setObjectName(QString::fromUtf8("menu_software"));
        menu_software->setFont(font);
        menu_software->setStyleSheet(QString::fromUtf8("    QMenu:hover {\n"
"         background-color: #13B3B3;\n"
"        }"));
        menu_magsetup = new QMenu(menuBar);
        menu_magsetup->setObjectName(QString::fromUtf8("menu_magsetup"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menu_file->menuAction());
        menuBar->addAction(menu_setup->menuAction());
        menuBar->addAction(menu_standar->menuAction());
        menuBar->addAction(menu_magsetup->menuAction());
        menuBar->addAction(menu_software->menuAction());
        menu_file->addAction(action_filesave);
        menu_file->addAction(action_fileperview);
        menu_setup->addAction(action_serialSetup);
        menu_setup->addAction(action_thresholdSetup);
        menu_setup->addAction(action_fit_circle);
        menu_setup->addAction(action_filter);
        menu_standar->addAction(action_outside);
        menu_standar->addAction(action_inside);
        menu_software->addAction(action_version);
        menu_software->addAction(action_readme);
        menu_magsetup->addAction(action_magstimulate);

        retranslateUi(MainWindow);

        pushButton_5->setDefault(true);
        pushButton->setDefault(true);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\351\207\221\345\261\236\346\236\204\344\273\266\350\243\202\347\272\271\347\274\272\351\231\267\347\232\204\347\243\201\346\243\200\346\265\213\347\263\273\347\273\237", nullptr));
        action_version->setText(QCoreApplication::translate("MainWindow", "\350\275\257\344\273\266\347\211\210\346\234\254", nullptr));
        action_readme->setText(QCoreApplication::translate("MainWindow", "\350\275\257\344\273\266\350\257\264\346\230\216", nullptr));
        action_outside->setText(QCoreApplication::translate("MainWindow", "\350\241\250\351\235\242\347\274\272\351\231\267", nullptr));
        action_inside->setText(QCoreApplication::translate("MainWindow", "\345\206\205\351\203\250\347\274\272\351\231\267", nullptr));
        action_serialSetup->setText(QCoreApplication::translate("MainWindow", "\344\270\262\345\217\243\350\256\276\347\275\256", nullptr));
        action_thresholdSetup->setText(QCoreApplication::translate("MainWindow", "\351\230\210\345\200\274\350\256\276\347\275\256", nullptr));
        action_filesave->setText(QCoreApplication::translate("MainWindow", "\346\225\260\346\215\256\345\217\246\345\255\230\344\270\272", nullptr));
        action_fileperview->setText(QCoreApplication::translate("MainWindow", "\346\225\260\346\215\256\351\242\204\350\247\210", nullptr));
        action_fit_circle->setText(QCoreApplication::translate("MainWindow", "\346\213\237\345\220\210\345\234\206\350\256\276\347\275\256", nullptr));
        action_filter->setText(QCoreApplication::translate("MainWindow", "\346\273\244\346\263\242\350\256\276\347\275\256", nullptr));
        action_magstimulate->setText(QCoreApplication::translate("MainWindow", "\346\277\200\345\212\261\350\256\276\347\275\256", nullptr));
        checkBox->setText(QCoreApplication::translate("MainWindow", "\351\200\232\351\201\2231", nullptr));
        checkBox_2->setText(QCoreApplication::translate("MainWindow", "\351\200\232\351\201\2232", nullptr));
        checkBox_upline->setText(QCoreApplication::translate("MainWindow", "\344\270\212\351\230\210\345\200\274\347\272\277", nullptr));
        checkBox_3->setText(QCoreApplication::translate("MainWindow", "\344\270\213\351\230\210\345\200\274\347\272\277", nullptr));
        groupBox_2->setTitle(QString());
        pushButton_connect_state->setText(QCoreApplication::translate("MainWindow", "\344\270\262\345\217\243\347\212\266\346\200\201", nullptr));
        pushButton_5->setText(QCoreApplication::translate("MainWindow", "\347\211\271\345\276\201\345\214\272\345\237\237", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "\345\274\200\345\247\213", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "\346\225\260\346\215\256\345\244\204\347\220\206", nullptr));
        groupBox->setTitle(QString());
        label_2->setText(QCoreApplication::translate("MainWindow", "\346\265\213\351\207\217\351\225\277\345\272\246", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\347\274\272\351\231\267\347\261\273\345\236\213", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("MainWindow", "\345\244\226\351\203\250\347\274\272\351\231\267", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("MainWindow", "\345\206\205\351\203\250\347\274\272\351\231\267", nullptr));

        groupBox_result_outside->setTitle(QCoreApplication::translate("MainWindow", "\345\244\226\351\203\250\347\274\272\351\231\267", nullptr));
        label_func->setText(QCoreApplication::translate("MainWindow", "\347\272\277\346\200\247\346\213\237\345\220\210\345\207\275\346\225\260\357\274\232", nullptr));
        label_standar_function->setText(QString());
        label_7->setText(QCoreApplication::translate("MainWindow", "\347\274\272\351\231\267\345\256\275\346\267\261\346\257\224\357\274\232", nullptr));
        label_detection_xy->setText(QString());
        label_6->setText(QCoreApplication::translate("MainWindow", "\347\274\272\351\231\267\345\256\275\345\272\246\357\274\232", nullptr));
        label_detection_length->setText(QString());
        groupBox_result_inside->setTitle(QCoreApplication::translate("MainWindow", "\345\206\205\351\203\250\347\274\272\351\231\267", nullptr));
        label_detection_fuzhi->setText(QString());
        label_db_equal->setText(QString());
        label_8->setText(QCoreApplication::translate("MainWindow", "\347\274\272\351\231\267\345\271\205\345\200\274\357\274\232", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "\347\274\272\351\231\267\345\275\223\351\207\217\357\274\232", nullptr));
        comboBox_2->setItemText(0, QCoreApplication::translate("MainWindow", "-\350\257\267\351\200\211\346\213\251", nullptr));

        menu_file->setTitle(QCoreApplication::translate("MainWindow", "\346\226\207\344\273\266", nullptr));
        menu_setup->setTitle(QCoreApplication::translate("MainWindow", "\350\256\276\347\275\256", nullptr));
        menu_standar->setTitle(QCoreApplication::translate("MainWindow", "\346\240\207\345\256\232", nullptr));
        menu_software->setTitle(QCoreApplication::translate("MainWindow", "\345\205\263\344\272\216", nullptr));
        menu_magsetup->setTitle(QCoreApplication::translate("MainWindow", "\347\243\201\346\277\200\345\212\261", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
