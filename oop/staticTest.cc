#include <iostream>

using namespace std;
//static只存在独一份
class Base
{
	public:
		static void func(){cout << "hhh" << endl;};
};

//以下访问方法均正确
class Derived :public Base
{
	public:
	void f(Derived obj)
	{	
		Base::func();
		Derived::func();
		obj.func();
		func();
	}
};

int main(void)
{
	Derived v;
	v.f(v);
}

