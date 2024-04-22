/*!
 * Name: Mukti Flora Rahman
 * Course name: Programmeringsmetodik, 6 hp
 * Date: 2020-11-03
 * Assignment: Sudoku project
 * File: main.cpp
 *
 *
 *
 */

#include "mainwindow.h"

#include <QtWidgets/QApplication>

/*!
 * För att kunna köra Qt
 * skapar en instans w av klassen MainWindow
 * Kör igång programmet, går sen till run-funktionen
 * Går till show funktion
 */

int main(int argc, char *argv[])
{
    QApplication a(argc, argv); // för att få Qt att starta
    MainWindow w;
    w.run();
    w.show();
    return a.exec();
}
