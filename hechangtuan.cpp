#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <queue>

using namespace std;

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
void print_point(int x, int y)
{
  MAPPOINTS temp = points[x*cols + y];
  cout<<"x: "<< temp.x<<"  y: "<< " min walk: "<< temp.min_walk<<temp.y<<" can be walk: "<<temp.flag<< " reached:"<<temp.reached<<endl;
}
void print_all()
{
  int i , j;
for (i = 0; i< cols ; i++)
  {
    for(j = 0; j < rows; j++)
      print_point(i,j);
  }
}
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
          !points[next_x* cols + next_y].reached &&
          points[next_x*cols + next_y].min_walk == 1)
        {
          points[next_x* cols + next_y].min_walk = now.min_walk + 1;
          need_to_walk.push(points[next_x* cols + next_y]);
        }
    }
}
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
