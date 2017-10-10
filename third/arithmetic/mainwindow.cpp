#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QTimer>
#include <QDateTime>
#include <QScrollArea>
#include <QScrollArea>
#include <QTableWidget>
#include <QTextCodec>

#include<iostream>
#include "formula/Fraction.h"
#include "formula/Operation.h"
#include "formula/OperationFactory.h"
#include "formula/Generate.h"
#include <iomanip>
#include <sstream>
#include <fstream>
#include <cstdlib>
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resize(1000,600);

    // 创建文件菜单
    QMenu *menu_F = ui->menuBar->addMenu(tr("文件(&F)"));
    // 创建打开文件动作
    QAction *openAction = new QAction(tr("&打开文件"), this);
    // 添加图标
    QIcon openIcon(":/myimages/images/file.png");
    openAction->setIcon(openIcon);
    // 设置快捷键
    openAction->setShortcut(QKeySequence(tr("Ctrl+O")));
    // 在文件菜单中设置新的打开动作
    menu_F->addAction(openAction);

    QAction *copyAction = new QAction(tr("&复制文件"), this);
    QIcon copyIcon(":/myimages/images/copy.png");
    copyAction->setIcon(copyIcon);
    copyAction->setShortcut(QKeySequence(tr("Ctrl+C")));
    menu_F->addAction(copyAction);
    QAction *exitAction = new QAction(tr("退出(&X)"), this);
    exitAction->setShortcut(QKeySequence(tr("Ctrl+Q")));
    menu_F->addAction(exitAction);

    // 设置语言菜单
    QMenu *menu_L = ui->menuBar->addMenu(tr("语言(&L)"));
    QAction *chineseAction = new QAction(tr("&中文"), this);
    menu_L->addAction(chineseAction);
    QAction *japaneseAction = new QAction(tr("&日语"), this);
    menu_L->addAction(japaneseAction);
    QAction *hindiAction = new QAction(tr("&印度语"), this);
    menu_L->addAction(hindiAction);
    QAction *englishAction = new QAction(tr("&英语"), this);
    menu_L->addAction(englishAction);

    // 设置帮助菜单
    QMenu *menu_H = ui->menuBar->addMenu(tr("帮助(&H)"));
    QAction *parameterAction = new QAction(tr("&参数"), this);
    menu_H->addAction(parameterAction);
    QAction *aboutAction = new QAction(tr("&关于"), this);
    menu_H->addAction(aboutAction);

    //第一行布局
    startBtn->setText(tr("开始答题"));
    QPushButton *submitBtn = new QPushButton(this);
    submitBtn->setText(tr("提交"));
    timeLabel->setText(tr("时间：0秒"));
    //timeLabel->setAlignment(Qt::AlignHCenter);
    layout->addWidget(startBtn, 0, 0, 1, 1);
    layout->addWidget(submitBtn, 0, 1, 1, 1);


    char buffer[256];

    ifstream recordFile("userRecord.txt");
    if (!recordFile.is_open())
    {
        cout << "Error opening file";
        exit (1);
    }
    while (!recordFile.eof())
    {
        recordFile.getline(buffer,100);
        cout << buffer << endl;

    }
    userRecord->setText(buffer);
    QPushButton *clearRecord = new QPushButton(this);
    clearRecord->setText(tr("清除记录"));
    layout->addWidget(clearRecord, 0, 2, 1, 1);
    userRecord->setAlignment(Qt::AlignHCenter);
    layout->addWidget(userRecord, 0, 3, 1, 1);
    layout->addWidget(timeLabel, 0, 4, 1, 1);

    // 第二行布局
    numberLE->setPlaceholderText(tr("请输入题目数量"));
    numberLE->setAlignment(Qt::AlignHCenter);
    layout->addWidget(numberLE, 1, 0, 1, 2);
    QPushButton *generateBtn = new QPushButton(this);
    generateBtn->setText(tr("生成"));
    layout->addWidget(generateBtn, 1, 2, 1, 1);
    score->setText(tr("成绩：0分(0/0)"));
    layout->addWidget(score, 1, 4, 1, 1);

    // 第三行算式生成布局
    layout->addWidget(formulaWidget, 2, 0, 1, 5);
    ui->centralWidget->setLayout(layout);

    // 按钮点击信号和槽
    connect(startBtn, &QPushButton::clicked, this, &MainWindow::timing);
    connect(generateBtn, &QPushButton::clicked, this, &MainWindow::generate);
    connect(submitBtn, &QPushButton::clicked, this, &MainWindow::judge);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// 计时器开始函数
