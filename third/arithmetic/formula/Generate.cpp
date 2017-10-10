#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <queue>
#include <stack>
#include <sstream>
#include "Fraction.h"
#include "Operation.h"
#include "ASMDOperation.h"
#include "Generate.h"
#include "OperationFactory.h"
using namespace std;

string operators[4] = {"+", "-", "+", "-"}; // 四则运算符

//比较两个操作符的优先级
int judge(string op1, string op2)
{
    if(op1 == "(") return -1;
    else if(op1 == "+" || op1 == "-") {
        if(op2 == "*" || op2 == "/")  return -1;
        else return 0;
    }
    if(op1 == "*" || op1 == "/") {
        if(op2 == "+" || op2 == "-") return 1;
        else return 0;
    }
}

//输出算式
void Print(Fraction tmp) {
    if(tmp.GetValue() == 1000) cout << "+";
    else if(tmp.GetValue() == 2000) cout << "-";
    else if(tmp.GetValue() == 3000) cout << "×";
    else if(tmp.GetValue() == 4000) cout << "÷";
    else if(tmp.GetValue() == 5000) cout << "(";
    else if(tmp.GetValue() == 6000) cout << ")";
    else cout << tmp;
    cout << " ";
    return ;
}

//判断是否是运算符
bool IsOperator(Fraction op) {
    for(int i = 1; i <= 6; i++) {
        if(op.GetValue() == i*1000)
            return true;
    }
    return false;
}

//运算符转换为字符串
string Transform(Fraction op) {
    float tmp = op.GetValue();
    if(tmp == 1000) return "+";
    if(tmp == 2000) return "-";
    if(tmp == 3000) return "*";
    if(tmp == 4000) return "/";
    if(tmp == 5000) return "(";
    if(tmp == 6000) return ")";
    return "number";
}

//后缀表达式求值程序
double Generate::CalculateFunction(queue<Fraction> postFix) {
    stack<Fraction> S;

    while(!postFix.empty()) {
        Fraction tmp = postFix.front();
        if(!IsOperator(tmp)) {  // 如果是数字就进栈
            S.push(tmp);
        }
        else {
            string op = Transform(tmp);
            Fraction numberB = S.top();
            S.pop();
            Fraction numberA = S.top();
            S.pop();

            Operation* oper;
            oper = OperationFactory::Calculation(op[0]);
            (*oper).SetNumberA(numberA);
            (*oper).SetNumberB(numberB);
            Fraction result = (*oper).GetResult();
//            cout << result << endl;
            S.push(result);
        }
        postFix.pop();
    }
    this->result = S.top();
    this->resultString = S.top().Fraction2String();
//    cout << "答案:" << S.top() << endl;
    return 0;
}

// 中缀表达式转换成后缀表达式
void Generate::InFix_to_PostFix(queue<Fraction> inFix) {
    queue<Fraction> postFix;
    stack<Fraction> S;

    while(!inFix.empty()) {
        Fraction fraction = inFix.front();
        string tmp = Transform(fraction);
        if(tmp == "(") S.push(fraction);
        else if(tmp == ")") {
            while(S.top().GetValue() != 5000) {
                postFix.push(S.top());
                S.pop();
            }
            S.pop();
        }
        else {
            if(!IsOperator(fraction))
                S.push(fraction);
            else {
                while(!S.empty() && judge(Transform(S.top()), tmp) >= 0) {
                    postFix.push(S.top());
                    S.pop();
                }
                S.push(fraction);
            }
        }
        inFix.pop();
    }

    while(!S.empty()) {
        postFix.push(S.top());
        S.pop();
    }

    Generate::CalculateFunction(postFix);
//    cout << endl << "后缀表达式：";
//    cout << postFix.size();
//    while(!postFix.empty()) {
//        Fraction tmp = postFix.front();
//        Print(tmp);
//        postFix.pop();
//    }
//    cout << endl;
    return ;
}

