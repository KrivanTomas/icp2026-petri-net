/**
 * @file main_window.h
 *
 * @brief Header file for the main gui window
 *
  * @author
 *     Tomáš Křivan
 */

#pragma once

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
};
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

};
