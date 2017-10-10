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
    string resultString;
    string formulaString;
};
#include "Generate.cpp"
#endif;


