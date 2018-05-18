#include <stdlib.h>
#include <iostream>
#include <string>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
/***********************************************
name: 小明布置新房
question:
总预算  N元
重要度  5等
价格    整数
条件    在不超过N的前提下，物品的价格与重要度的乘积的总和最大
input: 二位数组
第0行， 总钱数  希望购买的物品数
其余：  价格    重要度
output: 价格与重要度乘积的总和的最大值
ques slove idea:
idea1:
重要度/价格 = a[i]
优先满足a[i]较大的
idea2:
比如abcde五件商品，重量 2 2 3 4 5， 价值 3 3 5 6 4；
问题可以分解为：
1. 考虑放入a时的最大价值，f[4][10-weight(a)]+value(a)
2. 不考虑放入a时的最大价值， f[4][10]
f[5][10] = max{f[4][10], f[4][10-weight[a]] + value(a)}
DP求解过程可以理解为: 对于前i件物品，背包剩余容量为j时，所取得的最大价值只依赖于两个选项
1. 前i-1个物品，剩余容量为j;
2. 前i-1个物品，剩余容量为j-w[i];
dp(i, j) = max{dp(i-1, j), dp(i-1, j-w[i]) + w[i] * v[i]}
等价于
dp(j) = max{dp(j), dp(j-w[i]) + w[i]*v[i]}
参考：
https://www.cnblogs.com/zlcxbb/p/5820666.html
https://baike.baidu.com/item/01%E8%83%8C%E5%8C%85/4301245?fr=aladdin
create:pan 
***********************************************/
#define MAX_TEMP 1024
using namespace::std;
int split_line(char * buf, int &a, int &b)
{
    char temp[MAX_TEMP] = {0};
    char * saveptr = NULL;
    char * token = NULL;
    token = strtok_r(buf, " ", &saveptr);
    a = atoi(token);
    b = atoi(saveptr);
    return 0;
}
class MyTest
{
public:
    int num;
    int total;
    MyTest(string path )
        {
            char * temp = NULL;
            char buf[MAX_TEMP] = {0};
            int first, second = 0;
            FILE * file;
            if (path == ""){
                cout<<"empty"<<endl;
            }
            else {
                
            file = fopen(path.c_str(), "r");
            if (NULL == file) {
                perror("can not open file");
                exit(1);         // 无法开发文件，异常退出
            }
            }
            temp = fgets(buf, MAX_TEMP, file);
            split_line(buf, first, second);
            goods = new int* [2]; // 分配2个指针数组
            goods[0] = new int[second];
            goods[1] = new int[second];
            num = second;
            total = first;
            cal = new int[total + 1];
            for (int i = 0; i < num; ++i) {
                memset(buf, 0, MAX_TEMP);
                temp = fgets(buf, MAX_TEMP, file);
                if (NULL == temp) {
                    break;
                }
                (void)split_line(buf, first, second);
                goods[0][i] = first;
                goods[1][i] = second;
            }
        }
    ~MyTest()
        {
            for (int i = 0; i < 2; ++i) {
                delete goods[i];
                goods[i] = NULL;
            }
            delete goods;
            goods = NULL;
            delete cal;
            cal = NULL;
        }
    // void get_max()
    //     {
    //         for (int i = 0; i < num; i++) {
    //             for (int j = total; j > goods[0][i]; j--) {
    //                 cal[j] = cal[j] > cal[j-goods[0][i]] + goods[0][i] * goods[1][i] ? cal[j]:cal[j - goods[0][i]] + goods[0][i] * goods[1][i];
    //             }
    //         }
    //     }
    void get_max()
        {
            int two[num][total];
            for (int i = 0; i< num; ++i) {
                for (int j = 0; j< total; ++j) {
                    if (j > goods[0][i]) {
                        two[i][j] = two[i-1][j]>two[i-1][j-goods[0][i]] + goods[0][i] * goods[1][i]?two[i-1][j]:two[i-1][j-goods[0][i]] + goods[0][i] * goods[1][i];
                    }
                    else{
                        two[i][j] = two[i-1][j];
                    }
                }

            }

            int tem = 0;
            for (int i = 0; i < num; ++i) {
                for (int j =0; j< total; j++) {
                    if (tem< two[i][j])
                        {
                            tem = two[i][j];
                        }
                }

            }
            cout<<"max: "<<tem<<endl;
        }
    void print_input()
        {
            for (int i = 0; i< num; ++i) {
                cout<<"value: "<< goods[0][i]<< "weight: "<<goods[1][i]<<endl;
            }
        }
    // void max()
    //     {
    //         int tem = 0;
    //         for (int i = 0; i< total; ++i) {
    //             if (tem < cal[i])
    //                 {
    //                     tem = cal[i];
    //                 }
    //         }
    //         cout<<"max: "<<tem<<endl;
    //     }
    void max()
        {

        }
private:
    int ** goods;
    int * cal;
};

int main()
{
    MyTest * test = new MyTest("test");
    test->print_input();
    test->get_max();
    test->max();
}
