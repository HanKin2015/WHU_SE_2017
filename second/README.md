[Github项目]()

# 1、题目描述
从《构建之法》第一章的 “程序” 例子出发，完成一个能自动生成小学四则运算题目的命令行 “软件”，满足以下需求：

1. 参与运算的操作数(operands)除了100以内的整数以外，还要支持真分数的四则运算，例如：1/6 + 1/8 = 7/24。操作数必须随机生成。
2. 运算符(operators)为 +, −, ×, ÷ （如运算符个数固定，则不得小于3）运算符的种类和顺序必须随机生成。
3. 要求能处理用户的输入，并判断对错，打分统计正确率。
4. 使用 -n 参数控制生成题目的个数，例如执行下面命令将生成5个题目  
	- (以C/C++/C#为例) calgen.exe -n 5
	- (以python为例) python3 calgen.py -n 5

附加功能（算附加分）

1. 支持带括号的多元复合运算
2. 运算符个数随机生成（考虑小学生运算复杂度，范围在1~10）

# 2、解题思路
把运算符和运算数当成分数，随机生成四则运算式保存到队列(queue)中,利用栈(stack)进行转换为逆波兰式，然后进行计算得出结果。
第一步：写分数类Fraction.h，并将运算符转换成相应的分数形式。   
    Fraction(1000,1) 加
    Fraction(2000,1) 减
    Fraction(3000,1) 乘
    Fraction(4000,1) 除
    Fraction(5000,1) ()
    Fraction(6000,1) )

    1 左括号
    11 同一个位置两个左括号
    2 右括号
    22 同一个位置两个右括号

第二步：运算类Operation.h，生成类Generate.h等等。
第三步：单元测试。
第四步：上传到Github。
第五步：发表博客。

# 3、PSP

| PSP2.1                                  | Personal Software Process Stages        | 预估耗时（分钟） | 实际耗时（分钟） |
|-----------------------------------------|-----------------------------------------|------------------|------------------|
| Planning                                | 计划                                    |                  |                  |
| · Estimate                              | · 估计这个任务需要多少时间              |    10              |                 |
| Development                             | 开发                                    |                  |                  |
| · Analysis                              | · 需求分析 (包括学习新技术)             |       40           |                 |
| · Design Spec                           | · 生成设计文档                          |       30           |                  |
| · Design Review                         | · 设计复审 (和同事审核设计文档)         |       10            |                  |
| · Coding Standard                       | · 代码规范 (为目前的开发制定合适的规范) |        60           |                  |
| · Design                                | · 具体设计                              |        120        |                  |
| · Coding                                | · 具体编码                              |         300       |                  |
| · Code Review                           | · 代码复审                              |         60       |                 |
| · Test                                  | · 测试（自我测试，修改代码，提交修改）  |         120         |                  |
| Reporting                               | 报告                                    |                  |                  |
| · Test Report                           | · 测试报告                              |           30      |                 |
| · Size Measurement                      | · 计算工作量                            |           50       |                  |
| · Postmortem & Process Improvement Plan | · 事后总结, 并提出过程改进计划          |           30       |                  |
| 合计                                    |                                         |            860      |                 |

---

# 4、代码说明
1. 程序入口文件Main.cpp，其中包含了判断对错的Judg()函数。
2. 分数类Fraction.h，分数类中函数的具体实现在Fraction.cpp中。
```C++
#ifndef FRACTION_H_
#define FRACTION_H_
#include <iostream>
using  namespace std;

class Fraction {

public:
    Fraction(int molecular = 1, int denomilator = 1);    //构造函数
    virtual ~Fraction() {};    //虚函数
    float GetValue() const;    //获取分数值
    void Simplification();     //化简
    void Show();               //显示分数
    friend ostream& operator <<(ostream& os, Fraction& f);
    //重载四则运算操作符
    Fraction operator +(const Fraction& f)const;
    Fraction operator -(const Fraction& f)const;
    Fraction operator *(const Fraction& f)const;
    Fraction operator /(Fraction f)const;
    //重载比较操作符,计算减法或异号加法时判断符号
    bool operator ==(const Fraction& f)const;
    bool operator >(const Fraction& f)const;
    bool operator <(const Fraction& f)const;
    Fraction GetReciprocal();//获取分数的倒数
    void ChangeValue(int molecular, int denomilator); //改变当前分数分子和分母

protected:

private:
    int molecular;      //分子
    int denomilator;    //分母
    bool isNegative;  //是否为负数
};
#include "Fraction.cpp"
#endif;
```

