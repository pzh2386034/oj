#include <string.h>
#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;
/***********************************************
 * @brief:
 * @author: pzh2467908@163.com
question: 找出空缺数组中所有可能填法；要求数据不能重复，顺序队的数量为k
ques slove idea: 广义优先搜索
1. 输入数据作为起始点，压入队列
2. 循环队列，如果搜索到数据中有0，则展开填充所有可能数据
3. 每填充进一个数据，都要判断期是否满足条件，是否需要在此基础上继续搜索
4. 如果需要继续搜索则压入队列
5. 如果所有数据都不是0，则判断该数据是否满足要求
* @date: <2018-08-11>

mark:
目前只通过70%测试用例，暂时没找到问题点
***********************************************/
int n;
int k;
queue<int *> possible;
int results;
/*********************************************
 * @brief: 对输入样本判断其是否满足要求
1. 如果已经有两个数相同，则直接抛弃
2. 如果顺序对数量小于k，则说明该数据可以进一步填充搜索
3. 如果顺序对数量>k,直接抛弃
4. 如果顺序对数量=k,可以进一步搜索
 * @param:样本
 * @return:对该样本的判断
 * @create: pzh2467908@163.com
 * @date: <2018-08-11>
 **********************************************/
int check_possi(const int * sample)
{
  int i, j = 0;
  int times = 0;
  int zeros = 0;
  for (i = 0; i< n - 1; i++)
    {
      if (sample[i] == 0)
        {
          zeros ++;
          continue;
        }
      for (j = i + 1; j< n; j++)
        {
          if(sample[j] == 0)
            continue;
          if (sample[i] == sample[j])
            {
              return -1;
            }
          if(sample[j]> sample[i])
            times ++;
        }
    }
  if (times < k)
    return 0;
  else if(times== k)
    return 1;
  else
    return -1;
}
/*********************************************
 * @brief: 循环队列，搜索样本中是否有0
1. 有0则扩展开，入队，进一步搜索
2. 没有0则判断是否满足条件
 * @param:none
 * @return:none
 * @create: pzh2467908@163.com
 * @date: <2018-08-11>
 **********************************************/
void search_possi()
{
  int i = 0, j = 0 , m =0;
  while(!possible.empty())
    {
      int *sample= possible.front();
      possible.pop();
      for (i = 0; i< n; i++)
        {
          if (sample[i] == 0)
            {
              for (j = 1; j<= n; j++)
                {
                  sample[i] = j;
                  if (check_possi(sample) >= 0)
                    {
                      int * target = new int[n];
                      memcpy(target, sample, sizeof(int)*n);
                      possible.push(target);
                      // for (m = 0 ; m< n; m++ )
                      //   cout<<sample[m];
                      // cout<<endl;
                    }
                }
              break;
            }
        }
      if(i == n)
        {
          if (check_possi(sample) == 1)
            {
              for (j = 0 ; j< n; j++ )
                cout<<sample[j];
              cout<<endl;
              results ++;
            }
        }

    }
}

int main()
{
  string in_str;
  int i=0, j;
  cin>>in_str;
  n = atoi(in_str.c_str());
  cin>>in_str;
  k = atoi(in_str.c_str());

  int *a = new int(n);
  for (i = 0; i< n;i++)
    {
      cin>>in_str;
      a[i] = atoi(in_str.c_str());
    }
  possible.push(a);
  search_possi();
  cout<<results<<endl;
  delete a;
}
