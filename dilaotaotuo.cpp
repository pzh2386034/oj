#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <queue>

using namespace std;
/***********************************************
 * @brief: 地牢逃脱
 * @param:
 * @return:
 * @create:panzehua
question:随机给一个出发点，根据给定的走路规则走，出口可能在地图的任意点，要求：遍历整个地图，找出在哪个点是出口的情况下，离开地图的步数最长(障碍点不可走，可以跨过)
https://www.nowcoder.com/practice/0385945b7d834a99bc0010e67f892e38?tpId=85&tqId=29831&tPage=1&rp=1&ru=%2Fta%2F2017test&qru=%2Fta%2F2017test%2Fquestion-ranking
ques slove idea:广义优先搜索
1. 使用队列来保存需要搜索的点
2. 每次尝试到达一个点，要首先计算到达该点需要的步数，再将下一步可能到达的点加入队列
3. 循环访问队列中的每一个点即可遍历整个地图所有能到达的点
4. 最后找出最长步数
* @date: <2018-08-11>
***********************************************/
int rows;
int cols;
int walk_num;

typedef struct mappoints
{
  int x;
  int y;
  bool reached;//if reached
  bool flag;//if this point can be reached
  int min_walk;
}MAPPOINTS;

typedef struct walks
{
  int x;
  int y;
}WALKS;
queue<MAPPOINTS> need_to_walk;
MAPPOINTS * points  = NULL;
WALKS *walks= NULL;
/*********************************************
 * @brief: 到达一个点后，
1.先判断该点是否合法，是否已经到达过，最小步数是否为-1，如果不是-1，说明已经有更小的步数可到达了
2. 根据可移动的行和列来找出下一步可以到达的点，push入队
 * @param:坐标x,y
 * @return:none
 * @create:panzehua
 * @date: <2018-08-11>
 **********************************************/
void deal_points_around(int x, int y)
{
  int i;
  int next_x, next_y;
  MAPPOINTS now = points[x * cols + y];
  for (i = 0; i< walk_num; i++ )
    {
      next_x = walks[i].x + x;
      next_y = walks[i].y + y;
      if (next_y>= 0 && next_x >= 0 && next_x<rows && next_y<cols &&
          points[next_x* cols + next_y].flag &&
          !points[next_x* cols + next_y].reached
         && points[next_x * cols +next_y].min_walk == -1)
        {
          points[next_x* cols + next_y].min_walk = now.min_walk + 1;
          need_to_walk.push(points[next_x* cols + next_y]);
        }
    }
}
/*********************************************
 * @brief:  循环队列，如果不为空，则访问队首元素，并标记该点已到达
 * @param:none
 * @return:none
 * @create:panzehua
 * @date: <2018-08-11>
 **********************************************/
void walk_all_point()
{
  while(!need_to_walk.empty())
    {
      MAPPOINTS temp = need_to_walk.front();
      need_to_walk.pop();

      deal_points_around(temp.x, temp.y);
      points[temp.x * cols + temp.y].reached = true;
    }
}
/*********************************************
 * @brief: 循环地图找出最长步数
 * @param:none
 * @return:最长步数
 * @create: pzh2467908@163.com
 * @date: <2018-08-11>
 **********************************************/
int get_max_step()
{
  int i ,maxstep = 0;
  for (i = 0; i <cols * rows; i ++)
    {
      if (points[i].min_walk == -1 && points[i].flag == true)
        return -1;
    }
  for (i = 0; i< rows * cols; i ++)
    {
      if (maxstep < points[i].min_walk && points[i].flag == true)
        {
          maxstep = points[i].min_walk;
        }
    }
  return maxstep;
}
int main()
{
  string in_str;
  int max_step = 0;
  int i, j;
  cin>>in_str;
  rows = atoi(in_str.c_str());
  cin>>in_str;
  cols = atoi(in_str.c_str());
  points = new MAPPOINTS[rows*cols];
  memset(points,0,sizeof(MAPPOINTS)* rows * cols);
  MAPPOINTS *begin = new MAPPOINTS;
  for (i = 0; i< rows; i++)
    {
      cin>>in_str;
      for (j = 0; j< cols; j++)
        {
          if (in_str.c_str()[j] == '.')
            {
              points[i*cols +j].x = i;
              points[i*cols +j].y = j;
              points[i*cols +j].flag = true;
              points[i*cols +j].min_walk = -1;
            }
          else
            {
              points[i*cols +j].x = i;
              points[i*cols +j].y = j;
              points[i*cols +j].flag = false;
              points[i*cols +j].min_walk = -1;
            }
        }
    }
  cin>>in_str;
  begin->x = atoi(in_str.c_str());
  cin>>in_str;
  begin->y = atoi(in_str.c_str());
  cin>>in_str;
  points[begin->x * cols + begin->y].min_walk = 0;
  need_to_walk.push(points[begin->x * cols + begin->y]);

  walk_num = atoi(in_str.c_str());
  walks = new WALKS[walk_num];

  for (i = 0; i< walk_num; i++)
    {
      cin>>in_str;
      walks[i].x = atoi(in_str.c_str());
      cin>>in_str;
      walks[i].y = atoi(in_str.c_str());
    }
  walk_all_point();
  max_step = get_max_step();
  cout<<max_step<<endl;
  delete []points;
  delete []walks;
  delete begin;
  return 0;
}
