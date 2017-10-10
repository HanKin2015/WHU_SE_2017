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
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableWidget>

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
    QLabel *timeLabel = new QLabel(this);
    QTimer *timer = new QTimer(this);
    QLineEdit *numberLE = new QLineEdit(this);  // 算式数量输入
    QGridLayout *layout = new QGridLayout;      // 前两行的显示布局
    QTableWidget *formulaWidget = new QTableWidget(this); // 算式显示窗体
    QLabel *score = new QLabel(this);  // 分数
    QLabel *userRecord = new QLabel(this);   // 用户历史记录卡
    bool CanSubmit = false;

private slots:
    void timing();
    void timerUpdate();
    void generate();
    void judge();
};

#endif // MAINWINDOW_H
