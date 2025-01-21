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
    QVBoxLayout *verticalLayout_3;
    QWidget *widget_up;
    QHBoxLayout *horizontalLayout;
    QWidget *widget_upleft;
    QVBoxLayout *verticalLayout;
    QWidget *widget_real_chat_view;
    QWidget *widget_real_chat_view_2;
    QWidget *widget_real_upright;
    QVBoxLayout *verticalLayout_4;
    QWidget *widget_upright;
    QWidget *widget_down;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton_connect_state;
    QPushButton *pushButton;
    QPushButton *pushButton_5;
    QPushButton *pushButton_detect_area2;
    QGroupBox *groupBox_result_outside;
    QGridLayout *gridLayout;
    QLabel *label_2;
    QLineEdit *lineEdit_scan_length;
    QLabel *label;
    QPushButton *pushButton_3;
    QLabel *label_detect_type;
    QComboBox *comboBox;
    QComboBox *comboBox_2;
    QLabel *label_dynamic_content_1;
    QLabel *label_detection_deepth_and_db;
    QLabel *label_unit1_mm;
    QLabel *label_dynamic_content_2;
    QLabel *label_unit2_mm;
    QSpacerItem *horizontalSpacer;
    QLabel *label_detection_length_and_amp;
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
"background-color:#FAFAFF\n"
"}"));
        verticalLayout_3 = new QVBoxLayout(centralwidget);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
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
        verticalLayout = new QVBoxLayout(widget_upleft);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        widget_real_chat_view = new QWidget(widget_upleft);
        widget_real_chat_view->setObjectName(QString::fromUtf8("widget_real_chat_view"));

        verticalLayout->addWidget(widget_real_chat_view);

        widget_real_chat_view_2 = new QWidget(widget_upleft);
        widget_real_chat_view_2->setObjectName(QString::fromUtf8("widget_real_chat_view_2"));

        verticalLayout->addWidget(widget_real_chat_view_2);


        horizontalLayout->addWidget(widget_upleft);

        widget_real_upright = new QWidget(widget_up);
        widget_real_upright->setObjectName(QString::fromUtf8("widget_real_upright"));
        verticalLayout_4 = new QVBoxLayout(widget_real_upright);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        widget_upright = new QWidget(widget_real_upright);
        widget_upright->setObjectName(QString::fromUtf8("widget_upright"));
        widget_upright->setMinimumSize(QSize(500, 0));

        verticalLayout_4->addWidget(widget_upright);

        widget_down = new QWidget(widget_real_upright);
        widget_down->setObjectName(QString::fromUtf8("widget_down"));
        widget_down->setMinimumSize(QSize(0, 0));
        widget_down->setMaximumSize(QSize(16777215, 1000));
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush1);
        QBrush brush3(QColor(250, 250, 255, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Button, brush3);
        palette1.setBrush(QPalette::Active, QPalette::Text, brush1);
        palette1.setBrush(QPalette::Active, QPalette::ButtonText, brush1);
        palette1.setBrush(QPalette::Active, QPalette::Base, brush3);
        palette1.setBrush(QPalette::Active, QPalette::Window, brush3);
        QBrush brush4(QColor(0, 0, 0, 128));
        brush4.setStyle(Qt::SolidPattern);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette1.setBrush(QPalette::Active, QPalette::PlaceholderText, brush4);
#endif
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Button, brush3);
        palette1.setBrush(QPalette::Inactive, QPalette::Text, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::ButtonText, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Base, brush3);
        palette1.setBrush(QPalette::Inactive, QPalette::Window, brush3);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette1.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush4);
#endif
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Button, brush3);
        palette1.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Base, brush3);
        palette1.setBrush(QPalette::Disabled, QPalette::Window, brush3);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette1.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush4);
