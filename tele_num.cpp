#include <string.h>
#include <iostream>
#include <vector>
#include <map>
#include <stdio.h>
#include <stdlib.h>
char transform(char  a)
{
  char ret = 0xff;
  switch (a)
    {
    case 'A':
    case 'B':
    case 'C':
      ret = '2';
      break;
    case 'D':
    case 'E':
    case 'F':
      ret = '3';
      break;
    case 'G':
    case 'H':
    case 'I':
      ret = '4';
      break;
    case 'J':
    case 'K':
    case 'L':
      ret = '5';
      break;
    case 'M':
    case 'N':
    case 'O':
      ret = '6';
      break;
    case 'P':
    case 'R':
    case 'S':
      ret ='7';
      break;
    case 'T':                  // comment
    case 'U':
    case 'V':
      ret = '8';
      break;
    case 'W':
    case 'X':
    case 'Y':
      ret = '9';
      break;
    default:
      printf("can not recognize char.%c",a );
    }
  return ret;
}
char judgeType(char a)
{
  if (a == '-' || a == 'Q' || a== 'Z')
    {
      return 0;
    }
  else if (0x30 <= a && a <= 0x39)
    {
      return 1;
    }
  else
    {
      return 2;
    }
}

using namespace::std;
class teleNumber
{
public:
  vector<string> input_string;
private:
  map<string, int> Map;
  
public:
  void convert()
  {
    char type = 0; //标示每个字符类型
    string tele_string;
    string out_put;
    // 
    vector<string>::iterator iter = input_string.begin();
    for (; iter != input_string.end(); iter++)
      {
        out_put = "";
        tele_string = *iter;
        for (unsigned int i = 0; i < tele_string.length(); i ++)
          {
            if (3 == out_put.length())
              {
                out_put = out_put + '-';
              }
            type = judgeType(tele_string[i]);
            switch (type)
              {
              case 0:
                // 连字符，直接去除
                break;
              case 1:
                //数组，保持原样
                out_put = out_put + tele_string[i];
                break;
              case 2:
                // 字符，使用transform函数转换
                type = transform(tele_string[i]);
                out_put = out_put + type;
                break;
              default:
                cout<< "judge type error, char : "<< tele_string[i]<< endl;
                break;
              }
          }
        if (8 == out_put.length())
          {
            map<string, int>::iterator iter_map = Map.begin();
            for (; iter_map != Map.end(); iter_map ++)
              {
                if (iter_map->first == out_put)
                  {
                    iter_map->second ++;
                    break;
                  }
              }
            if (iter_map == Map.end())
              {
                Map.insert(make_pair<string, int>(out_put, 0));
              }
          }
        else
          {
            cout << "out_put length err, len: "<< out_put.length()<<endl;
          }
      }
  }
  void print_map()
  {
    map<string, int>::iterator iter = Map.begin();
    unsigned int dup_times = 0;
    for (; iter != Map.end(); iter ++)
      {
        if (iter->second != 0)
          {
            cout<< iter->first << " "<< iter->second + 1<< endl;
          }
        else
          {
            dup_times ++ ;
          }
      }
    if ( dup_times == Map.size())
      {
        cout << "No duplicates."<< endl;
      }
  }
  void print_string()
  {
    vector<string>::iterator it = input_string.begin();
    while(it != input_string.end())
      {
        cout<< *it<<endl;
        it ++;
      }
  }
  void readNum()
  {
    FILE *file = NULL;
    char line_buf[1024] = {0};
    int line_num = 0;
    int ret = 0l;
    file = fopen("tele", "r");
    if (file == NULL)
      {
        perror("fopen file failed");
        return ;// 
      }
    fgets(line_buf, 1024, file);
    line_num = atoi(line_buf);
    while(line_num > 0)
      {
        memset(line_buf, 0, 1024);
        fgets(line_buf, 1024, file);
        int len = strlen(line_buf);
        line_buf[len - 1] = '\0';
        input_string.push_back(line_buf);
        line_num --;
      }
    
  }
  
};

int main ()
{
  teleNumber *TN = new teleNumber();
  int line_num = 0;
  char line_buf[1024] = {0};
    scanf("%d", &line_num);
    while(line_num > 0)
      {
        scanf("%s", line_buf);
        TN->input_string.push_back(line_buf);
        line_num --;             // 
      }
  TN->convert();
  TN->print_map();
}
