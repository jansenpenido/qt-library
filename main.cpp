/*
 * Sistema Bibliotecário - MAIN.CPP
 *
 **/

#include <QtGui/QApplication>
#include "database.h"
#include "mainwindow.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Habilitar caracteres unicode
    QTextCodec* codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForCStrings(codec);

    // Conectar com o banco de dados
    if ( !connectToDatabase() ) {
        return 1;
    }

    MainWindow w;
    w.show();

    return a.exec();
}
