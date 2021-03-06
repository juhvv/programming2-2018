﻿/*
####################################################################
# TIE-02207 Programming 2: Basics, F2018                           #
# Project4: Slots                                                  #
# Program description: Implements a virtual slots game.            #
# File: main.cpp                                                   #
# Description: Starts executing the program.                       #
# Notes: * This is an exercise program.                            #
#        * Students shall not touch this file.                     #
####################################################################
*/

#include "main_window.hh"
#include <QApplication>


int main(int argc, char** argv) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    w.setWindowTitle("Slots");
    return a.exec();
}