#endif
        widget_down->setPalette(palette1);
        widget_down->setStyleSheet(QString::fromUtf8("QWidget{\n"
"		color: black\n"
"}"));
        verticalLayout_2 = new QVBoxLayout(widget_down);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        groupBox_2 = new QGroupBox(widget_down);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setMinimumSize(QSize(0, 0));
        groupBox_2->setMaximumSize(QSize(600, 66));
        horizontalLayout_2 = new QHBoxLayout(groupBox_2);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        pushButton_connect_state = new QPushButton(groupBox_2);
        pushButton_connect_state->setObjectName(QString::fromUtf8("pushButton_connect_state"));
        pushButton_connect_state->setStyleSheet(QString::fromUtf8(""));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/source/serial_close.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_connect_state->setIcon(icon1);
        pushButton_connect_state->setFlat(true);

        horizontalLayout_2->addWidget(pushButton_connect_state);

        pushButton = new QPushButton(groupBox_2);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        QFont font;
        font.setPointSize(12);
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

        horizontalLayout_2->addWidget(pushButton);

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

        horizontalLayout_2->addWidget(pushButton_5);

        pushButton_detect_area2 = new QPushButton(groupBox_2);
        pushButton_detect_area2->setObjectName(QString::fromUtf8("pushButton_detect_area2"));
        pushButton_detect_area2->setFont(font);
        pushButton_detect_area2->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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

        horizontalLayout_2->addWidget(pushButton_detect_area2);


        verticalLayout_2->addWidget(groupBox_2);

        groupBox_result_outside = new QGroupBox(widget_down);
        groupBox_result_outside->setObjectName(QString::fromUtf8("groupBox_result_outside"));
        groupBox_result_outside->setFlat(false);
        gridLayout = new QGridLayout(groupBox_result_outside);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_2 = new QLabel(groupBox_result_outside);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font);

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        lineEdit_scan_length = new QLineEdit(groupBox_result_outside);
        lineEdit_scan_length->setObjectName(QString::fromUtf8("lineEdit_scan_length"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lineEdit_scan_length->sizePolicy().hasHeightForWidth());
        lineEdit_scan_length->setSizePolicy(sizePolicy);
        lineEdit_scan_length->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(lineEdit_scan_length, 0, 1, 1, 2);

        label = new QLabel(groupBox_result_outside);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 3, 1, 1);

        pushButton_3 = new QPushButton(groupBox_result_outside);
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

        gridLayout->addWidget(pushButton_3, 0, 4, 1, 1);

        label_detect_type = new QLabel(groupBox_result_outside);
        label_detect_type->setObjectName(QString::fromUtf8("label_detect_type"));
        label_detect_type->setFont(font);

        gridLayout->addWidget(label_detect_type, 1, 0, 1, 1);

        comboBox = new QComboBox(groupBox_result_outside);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setFont(font);

        gridLayout->addWidget(comboBox, 1, 1, 1, 2);

        comboBox_2 = new QComboBox(groupBox_result_outside);
        comboBox_2->addItem(QString());
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));
        comboBox_2->setFont(font);

        gridLayout->addWidget(comboBox_2, 1, 4, 1, 1);

        label_dynamic_content_1 = new QLabel(groupBox_result_outside);
        label_dynamic_content_1->setObjectName(QString::fromUtf8("label_dynamic_content_1"));
        label_dynamic_content_1->setFont(font);

        gridLayout->addWidget(label_dynamic_content_1, 2, 0, 1, 1);

        label_detection_deepth_and_db = new QLabel(groupBox_result_outside);
        label_detection_deepth_and_db->setObjectName(QString::fromUtf8("label_detection_deepth_and_db"));

        gridLayout->addWidget(label_detection_deepth_and_db, 2, 1, 1, 1);

        label_unit1_mm = new QLabel(groupBox_result_outside);
        label_unit1_mm->setObjectName(QString::fromUtf8("label_unit1_mm"));

        gridLayout->addWidget(label_unit1_mm, 2, 3, 1, 1);

        label_dynamic_content_2 = new QLabel(groupBox_result_outside);
        label_dynamic_content_2->setObjectName(QString::fromUtf8("label_dynamic_content_2"));
        label_dynamic_content_2->setFont(font);

        gridLayout->addWidget(label_dynamic_content_2, 3, 0, 1, 1);

        label_unit2_mm = new QLabel(groupBox_result_outside);
        label_unit2_mm->setObjectName(QString::fromUtf8("label_unit2_mm"));

        gridLayout->addWidget(label_unit2_mm, 3, 3, 1, 1);

        horizontalSpacer = new QSpacerItem(499, 18, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 4, 0, 1, 5);

        label_detection_length_and_amp = new QLabel(groupBox_result_outside);
        label_detection_length_and_amp->setObjectName(QString::fromUtf8("label_detection_length_and_amp"));

        gridLayout->addWidget(label_detection_length_and_amp, 3, 1, 1, 1);


        verticalLayout_2->addWidget(groupBox_result_outside);


        verticalLayout_4->addWidget(widget_down);


        horizontalLayout->addWidget(widget_real_upright);


        verticalLayout_3->addWidget(widget_up);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1200, 25));
        menuBar->setFont(font);
        menuBar->setStyleSheet(QString::fromUtf8("QMenu{\n"
"        color:black\n"
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

        pushButton->setDefault(true);
        pushButton_5->setDefault(true);


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
        groupBox_2->setTitle(QString());
        pushButton_connect_state->setText(QCoreApplication::translate("MainWindow", "\344\270\262\345\217\243\347\212\266\346\200\201", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "\345\274\200\345\247\213", nullptr));
        pushButton_5->setText(QCoreApplication::translate("MainWindow", "\347\211\271\345\276\201\345\214\272\345\237\2371", nullptr));
        pushButton_detect_area2->setText(QCoreApplication::translate("MainWindow", "\347\211\271\345\276\201\345\214\272\345\237\2372", nullptr));
        groupBox_result_outside->setTitle(QString());
        label_2->setText(QCoreApplication::translate("MainWindow", "\346\265\213\351\207\217\351\225\277\345\272\246", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "mm", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "\346\225\260\346\215\256\345\244\204\347\220\206", nullptr));
        label_detect_type->setText(QCoreApplication::translate("MainWindow", "\347\274\272\351\231\267\347\261\273\345\236\213", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("MainWindow", "\345\244\226\351\203\250\347\274\272\351\231\267", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("MainWindow", "\345\206\205\351\203\250\347\274\272\351\231\267", nullptr));

        comboBox_2->setItemText(0, QCoreApplication::translate("MainWindow", "\345\206\205\351\203\250\347\274\272\351\231\267\347\255\211\347\272\247", nullptr));

        label_dynamic_content_1->setText(QCoreApplication::translate("MainWindow", "\347\274\272\351\231\267\346\267\261\345\272\246\357\274\232", nullptr));
        label_detection_deepth_and_db->setText(QString());
        label_unit1_mm->setText(QCoreApplication::translate("MainWindow", "mm", nullptr));
        label_dynamic_content_2->setText(QCoreApplication::translate("MainWindow", "\347\274\272\351\231\267\351\225\277\345\272\246\357\274\232", nullptr));
        label_unit2_mm->setText(QCoreApplication::translate("MainWindow", "mm", nullptr));
        label_detection_length_and_amp->setText(QString());
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
