#include "mainwindow.h"
#include "application.h"

int main(int argc, char *argv[])
{
    Application App(argc, argv);
    MainWindow w;
    w.show();

    return App.exec();
}
