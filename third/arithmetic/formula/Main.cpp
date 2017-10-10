#include<iostream>
#include "Fraction.h"
#include "Operation.h"
#include "OperationFactory.h"
#include "Generate.h"
#include <iomanip>
#include <sstream>

using namespace std;

bool Judge(Generate formula) {
    cout << "= ";
    string str;
    cin >> str;
    int len = str.length();
    int molecular;      //分子
    int denomilator;    //分母
    int number = 0;
    bool flag = false;
    bool isNegative = false;
    for(int i = 0; i < len; i++) {
        char charNumber = str[i];
        int intNumber = charNumber - '0';
        if(charNumber == '/') {
            molecular = number;
            number = 0;
            flag = true;
            continue;
        }
        if(charNumber == '-') {
            isNegative = true;
            continue;
        }
        number = number * 10 + intNumber;
    }
    if(flag) denomilator = number;
    else {
        molecular = number;
        denomilator = 1;
    }
    if(isNegative) molecular *= -1;
//    cout << molecular << ' ' << denomilator << endl;
    Fraction ans(molecular, denomilator);
    if(ans == formula.result) {
        cout << "正确！" << endl << endl;
        return true;
    }
    else {
        cout << "不正确！正确答案 = " << formula.result << endl << endl;
        return false;
    }
}

int main(int argc, char* argv[])
{
    srand((unsigned)time(NULL));  // 随机函数值动态变化

    int num = 4;    //四则运算数量
//    for (int i = 1; i <= argc; i++) {
//		string str = argv[i];
//		if(str == "-n") {
//			char *tmp = argv[i + 1];
//			num = *tmp - '0';
//		}
//	}

    cout << "本次共有" << num << "道题，满分100分。" << endl << endl;
    int rightNum = 0;               // 计算正确的个数
    float perScore = 100.0 / num;   // 每道题占有分数
	for(int i = 0; i < num; i++) {
        cout << i + 1 << ": ";
        Generate formula;
        cout << formula.formulaString;
        bool flag = Judge(formula);
        if(flag) rightNum++;

	}
	float scores = rightNum * perScore;
	cout << endl << "本次得分：" << fixed << setprecision(2) << scores << "分" << endl;
    return 0;
}


