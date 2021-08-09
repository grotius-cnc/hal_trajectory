/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_9;
    QGridLayout *gridLayout_6;
    QPushButton *pushButton_mode_auto_start;
    QPushButton *pushButton_run_from_line;
    QLineEdit *lineEdit_run_from_line;
    QPushButton *pushButton_mode_auto_stop;
    QGridLayout *gridLayout_2;
    QPushButton *pushButton_m3_on;
    QPushButton *pushButton_m3_off;
    QPushButton *pushButton_m7_on;
    QPushButton *pushButton_m7_off;
    QPushButton *pushButton_m8_on;
    QPushButton *pushButton_m8_off;
    QPushButton *pushButton_power_rpm;
    QLineEdit *lineEdit_power_rpm;
    QGridLayout *gridLayout_5;
    QPushButton *pushButton_mode_auto;
    QPushButton *pushButton_load_gcode_file;
    QPushButton *pushButton_mode_jog;
    QGridLayout *gridLayout_3;
    QLabel *label_5;
    QLineEdit *lineEdit_max_velocity;
    QLabel *label_6;
    QLineEdit *lineEdit_max_acceleration;
    QLabel *label_7;
    QLineEdit *lineEdit_max_jerk;
    QPushButton *pushButton_max_values;
    QGridLayout *gridLayout;
    QPushButton *pushButton_jog_x_min;
    QPushButton *pushButton_jog_z_min;
    QPushButton *pushButton_jog_y_plus;
    QPushButton *pushButton_jog_z_plus;
    QPushButton *pushButton_jog_y_min;
    QPushButton *pushButton_jog_x_plus;
    QGridLayout *gridLayout_4;
    QLabel *label_2;
    QLineEdit *lineEdit_tooloffset_x;
    QLabel *label_3;
    QLineEdit *lineEdit_tooloffset_y;
    QLabel *label_4;
    QLineEdit *lineEdit_tooloffset_z;
    QPushButton *pushButton_tooloffset;
    QGridLayout *gridLayout_8;
    QPushButton *pushButton_load_mdi;
    QLabel *label_8;
    QLineEdit *lineEdit_mdi;
    QGridLayout *gridLayout_7;
    QLabel *label;
    QLineEdit *lineEdit_path_to_lcnc_bin;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(389, 577);
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(65, 65, 65, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Active, QPalette::ToolTipText, brush);
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
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush2);
#endif
        QBrush brush3(QColor(190, 190, 190, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush);
        QBrush brush4(QColor(0, 0, 0, 128));
        brush4.setStyle(Qt::SolidPattern);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush4);
