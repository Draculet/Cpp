#include <iostream>
using namespace std;

//* 测试派生类的名字查找和覆盖

struct Base
{
	int memfunc(){cout << "hello" << endl;}
	int mem = 99;
};
struct Derived : Base
{
	int memfunc(int){};
	int mem = 100;
};

int main(void)
{
	Derived d; Base b;
	b.memfunc();
	d.memfunc(10);
	//d.memfunc();//被隐藏,无法调用到
	d.Base::memfunc();//显式声明
	cout << d.mem << endl;
	cout << b.mem << endl;
}
