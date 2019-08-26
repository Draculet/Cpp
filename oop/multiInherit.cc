#include <iostream>

using namespace std;
// * 测试多继承构造函数,名字覆盖,private继承等
class Base
{
	public:
	Base(){cout << "Base()" << endl;}
	virtual void vfunc(){cout << "base vfunc()" << endl;}//继承树上类都有此虚函数
	
	int mem_int;//用于二异性测试
	int base_mem = 1;//各类独有成员
};

class Base1: public Base
{
	public:
	Base1(){cout << "Base1()" << endl;}
	Base1(int i){cout << "Base1: " << i << endl;}
	void memfunc(){cout << "b1 memfunc()" << endl;}
	
	void vfunc() override {cout << "base1 vfunc()" << endl;}
	
	int base1_mem = 2;
	int base1_mem_using = 4;
};

class Base2
{
	public:
	Base2(){cout << "Base2()" << endl;}
	Base2(int i){cout << "Base2: " << i << endl;}
	void memfunc(){cout << "b2 memfunc()" << endl;}
	virtual void vfunc(){cout << "base2 vfunc()" << endl;}
	
	int mem_int;
	int base2_mem = 3;
};

class Sub :public Base1, public Base2
{
	public:
	Sub(int n):Base1(n-5), Base2(n+5){cout << "Sub()" << endl;}
	Sub():Base2(101){};
	void memfunc(){cout << "sub memfunc()" << endl;}
	
	
	//int mem_int;
};

//注意其中一个是虚继承
class priSub: private Base1, public Base2
{
	public:
	using Base1::base1_mem_using;	
	void visit()
	{
		//虽然是private继承,但类内并不会有影响
		cout << base_mem << endl;
		cout << base1_mem << endl;
		cout << base2_mem << endl;
	}
};

class priSub2 : public priSub
{
	void visit()
	{
		//private继承影响了priSub派生类的对Base1(包括Base)类成员访问
		//cout << base_mem << endl;//‘int Base::base_mem’ is inaccessible
		//cout << base1_mem << endl;//‘int Base1::base1_mem’ is inaccessible
		cout << base2_mem << endl;
	}
};

//用于二异性测试
void print(const Base1& b)
{
	
}

void print(const Base2& b)
{
	
}

int main(void)
{
	Sub b;
	//print(b);//二异性错误
	
	//============
	//memfunc是普通函数,都是静态绑定
	Base1 &p = b;
	p.memfunc();
	Base2 &p2 = b;
	p2.memfunc();
	Sub &p3 = b;
	p3.memfunc();


	cout << "===============" << endl;	
	//============
	//cout << b.mem_int << endl;//二异性错误
			
	//============
	//b.vfunc();//静态绑定,二异性错误
	//报错信息:
	//multiInherit.cc:30:15: note: candidates are: virtual void Base2::vfunc()
  	//	virtual void vfunc(){cout << "base2 vfunc()" << endl;}
	//multiInherit.cc:21:7: note:virtual void Base1::vfunc()
  	//	void vfunc() override {cout << "base1 vfunc()" << endl;}

	cout << "===============" << endl;
	//============!!
	Base *p4 = &b;
	p4->vfunc();//动态绑定,输出为:base1 vfunc()
	Sub *p5 = &b;
	//p5->vfunc();//动态绑定,二异性错误,与上部分报错一致,Sub类有两个分别来自两基类的vfunc()
	Base2 *p6 = &b;
	p6->vfunc();//动态绑定,输出为base2 vfunc()
	
	
	cout << "===============" << endl;
	//=============
	Sub pus;
	cout << pus.base2_mem << endl;
	cout << pus.base1_mem << endl;
	cout << pus.base_mem << endl;
	
	priSub prs;
	cout << prs.base2_mem << endl;
	//由于是private继承,Base, Base2的成员都是private的,外部无法访问,除了被显式using的base1_mem_using.
	//cout << prs.base1_mem << endl;
	//cout << prs.base_mem << endl;
	cout << prs.base1_mem_using << endl;
	
	cout << "===============" << endl;
	//==============
	prs.visit();
}
