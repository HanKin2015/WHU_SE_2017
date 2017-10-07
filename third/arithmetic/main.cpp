#include "mainwindow.h"
#include <QApplication>
#include <QFont>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle(QString("四则运算生成器"));
    QFont font;
    font.setPointSize(20);
    font.setFamily(("simsun"));
    w.setBaseSize(1800,1000);
    w.setFont(font);
    w.show();

    return a.exec();
}
