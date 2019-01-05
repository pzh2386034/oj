#include <iostream>
#include <stdlib.h>
#include <map>
#include <algorithm>

using namespace std;

int cows ;
int *apples;
int steps;
int avg ;
int apple_sum(int * app_ser, int num)
{
  int i = 0;
  int ret =0;
  for (i = 0; i<num; i++)
    {
      ret += app_ser[i];
    }
  return ret;
}
int max_num(int *app_str , int num)
{
  int i =0;
  int ret= 0;
  for (i = 0; i<num; i++)
    {
      ret = max(ret, app_str[i]);
    }
  return ret;
}
void share_apple(int begin, int end)
{
  int max_num= 0;
  int i,j;
  int max_index = 0;
  int max_apple = 0;
  if (begin == end)
    {
      return;
    }
  for(i = begin ; i< end; i++)
    {
      if (apples[i] > max_apple)
        {
          max_index = i;
          max_apple = apples[i];
        }
    }
  //calculate steps
}
int check_possible()
{
  int i = 0;
  for (i = 0; i< cows; i++){
    if (apples[i]%2 != 0 || apples[i]%cows != 0)
      return -1;
  }
  return 0;
}
int main()
{
  string in_str;
  int i;
  int  possi =0;
  cin>>in_str;
  cows = atoi(in_str.c_str());
  apples = new int[cows];

  for (i = 0; i< cows; i++)
    {
      cin>>in_str;
      apples[i] = atoi(in_str.c_str());
    }
  avg = apple_sum(apples,cows)/cows;
  possi = check_possible();
  if (possi == -1)
    {
      cout<<possi<<endl;
      return 0;
    }
  share_apple(0, cows-1);

  delete []apples;
}
