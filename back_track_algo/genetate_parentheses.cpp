#include <stdlib.h>
#include <vector>
#include <map>
#include <stack>
#include <string>
#include <iostream>
#include <stdio.h>
/**************************
左括号:2; 右括号:0
1. 选择：0 1
2. 限制条件: 从左往右之和都大于等于0  且   全部之和=0
3. 最多2*n个数

 *************************/
using namespace::std;
class Parenthese
{
public:
  Parenthese(int num){_num = num;}
  vector<string> parent_string;
  void addParent(string parentString)
  {
    int left = 0;
    int right = 0;
    for (unsigned int i =0 ; i < parentString.length(); i ++)
      {
        switch (parentString[i])
          {
          case '(':
            left ++;
            break;
          case ')':
            right ++;
            break;
          default:
            cout<< "char err."<<endl;
          }
      }
    if (left == _num && right == _num)
      {
        parent_string.push_back(parentString);
        return;
      }
    if (left < _num)
      {
        // parentString = parentString + '(';
        addParent(parentString + '(');
      }
    if (left > right)
      {
        // parentString = parentString + ')';
        addParent(parentString + ')');
      }
  }
  void print()
  {
    vector<string>::iterator ite = parent_string.begin();
    for(; ite != parent_string.end(); ite ++)
      {
        cout<< *ite<<endl;
      }
  }
private:
  int _num;
};

int main()
{
  scanf("%d", &num);
  string buf="";
  Parenthese * PS = new Parenthese(num);
  PS->addParent(buf);
  PS->print();                   // 
  return 0;
}
