#include <iostream>
using namespace std;
//如果双方都不是static成员
//相互包含是无法通过编译的
//至少一方为指针
class B;
class A
{
	public:
		A(){cout << "A()" << endl;}
	static B b;
	int n;
};


class B
{
	public:
		B(){n = -1; cout << "B()" << endl;}
	int n;
	A a;
};

B A::b = B();//初始化static成员,如不初始化,访问时会出现链接错误!!因为该成员不会自动初始化构造

int main()
{
	B b;
	A a;
	cout << a.b.n << endl;
}