3. 运算类Operaton.h。
```C++
#ifndef OPERATION_H_
#define OPERATION_H_
#include <iostream>
#include "Fraction.h"
using  namespace std;

//运算类
class Operation {
private:
    Fraction _numberA;
    Fraction _numberB;

public:
    Fraction GetNumberA() {
        return _numberA;
    }
    Fraction SetNumberA(Fraction value) {
        _numberA = value;
    }
    Fraction GetNumberB() {
        return _numberB;
    }
    Fraction SetNumberB(Fraction value) {
        _numberB = value;
    }

    virtual Fraction GetResult() {
        Fraction result;
        return result;
    }
};
#endif;

```

4. 简单工厂运算类OperationFactory.h。
```C++
#ifndef OPERATIONFACTORY_H_
#define OPERATIONFACTORY_H_
#include <iostream>
#include "Fraction.h"
#include "Operation.h"
#include "ASMDOperation.h"
using  namespace std;

//简单工厂运算类
class OperationFactory {

public:
    static Operation* Calculation(char operate) {
        Operation* result;
        switch(operate) {
            case '+':
                result = new AddOperation();
                break;
            case '-':
                result = new SubOperation();
                break;
            case '*':
                result = new MulOperation();
                break;
            case '/':
                result = new DivOperation();
                break;
        }
        return result;
    }
protected:

private:

};
#endif;
```

5. 加减乘除类ASMDOperatiion.h。
```C++
#ifndef ASMDOPERATION_H_
#define ASMDOPERATION_H_
#include <iostream>
#include "Fraction.h"
#include "Operation.h"
using  namespace std;

//加减乘除运算类
class AddOperation:public Operation {

public:
    Fraction GetResult() {
        Fraction result;
        result = GetNumberA() + GetNumberB();
        return result;
    }
};

class SubOperation:public Operation {

public:
    Fraction GetResult() {
        Fraction result;
        result = GetNumberA() - GetNumberB();
        return result;
    }
};

class MulOperation:public Operation {

public:
    Fraction GetResult() {
        Fraction result;
        result = GetNumberA() * GetNumberB();
        return result;
    }
};

class DivOperation:public Operation {

public:
    Fraction GetResult() {
        Fraction result;
        result = GetNumberA() / GetNumberB();
        return result;
    }
};
#endif;
```

6.生成四则运算式子类Generate.h，具体实现函数在Generate.cpp中。
```C++
#ifndef GENERATE_H_
#define GENERATE_H_
#include <iostream>
#include <queue>
#include "Fraction.h"
using  namespace std;

class Generate {

public:
    Generate(int n = 1);    //构造函数
    double CalculateFunction(queue<Fraction> postFix);  //计算结果
    void InFix_to_PostFix(queue<Fraction> inFix);  //逆波兰式
    virtual ~Generate() {};    //虚函数

protected:

public:
    Fraction result;      //结果
};
#include "Generate.cpp"
#endif;
```

# 5、运行效果
![](http://images.cnblogs.com/cnblogs_com/hankin2017/1078394/o_hj.png)
# 6、单元测试
自己写的简易程序测试，来不及写正规的单元测试。  
```C++
#include<iostream>
#include "Fraction.h"
#include "Operation.h"
#include "OperationFactory.h"
#include "Generate.h"
#include <cstring>
#include <sstream>

using namespace std;

int main()
{
    srand((unsigned)time(NULL));  // 随机数根据时间不同而不同
    Fraction A(5,6),B(2,6);
    Fraction C = A + B;
    cout << C<< endl;

    Operation* oper;
    oper = OperationFactory::Calculation('+');
    (*oper).SetNumberA(A);
    (*oper).SetNumberB(B);
    Fraction ans = (*oper).GetResult();
//    cout << ans << endl;

    Generate formula;
    cout << endl;
    Generate formulb;

    return 0;
}
```
# 7、总结
大概实现了老师给的任务要求，但程序不是很完美，单元测试部分没有做。
# 8、参考
[前缀、中缀、后缀](http://blog.csdn.net/antineutrino/article/details/6763722)
<!-- [后缀求值](http://www.cnblogs.com/nzbbody/p/3504199.html) -->
