#include <iostream>

//* 测试default构造函数
//* 测试析构函数造成不合成移动构造函数的现象

using namespace std;

class Base
{
	public:
	Base(){cout << "default constructor" << endl;}
	Base(const Base &b){cout << "default copy constructor" << endl;}
	Base(Base &&){cout << "default move constructor" << endl;}
	virtual ~Base(){cout << "default Base destructor" << endl;}
	//由于虚析构函数,而不会合成移动构造函数
	
	Base &operator=(const Base &s)
	{
		cout << "default operator=" << endl;
	}
};

class Sub : public Base
{
	public:
	//依靠合成
	//由于有析构函数,不会合成移动构造函数
	~Sub(){cout << "default Sub destructor" << endl;}
	//如果将line28注释掉,line36行的输出将是move constructor!!
	//即没有析构函数就会合成默认移动函数,进而调用Base的移动构造函数!!!
};

int main(void)
{
	Sub b;
	Sub b2 = b;
	Sub b3(move(b));//本应调用move constructor,实际调用的是copy constructor
	b3 = b2;
}
