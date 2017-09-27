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
