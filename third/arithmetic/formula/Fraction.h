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

    string Fraction2String();

protected:

private:
    int molecular;      //分子
    int denomilator;    //分母
    bool isNegative;  //是否为负数
};
#include "Fraction.cpp"
#endif;


