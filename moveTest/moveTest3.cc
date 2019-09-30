#include "../fastNet/Noncopyable.h"
#include <iostream>
#include <vector>
using namespace std;

//测试被禁止拷贝后使用move拷贝具有对象语义的对象

class Test : base::noncopyable
{
    public:
    Test(int i):i_(i){cout << "Test()" << endl;}
    Test(Test&&){cout << "MOVE" << endl;}
    ~Test(){cout << "~Test()" << endl;} 
    void call(){i_++; cout <<  i_ << endl;}
    int i_ = 100;
};

int main(void)
{
    vector<Test> vec;
    Test t(12);
    vec.push_back(move(t));
    //输出13
    t.call();
    //输出101
    vec.back().call();
}