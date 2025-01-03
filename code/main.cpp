/**
 * @file main.cpp
 * @brief Main file that runs program
 *
 *
 * This file is the main file that calls the main window
 *
 * @date November 16, 2024
 */

#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[]) {

    QApplication a(argc, argv);

    a.setWindowIcon(QIcon(":/new/images/Logo.png"));


    MainWindow w;
    w.show();
    return a.exec();
}
