/********************************************************************************
** Form generated from reading UI file 'calibrateview.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CALIBRATEVIEW_H
#define UI_CALIBRATEVIEW_H

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
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CalibrateView
{
public:
    QWidget *tab;
    QWidget *widget_outside;
    QWidget *widget_2;
    QWidget *widget_9;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_3;
    QComboBox *comboBox_outside_list;
    QWidget *widget_10;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLabel *label_outside_depth_read;
    QWidget *widget_11;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_2;
    QLabel *label_outside_db_read;
    QWidget *widget_15;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_16;
    QLabel *label_outside_width_read;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_3;
    QWidget *widget_12;
    QGridLayout *gridLayout;
    QLabel *label_4;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *pushButton_outside_add;
    QLineEdit *lineEdit_deep_set;
    QLineEdit *lineEdit_outside_addnum;
    QLabel *label_11;
    QLabel *label_5;
    QLineEdit *lineEdit_width_set;
    QLabel *label_15;
    QLineEdit *lineEdit_outside_db_set;
    QWidget *widget_4;
    QGridLayout *gridLayout_2;
    QLabel *label_6;
    QComboBox *comboBox_outside_del;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *pushButton_outside_del;
    QLabel *label_13;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_3;
    QLabel *label_17;
    QLineEdit *lineEdit_stand_result;
    QPushButton *pushButton_outside_stand;
    QLabel *label_18;
    QLineEdit *lineEdit_stand_result_label;
    QPushButton *pushButton_outside_stand_save;
    QWidget *tab_2;
    QWidget *widget_3;
    QWidget *widget_14;
    QVBoxLayout *verticalLayout;
    QWidget *widget_5;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_7;
    QComboBox *comboBox_inside_list;
    QWidget *widget_13;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_8;
    QLabel *label_inside_db_read;
    QLabel *label_14;
    QWidget *widget_8;
    QHBoxLayout *horizontalLayout_6;
    QWidget *widget_6;
    QGridLayout *gridLayout_6;
    QLabel *label_12;
    QLineEdit *lineEdit_inside_add_num;
    QLabel *label_9;
    QPushButton *pushButton_inside_add;
    QLineEdit *lineEdit_inside_write;
    QSpacerItem *horizontalSpacer_7;
    QWidget *widget_7;
    QGridLayout *gridLayout_5;
    QComboBox *comboBox_inside_del;
    QPushButton *pushButton_inside_del;
    QSpacerItem *horizontalSpacer_8;
    QLabel *label_10;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout_9;
    QPushButton *pushButton_inside_stand;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *pushButton_inside_stand_save;

    void setupUi(QTabWidget *CalibrateView)
    {
        if (CalibrateView->objectName().isEmpty())
            CalibrateView->setObjectName(QString::fromUtf8("CalibrateView"));
        CalibrateView->resize(641, 498);
        QFont font;
        font.setPointSize(12);
        CalibrateView->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/source/title.png"), QSize(), QIcon::Normal, QIcon::Off);
        CalibrateView->setWindowIcon(icon);
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        widget_outside = new QWidget(tab);
        widget_outside->setObjectName(QString::fromUtf8("widget_outside"));
        widget_outside->setGeometry(QRect(10, 10, 611, 441));
        widget_2 = new QWidget(widget_outside);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        widget_2->setGeometry(QRect(10, 0, 551, 117));
        widget_9 = new QWidget(widget_2);
        widget_9->setObjectName(QString::fromUtf8("widget_9"));
        widget_9->setGeometry(QRect(9, 9, 231, 47));
        horizontalLayout_5 = new QHBoxLayout(widget_9);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_3 = new QLabel(widget_9);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_5->addWidget(label_3);

        comboBox_outside_list = new QComboBox(widget_9);
        comboBox_outside_list->addItem(QString());
        comboBox_outside_list->addItem(QString());
        comboBox_outside_list->addItem(QString());
        comboBox_outside_list->setObjectName(QString::fromUtf8("comboBox_outside_list"));
        comboBox_outside_list->setMinimumSize(QSize(120, 30));

        horizontalLayout_5->addWidget(comboBox_outside_list);

        widget_10 = new QWidget(widget_2);
        widget_10->setObjectName(QString::fromUtf8("widget_10"));
        widget_10->setGeometry(QRect(9, 62, 181, 46));
        horizontalLayout = new QHBoxLayout(widget_10);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(widget_10);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        label_outside_depth_read = new QLabel(widget_10);
        label_outside_depth_read->setObjectName(QString::fromUtf8("label_outside_depth_read"));

        horizontalLayout->addWidget(label_outside_depth_read);

        widget_11 = new QWidget(widget_2);
        widget_11->setObjectName(QString::fromUtf8("widget_11"));
        widget_11->setGeometry(QRect(370, 62, 171, 46));
        horizontalLayout_4 = new QHBoxLayout(widget_11);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_2 = new QLabel(widget_11);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_4->addWidget(label_2);

        label_outside_db_read = new QLabel(widget_11);
        label_outside_db_read->setObjectName(QString::fromUtf8("label_outside_db_read"));

        horizontalLayout_4->addWidget(label_outside_db_read);

        widget_15 = new QWidget(widget_2);
        widget_15->setObjectName(QString::fromUtf8("widget_15"));
        widget_15->setGeometry(QRect(200, 60, 161, 46));
        horizontalLayout_10 = new QHBoxLayout(widget_15);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        label_16 = new QLabel(widget_15);
        label_16->setObjectName(QString::fromUtf8("label_16"));

        horizontalLayout_10->addWidget(label_16);

        label_outside_width_read = new QLabel(widget_15);
        label_outside_width_read->setObjectName(QString::fromUtf8("label_outside_width_read"));

        horizontalLayout_10->addWidget(label_outside_width_read);

        widget = new QWidget(widget_outside);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(10, 130, 541, 201));
        horizontalLayout_3 = new QHBoxLayout(widget);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        widget_12 = new QWidget(widget);
        widget_12->setObjectName(QString::fromUtf8("widget_12"));
        gridLayout = new QGridLayout(widget_12);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_4 = new QLabel(widget_12);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 1, 0, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(61, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 4, 0, 1, 1);

        pushButton_outside_add = new QPushButton(widget_12);
        pushButton_outside_add->setObjectName(QString::fromUtf8("pushButton_outside_add"));

        gridLayout->addWidget(pushButton_outside_add, 4, 1, 1, 1);

        lineEdit_deep_set = new QLineEdit(widget_12);
        lineEdit_deep_set->setObjectName(QString::fromUtf8("lineEdit_deep_set"));
        lineEdit_deep_set->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(lineEdit_deep_set, 1, 1, 1, 1);

        lineEdit_outside_addnum = new QLineEdit(widget_12);
        lineEdit_outside_addnum->setObjectName(QString::fromUtf8("lineEdit_outside_addnum"));
        lineEdit_outside_addnum->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(lineEdit_outside_addnum, 0, 1, 1, 1);

        label_11 = new QLabel(widget_12);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        gridLayout->addWidget(label_11, 0, 0, 1, 1);

        label_5 = new QLabel(widget_12);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 2, 0, 1, 1);

        lineEdit_width_set = new QLineEdit(widget_12);
        lineEdit_width_set->setObjectName(QString::fromUtf8("lineEdit_width_set"));
        lineEdit_width_set->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(lineEdit_width_set, 2, 1, 1, 1);

        label_15 = new QLabel(widget_12);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        gridLayout->addWidget(label_15, 3, 0, 1, 1);

        lineEdit_outside_db_set = new QLineEdit(widget_12);
        lineEdit_outside_db_set->setObjectName(QString::fromUtf8("lineEdit_outside_db_set"));
        lineEdit_outside_db_set->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(lineEdit_outside_db_set, 3, 1, 1, 1);


        horizontalLayout_3->addWidget(widget_12);

        widget_4 = new QWidget(widget);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        gridLayout_2 = new QGridLayout(widget_4);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_6 = new QLabel(widget_4);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_2->addWidget(label_6, 0, 0, 1, 1);

        comboBox_outside_del = new QComboBox(widget_4);
        comboBox_outside_del->setObjectName(QString::fromUtf8("comboBox_outside_del"));
        comboBox_outside_del->setMinimumSize(QSize(120, 30));

        gridLayout_2->addWidget(comboBox_outside_del, 0, 1, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(125, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_4, 1, 0, 1, 1);

        pushButton_outside_del = new QPushButton(widget_4);
        pushButton_outside_del->setObjectName(QString::fromUtf8("pushButton_outside_del"));

        gridLayout_2->addWidget(pushButton_outside_del, 1, 1, 1, 1);


        horizontalLayout_3->addWidget(widget_4);

        label_13 = new QLabel(widget_outside);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(20, 120, 551, 20));
        groupBox = new QGroupBox(widget_outside);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 330, 471, 91));
        gridLayout_3 = new QGridLayout(groupBox);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        label_17 = new QLabel(groupBox);
        label_17->setObjectName(QString::fromUtf8("label_17"));

        gridLayout_3->addWidget(label_17, 0, 0, 1, 1);

        lineEdit_stand_result = new QLineEdit(groupBox);
        lineEdit_stand_result->setObjectName(QString::fromUtf8("lineEdit_stand_result"));

        gridLayout_3->addWidget(lineEdit_stand_result, 0, 1, 1, 1);

        pushButton_outside_stand = new QPushButton(groupBox);
        pushButton_outside_stand->setObjectName(QString::fromUtf8("pushButton_outside_stand"));

        gridLayout_3->addWidget(pushButton_outside_stand, 0, 2, 1, 1);

        label_18 = new QLabel(groupBox);
        label_18->setObjectName(QString::fromUtf8("label_18"));

        gridLayout_3->addWidget(label_18, 1, 0, 1, 1);

        lineEdit_stand_result_label = new QLineEdit(groupBox);
        lineEdit_stand_result_label->setObjectName(QString::fromUtf8("lineEdit_stand_result_label"));

        gridLayout_3->addWidget(lineEdit_stand_result_label, 1, 1, 1, 1);

        pushButton_outside_stand_save = new QPushButton(groupBox);
        pushButton_outside_stand_save->setObjectName(QString::fromUtf8("pushButton_outside_stand_save"));

        gridLayout_3->addWidget(pushButton_outside_stand_save, 1, 2, 1, 1);

        CalibrateView->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        widget_3 = new QWidget(tab_2);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        widget_3->setGeometry(QRect(10, 10, 501, 371));
        widget_14 = new QWidget(widget_3);
        widget_14->setObjectName(QString::fromUtf8("widget_14"));
        widget_14->setGeometry(QRect(9, 9, 271, 111));
        verticalLayout = new QVBoxLayout(widget_14);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        widget_5 = new QWidget(widget_14);
        widget_5->setObjectName(QString::fromUtf8("widget_5"));
        horizontalLayout_2 = new QHBoxLayout(widget_5);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_7 = new QLabel(widget_5);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        horizontalLayout_2->addWidget(label_7);

        comboBox_inside_list = new QComboBox(widget_5);
        comboBox_inside_list->setObjectName(QString::fromUtf8("comboBox_inside_list"));
        comboBox_inside_list->setMinimumSize(QSize(120, 30));

        horizontalLayout_2->addWidget(comboBox_inside_list);


        verticalLayout->addWidget(widget_5);

        widget_13 = new QWidget(widget_14);
        widget_13->setObjectName(QString::fromUtf8("widget_13"));
        horizontalLayout_7 = new QHBoxLayout(widget_13);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        label_8 = new QLabel(widget_13);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        horizontalLayout_7->addWidget(label_8);

        label_inside_db_read = new QLabel(widget_13);
        label_inside_db_read->setObjectName(QString::fromUtf8("label_inside_db_read"));

        horizontalLayout_7->addWidget(label_inside_db_read);


        verticalLayout->addWidget(widget_13);

        label_14 = new QLabel(widget_3);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(10, 130, 461, 5));
        label_14->setMaximumSize(QSize(16777215, 5));
        widget_8 = new QWidget(widget_3);
        widget_8->setObjectName(QString::fromUtf8("widget_8"));
        widget_8->setGeometry(QRect(10, 150, 471, 133));
        horizontalLayout_6 = new QHBoxLayout(widget_8);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        widget_6 = new QWidget(widget_8);
        widget_6->setObjectName(QString::fromUtf8("widget_6"));
        gridLayout_6 = new QGridLayout(widget_6);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        label_12 = new QLabel(widget_6);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        gridLayout_6->addWidget(label_12, 0, 0, 1, 2);

        lineEdit_inside_add_num = new QLineEdit(widget_6);
        lineEdit_inside_add_num->setObjectName(QString::fromUtf8("lineEdit_inside_add_num"));
        lineEdit_inside_add_num->setStyleSheet(QString::fromUtf8(""));

        gridLayout_6->addWidget(lineEdit_inside_add_num, 0, 2, 1, 2);

        label_9 = new QLabel(widget_6);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout_6->addWidget(label_9, 1, 0, 1, 1);

        pushButton_inside_add = new QPushButton(widget_6);
        pushButton_inside_add->setObjectName(QString::fromUtf8("pushButton_inside_add"));

        gridLayout_6->addWidget(pushButton_inside_add, 2, 3, 1, 1);

        lineEdit_inside_write = new QLineEdit(widget_6);
        lineEdit_inside_write->setObjectName(QString::fromUtf8("lineEdit_inside_write"));
        lineEdit_inside_write->setStyleSheet(QString::fromUtf8(""));

        gridLayout_6->addWidget(lineEdit_inside_write, 1, 2, 1, 2);

        horizontalSpacer_7 = new QSpacerItem(123, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_6->addItem(horizontalSpacer_7, 2, 0, 1, 2);


        horizontalLayout_6->addWidget(widget_6);

        widget_7 = new QWidget(widget_8);
        widget_7->setObjectName(QString::fromUtf8("widget_7"));
        gridLayout_5 = new QGridLayout(widget_7);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        comboBox_inside_del = new QComboBox(widget_7);
        comboBox_inside_del->setObjectName(QString::fromUtf8("comboBox_inside_del"));
        comboBox_inside_del->setMinimumSize(QSize(120, 30));

        gridLayout_5->addWidget(comboBox_inside_del, 0, 1, 1, 1);

        pushButton_inside_del = new QPushButton(widget_7);
        pushButton_inside_del->setObjectName(QString::fromUtf8("pushButton_inside_del"));

        gridLayout_5->addWidget(pushButton_inside_del, 1, 1, 1, 1);

        horizontalSpacer_8 = new QSpacerItem(126, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_5->addItem(horizontalSpacer_8, 1, 0, 1, 1);

        label_10 = new QLabel(widget_7);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_5->addWidget(label_10, 0, 0, 1, 1);


        horizontalLayout_6->addWidget(widget_7);

        groupBox_2 = new QGroupBox(widget_3);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(140, 300, 271, 61));
        horizontalLayout_9 = new QHBoxLayout(groupBox_2);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        pushButton_inside_stand = new QPushButton(groupBox_2);
        pushButton_inside_stand->setObjectName(QString::fromUtf8("pushButton_inside_stand"));

        horizontalLayout_9->addWidget(pushButton_inside_stand);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_5);

        pushButton_inside_stand_save = new QPushButton(groupBox_2);
        pushButton_inside_stand_save->setObjectName(QString::fromUtf8("pushButton_inside_stand_save"));

        horizontalLayout_9->addWidget(pushButton_inside_stand_save);

        CalibrateView->addTab(tab_2, QString());

        retranslateUi(CalibrateView);

        CalibrateView->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(CalibrateView);
    } // setupUi

    void retranslateUi(QTabWidget *CalibrateView)
    {
        CalibrateView->setWindowTitle(QCoreApplication::translate("CalibrateView", "\347\274\272\351\231\267\346\240\207\345\256\232", nullptr));
        label_3->setText(QCoreApplication::translate("CalibrateView", "\347\274\272\351\231\267\345\210\227\350\241\250", nullptr));
        comboBox_outside_list->setItemText(0, QCoreApplication::translate("CalibrateView", "\347\274\272\351\231\2671", nullptr));
        comboBox_outside_list->setItemText(1, QCoreApplication::translate("CalibrateView", "\347\274\272\351\231\2672", nullptr));
        comboBox_outside_list->setItemText(2, QCoreApplication::translate("CalibrateView", "\347\274\272\351\231\2673", nullptr));

        label->setText(QCoreApplication::translate("CalibrateView", "\347\274\272\351\231\267\346\267\261\345\272\246\357\274\232", nullptr));
        label_outside_depth_read->setText(QString());
        label_2->setText(QCoreApplication::translate("CalibrateView", "\347\274\272\351\231\267\345\271\205\345\200\274\357\274\232", nullptr));
        label_outside_db_read->setText(QString());
        label_16->setText(QCoreApplication::translate("CalibrateView", "\347\274\272\351\231\267\345\256\275\345\272\246\357\274\232", nullptr));
        label_outside_width_read->setText(QString());
        label_4->setText(QCoreApplication::translate("CalibrateView", "\347\274\272\351\231\267\346\267\261\345\272\246", nullptr));
        pushButton_outside_add->setText(QCoreApplication::translate("CalibrateView", "\346\226\260\345\242\236\347\274\272\351\231\267", nullptr));
        label_11->setText(QCoreApplication::translate("CalibrateView", "\347\274\272\351\231\267\347\274\226\345\217\267", nullptr));
        label_5->setText(QCoreApplication::translate("CalibrateView", "\347\274\272\351\231\267\345\256\275\345\272\246", nullptr));
        label_15->setText(QCoreApplication::translate("CalibrateView", "\347\274\272\351\231\267\345\271\205\345\200\274", nullptr));
        label_6->setText(QCoreApplication::translate("CalibrateView", "\351\200\211\346\213\251\345\210\240\351\231\244\347\274\272\351\231\267\347\274\226\345\217\267", nullptr));
        pushButton_outside_del->setText(QCoreApplication::translate("CalibrateView", "\345\210\240\351\231\244\347\274\272\351\231\267", nullptr));
        label_13->setText(QCoreApplication::translate("CalibrateView", "--------------------------------------------------------------------------------------------", nullptr));
        groupBox->setTitle(QString());
        label_17->setText(QCoreApplication::translate("CalibrateView", "\346\240\207\345\256\232\347\273\223\346\236\234", nullptr));
        pushButton_outside_stand->setText(QCoreApplication::translate("CalibrateView", "\346\240\207\345\256\232", nullptr));
        label_18->setText(QCoreApplication::translate("CalibrateView", "\344\277\235\345\255\230\346\240\207\347\255\276", nullptr));
        pushButton_outside_stand_save->setText(QCoreApplication::translate("CalibrateView", "\346\240\207\345\256\232\344\277\235\345\255\230", nullptr));
        CalibrateView->setTabText(CalibrateView->indexOf(tab), QCoreApplication::translate("CalibrateView", "\345\244\226\351\203\250\347\274\272\351\231\267\346\240\207\345\256\232", nullptr));
        label_7->setText(QCoreApplication::translate("CalibrateView", "\347\274\272\351\231\267\347\274\226\345\217\267", nullptr));
        label_8->setText(QCoreApplication::translate("CalibrateView", "\347\274\272\351\231\267\345\275\223\351\207\217\357\274\232", nullptr));
        label_inside_db_read->setText(QString());
        label_14->setText(QCoreApplication::translate("CalibrateView", "-----------------------------------------------------------------------------------", nullptr));
        label_12->setText(QCoreApplication::translate("CalibrateView", "\347\274\272\351\231\267\347\274\226\345\217\267", nullptr));
        label_9->setText(QCoreApplication::translate("CalibrateView", "\347\274\272\351\231\267\345\275\223\351\207\217", nullptr));
        pushButton_inside_add->setText(QCoreApplication::translate("CalibrateView", "\346\226\260\345\242\236\347\274\272\351\231\267", nullptr));
        pushButton_inside_del->setText(QCoreApplication::translate("CalibrateView", "\345\210\240\351\231\244\347\274\272\351\231\267", nullptr));
        label_10->setText(QCoreApplication::translate("CalibrateView", "\347\274\272\351\231\267\347\274\226\345\217\267", nullptr));
        groupBox_2->setTitle(QString());
        pushButton_inside_stand->setText(QCoreApplication::translate("CalibrateView", "\346\240\207\345\256\232", nullptr));
        pushButton_inside_stand_save->setText(QCoreApplication::translate("CalibrateView", "\346\240\207\345\256\232\344\277\235\345\255\230", nullptr));
        CalibrateView->setTabText(CalibrateView->indexOf(tab_2), QCoreApplication::translate("CalibrateView", "\345\206\205\351\203\250\347\274\272\351\231\267\346\240\207\345\256\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CalibrateView: public Ui_CalibrateView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CALIBRATEVIEW_H
