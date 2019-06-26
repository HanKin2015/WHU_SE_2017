# 0.小组成员
何健 / 2017282110267

蔡凯峰 / 2017282110285

# 1.项目 GitHub 地址 
GitHub: https://github.com/caikkk2017/arithmetic.git

# 2.题目
结对项目：四则运算题目生成程序（基于GUI）http://www.cnblogs.com/hyfatwhu/p/7605757.html

# 3.预估耗时

| PSP2.1                                  |Personal Software Process Stages| 预估耗时(分) | 实际耗时(分)|
|:-----------|:-------------|:----------------:|:----------------:|
| Planning       | 计划                                    |     10           |                  |
| · Estimate     | · 估计这个任务需要多少时间              |    10            |                 |
| Development    |  开发                                   |     1080         |                  |
| · Analysis     | · 需求分析 (包括学习新技术)             |       30         |                 |
| · Design Spec  | · 生成设计文档                          |       30         |                  |
| · Design Review  | · 设计复审 (和同事审核设计文档)       |       30         |                  |
| · Coding Standard| · 代码规范 (为目前的开发制定合适的规范)|        30       |                  |
| · Design         | · 具体设计                            |        60        |                  |
| · Coding                                | · 具体编码     |         600        |                  |
| · Code Review                           | · 代码复审     |         180        |                 |
| · Test     | · 测试（自我测试，修改代码，提交修改）      |         120        |                  |
| Reporting        | 报告                                  |         150        |                  |
| · Test Report      | · 测试报告                          |           120      |                 |
| · Size Measurement  | · 计算工作量                       |           10       |                  |
| ·Postmortem&Process Improvement Plan | · 事后总结, 并提出过程改进计划|    20  |                  |
| 合计      |                                              |        1250        |                 |

# 4.解题思路
> 界面部分：使用QT来做

> 要求功能的解决思路：

　　1.记录用户的对错总数，程序退出再启动的时候，能把以前的对错数量保存并在此基础上增量计算。

- 每次用户做完题目后都将答题对错情况记录在本地的一个记录文档中，程序启动时读取该文档，再将历史记录显示在页面上，同时菜单栏中  记录->重置  可以重置记录。

　　2.有计时功能，能显示用户开始答题后的消耗时间。

- 使用QTime计时器，每1s回调一次回调函数，在回调函数中更新时间。在用户每次开始答题时会为QTime绑定回调函数并从0计时，用户提交后就会解绑回调函数，时间不会再累加。

　　3.界面支持中文简体/中文繁体/英语，用户可以选择一种。

- 设计了一个结构体，包含了所需文本的字符串指针，每种语言都提供了一个函数来动态设置该结构体。同时设计了一个Language类，该类通过所选的语言来调用不同的设置函数来设置结构体。只需要调用相应的获取函数就能获取到所需的文本内容。
 

# 5.设计实现过程
## 5.1获取题目

```C++
void MainWindow::generate()
{
    srand((unsigned)time(NULL));  // 随机函数值动态变化
        // 关联定时器溢出信号和相应的槽函数
    this->setTime();
    timeCnt = 0;
    connect(timer,&QTimer::timeout, this, &MainWindow::timerUpdate);
    timer->start(1000);
    startBtn->disconnect();      // 关闭开始按钮的信息传递

    formulaCount = numberLE->text().toInt();
    if (formulaCount==0) return ;
    formulaWidget->setRowCount(formulaCount);   // 设置题目占的行数
    formulaWidget->setColumnCount(3);
    this->setFormulaWidget();
    formulaWidget->setColumnWidth(0, 500);
    formulaWidget->setColumnWidth(1, 200);
    formulaWidget->setColumnWidth(2, 200);
    formulaWidget->setColumnHidden(2,true);
    for(int i = 0; i < formulaCount; i++)
    {
        QTableWidgetItem *item0 = formulaWidget->item(i,0);
        QTableWidgetItem *item2 = formulaWidget->item(i,2);
        Generate FORMULA;
        if(item0) {
            item0->setFlags((item0->flags()&(~Qt::ItemIsEditable)));
        }
        else {
            item0 = new QTableWidgetItem;
            item0->setText(QString::fromLocal8Bit(FORMULA.formulaString.c_str()));
            item0->setFlags(item0->flags() & (~Qt::ItemIsEditable));
            item0->setFlags(item0->flags() & (~Qt::ItemIsSelectable));
            formulaWidget->setItem(i, 0, item0);

            item2 = new QTableWidgetItem;
            item2->setText(QString::fromLocal8Bit(FORMULA.resultString.c_str()));
            item2->setFlags(item2->flags() & (~Qt::ItemIsEditable));
            item2->setFlags(item2->flags() & (~Qt::ItemIsSelectable));
            item2->setTextAlignment(Qt::AlignHCenter);
            formulaWidget->setItem(i, 2, item2);
        }
    }
    CanSubmit = true;   //当前可以提交
}
```

