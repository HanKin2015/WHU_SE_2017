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

    Generate formula; cout << endl;
    Generate formulb;

    return 0;
}


