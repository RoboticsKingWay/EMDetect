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
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_save;
    QAction *action_saveas;
    QAction *action_serial;
    QAction *action_setup_other;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *tab_1;
    QWidget *widget_tab_1;
    QVBoxLayout *verticalLayout_2;
    QWidget *widget_real_chat_view;
    QWidget *widget_chinnel;
    QHBoxLayout *horizontalLayout;
    QCheckBox *checkBox;
    QCheckBox *checkBox_2;
    QCheckBox *checkBox_3;
    QCheckBox *checkBox_4;
    QCheckBox *checkBox_5;
    QCheckBox *checkBox_6;
    QSpacerItem *horizontalSpacer;
    QWidget *tab_2;
    QWidget *widget_tab_2;
    QHBoxLayout *horizontalLayout_2;
    QWidget *widget_tab_2_view;
    QVBoxLayout *verticalLayout_3;
    QWidget *widget_real_total_view;
    QWidget *widget_image_view;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_image;
    QWidget *widget_down;
    QGridLayout *gridLayout_3;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *label_2;
    QLineEdit *lineEdit;
    QLabel *label;
    QLineEdit *lineEdit_2;
    QComboBox *comboBox;
    QLabel *label_3;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton;
    QPushButton *pushButton_SerialSetup;
    QPushButton *pushButton_6;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer;
    QGroupBox *groupBox_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_4;
    QLabel *label_5;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1009, 749);
        MainWindow->setMinimumSize(QSize(850, 700));
        MainWindow->setStyleSheet(QString::fromUtf8("/*QMainWindow\n"
"{\n"
"    background-color: #D7D7D7;\n"
"	border: 3px solid #333333;\n"
"}*/"));
        action_save = new QAction(MainWindow);
        action_save->setObjectName(QString::fromUtf8("action_save"));
        action_saveas = new QAction(MainWindow);
        action_saveas->setObjectName(QString::fromUtf8("action_saveas"));
        action_serial = new QAction(MainWindow);
        action_serial->setObjectName(QString::fromUtf8("action_serial"));
        action_setup_other = new QAction(MainWindow);
        action_setup_other->setObjectName(QString::fromUtf8("action_setup_other"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        centralwidget->setMinimumSize(QSize(850, 670));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setSpacing(5);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(-1, 5, -1, 5);
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy);
        tabWidget->setMinimumSize(QSize(670, 540));
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        tabWidget->setFont(font);
        tabWidget->setIconSize(QSize(30, 8));
        tab_1 = new QWidget();
        tab_1->setObjectName(QString::fromUtf8("tab_1"));
        tab_1->setMinimumSize(QSize(670, 500));
        tab_1->setFont(font);
        widget_tab_1 = new QWidget(tab_1);
        widget_tab_1->setObjectName(QString::fromUtf8("widget_tab_1"));
        widget_tab_1->setGeometry(QRect(0, -20, 991, 541));
        widget_tab_1->setMinimumSize(QSize(670, 0));
        QFont font1;
        font1.setPointSize(9);
        font1.setBold(false);
        widget_tab_1->setFont(font1);
        verticalLayout_2 = new QVBoxLayout(widget_tab_1);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        widget_real_chat_view = new QWidget(widget_tab_1);
        widget_real_chat_view->setObjectName(QString::fromUtf8("widget_real_chat_view"));
        QFont font2;
        font2.setPointSize(12);
        widget_real_chat_view->setFont(font2);
        widget_real_chat_view->setMouseTracking(true);
        widget_real_chat_view->setAutoFillBackground(true);

        verticalLayout_2->addWidget(widget_real_chat_view);

        widget_chinnel = new QWidget(widget_tab_1);
        widget_chinnel->setObjectName(QString::fromUtf8("widget_chinnel"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(widget_chinnel->sizePolicy().hasHeightForWidth());
        widget_chinnel->setSizePolicy(sizePolicy1);
        widget_chinnel->setMinimumSize(QSize(0, 40));
        horizontalLayout = new QHBoxLayout(widget_chinnel);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        checkBox = new QCheckBox(widget_chinnel);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));

        horizontalLayout->addWidget(checkBox);

        checkBox_2 = new QCheckBox(widget_chinnel);
        checkBox_2->setObjectName(QString::fromUtf8("checkBox_2"));

        horizontalLayout->addWidget(checkBox_2);

        checkBox_3 = new QCheckBox(widget_chinnel);
        checkBox_3->setObjectName(QString::fromUtf8("checkBox_3"));

        horizontalLayout->addWidget(checkBox_3);

        checkBox_4 = new QCheckBox(widget_chinnel);
        checkBox_4->setObjectName(QString::fromUtf8("checkBox_4"));

        horizontalLayout->addWidget(checkBox_4);

        checkBox_5 = new QCheckBox(widget_chinnel);
        checkBox_5->setObjectName(QString::fromUtf8("checkBox_5"));

        horizontalLayout->addWidget(checkBox_5);

        checkBox_6 = new QCheckBox(widget_chinnel);
        checkBox_6->setObjectName(QString::fromUtf8("checkBox_6"));

        horizontalLayout->addWidget(checkBox_6);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout_2->addWidget(widget_chinnel);

        tabWidget->addTab(tab_1, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        tab_2->setMinimumSize(QSize(670, 0));
        tab_2->setFont(font);
        widget_tab_2 = new QWidget(tab_2);
        widget_tab_2->setObjectName(QString::fromUtf8("widget_tab_2"));
        widget_tab_2->setGeometry(QRect(10, 0, 971, 521));
        widget_tab_2->setMinimumSize(QSize(670, 500));
        horizontalLayout_2 = new QHBoxLayout(widget_tab_2);
        horizontalLayout_2->setSpacing(1);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(-1, 0, -1, 0);
        widget_tab_2_view = new QWidget(widget_tab_2);
        widget_tab_2_view->setObjectName(QString::fromUtf8("widget_tab_2_view"));
        sizePolicy.setHeightForWidth(widget_tab_2_view->sizePolicy().hasHeightForWidth());
        widget_tab_2_view->setSizePolicy(sizePolicy);
        verticalLayout_3 = new QVBoxLayout(widget_tab_2_view);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        widget_real_total_view = new QWidget(widget_tab_2_view);
        widget_real_total_view->setObjectName(QString::fromUtf8("widget_real_total_view"));
        sizePolicy.setHeightForWidth(widget_real_total_view->sizePolicy().hasHeightForWidth());
        widget_real_total_view->setSizePolicy(sizePolicy);
        widget_real_total_view->setAutoFillBackground(true);

        verticalLayout_3->addWidget(widget_real_total_view);

        widget_image_view = new QWidget(widget_tab_2_view);
        widget_image_view->setObjectName(QString::fromUtf8("widget_image_view"));
        widget_image_view->setMinimumSize(QSize(600, 150));
        horizontalLayout_4 = new QHBoxLayout(widget_image_view);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_image = new QLabel(widget_image_view);
        label_image->setObjectName(QString::fromUtf8("label_image"));
        label_image->setAutoFillBackground(true);
        label_image->setAlignment(Qt::AlignCenter);

        horizontalLayout_4->addWidget(label_image);


        verticalLayout_3->addWidget(widget_image_view);


        horizontalLayout_2->addWidget(widget_tab_2_view);

        tabWidget->addTab(tab_2, QString());

        verticalLayout->addWidget(tabWidget);

        widget_down = new QWidget(centralwidget);
        widget_down->setObjectName(QString::fromUtf8("widget_down"));
        widget_down->setMinimumSize(QSize(780, 100));
        widget_down->setMaximumSize(QSize(16777215, 150));
        widget_down->setStyleSheet(QString::fromUtf8("QWidget\n"
"{\n"
"	background-color: white;\n"
"	#border: 3px solid #D3D3D3; \n"
"}"));
        gridLayout_3 = new QGridLayout(widget_down);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        groupBox = new QGroupBox(widget_down);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setMinimumSize(QSize(200, 110));
        groupBox->setMaximumSize(QSize(300, 120));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font2);

        gridLayout->addWidget(label_2, 1, 1, 1, 1);

        lineEdit = new QLineEdit(groupBox);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        gridLayout->addWidget(lineEdit, 0, 2, 1, 1);

        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setFont(font2);

        gridLayout->addWidget(label, 0, 1, 1, 1);

        lineEdit_2 = new QLineEdit(groupBox);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));

        gridLayout->addWidget(lineEdit_2, 1, 2, 1, 1);

        comboBox = new QComboBox(groupBox);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        gridLayout->addWidget(comboBox, 2, 2, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFont(font2);

        gridLayout->addWidget(label_3, 2, 1, 1, 1);


        gridLayout_3->addWidget(groupBox, 0, 0, 2, 1);

        groupBox_2 = new QGroupBox(widget_down);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setMinimumSize(QSize(240, 110));
        groupBox_2->setMaximumSize(QSize(240, 120));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setSizeConstraint(QLayout::SetDefaultConstraint);
        pushButton_2 = new QPushButton(groupBox_2);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setFont(font2);
        pushButton_2->setAutoDefault(false);

        gridLayout_2->addWidget(pushButton_2, 1, 1, 1, 1);

        pushButton_3 = new QPushButton(groupBox_2);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setFont(font2);

        gridLayout_2->addWidget(pushButton_3, 2, 0, 1, 1);

        pushButton_4 = new QPushButton(groupBox_2);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setFont(font2);

        gridLayout_2->addWidget(pushButton_4, 2, 1, 1, 1);

        pushButton = new QPushButton(groupBox_2);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setFont(font2);

        gridLayout_2->addWidget(pushButton, 1, 0, 1, 1);

        pushButton_SerialSetup = new QPushButton(groupBox_2);
        pushButton_SerialSetup->setObjectName(QString::fromUtf8("pushButton_SerialSetup"));
        pushButton_SerialSetup->setFont(font2);
        pushButton_SerialSetup->setStyleSheet(QString::fromUtf8("/*QPushButton {\n"
"				border: 4px outset gray;\n"
"                   border-radius: 3px;\n"
"}*/"));
        pushButton_SerialSetup->setFlat(false);

        gridLayout_2->addWidget(pushButton_SerialSetup, 0, 1, 1, 1);

        pushButton_6 = new QPushButton(groupBox_2);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
        pushButton_6->setFlat(true);

        gridLayout_2->addWidget(pushButton_6, 0, 0, 1, 1);


        gridLayout_3->addWidget(groupBox_2, 0, 1, 2, 1);

        horizontalSpacer_2 = new QSpacerItem(120, 68, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_2, 0, 2, 2, 1);

        verticalSpacer = new QSpacerItem(148, 73, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer, 0, 3, 1, 1);

        groupBox_3 = new QGroupBox(widget_down);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setMinimumSize(QSize(160, 50));
        groupBox_3->setMaximumSize(QSize(240, 50));
        horizontalLayout_3 = new QHBoxLayout(groupBox_3);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_4 = new QLabel(groupBox_3);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_3->addWidget(label_4);

        label_5 = new QLabel(groupBox_3);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setMinimumSize(QSize(140, 0));
        label_5->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(label_5);


        gridLayout_3->addWidget(groupBox_3, 1, 3, 1, 1);


        verticalLayout->addWidget(widget_down);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);
        pushButton_2->setDefault(false);
        pushButton_SerialSetup->setDefault(false);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "EMDetect", nullptr));
        action_save->setText(QCoreApplication::translate("MainWindow", "\344\277\235\345\255\230", nullptr));
        action_saveas->setText(QCoreApplication::translate("MainWindow", "\346\243\200\346\265\213\346\225\260\346\215\256\345\217\246\345\255\230", nullptr));
        action_serial->setText(QCoreApplication::translate("MainWindow", "\344\270\262\345\217\243\350\256\276\347\275\256", nullptr));
        action_setup_other->setText(QCoreApplication::translate("MainWindow", "\345\205\266\344\273\226\350\256\276\347\275\256", nullptr));
        checkBox->setText(QCoreApplication::translate("MainWindow", "\351\200\232\351\201\2231", nullptr));
        checkBox_2->setText(QCoreApplication::translate("MainWindow", "\351\200\232\351\201\2232", nullptr));
        checkBox_3->setText(QCoreApplication::translate("MainWindow", "\351\200\232\351\201\2233", nullptr));
        checkBox_4->setText(QCoreApplication::translate("MainWindow", "\351\200\232\351\201\2234", nullptr));
        checkBox_5->setText(QCoreApplication::translate("MainWindow", "\351\200\232\351\201\2235", nullptr));
        checkBox_6->setText(QCoreApplication::translate("MainWindow", "\351\200\232\351\201\2236", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_1), QCoreApplication::translate("MainWindow", "\345\256\236\346\227\266\346\233\262\347\272\277", nullptr));
        label_image->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("MainWindow", "\346\242\257\345\272\246\346\233\262\347\272\277", nullptr));
        groupBox->setTitle(QString());
        label_2->setText(QCoreApplication::translate("MainWindow", "\346\265\213\351\207\217\351\225\277\345\272\246", nullptr));
        lineEdit->setText(QString());
        label->setText(QCoreApplication::translate("MainWindow", "\344\277\235\345\255\230\346\240\207\347\255\276", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\347\201\265\346\225\217\345\272\246", nullptr));
        groupBox_2->setTitle(QString());
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "\344\277\235\345\255\230", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "\346\225\260\346\215\256\345\244\204\347\220\206", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "\346\225\260\346\215\256\351\242\204\350\247\210", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "\345\274\200\345\247\213", nullptr));
        pushButton_SerialSetup->setText(QCoreApplication::translate("MainWindow", "\344\270\262\345\217\243", nullptr));
        pushButton_6->setText(QCoreApplication::translate("MainWindow", "\350\277\236\346\216\245\347\212\266\346\200\201", nullptr));
        groupBox_3->setTitle(QString());
        label_4->setText(QCoreApplication::translate("MainWindow", "\346\243\200\346\265\213\346\227\266\351\227\264", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "2024.5.26 18:00:00", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
