#include <string.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include <vector>

using namespace std;
/***********************************************
 * @brief:合唱团
 * @author: pzh2467908@163.com
question: n个学生站成一排，从中顺序取k个，要求相邻两个的位置编号不超过d，使k个学生能力值乘积最大
https://www.nowcoder.com/practice/661c49118ca241909add3a11c96408c8?tpId=85&tqId=29830&rp=1&ru=%2Fta%2F2017test&qru=%2Fta%2F2017test%2Fquestion-ranking&tPage=1
ques slove idea:动态规划，首先要总结状态转移函数;可以看作
1. 先从n个学生中选择最后一个i
2. 由于是顺序选，然后在前i-1个里面选择k-1个；
maxval[i][j] = max(maxval[k][j-1] * score[i], minval[k][j-1] *score[i], k=0,1,..,i-1)
* @date: <2018-08-11>
***********************************************/
long long check_max();
vector<int> score, score_used;
int kstu , dist = 0;
int nums = 0;
long long maxval[50][50];
long long minval[50][50];
int main()
{
  string input_str;
  long long final = 0;
  cin>>input_str;
  nums = atoi(input_str.c_str());
  int i = 0;
  for (i = 0; i< nums; i ++)
    {
      cin>>input_str;
      score.push_back(atoi(input_str.c_str()));
    }
  cin>>input_str;
  kstu = atoi(input_str.c_str());
  cin>>input_str;
  dist = atoi(input_str.c_str());

  final =  check_max();
  cout<<final<<endl;
  return 0;
}
/*********************************************
 * @brief: 计算maxval[i][j](第i个学生为最后一个，共j+1个学生)，minval[i][j]
为了使j从0开始，j表示共有j+1个学生，即maxval[i][j]:第i个学生为最后一个，共j+1个学生
 * @param:none
 * @return:最大乘积
 * @create: pzh2467908@163.com
 * @date: <2018-08-11>
 **********************************************/
long long check_max()
{
  int i = 0;
  int j = 0;
  int k = 0;
  long long max_value = 0;
  for (i = 0; i < nums; i ++)
    {
      maxval[i][0] = minval[i][0] = score[i];
    }
  for(i = 0; i < nums; i++)
    {
      for (j = 1; j < kstu; j++)
        {
          /* 由于是按顺序选学生，只要从i往前找即可 date:<2018-08-12>*/
          for(k = i - 1; i - k <= dist && k >=0; k --)
            {
              maxval[i][j] = max(maxval[i][j], max(maxval[k][j - 1]* score[i], minval[k][j - 1] * score[i]));
              minval[i][j] = min(minval[i][j], min(maxval[k][j - 1]* score[i], minval[k][j - 1] * score[i]));
            }
        }
    }

  for (i = 0; i < nums; i++)
    {
          max_value = max(max_value, max(maxval[i][kstu - 1], minval[i][kstu  - 1]));
    }
  return max_value;
}
