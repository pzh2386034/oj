#include <string.h>
#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

int n;
int k;
queue<int *> possible;
int results;

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