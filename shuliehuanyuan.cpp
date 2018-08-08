#include <string.h>
#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;


int n;

int k;
queue<int *> possible;
int results;

int check_possi(int * sample)
{
  int i, j = 0;
  int times = 0;
  for (i = 0; i< n - 1; i++)
    {
      if (sample[i] == 0)
        continue;
      for (j = i + 1; j< n; j++)
        {
          if(sample[j] == 0)
            continue;
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
      cout<<"queue remain : "<< possible.size()<<endl;
      int *sample = possible.front();
      possible.pop();
      for (i = 0; i< n; i++)
        {
          if (sample[i] == 0)
            {
              for (j = 1; j< 10; j++)
                {
                  sample[i] = j;
                  if (check_possi(sample) >= 0)
                    {
                      possible.push(sample);
                      for (m = 0 ; m< n; m++ )
                        cout<<sample[m];
                      cout<<endl;
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
  for (j = 0 ; j< n; j++ )
    cout<<a[j];
  cout<<endl;
  possible.push(a);
  search_possi();
  cout<<results<<endl;
  delete a;
}
