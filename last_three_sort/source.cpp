#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <string>
#include <string.h>
#include <unistd.h>
#include <iostream>
/***********************************************
name: 排序
question: 按照后三位给整数进行排序，小到大
1. 如果不足三位，则按实际位数组成的整数进行排序
2. 如果相等，则按输入字符串中的原始顺序排序
input: 一行数字，以空格分开
output: 返回指定位置的整数
ques slove idea:
1. 对整数进行排序，存放在整形数组中
2. 返回下标对应的数字
create: panzehua
***********************************************/
#define MAX_INPUT 1024
using namespace::std;

void split(const char * input_buf, size_t len, vector<string> & vec_str)
{
    char str[len];
    char *str1 = str;
    char *savestr;
    char *token;
    memcpy(str, input_buf, len);
    cout<< "str:"<<str<<endl;
    for (int i = 0; ; ++i, str1 = NULL) {
        token = strtok_r(str1, " ", &savestr);
        if (token == NULL) {
            break;
        }
        vec_str.push_back(token);
    }
}
class MyTest
{
public:
    vector<string> input_str;
    vector<int> input_num;
    int * num;
    int num_num;

   /*********************************************
name: sort_num
function: 比较a, b，并修改,返回值a<=b
create: pan
time: 2018-3-12
   **********************************************/ 
    void sort_num(int * a, int * b)
        {
            if ((*a%1000) > (*b%1000)) {
                int tmp = *b;
                *b = *a;
                *a = tmp;
            }
        }
    MyTest()
        {
            char buf[MAX_INPUT] = {0};
            int ret = 0, i = 0;
            ret = read(0, buf, MAX_INPUT);
            split(buf, ret, input_str);
            num_num = input_str.size();
            num = new int[num_num];
            for (vector<string>::iterator ite = input_str.begin(); input_str.end() != ite; ite ++, i ++) {
                num[i] = atoi((*ite).c_str());
            }
        }
    MyTest(string path)
        {
            FILE * file = fopen(path.c_str(), "r");
            if (NULL == file)
                {
                    perror("file open err");
                    exit(1);
                }
            char buf[MAX_INPUT] = {0};
            int ret = 0, i = 0;
            fgets(buf, MAX_INPUT, file);
            split(buf, MAX_INPUT, input_str);
            num_num = input_str.size();
            num = new int[num_num];
            for (vector<string>::iterator ite = input_str.begin(); input_str.end() != ite; ite ++, i ++) {
                num[i] = atoi((*ite).c_str());
            }
        }
    ~MyTest()
        {
            delete []num;
        }
    void print()
        {
            cout<< "num_num:"<< num_num<<endl;
            for (int i = 0; i < num_num; ++i) {
                cout<< num[i]<< "    "<<endl;
            }
        }
    /*********************************************
name: sort
function: 冒泡排序
create: pan
time: 2018-3-12
    **********************************************/
    void sort()
        {
            for (int i = 0; i < num_num; ++i) {
                for (int j = 0; j < i; ++j) {
                    sort_num(&num[j], &num[i]);
                }

            }

        }

};

int main(int argc, char * argv[])
{
    // FILE * file = NULL;
    // string input_string;
    // file = fopen("test", "r");
    // if (file == NULL) {
    //     perror("open file err.");
    //     exit(1);
    // }
    MyTest * test = NULL;
    if (argc == 1)
        test = new MyTest();
    else
        test = new MyTest(argv[1]);
    test->sort();
    test->print();
    
}
