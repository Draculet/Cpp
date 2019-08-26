#include <iostream>
#include <memory>
using namespace std;
// * 测试使用智能指针时,在缺乏虚析构函数的情况下能否正常析构
// 结论:使用智能指针管理的对象,即使缺乏虚析构函数仍能正常析构
class Base
{
	public:
	Base(){cout << "Base()" << endl;}
	~Base(){cout << "~Base()" << endl;}
	virtual void vfunc(){cout << "Base::vfunc" << endl;}
	void cfunc(){cout << "cfunc()" << endl;}
};

class Sub : public Base
{
	public:
	Sub(int n){cout << n << ": SUb()" << endl;}
	~Sub(){cout << "~Sub()" << endl;}
	void vfunc() override {cout << "Sub::vfunc" << endl;};
	void cfunc(){cout << "commonfunc()" << endl;}
};

int main(void)
{
	shared_ptr<Base> ptr = make_shared<Sub>(3);
	//~Sub()
	//~Base()
	Base *p = new Sub(9);
	delete p;
	//~Base
	shared_ptr<Base> ptr2 = shared_ptr<Sub>(new Sub(3));
	//~Sub()
	//~Base()
	
}