##  5.2判断并记录得分

```C++
void MainWindow::judge()
{
    /*如果未生成题目或已经提交过了，就不能提交*/
    if (formulaCount == 0 || !CanSubmit)
        return ;
    /*解绑计时器的回调函数*/
    timer->disconnect();
    startBtn->connect(startBtn, &QPushButton::clicked, this, &MainWindow::generate);

    formulaWidget->setColumnHidden(2,false);
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
    QString pre = get_langue_str(language,score);
    QString temp = QString("：%1").arg(scores);
    qscore = temp;
    this->setScore();
    CanSubmit = false;

    // 记录本次答题
    QString qstr = userRecord->text();
    string str = qstr.toStdString();
    int rightCount = 0, allCount = 0;
    bool flag = false;
    for(int i = 0; i < str.length(); i++) {
        if(str[i] == '/') {
            flag = true;
            continue;
        }
        int tmp = str[i] - '0';
        if(!flag)
            rightCount = rightCount*10 + tmp;
        else
            allCount = allCount*10 + tmp;
    }

    rightCount += rightNum;
    allCount += formulaCount;
    str = "";
    str = to_string(rightCount) + "/" + to_string(allCount);
    ofstream recordFile("userRecord.txt");
    if (recordFile.is_open())
    {
        recordFile << str;
        recordFile.close();
    }
    userRecord->setText(QString::fromStdString(str));
}
```

## 5.3计时器功能

```C++
/*更新界面时间*/
void MainWindow::setTime()
{
    /*动态获取界面文本内容*/
    QString temp = get_langue_str(language,mtime);
    QString s =get_langue_str(language,second);
    QString str = QString(temp+"%1"+s).arg(QString::number(timeCnt, 10));
    timeLabel->setText(str);
}
// 更新计时器时间
void MainWindow::timerUpdate()
{
    timeCnt++;
    this->setTime();
}
```

## 5.4多语言支持
language.h的定义

```C++
#ifndef LANGUAGE_H
#define LANGUAGE_H

enum{
    LANGUAGE_CHINESE,
    LANGUAGE_ENGLISH,
    LANGUAGE_CHINESE_T,
}LANGUAGE_TYPE;
/*界面所需的文本*/
typedef struct {
    char *start;
    char *stop;
    char *input;
    char *submit;
    char *generate;
    char *second;
    char *clear;
    char *score;
    char *file;
    char *openfile;
    char *copyfile;
    char *exit;
    char *language;
    char *help;
    char *params;
    char *about;
    char *record;
    char *history;
    char *mtime;
    char *unit;
    char *reset;
    char *formula;
    char *answer;
    char *uinput;
}Language_Context;


#define Declare_func(x) char *get_##x();
class Language{
public:
    Language(int t);
    Language();
    void setLanguageType(int t);
    /*声明相应的文本获取函数*/
    Declare_func(start)
    Declare_func(stop)
    Declare_func(input)
    Declare_func(clear)
    Declare_func(second)
    Declare_func(score)
    Declare_func(submit)
    Declare_func(generate)
    Declare_func(file)
    Declare_func(openfile)
    Declare_func(copyfile)
    Declare_func(exit)
    Declare_func(language)
    Declare_func(help)
    Declare_func(params)
    Declare_func(about)
    Declare_func(record)
    Declare_func(history)
    Declare_func(mtime)
    Declare_func(unit)
    Declare_func(reset)
    Declare_func(formula)
    Declare_func(answer)
    Declare_func(uinput)
private:
    void setContext();
    int type;
    Language_Context context;
};

#endif // LANGUAGE_H
```

