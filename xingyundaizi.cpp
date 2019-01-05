#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <stdio.h>
#include <queue>
#include <stack>
/***********************************************
 * @brief: 幸运袋子
 * @author: pzh2467908@163.com
question:
https://www.nowcoder.com/practice/a5190a7c3ec045ce9273beebdfe029ee?tpId=85&tqId=29839&rp=1&ru=%2Fta%2F2017test&qru=%2Fta%2F2017test%2Fquestion-ranking&tPage=1
ques slove idea:通过递归，构造全排列搜索，剪枝
1. 先将球球按号码排序
2. 以1为开始搜索，如果号码中没有1，则一定不可能
3. 如果加入了某个数字，发现就不满足要求了，则直接剪枝
* @date: <2018-08-12>
***********************************************/
using namespace std;
int balls = 0;
int num[1001];
queue<int> que;
stack<int> stacks;
int cmp(const void * a, const void *b)
{
  return *(int *)a - *(int *)b;
}
int deep_search(int index, long sum, long mul)
{
  int i = 0;
  int count = 0;
  for(i =index ,count = 0; i< balls; i++)
    {
      sum += num[i];
      mul *= num[i];
      if (sum>mul) /* 满足条件，数量加1， 并以此为基础继续往下搜索 date:<2018-08-15>*/
        count += 1 + deep_search(i+1,sum,mul);
      else if (num[i] == 1)/* 由于数列排过序，可以保证进此分支的是第一个数 date:<2018-08-15>*/
        count += deep_search(i+1,sum,mul);
      else /* 由于拍过序，一旦不满足条件的分支出现，再后面加数字一定不满足条件，剪枝 date:<2018-08-15>*/
        break;
      /* 以A数组为基础，尝试了加num[i]后，要先清除影响回到A，要尝试num[i+1] date:<2018-08-15>*/
      sum -= num[i];
      mul /= num[i];
      /* 去重，由于已排序，只要保证每个分支下一次尝试和上一次尝试加的数字不一样，即可保证去重 date:<2018-08-15>*/
      for(; i< balls - 1 && num[i] == num[i+1]; i++);
    }
  return count;
}
int main()
{
  int  i = 0;

  cin>>balls;
  for(i = 0; i< balls; i++)
    {
      cin>>num[i];
    }
  string str;
  queue<char> quechar;


  qsort(num,balls,sizeof(int),cmp);
  cout<<deep_search(0, 0, 1);
  return 0;
}