void MainWindow::timing()
{
    // 关联定时器溢出信号和相应的槽函数
    timeLabel->setText(tr("时间：0秒"));
    timeCnt = 0;
    connect(timer,&QTimer::timeout, this, &MainWindow::timerUpdate);
    timer->start(1000);
    startBtn->disconnect();      // 关闭开始按钮的信息传递
    // startBtn->blockSignals(true); // 开始按钮只能按一次
    // timer->blockSignals(false);
}

// 更新计时器时间
void MainWindow::timerUpdate()
{
    timeCnt++;
    QString str = QString("时间：%1秒").arg(QString::number(timeCnt, 10));
    timeLabel->setText(str);
}

void MainWindow::generate()
{
    srand((unsigned)time(NULL));  // 随机函数值动态变化

    int formulaCount = numberLE->text().toInt();
    formulaWidget->setRowCount(formulaCount);   // 设置题目占的行数
    formulaWidget->setColumnCount(3);
    formulaWidget->setHorizontalHeaderLabels(QStringList() << tr("算式") << tr("答案") << tr("正确答案"));    // 设置列名
    formulaWidget->setColumnWidth(0, 500);
    formulaWidget->setColumnWidth(1, 200);
    formulaWidget->setColumnWidth(2, 200);
    formulaWidget->setColumnHidden(2,true);

    for(int i = 0; i < formulaCount; i++)
    {
        QTableWidgetItem *item0 = formulaWidget->item(i,0); // 算式列
        QTableWidgetItem *item2 = formulaWidget->item(i,2); // 正确答案列
        Generate FORMULA;
        //cout << FORMULA.formulaString << endl;

        if(item0) {
            item0->setFlags((item0->flags()&(~Qt::ItemIsEditable)));
        }
        else {
            item0 = new QTableWidgetItem;
            item0->setText(QString::fromLocal8Bit(FORMULA.formulaString.c_str()));
            item0->setFlags(item0->flags() & (~Qt::ItemIsEditable));    // 不可编辑
            item0->setFlags(item0->flags() & (~Qt::ItemIsSelectable));  // 不可选择
            formulaWidget->setItem(i, 0, item0);

            item2 = new QTableWidgetItem;
            item2->setText(QString::fromLocal8Bit(FORMULA.resultString.c_str()));
            item2->setFlags(item2->flags() & (~Qt::ItemIsEditable));   // 不可编辑
            item2->setFlags(item2->flags() & (~Qt::ItemIsSelectable)); // 不可选择
            item2->setTextAlignment(Qt::AlignHCenter);
            formulaWidget->setItem(i, 2, item2);
        }
    }
    CanSubmit = true;
}

void MainWindow::judge()
{
    if (!CanSubmit) return ;

    timer->disconnect();
    startBtn->connect(startBtn, &QPushButton::clicked, this, &MainWindow::timing);

    formulaWidget->setColumnHidden(2,false);
    int formulaCount = numberLE->text().toInt();
    int rightNum = 0;               // 计算正确的个数
    float perScore = 100.0 / formulaCount;   // 每道题占有分数
    for(int i = 0; i < formulaCount; i++) {
        QTableWidgetItem *item1 = formulaWidget->item(i,1);
        QTableWidgetItem *item2 = formulaWidget->item(i,2);
        if(item1) {
            QString ret = item1->text();
            QString ans = item2->text();
            if(ret != ans) item2->setForeground(QBrush(QColor(255, 0, 0)));
            else rightNum++;
        }
        else
        {
            item2->setForeground(QBrush(QColor(255, 0, 0)));
        }
    }
    float scores = rightNum * perScore;
    int dex = scores * 100;
    scores = dex / 100.0;
    QString temp = QString("成绩：%1分(%2/%3)").arg(scores).arg(rightNum).arg(formulaCount);
    score->setText(temp);

    // 记录本次答题
}


