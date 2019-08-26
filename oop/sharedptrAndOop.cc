#include <iostream>
#include <memory>
using namespace std;
// * 测试智能指针与派生类的使用

class Base
{
	public:
	Base(){cout << "Base()" << endl;}
	virtual ~Base(){cout << "~Base()" << endl;}
	virtual void vfunc(){cout << "Base::vfunc" << endl;}
	void cfunc(){cout << "cfunc()" << endl;}
};

class Sub : public Base
{
	public:
	Sub(){cout << "SUb()" << endl;}
	~Sub(){cout << "~Sub()" << endl;}
	void vfunc() override {cout << "Sub::vfunc" << endl;};
	void cfunc(){cout << "commonfunc()" << endl;}
};


int main(void)
{
	Base *p;
	Sub *ps;
	Base *pb;
	p = new Base();
	ps = new Sub();
	pb = ps;
	pb->vfunc();
	pb->cfunc();
	pb = p;
	pb->vfunc();
	pb->cfunc();
	
	cout << "===========test1==========" << endl;
	shared_ptr<Base> sp;
	shared_ptr<Sub> sp2;
	shared_ptr<Base> ptr;
	sp = shared_ptr<Base>(new Base);
	sp2 = shared_ptr<Sub>(new Sub);
	ptr = sp2;
	ptr->vfunc();
	ptr = sp;
	ptr->vfunc();
	
	cout << "===========test2==========" << endl;
	ptr = shared_ptr<Base>(new Sub);
	ptr->vfunc();
	cout << "===========test3==========" << endl;
	ptr = make_shared<Sub>();
	ptr->vfunc();
	ptr = make_shared<Base>();
	ptr->vfunc();
}
