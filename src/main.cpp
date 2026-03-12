// src/main.cpp
// Authors:
//  Tomáš Křivan
//
#include <iostream>
#include <QApplication>
#include "module_test.h"
#include "main_window.h"

int main(int argc, char *argv[]) {
    std::cout << "Hello, World!\n";
    module_test();

    QApplication app(argc, argv);
    MainWindow w;
    w.show();
    return app.exec();
}
