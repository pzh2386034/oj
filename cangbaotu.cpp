#include <iostream>
#include <stdlib.h>
#include <map>
#include <string>

using namespace std;

int main()
{
  string in_str;
  size_t i, j;
  string moban;
  int flag = 0;
  cin>>in_str;
  moban = in_str;
 cin>>in_str;
 for(i = 0; i< in_str.size();i ++)
   {
     flag = 0;
     for(j = 0; j < moban.size(); j++)
       {
         if (moban[j] == in_str[i])
           {
             moban = moban.substr(j+1);//先改变了moban变量，后面又通过j==moban.size()判断退出条件，bug
             flag =1;
             break;
           }
       }
     if ( flag == 0)
       {

         cout<<moban<<endl;
         cout<<"No"<<endl;
         return 0;
       }
   }
 cout<<"Yes"<<endl;
}