language.cpp的实现
```C++
#include <stdio.h>
#include <stdlib.h>
#include "Language.h"
#include "Languages.h"

#define Implement_func(x) char *Language::get_##x()\
        {                               \
            return this->context.x;        \
        }

Language::Language()
{
    this->type =LANGUAGE_CHINESE;
    this->setContext();
}

Language::Language(int t)
{
    this->type=t;
    this->setContext();
}

void Language::setContext()
{
    switch(this->type)
    {
        case(LANGUAGE_CHINESE):
            set_CN_context(&context);
            break;
        case(LANGUAGE_ENGLISH):
            set_EN_context(&context);
            break;
        case(LANGUAGE_CHINESE_T):
            set_CN_T_context(&context);
            break;
        default:
            set_CN_context(&context);
    }
}

 void Language::setLanguageType(int t){
     this->type=t;
     this->setContext();
 }
/*实现相应的文本获取函数*/
Implement_func(start)
Implement_func(stop)
Implement_func(input)
Implement_func(clear)
Implement_func(second)
Implement_func(score)
Implement_func(submit)
Implement_func(generate)
Implement_func(file)
Implement_func(openfile)
Implement_func(copyfile)
Implement_func(exit)
Implement_func(language)
Implement_func(help)
Implement_func(params)
Implement_func(about)
Implement_func(record)
Implement_func(history)
Implement_func(mtime)
Implement_func(unit)
Implement_func(reset)
Implement_func(formula)
Implement_func(answer)
Implement_func(uinput)
```

使用Language类来动态更新界面语言

