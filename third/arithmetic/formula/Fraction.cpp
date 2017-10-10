#include "Fraction.h"
#include <cmath>
#include <cstdlib>
#include <sstream>
#define eps 1e-7

//辗转相除法求最大公约数
int GCD(int a, int b) {
    return b == 0 ? a : GCD(b, a % b);
}

//重载输出符
ostream& operator<<(ostream& os, Fraction& f) {  //f代表一个分数
    f.Simplification();     //化简
    if(f.isNegative) {      //负数
        if(f.denomilator == 1)
            os << "-" << f.molecular;
        else
            os << "-" << f.molecular << "/" << f.denomilator;
    }
    else {                  //正数
        if(f.denomilator == 1)
            os << f.molecular;
        else
            os << f.molecular << "/" << f.denomilator;
    }
    return os;
}

//构造函数，默认分数为正1
Fraction::Fraction(int a, int b): isNegative(false) {
    while(b == 0) {
        cout << "分母不能为0，请重新输入分母:" << endl;
        cin >> b;
    }
    this->molecular = abs(a);
    this->denomilator = abs(b);
    if(a < 0 && b < 0)
        this->isNegative = false;
    else if(a < 0 || b < 0)
        this->isNegative = true;
    else
        this->isNegative = false;
    this->Simplification();
}

//得到分数值
float Fraction::GetValue() const {
    return this->molecular / (float)denomilator;
}

//化简函数，约分
void Fraction::Simplification() {
    int a = molecular, b = denomilator;
    int ret = GCD(a, b);
    molecular /= ret;
    denomilator /= ret;
}

//输出分数
void Fraction::Show() {
    cout << *this;
}

//重载加号
Fraction Fraction::operator +(const Fraction &f) const {
    Fraction temp;
    if(isNegative == f.isNegative) { //同号相加
        temp.molecular = molecular * f.denomilator + denomilator * f.molecular;
        temp.denomilator = denomilator * f.denomilator;
        temp.isNegative = isNegative;
    }
    else {    // 不同号
        temp.molecular = abs(molecular * f.denomilator - denomilator * f.molecular);
        temp.denomilator = abs(denomilator * f.denomilator);
        if(this->GetValue() > f.GetValue())
            temp.isNegative = isNegative;
        else
            temp.isNegative = f.isNegative;
    }
    return temp;
}

//重载减号
Fraction Fraction::operator -(const Fraction &f) const {
    Fraction temp;
    if(isNegative == f.isNegative) { //同号相减
        temp.molecular = abs(molecular * f.denomilator - denomilator * f.molecular);
        temp.denomilator = denomilator * f.denomilator;
        if(GetValue() >= f.GetValue())
            temp.isNegative = false;
        else
            temp.isNegative = true;
    }
    else {  //异号相减
        temp.molecular = molecular * f.denomilator + denomilator * f.molecular;
        temp.denomilator = denomilator * f.denomilator;
        temp.isNegative = isNegative;
    }
    return temp;
}

//重载乘号
Fraction Fraction::operator *(const Fraction &f) const {
    Fraction temp;
    temp.molecular = molecular * f.molecular;
    temp.denomilator = denomilator * f.denomilator;
    //接下来确定符号
    if(isNegative == f.isNegative) //同号相乘符号为正
        temp.isNegative = false;
    else
        temp.isNegative = true;
    return temp;
}

//重载除号
Fraction Fraction::operator /(Fraction f) const {
    Fraction temp, r;
    r = f.GetReciprocal();  //求倒数，转换为乘法
    temp = *this * r;
    return temp;
}

//求倒数
Fraction Fraction::GetReciprocal() {
    Fraction temp;
    temp.denomilator = molecular;
    temp.molecular = denomilator;
    temp.isNegative = isNegative;
    return temp;
}

//重载等号
bool Fraction::operator ==(const Fraction &f) const {
    if(isNegative != f.isNegative) //不同号肯定不相等
        return false;
    if(abs(GetValue() - f.GetValue()) < eps)
        return true;
    else
        return false;
}

//重载小于
bool Fraction::operator <(const Fraction &f) const {
    if(isNegative == f.isNegative) { //同号比较大小

        if(GetValue() < f.GetValue()) {
            if(isNegative)
                return false;
            else
                return true;
        }
        else if(GetValue() > f.GetValue()) {
            if(isNegative)
                return true;
            else
                return false;
        }
        else//相等的分数
            return false;
    }
    else if(isNegative)//左负友正
        return true;
    else// 左正右负
        return false;
}

//重载大于符号
bool Fraction::operator >(const Fraction& f)const { //大于号小于号刚好相反
    return (f < *this);
}

//改变当前分数分子和分母
void Fraction::ChangeValue(int a, int b) {
    *this = Fraction(a, b);
}

//分数转换为字符串
string Fraction::Fraction2String() {
    this->Simplification();
    string str = "";
    if(this->isNegative && this->molecular != 0) str += "-";    // 防止出现-0情况
    stringstream ss;
    ss << this->molecular;
    str += ss.str();
    ss.str("");
    if(this->denomilator != 1) {
        ss << this->denomilator;
        str += "/";
        str += ss.str();
        ss.str("");
    }
    return str;
}

