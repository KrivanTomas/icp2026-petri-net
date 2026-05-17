/**
 * @file main.cpp
 *
 * @brief Entry point for the main GUI application
 *
 * @author
 *     Tomáš Křivan
 */

#include "include/main_window.h"

#include <QApplication>

/**
 * @brief Entry point for the GUI editor application
 */
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow w;
    w.show();
    return app.exec();
}
