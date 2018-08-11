#include <string.h>
#include <iostream>
#include <algorithm>

using namespace std;

int cows = 0;
int steps = 0;

int main()
{
  string in_str;
  int i;
  int  possi =0;
  int sum = 0;
  int avg= 0;
  cin>>in_str;
  cows = atoi(in_str.c_str());
  int *apples = new int[cows];

  for (i = 0; i< cows; i++)
    {
      cin>>in_str;
      apples[i] = atoi(in_str.c_str());
      sum += apples[i];
    }
  if (sum%cows != 0)
    {
      cout<< -1<<endl;
      return 0;
    }
  avg = sum/cows;
  for (i = 0; i< cows; i++)
    {
      if (((apples[i] - avg) & 0x1)== 1)
        {
          cout<< -1<<endl;
          return 0;
        }
      if (apples[i] > avg)
        {
          steps += ((apples[i] - avg)>>1);
        }

    }
  cout<<steps<<endl;
  // if (possi == -1)
  //   {
  //     cout<<possi<<endl;
  //     return 0;
  //   }
  // share_apple(apples);
  // cout<<steps<<endl;
}
