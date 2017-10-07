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