#endif
        MainWindow->setPalette(palette);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout_9 = new QGridLayout(centralwidget);
        gridLayout_9->setObjectName(QString::fromUtf8("gridLayout_9"));
        gridLayout_6 = new QGridLayout();
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        pushButton_mode_auto_start = new QPushButton(centralwidget);
        pushButton_mode_auto_start->setObjectName(QString::fromUtf8("pushButton_mode_auto_start"));

        gridLayout_6->addWidget(pushButton_mode_auto_start, 0, 0, 1, 1);

        pushButton_run_from_line = new QPushButton(centralwidget);
        pushButton_run_from_line->setObjectName(QString::fromUtf8("pushButton_run_from_line"));

        gridLayout_6->addWidget(pushButton_run_from_line, 1, 0, 1, 2);

        lineEdit_run_from_line = new QLineEdit(centralwidget);
        lineEdit_run_from_line->setObjectName(QString::fromUtf8("lineEdit_run_from_line"));

        gridLayout_6->addWidget(lineEdit_run_from_line, 1, 2, 1, 2);

        pushButton_mode_auto_stop = new QPushButton(centralwidget);
        pushButton_mode_auto_stop->setObjectName(QString::fromUtf8("pushButton_mode_auto_stop"));

        gridLayout_6->addWidget(pushButton_mode_auto_stop, 0, 2, 1, 2);


        gridLayout_9->addLayout(gridLayout_6, 1, 0, 1, 1);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        pushButton_m3_on = new QPushButton(centralwidget);
        pushButton_m3_on->setObjectName(QString::fromUtf8("pushButton_m3_on"));

        gridLayout_2->addWidget(pushButton_m3_on, 0, 0, 1, 1);

        pushButton_m3_off = new QPushButton(centralwidget);
        pushButton_m3_off->setObjectName(QString::fromUtf8("pushButton_m3_off"));

        gridLayout_2->addWidget(pushButton_m3_off, 0, 1, 1, 1);

        pushButton_m7_on = new QPushButton(centralwidget);
        pushButton_m7_on->setObjectName(QString::fromUtf8("pushButton_m7_on"));

        gridLayout_2->addWidget(pushButton_m7_on, 1, 0, 1, 1);

        pushButton_m7_off = new QPushButton(centralwidget);
        pushButton_m7_off->setObjectName(QString::fromUtf8("pushButton_m7_off"));

        gridLayout_2->addWidget(pushButton_m7_off, 1, 1, 1, 1);

        pushButton_m8_on = new QPushButton(centralwidget);
        pushButton_m8_on->setObjectName(QString::fromUtf8("pushButton_m8_on"));

        gridLayout_2->addWidget(pushButton_m8_on, 2, 0, 1, 1);

        pushButton_m8_off = new QPushButton(centralwidget);
        pushButton_m8_off->setObjectName(QString::fromUtf8("pushButton_m8_off"));

        gridLayout_2->addWidget(pushButton_m8_off, 2, 1, 1, 1);

        pushButton_power_rpm = new QPushButton(centralwidget);
        pushButton_power_rpm->setObjectName(QString::fromUtf8("pushButton_power_rpm"));

        gridLayout_2->addWidget(pushButton_power_rpm, 3, 0, 1, 1);

        lineEdit_power_rpm = new QLineEdit(centralwidget);
        lineEdit_power_rpm->setObjectName(QString::fromUtf8("lineEdit_power_rpm"));

        gridLayout_2->addWidget(lineEdit_power_rpm, 3, 1, 1, 1);


        gridLayout_9->addLayout(gridLayout_2, 1, 1, 2, 1);

        gridLayout_5 = new QGridLayout();
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        pushButton_mode_auto = new QPushButton(centralwidget);
        pushButton_mode_auto->setObjectName(QString::fromUtf8("pushButton_mode_auto"));

        gridLayout_5->addWidget(pushButton_mode_auto, 0, 1, 1, 1);

        pushButton_load_gcode_file = new QPushButton(centralwidget);
        pushButton_load_gcode_file->setObjectName(QString::fromUtf8("pushButton_load_gcode_file"));

        gridLayout_5->addWidget(pushButton_load_gcode_file, 0, 0, 1, 1);

        pushButton_mode_jog = new QPushButton(centralwidget);
        pushButton_mode_jog->setObjectName(QString::fromUtf8("pushButton_mode_jog"));

        gridLayout_5->addWidget(pushButton_mode_jog, 1, 1, 1, 1);


        gridLayout_9->addLayout(gridLayout_5, 2, 0, 1, 1);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_3->addWidget(label_5, 0, 0, 1, 1);

        lineEdit_max_velocity = new QLineEdit(centralwidget);
        lineEdit_max_velocity->setObjectName(QString::fromUtf8("lineEdit_max_velocity"));

        gridLayout_3->addWidget(lineEdit_max_velocity, 0, 1, 1, 1);

        label_6 = new QLabel(centralwidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_3->addWidget(label_6, 1, 0, 1, 1);

        lineEdit_max_acceleration = new QLineEdit(centralwidget);
        lineEdit_max_acceleration->setObjectName(QString::fromUtf8("lineEdit_max_acceleration"));

        gridLayout_3->addWidget(lineEdit_max_acceleration, 1, 1, 1, 1);

        label_7 = new QLabel(centralwidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout_3->addWidget(label_7, 2, 0, 1, 1);

        lineEdit_max_jerk = new QLineEdit(centralwidget);
        lineEdit_max_jerk->setObjectName(QString::fromUtf8("lineEdit_max_jerk"));

        gridLayout_3->addWidget(lineEdit_max_jerk, 2, 1, 1, 1);

        pushButton_max_values = new QPushButton(centralwidget);
        pushButton_max_values->setObjectName(QString::fromUtf8("pushButton_max_values"));

        gridLayout_3->addWidget(pushButton_max_values, 3, 1, 1, 1);


        gridLayout_9->addLayout(gridLayout_3, 3, 0, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        pushButton_jog_x_min = new QPushButton(centralwidget);
        pushButton_jog_x_min->setObjectName(QString::fromUtf8("pushButton_jog_x_min"));

        gridLayout->addWidget(pushButton_jog_x_min, 0, 0, 1, 1);

        pushButton_jog_z_min = new QPushButton(centralwidget);
        pushButton_jog_z_min->setObjectName(QString::fromUtf8("pushButton_jog_z_min"));

        gridLayout->addWidget(pushButton_jog_z_min, 2, 0, 1, 1);

        pushButton_jog_y_plus = new QPushButton(centralwidget);
        pushButton_jog_y_plus->setObjectName(QString::fromUtf8("pushButton_jog_y_plus"));

        gridLayout->addWidget(pushButton_jog_y_plus, 1, 1, 1, 1);

        pushButton_jog_z_plus = new QPushButton(centralwidget);
        pushButton_jog_z_plus->setObjectName(QString::fromUtf8("pushButton_jog_z_plus"));

        gridLayout->addWidget(pushButton_jog_z_plus, 2, 1, 1, 1);

        pushButton_jog_y_min = new QPushButton(centralwidget);
        pushButton_jog_y_min->setObjectName(QString::fromUtf8("pushButton_jog_y_min"));

        gridLayout->addWidget(pushButton_jog_y_min, 1, 0, 1, 1);

        pushButton_jog_x_plus = new QPushButton(centralwidget);
        pushButton_jog_x_plus->setObjectName(QString::fromUtf8("pushButton_jog_x_plus"));

        gridLayout->addWidget(pushButton_jog_x_plus, 0, 1, 1, 1);


        gridLayout_9->addLayout(gridLayout, 3, 1, 2, 1);

        gridLayout_4 = new QGridLayout();
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_4->addWidget(label_2, 0, 0, 1, 1);

        lineEdit_tooloffset_x = new QLineEdit(centralwidget);
        lineEdit_tooloffset_x->setObjectName(QString::fromUtf8("lineEdit_tooloffset_x"));

        gridLayout_4->addWidget(lineEdit_tooloffset_x, 0, 1, 1, 1);

        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_4->addWidget(label_3, 1, 0, 1, 1);

        lineEdit_tooloffset_y = new QLineEdit(centralwidget);
        lineEdit_tooloffset_y->setObjectName(QString::fromUtf8("lineEdit_tooloffset_y"));

        gridLayout_4->addWidget(lineEdit_tooloffset_y, 1, 1, 1, 1);

        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_4->addWidget(label_4, 2, 0, 1, 1);

        lineEdit_tooloffset_z = new QLineEdit(centralwidget);
        lineEdit_tooloffset_z->setObjectName(QString::fromUtf8("lineEdit_tooloffset_z"));

        gridLayout_4->addWidget(lineEdit_tooloffset_z, 2, 1, 1, 1);

        pushButton_tooloffset = new QPushButton(centralwidget);
        pushButton_tooloffset->setObjectName(QString::fromUtf8("pushButton_tooloffset"));

        gridLayout_4->addWidget(pushButton_tooloffset, 3, 1, 1, 1);


        gridLayout_9->addLayout(gridLayout_4, 4, 0, 1, 1);

        gridLayout_8 = new QGridLayout();
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        pushButton_load_mdi = new QPushButton(centralwidget);
        pushButton_load_mdi->setObjectName(QString::fromUtf8("pushButton_load_mdi"));

        gridLayout_8->addWidget(pushButton_load_mdi, 0, 1, 1, 1);

        label_8 = new QLabel(centralwidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_8->sizePolicy().hasHeightForWidth());
        label_8->setSizePolicy(sizePolicy);

        gridLayout_8->addWidget(label_8, 0, 0, 1, 1);

        lineEdit_mdi = new QLineEdit(centralwidget);
        lineEdit_mdi->setObjectName(QString::fromUtf8("lineEdit_mdi"));

        gridLayout_8->addWidget(lineEdit_mdi, 1, 0, 1, 2);


        gridLayout_9->addLayout(gridLayout_8, 5, 0, 1, 2);

        gridLayout_7 = new QGridLayout();
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_7->addWidget(label, 0, 0, 1, 1);

        lineEdit_path_to_lcnc_bin = new QLineEdit(centralwidget);
        lineEdit_path_to_lcnc_bin->setObjectName(QString::fromUtf8("lineEdit_path_to_lcnc_bin"));

        gridLayout_7->addWidget(lineEdit_path_to_lcnc_bin, 0, 1, 1, 1);


        gridLayout_9->addLayout(gridLayout_7, 0, 0, 1, 2);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 389, 20));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "- trajectory component halcmd test app -", nullptr));
        pushButton_mode_auto_start->setText(QCoreApplication::translate("MainWindow", "start - resume", nullptr));
        pushButton_run_from_line->setText(QCoreApplication::translate("MainWindow", "Run from line", nullptr));
        lineEdit_run_from_line->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        pushButton_mode_auto_stop->setText(QCoreApplication::translate("MainWindow", "pause - stop", nullptr));
        pushButton_m3_on->setText(QCoreApplication::translate("MainWindow", "m3 on", nullptr));
        pushButton_m3_off->setText(QCoreApplication::translate("MainWindow", "m3 off", nullptr));
        pushButton_m7_on->setText(QCoreApplication::translate("MainWindow", "m7 on", nullptr));
        pushButton_m7_off->setText(QCoreApplication::translate("MainWindow", "m7 off", nullptr));
        pushButton_m8_on->setText(QCoreApplication::translate("MainWindow", "m8 on", nullptr));
        pushButton_m8_off->setText(QCoreApplication::translate("MainWindow", "m8 off", nullptr));
        pushButton_power_rpm->setText(QCoreApplication::translate("MainWindow", "set power", nullptr));
        lineEdit_power_rpm->setText(QCoreApplication::translate("MainWindow", "45", nullptr));
        pushButton_mode_auto->setText(QCoreApplication::translate("MainWindow", "mode auto", nullptr));
        pushButton_load_gcode_file->setText(QCoreApplication::translate("MainWindow", "load gcode file", nullptr));
        pushButton_mode_jog->setText(QCoreApplication::translate("MainWindow", "mode jog", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "max velocity [+/-]", nullptr));
        lineEdit_max_velocity->setText(QCoreApplication::translate("MainWindow", "100", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "max acceleration", nullptr));
        lineEdit_max_acceleration->setText(QCoreApplication::translate("MainWindow", "90", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "max jerk", nullptr));
        lineEdit_max_jerk->setText(QCoreApplication::translate("MainWindow", "500", nullptr));
        pushButton_max_values->setText(QCoreApplication::translate("MainWindow", "set values", nullptr));
        pushButton_jog_x_min->setText(QCoreApplication::translate("MainWindow", "X-", nullptr));
        pushButton_jog_z_min->setText(QCoreApplication::translate("MainWindow", "Z-", nullptr));
        pushButton_jog_y_plus->setText(QCoreApplication::translate("MainWindow", "Y+", nullptr));
        pushButton_jog_z_plus->setText(QCoreApplication::translate("MainWindow", "Z+", nullptr));
        pushButton_jog_y_min->setText(QCoreApplication::translate("MainWindow", "Y-", nullptr));
        pushButton_jog_x_plus->setText(QCoreApplication::translate("MainWindow", "X+", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "tool offset x", nullptr));
        lineEdit_tooloffset_x->setText(QCoreApplication::translate("MainWindow", "630", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "tool offset y", nullptr));
        lineEdit_tooloffset_y->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "tool offset z", nullptr));
        lineEdit_tooloffset_z->setText(QCoreApplication::translate("MainWindow", "500", nullptr));
        pushButton_tooloffset->setText(QCoreApplication::translate("MainWindow", "set tooloffset", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_load_mdi->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p><br/></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_load_mdi->setText(QCoreApplication::translate("MainWindow", "load mdi", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "Mdi input", nullptr));
        lineEdit_mdi->setText(QCoreApplication::translate("MainWindow", "G1 X100 Y100 Z50 F1400", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Path to lcnc:", nullptr));
        lineEdit_path_to_lcnc_bin->setText(QCoreApplication::translate("MainWindow", "/opt/linuxcnc", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
