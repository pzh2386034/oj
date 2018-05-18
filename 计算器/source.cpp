#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <vector>
using namespace ::std;
/***********************************************
name:计算器
question: 实现计算器，考虑优先级，括号
input: 算术表达式
output: 值
ques slove idea:
1. 自左向右扫描表达式，遇到操作数进操作数栈，遇到运算符进运算符栈
2.
当遇到运算符时，如果它的优先级比运算符栈顶的高，则入栈，否则取出栈顶运算符及操作数栈顶的两个连续操作数运算，把结果存入操作数栈，然后继续比较该运算符和栈顶运算符的优先级
3.
左括号一律进运算符栈，右括号不进栈，取出栈顶运算符和操作数栈顶的两个连续操作数运算，把结果存入栈中，直到取出右括号为止
create: pan
date: <2018-03-25>
***********************************************/
int add(int a, int b)
{
    return a + b;
}
int min(int a, int b)
{
    return a - b;
}
int mul(int a, int b)
{
    return a * b;
}
int divi(int a, int b)
{
    return a / b;
}
void getExpList(vector<string> &exp_list, string path = "")
{
    ifstream ifs;
    string buf;
    if (path != "")
    {
        ifs.open(path.c_str(), ios::binary | ios::in);
        while (ifs >> buf)
        {
            exp_list.push_back(buf);
        }
    }
    else
    {
        cin >> buf;
        exp_list.push_back(buf);
    }
    // vector<string>::iterator ite = exp_list.begin();
    // for (; ite != exp_list.end(); ++ite)
    // {
    //     cout << "exp:" << *ite << endl;
    // }
}
int get_priority(char ope)
{
    int priop = 0;
    switch(ope)
        {
        case '+':
        case '-':
            priop = 1;
            break;
        case '*':
        case '/':
            priop = 2;
            break;
        default:
            cout<<"can not recgnise operate:"<<ope<<endl;
            break;
        }
    return priop;
}
int (*fun)(int a, int b);  // 申明运算函数指针
class Calculate
{
   private:
    stack<char> operate;
    stack<float> ope_num;
    int leftBrace; /* 扫到右括号必须要先判断有没有左括号存在 date:<2018-03-25>*/