```C++
#define get_langue_str(x,y) CS2QS(x.get_##y())
/*类型转换*/
QString  CS2QS(char *x)
{
    QString ret= QString(x);
    return ret;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

        ui->setupUi(this);
     ........//省略部分代码
        // 设置记录菜单
        menu_R = ui->menuBar->addMenu(get_langue_str(language,record));
        resetAction = new QAction(get_langue_str(language,reset), this);
        menu_R->addAction(resetAction);

        // 设置语言菜单
        menu_L = ui->menuBar->addMenu(get_langue_str(language,language));
        QAction *chineseAction = new QAction(tr("&简体中文"), this);
        menu_L->addAction(chineseAction);
        QAction *chineseTAction = new QAction(tr("&繁体中文"), this);
        menu_L->addAction(chineseTAction);
        QAction *englishAction = new QAction(tr("&English"), this);
        menu_L->addAction(englishAction);
.......//省略部分代码
    connect(chineseAction,SIGNAL(triggered()),this,SLOT(setChinese()));
    connect(chineseTAction,SIGNAL(triggered()),this,SLOT(setChineseT()));
    connect(englishAction,SIGNAL(triggered()),this,SLOT(setEnglish()));
    connect(resetAction,SIGNAL(triggered()),this,SLOT(resetRecord()));
}

/*更新UI*/
void MainWindow::setUI()
{
   menu_F->setTitle((get_langue_str(language,file)));
   openAction->setText(get_langue_str(language,openfile));
   copyAction->setText(get_langue_str(language,copyfile));
   exitAction->setText(get_langue_str(language,exit));
   menu_L->setTitle(get_langue_str(language,language));
   menu_H->setTitle(get_langue_str(language,help));
   parameterAction->setText(get_langue_str(language,params));
   aboutAction->setText(get_langue_str(language,about));
   submitBtn->setText(get_langue_str(language,submit));
   startBtn->setText(get_langue_str(language,start)); ;
   numberLE->setPlaceholderText(get_langue_str(language,input));
   historyRecord->setText(get_langue_str(language,history));
   menu_R->setTitle(get_langue_str(language,record));
   resetAction->setText(get_langue_str(language,reset));
   this->setScore();
   this->setTime();
   this->setFormulaWidget();
}

void MainWindow::setChinese()
{
    language.setLanguageType(LANGUAGE_CHINESE);
    this->setUI();
}
void MainWindow::setChineseT()
{
    language.setLanguageType(LANGUAGE_CHINESE_T);
    this->setUI();
}

void MainWindow::setEnglish()
{
    language.setLanguageType(LANGUAGE_ENGLISH);
    this->setUI();
}
```
# 6 测试运行
## 6.1启动程序
![](http://images2017.cnblogs.com/blog/1239866/201710/1239866-20171011174642652-413460568.png)

## 6.2开始答题
![](http://images2017.cnblogs.com/blog/1239866/201710/1239866-20171011174758434-692389444.png)

## 6.3提交
![](http://images2017.cnblogs.com/blog/1239866/201710/1239866-20171011174823543-105543471.png)

## 6.4切换语言
![](http://images2017.cnblogs.com/blog/1239866/201710/1239866-20171011174910762-1689601450.png)

##  6.5重置记录
![](http://images2017.cnblogs.com/blog/1239866/201710/1239866-20171011175007621-1570483737.png)

# 7.合作情况
何健：这次结对编程项目的任务为四则运算生成器程序做成GUI，我和我的队友使用C++，并在QT Creater环境上进行编写。我主要负责、界面的设计开发以及把第二次的四则运算器添加到本次项目中。我是第一次接触C++可视化编程，在QT学习上花费时间较多。在编写过程中，遇到了许多问题和BUG。在实现GUI上设计计时器按钮信号和槽之间的触发上、界面显示除号出现乱码问题、程序运行操作偶尔会出现崩溃、四则运算算式滑动窗口显示问题等等。我通过网上查询资料和在我的合作伙伴的帮助下解决这些问题，我将编写好的程序上传到github，我的搭档pull项目到本地，并对程序添加语言切换功能和一些程序的逻辑判断功能。我们结对编程，大大减少了程序编写的时间。我们通过自身的努力和交流帮助最终实现了本次结对编程项目的完成。

蔡凯峰：在此次结对编程中，我主要负责后端，主要是语言切换和程序的逻辑判断。遇到的主要问题就是字符串的乱码问题，以及如何动态实现语言切换。在搭档的帮助和建议下，我逐渐地完善代码，并将最终的代码整合在一起，上传到github上。

# 8.中程汇报
项目进展情况：利用QT进行C++可视化编程，计时器功能完成，界面布局设计基本完成，用户记录对错总数功能完成，语言切换功能未完成。
面临的主要问题：QT以前没有接触过，在学习上花费时间较多，基本功能实现完成。目前最大的问题就是在考虑将上次写的程序加入到界面中，进行整合优化。语言切换目前在探索中。
基本的解决思路：摸索，探索，网上查询相关资料。

>问：两个人都没接触过QT吗？

答：都没有接触过。

>问：那选择这个技术的原因是？为何不选你们熟悉的技术？

答：我们上次作业用的c++，c++可视化常见的用mfc和qt，我们选择了较容易学习的qt。以前没有进行过c++可视化方面的编程。

# 9.项目小结
| PSP2.1                                  |Personal Software Process Stages| 预估耗时(分) | 实际耗时(分)|
|:-----------|:-------------|:----------------:|:----------------:|
| Planning       | 计划                                    |     10           |     10             |
| · Estimate     | · 估计这个任务需要多少时间              |    10            |      10           |
| Development    |  开发                                   |     1080         |     1240             |
| · Analysis     | · 需求分析 (包括学习新技术)             |       30         |     30            |
| · Design Spec  | · 生成设计文档                          |       30         |       30           |
| · Design Review  | · 设计复审 (和同事审核设计文档)       |       30         |  30                |
| · Coding Standard| · 代码规范 (为目前的开发制定合适的规范)|        30       |    30              |
| · Design         | · 具体设计                            |        60        |     90            |
| · Coding                                | · 具体编码     |         600        |   750               |
| · Code Review                           | · 代码复审     |         180        |    180             |
| · Test     | · 测试（自我测试，修改代码，提交修改）      |         120        |     100             |
| Reporting        | 报告                                  |         150        |     150             |
| · Test Report      | · 测试报告                          |           120      |   120              |
| · Size Measurement  | · 计算工作量                       |           10       |     10             |
| ·Postmortem&Process Improvement Plan | · 事后总结, 并提出过程改进计划|    20  |     20             |
| 合计      |                                              |        1250        |     1410            |

蔡凯峰

很荣幸有这一次结对编程的机会，让我对结对编程有了更深入的理解，在与搭档何健的合作中，我学会了许多，如面对困难时的思考方法以及解决难题的方式。我以前的编程习惯就是功能性为主，只要能实现功能，怎么简单方便怎么来，没有一点规范。但是在这次结对编程中，我意识到这种编程习惯的弊端：会给搭档带来许多不必要的烦扰，反而降低了整体效率。相信以后我会慢慢改掉这个坏毛病。

何健

在结对编程中，我学会了QT的基本知识，并能使用它实现简单的C++可视化编程。
在和搭档的交流合作中，虽然我们都是使用相同的语言C++，但是我们的代码编写风格和习惯不同，在代码查看上花费了一些不必要的时间。我们互相弥补不足，在此次项目下，我也意识到如何使代码更加规范化。
此次结对编程，我们之间分工不同，我负责前端，他负责后端。最后进行整合，大大缩减了项目完成的时间，程序完成的效果也不错。同时，我们增进之间的友谊，并且大大提高了自己的编程水平。

# 10.结对照片
![](http://images2017.cnblogs.com/blog/1239866/201710/1239866-20171011163310387-1707057774.png)

![](http://images2017.cnblogs.com/blog/1239866/201710/1239866-20171011163356168-502402534.png)