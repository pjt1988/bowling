#include "mainwindow.h"

#include <QApplication>
#include <iostream>
#include <string>

/*
 * For our purposes, the user can choose the result of the game. 
 * Valid options:
 *  - "r" totally random. May not be realistic
 *  - "x" STRIKE!
 *  - "/" spare - only on the second frame
 *  - "s" split
 *  - "g" gutter ball - no pins hit 
 *  - "e" exit
 *
 */

/*
 * Limitations 
 * - the code does not recognize randomly occuring strikes, spares, splits, or gutter balls
 * - the final frame should allow for 3 balls, but this is not yet implemented
 *
 */

int main(int argc, char *argv[]){

    QApplication a(argc, argv);
    QPalette pal = a.palette();
    pal.setColor(QPalette::Window, Qt::white);
    a.setPalette(pal);
    MainWindow w;
    w.show();
    return a.exec();


    return 0;



}
