#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <string>
#include <fstream>
#include <iostream>

using namespace::std;
class Mytest
{
  public:
    int * nums;
    Mytest(string path ="")
        {
            ifstream ifs("test");
            string str;
            int count;

            while(ifs >> str)
                {
                    cout<<str<<endl;
                    count++;
                }
            ifs.close();
        }
  private:
    void sort()
    {
        
    }
};

int main(void)
{
    Mytest * test = new Mytest();
}

