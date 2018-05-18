#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
/***********************************************
name: 两个栈实现队列
question: 使用两个栈实现队列
input: 
output: 
ques slove idea:
入栈：
1. 数据入stack1
出栈
1. 将stack1的数据按续出栈到stack2
2. 从stack2弹出一个数据
3. 将stack2剩余的数据按序出栈到stack1
create: pan
***********************************************/
using namespace::std;
#define MAX_ELE 5
class MyStack
{
private:
    int stack[MAX_ELE];
    int begin , end;
public:
    int pos;
    MyStack()
        {
            pos = -1;
        }
    int Init()
        {
            pos = -1;
            return 0;
        }
    int Push(int ele)
        {
            if (pos == MAX_ELE -1) {
                cout<<"stack is full."<<end;
                return -1;
            }
            else{
                pos++;
                stack[pos] = ele;
                return 0;
            }
        }
    int pop(int &ele)
        {
            if (pos == -1) {
                cout<<"stack is empty."<<endl;
            }
            else{
                ele = stack[pos];
                pos --;
            }
            return 0;
        }
    int isEmpty()
        {
            if (pos == -1)
                {
                    return 0;
                }
            else{
                return 1;
            }
               
        }
};

class MyQueue
{
private:
    MyStack * stack1;
    MyStack * stack2;
    
public:
    MyQueue()
        {
            stack1 = new MyStack();
            stack2 = new MyStack();
            
        }
    ~MyQueue()
        {
            delete stack1;
            stack1 = NULL;
            delete stack2;
            stack2 = NULL;
        }
    int InitQueue()
        {
            stack1->Init();
            stack2->Init();
            return 0;
        }
    int EnQueue(int elem)
        {
            stack1->Push(elem);
            return 0;
        }
    int DeQueue(int &elem)
        {
            int tem = 0;
            int ret = 0;
            int deep = stack1->pos;
            for (int i = 0; i <= deep; ++i) {
                ret = stack1->pop(tem);
                if (0 != ret) {
                    return 1;
                }
                ret = stack2->Push(tem);
                if (0 != ret) {
                    return 1;
                }
                // cout<<"temp: "<<tem<<"pos: "<< stack1->pos<<endl;
            }
            stack1->Init();
            stack2->pop(elem);
            deep = stack2->pos;
            for (int i = 0; i<= deep; ++i) {
                stack2->pop(tem);
                stack1->Push(tem);
            }
            stack2->Init();
            return 0l;
        }
    int IsEmpty()
        {
            if (0 == stack1->isEmpty()) {
                return 0;
            }
            else{
                return 1;
            }
        }

};

int main(void)
{
    MyQueue *test = new MyQueue();
    int tem = 0;
    test->EnQueue(1);
    test->EnQueue(2);
    test->EnQueue(3);
    test->EnQueue(4);
    test->DeQueue(tem);
    cout<<"tem:"<<tem<<endl;
    test->EnQueue(1);
    test->EnQueue(6);
    
    test->DeQueue(tem);
    cout<<"tem:"<<tem<<endl;
    test->DeQueue(tem);
    cout<<"tem:"<<tem<<endl;
    test->DeQueue(tem);
    cout<<"tem:"<<tem<<endl;
    test->DeQueue(tem);
    cout<<"tem:"<<tem<<endl;
}