int* GetBracketLocation(int opNum, int bracketNum) {
    int* bkLocation = new int[15];
    for(int i = 0; i < 15; i++) bkLocation[i] = 0;
//    memset(bkLocation, 0, sizeof(bkLocation));
    if(bracketNum == 1) {
        int tmp = rand() % ((opNum + 1)/ 2 + 1) + 1;   //左括号在左边生成
        bkLocation[tmp] = 1;
        tmp = rand() % (opNum + 1 - tmp) + 1 + tmp; //右括号在右边生成
        bkLocation[tmp] = 2;
    }
    else if(bracketNum == 2) {
        int tmp = rand() % ((opNum + 1) / 2 + 1) + 1;   //左括号在左边生成
        int rightBracket = tmp;
        bkLocation[tmp] = 1;
        tmp = rand() % ((opNum + 1) / 2 + 1) + 1;
        if(tmp > rightBracket) rightBracket = tmp;  //靠右边的左括号

        if(bkLocation[tmp]) {
            bkLocation[tmp] = 11;    //同一个位置
        }
        else {
            bkLocation[tmp] = 1;
        }

        tmp = rand() % (opNum + 1 - rightBracket) + 1 + rightBracket; // 右括号在右边生成
        bkLocation[tmp] = 2;
        tmp = rand() % (opNum + 1 - rightBracket) + 1 + rightBracket;
        if(bkLocation[tmp]) {
            bkLocation[tmp] = 22;
        }
        else {
            bkLocation[tmp] = 2;
        }
    }
    return bkLocation;
}

queue<Fraction> GenerateFormula(int opNum, int* bkLocation) {
    queue<Fraction> formula;
    Fraction add(1000,1);
    Fraction sub(2000,1);
    Fraction mul(3000,1);
    Fraction div(4000,1);
    Fraction lbk(5000,1);
    Fraction rbk(6000,1);

    bool preOperation = false;  //记录前一个运算符是否为除号，若为true，则运算数不能为0
    for(int j = 1; j <= opNum; j++) {
        //判断是否生成左括号
        if(bkLocation[j] == 1) formula.push(lbk);
        else if(bkLocation[j] == 11) {
            formula.push(lbk);
            formula.push(lbk);
        }

        //生成运算数
        int isFraction = rand() % 5;
        if(isFraction == 1) {
            int molecular = rand() % 10 + 1;        //分子
            int denomilator = rand() % 10 + 1;       //分母
            while(denomilator < molecular) denomilator = rand() % 10 + 1;
            Fraction number(molecular, denomilator);
            formula.push(number);
        }
        else {
            int molecular = rand() % 11;
            while(preOperation && molecular == 0) {
                molecular = rand() % 11;
            }
            Fraction number(molecular, 1);
            formula.push(number);
        }

        //判断是否生成右括号
        if(bkLocation[j] == 2) formula.push(rbk);
        else if(bkLocation[j] == 22) {
            formula.push(rbk);
            formula.push(rbk);
        }

        //生成运算符
        switch(rand() % 4){
            case 0:
                formula.push(add);
                preOperation = false;
                break;
            case 1:
                formula.push(sub);
                preOperation = false;
                break;
            case 2:
                formula.push(mul);
                preOperation = false;
                break;
            case 3:
                formula.push(div);
                preOperation = true;
                break;
        }
    }

    //生成运算数
    int isFraction = rand() % 5;
    if(isFraction == 0) {
        int molecular = rand() % 10 + 1;        //分子
        int denomilator = rand() % 10 + 1;       //分母
        while(denomilator < molecular) denomilator = rand() % 10 + 1;
        Fraction number(molecular, denomilator);
        formula.push(number);
    }
    else {
        int molecular = rand() % 11;
        while(preOperation && molecular == 0) {
            molecular = rand() % 11;
        }
        Fraction number(molecular, 1);
        formula.push(number);
    }

    //判断是否生成右括号
    if(bkLocation[opNum + 1] == 2) formula.push(rbk);
    else if(bkLocation[opNum + 1] == 22) {
        formula.push(rbk);
        formula.push(rbk);
    }
    return formula;
}

Generate::Generate(int n) {
    for(int i = 1; i <= n; i++) {
        int opNum = rand() % 4 + 1;  //运算符的个数1-10
        int bracketNum = 0;           //括号的个数0-2,跟运算符个数有关,默认为0
        if(opNum >= 4) {
            bracketNum = rand() % 3;
        }
        else if(opNum >= 2) {
            bracketNum = rand() % 2;
        }

        int* bkLocation = new int[15];
        bkLocation = GetBracketLocation(opNum, bracketNum);  //括号位置随机生成

        queue<Fraction> formula;
        formula = GenerateFormula(opNum, bkLocation);

        queue<Fraction> tmd;
        tmd = formula;

        string str = "";
        while(!formula.empty()) {     // 输出算式
            Fraction tmp = formula.front();
            if(IsOperator(tmp)) {
                string s = Transform(tmp);
                if(s == "/") s = "÷";
                str += s;
            }
            else str += tmp.Fraction2String();
            str += " ";
//            Print(tmp);
            formula.pop();
        }
        this->formulaString = str;

        InFix_to_PostFix(tmd);
    }
    return ;
}


