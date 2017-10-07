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

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resize(800,600);

    //布局
    QLabel *unitLabel = new QLabel(this);
    startBtn->setText(tr("开始"));
    stopBtn->setText(tr("结束"));
    clearBtn->setText(tr("归零"));
    timeLabel->setText(tr("0"));
    timeLabel->setAlignment(Qt::AlignHCenter);
    unitLabel->setText(tr("秒"));
    unitLabel->setAlignment(Qt::AlignHCenter);
    layout->addWidget(startBtn, 0, 0, 1, 1);
    layout->addWidget(stopBtn, 0, 1, 1, 1);
    layout->addWidget(clearBtn, 0, 2, 1, 1);

    layout->addWidget(timeLabel, 0, 3, 1, 1);
    layout->addWidget(unitLabel, 0, 4, 1, 1);

    numberLE->setPlaceholderText(tr("请输入题目数量"));
    layout->addWidget(numberLE, 1, 0, 1, 2);
    QPushButton *generateBtn = new QPushButton(this);
    generateBtn->setText(tr("生成"));
    layout->addWidget(generateBtn, 1, 2, 1, 1);

    QPushButton *submitBtn = new QPushButton(this);
    submitBtn->setText(tr("提交"));
    layout->addWidget(submitBtn, 1, 3, 1, 1);
    QPushButton *exitBtn = new QPushButton(this);
    exitBtn->setText(tr("退出"));
    layout->addWidget(exitBtn, 1, 4, 1, 1);




    QLabel *te = new QLabel(this);
    layout->addWidget(te, 2, 0, 1, 5);
    /*
    scrollAreaLayout
    layout->addChildLayout(scrollAreaLayout);
    //滚动区域
    QScrollArea *s = new QScrollArea(this);
    //垂直滚动条不可见，只能通过鼠标滑动
    s->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //窗体1，其父窗体为滚动区域
    QWidget *w = new QWidget(s);
    //设置滚动区域的窗体
    s->setWidget(w);
    w->setGeometry(2, 2, 300, 300);

    //在窗体1上添加按钮
    QPushButton *btn = new QPushButton(w);
    btn->setText("123");
    btn->move(230, 130);*/


    ui->centralWidget->setLayout(layout);

    timeId = startTimer(1000);

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

    connect(startBtn, &QPushButton::clicked, this, &MainWindow::timing);
    connect(stopBtn, &QPushButton::clicked, this, &MainWindow::timerStop);
    connect(clearBtn, &QPushButton::clicked, this, &MainWindow::timerClear);
    connect(generateBtn, &QPushButton::clicked, this, &MainWindow::generate);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::timing()
{
    // 关联定时器溢出信号和相应的槽函数
    connect(timer,&QTimer::timeout, this, &MainWindow::timerUpdate);
    timer->start(1000);
    startBtn->disconnect();      // 关闭开始按钮的信息传递
    // startBtn->blockSignals(true); // 开始按钮只能按一次
    // timer->blockSignals(false);
}

void MainWindow::timerUpdate()
{
    timeCnt++;
    QString str = QString::number(timeCnt, 10);
    timeLabel->setText(str);
}

void MainWindow::timerStop()
{
    timer->disconnect();
    // timer->blockSignals(true);
    startBtn->connect(startBtn, &QPushButton::clicked, this, &MainWindow::timing);
    // startBtn->blockSignals(false);
}

void MainWindow::timerClear()
{
    timeLabel->setText("0");
    timeCnt = 0;
}

void MainWindow::generate()
{
    for(int i = 0; i < numberLE->text().toInt(); i++)
    {
        QLabel *formula = new QLabel(this);
        formula->setText("hello" + QString::number(i + 1, 10));
        layout->addWidget(formula, i + 2, 0, 1, 1);
    }
}