   public:
    string express;
    Calculate(string exp) : express(exp){};
    /* 判断操作符优先级是否比栈顶的低
       是则返回true
       date:<2018-03-25>*/
    bool judge(char next)
    {
        char before ;
        if (operate.empty()) {
            return false;
        }
        before = operate.top();
        if (next == '+' || next == '-')
        {
            if (before == '*' || before == '/')
            {
                return true;
            }
        }
        return false;
    }
    /* 取运算符栈顶一个元素，操作数栈顶两个元素
       计算结果后，压回操作数栈
       date:<2018-03-26>*/
    int cal()
    {
        /* 检查
           操作数栈至少要有两个数据
           操作符栈至少要有一个数据
           否则返回失败
           date:<2018-03-26>*/
        if (0 == operate.size() || 2 > ope_num.size())
        {
            return 1;
        }
        float result = 0l;
        float left= ope_num.top();
        ope_num.pop();
        float right= ope_num.top();
        ope_num.pop();
        char ope = operate.top();
        operate.pop();
        switch (ope)
        {
            case '-':
                result = left - right;
                break;
            case '+':
                result = right + left;
                break;
            case '*':
                result = right * left;
                break;
            case '/':
                result = left / right;
                break;
            default:
                cout << "cal operate error, operator: " << ope << endl;
                break;
        }
        ope_num.push(result);
        return 0;
    }
    /* 碰到右括号，计算直到碰到左括号为止
       再将数据压回操作数栈
       date:<2018-03-26>*/
    void brace_cal()
    {
        while (operate.top() != ')')
        {
            cal();
        }
        operate.pop();
    }
    int expExchange()
    {
        int N = express.length();  // 表达式长度计数器
        int lastChar = -1;
        int num = 0;
        int res = 0;
        for (int i = 0; i < N; ++i)
        {
            if (express[i] <= '9' && express[i] >= '0')
            {
                if (N - 1 == i) {
                    /* 最后必为数字 date:<2018-03-27>*/
                    num = atoi(express.substr(lastChar+1, i).c_str());
                    ope_num.push(num);
                }
                continue;
            }
            else
            {
                /* 碰到非数字
                   1. 判断上一个字符是否为数字，如果lastChar =
                   i+1，则为连续字符串
                   2. 判断运算符栈顶符号优先级是否更高，如果是就要先计算
                   3. 判断是否为右括号，如果为右括号
                      a. 判断是否有左括号存在
                      b. 先计算到左括号
                      c. 将计算结果先入栈
                   date:<2018-03-25>*/
                if (lastChar + 1 != i)  // 则上一个符号必为数字，先操作数入栈
                {
                    num = atoi(express.substr(lastChar + 1, i ).c_str());
                    ope_num.push(num);
                }
                switch (express[i])
                {
                    case '-':
                    case '+':
                        /* 先判断运算符栈顶优先级
                           1. 如果比现在的高，则先计算，再将计算结果入操作数栈
                           date:<2018-03-25>*/
                        while (judge(express[i]))
                        {
                            res = cal();
                            if (res != 0)
                            {
                                return res;
                            }
                        }
                        operate.push(express[i]);
                        break;
                        cout<<"no break;"<<endl;
                    case '(':
                        leftBrace++;
                        operate.push(express[i]);
                        break;
                    case ')':
                        brace_cal();
                        operate.push(express[i]);
                        leftBrace--;
                        break;
                    case '*':
                    case '/':
                        operate.push(express[i]);
                        break;
                    default:
                        cout << "can not recognise char : " << express[i]
                             << endl;
                        break;
                }
                lastChar = i;
            }
        }
        return 0;
    }
    int revert(){
        vector<float> operateNum_rev;
        vector<char> operate_rev;
        int num = 0;
        float temp = 0;
        char ope_temp;
        num = ope_num.size();

        for(int i = 0; i < num; i++)
            {
                temp = ope_num.top();
                operateNum_rev.push_back(temp);
                ope_num.pop();
            }
        for( vector<float>::iterator ite = operateNum_rev.begin(); ite!=operateNum_rev.end(); ite++){
            temp = *ite;
            ope_num.push(temp);
        }
        num = operate.size();
        for(int i = 0; i< num; i++)
            {
                ope_temp = operate.top();
                operate_rev.push_back(ope_temp);
                operate.pop();
            }
        for(vector<char>::iterator ite = operate_rev.begin(); ite!=operate_rev.end(); ite++){
            ope_temp = *ite;
            operate.push(ope_temp);
        }
        return 0;
    }
    int expCal(){
        /* 先要将栈反一遍再计算 date:<2018-03-28>*/
        revert();
        int res = 0;
        while(!operate.empty()){
            res = cal();
            if(0 != res){
                return res;
            }
        }
        cout<<"result: "<< ope_num.top()<<endl;
        ope_num.pop(); 
        return 0;
    }
    void print_stack_num()
    {
        while (!ope_num.empty())
        {
            cout << "ope_num:" << ope_num.top() << endl;
            ope_num.pop();
        }
    }
    void print_stack_ope()
    {
        while (!operate.empty())
        {
            cout << "operate:" << operate.top() << endl;
            operate.pop();
        }
    }
};
int main(int argc, char *argv[])
{
    string path;
    vector<string> expList;
    Calculate *calculate = NULL;
    int res = 0;
    if (argc > 1)
    {
        path = argv[1];
        getExpList(expList, path);
    }
    else
    {
        getExpList(expList);
    }
    vector<string>::iterator ite = expList.begin();
    while (ite != expList.end())
    {
        calculate = new Calculate(*ite);
        res = calculate->expExchange();
        if (0 != res){
            cout<<"calculate err"<<endl;
            exit(1);
        }
            
        res = calculate->expCal();
        if (0 != res){
            cout<<"calculate err"<<endl;
            exit(1);
        }
        ite++;
    }
}
