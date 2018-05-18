#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <vector>
#include <algorithm>
#include <iostream>
#include <string.h>
#include <unistd.h>
/***********************************************
name: 纪念品分组
ques:
1. 每组最多两个纪念品
2. 每组纪念品之和不嫩超过MAX
3. 分组最少
input:
1. int *p(第一个数据为MAX， 第二个数据为num,其余为纪念品价格)
output:
1. 最少分组数
ques slove idea:
1. 排序，从小到大
2. 最小的从最大的开始组合
create: pan
***********************************************/

using namespace::std;
class MyTest
{
public:
    map<int, int> factors;
    int sum;
private:
    int pair_num;
public:
    MyTest(string txt_path)
        {
            txt_path = txt_path;
        }
    MyTest()
        {}
    void get_max_sum()
        {
            int resid = 0;
            map<int, int>::iterator pos_fir;
            map<int, int>::iterator ite= factors.begin();
            while(ite != factors.end())
                {
                    if (ite->second == 1)
                        {
                            cout<< "end"<< endl;
                            break;
                        }
                    resid = sum - ite->first;
                    pos_fir = factors.lower_bound(resid);
                    if (resid == pos_fir->first)
                        {
                            pos_fir->second = 1;
                            pos_fir->second = 1;
                            pair_num ++;
                        }
                    else
                        {
                            (--pos_fir)->second = 1;
                            ite->second = 1;
                            pair_num ++;
                            cout<< "pair success, key: "<< ite->first <<", value: "<< pos_fir->first<<endl;
                        }
                    ite++;
                }
        }
    void print_result()
        {
            std::cout << pair_num<< endl;
        }
    void read_from_file()
        {
            char buf[1024] = {0};
            const char * split = " ";
            char * saveptr = NULL;
            char * token = NULL;
            int num = 0;
            FILE * file = fopen("test.txt", "r");
            if (NULL != file)
                {
                    fgets(buf, 1024, file);
                    for (int i = 0; ; ++i) {
                        token = strtok_r(buf, split, &saveptr);
                        if ( NULL == token)
                            break;
                        if ( 0 == i ) sum = atoi(token);
                        else if ( 1 == i) num = atoi(token);
                        else
                            {
                                // factors.insert(make_pair(atoi(token), 0));
                                factors.insert(pair<int, int>(atoi(token), 0));
                                if (i > num + 1)
                                    {
                                        cout<< "input value too many."<<endl;
                                    }
                            }
                        strcpy(buf, saveptr);
                    }

                }
            else
                {
                    perror("open file failed");
                }
        }
    void print_fac()
        {
            map<int, int>::iterator ite = factors.begin();
            while (ite != factors.end()) {
                cout<< "key: "<< ite->first << "value: " << ite->second<< endl;
                ite++;
            }
        }
};

int main()
{
    MyTest * test = new MyTest();
    test->read_from_file();
    test->print_fac();
    test->get_max_sum();
    test->print_result();
}
