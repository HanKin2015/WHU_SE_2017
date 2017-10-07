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
