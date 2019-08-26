#include <iostream>
using namespace std;
// * 测试虚析构函数的作用
//总结:
//没有虚析构函数delete将不能正确地释放内存
//注意需虚析构函数将阻止默认移动函数的合成
class Base
{
	public:
	Base(){cout << "base constructor" << endl;}
	~Base(){cout << "base destructor" << endl;}
};

class Base2
{
	public:
	Base2(){cout << "base2 constructor" << endl;}
	virtual ~Base2(){cout << "base2 destructor" << endl;}
};

//没有虚析构函数delete将不能正确地释放内存


class Sub: public Base
{
	public:
	Sub(){cout << "sub constructor" << endl;}
	~Sub(){cout << "sub destructor" << endl;}
};

class Sub2: public Base2
{
	public:
	Sub2(){cout << "sub2 constructor" << endl;}
	~Sub2(){cout << "sub2 destructor" << endl;}
};

int main()
{
	Base *p;
	p = new Base();
	delete p;
	p = new Sub();
	delete p;//只析构了Base部分
	
	
	Base2 *ptr;
	ptr = new Base2();
	delete ptr;
	ptr = new Sub2();
	delete ptr;//Base部分和Sub部分均完成析构
	//析构顺序是先Sub后Base
}
