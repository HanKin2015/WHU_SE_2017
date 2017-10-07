#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QTimer>
#include <QDateTime>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    int timeId;
    int timeCnt = 0;
    QPushButton *startBtn = new QPushButton(this);
    QPushButton *stopBtn = new QPushButton(this);
    QPushButton *clearBtn = new QPushButton(this);
    QLabel *timeLabel = new QLabel(this);
    QTimer *timer = new QTimer(this);
    QLineEdit *numberLE = new QLineEdit(this);
    QGridLayout *layout = new QGridLayout;

private slots:
    void timing();
    void timerUpdate();
    void timerStop();
    void timerClear();
    void generate();
};

#endif // MAINWINDOW_H
