#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>

//! Hal
#ifndef ULAPI
#define ULAPI
#endif
#include "hal.h"

//! Filechooserdialog
#include <libdialog/portable-file-dialogs.h>
#if _WIN32
#define DEFAULT_PATH "C:\\"
#else
#define DEFAULT_PATH "/tmp"
#endif

//! Getdirectory
#include <libskynet/directory.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:

    void mode_auto();
    void mode_mdi();
    void mode_jog();

    void mode_auto_run_pressed();
    void mode_auto_stop_pressed();
    void mode_auto_pause_pressed();
    void mode_auto_resume_pressed();

    void jog_x_plus_pressed();
    void jog_x_min_pressed();
    void jog_y_plus_pressed();
    void jog_y_min_pressed();
    void jog_z_plus_pressed();
    void jog_z_min_pressed();
    void jog_euler_x_plus_pressed();
    void jog_euler_x_min_pressed();
    void jog_euler_y_plus_pressed();
    void jog_euler_y_min_pressed();
    void jog_euler_z_plus_pressed();
    void jog_euler_z_min_pressed();

    void jog_x_plus_released();
    void jog_x_min_released();
    void jog_y_plus_released();
    void jog_y_min_released();
    void jog_z_plus_released();
    void jog_z_min_released();
    void jog_euler_x_plus_released();
    void jog_euler_x_min_released();
    void jog_euler_y_plus_released();
    void jog_euler_y_min_released();
    void jog_euler_z_plus_released();
    void jog_euler_z_min_released();

    void loadfile();
    void gcodeblock();
    void tooloffset();
    void max_values();

    void m3_on();
    void m3_off();
    void m7_on();
    void m7_off();
    void m8_on();
    void m8_off();
    void power_rpm();


private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
