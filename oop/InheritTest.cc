#include <iostream>

//* 测试private继承
//* 测试虚函数和普通同名函数的动态绑定和静态绑定
//* 自定义构造函数,复制构造函数,operator=的编写及注意点测试
//* private继承中using的使用

using namespace std;

class Base
{
	public:
	Base()=default;
	Base(int n , int m = -1):pro_mem(n), pri_mem(m){cout << "Base constructor" << endl;}
	Base(const Base &b):pro_mem(b.pro_mem), pri_mem(b.pri_mem){cout << "copy constructor" << endl;}
	Base(Base &&) = default;
	virtual ~Base(){cout << "Base destructor(virtual)" << endl;}
	
	Base &operator=(const Base &s)
	{
		pro_mem = s.pro_mem;
		pri_mem = s.pri_mem;
		return *this;
	}
	
	
	virtual void print()
	{
		cout << "====base call print====" << endl;
		cout << "pro_mem: " << pro_mem << " pri_mem: " << pri_mem << endl;
	}
	
	
	void print2()
	{
		cout << "base test" << endl;
	}
	void print3()
	{
		cout << "test" << endl;
	}
	protected:
	int pro_mem;
	private:
	int pri_mem = 0;
};

//private继承
class PriSub: private Base
{
	public:
	PriSub():Base(1), sub_pri_men(1), sub_pro_men(1){}
	PriSub(const PriSub &s):Base(s),sub_pri_men(s.sub_pri_men), sub_pro_men(s.sub_pro_men){}
	PriSub &operator=(const PriSub &s)
	{
		Base::operator=(s);
		sub_pri_men = s.sub_pri_men;
		sub_pro_men = s.sub_pro_men;
		return *this;
	}
	void print()
	{
		cout << "====sub call print====" << endl;
		//cout << "pro_mem: " << pro_mem << " pri_mem" << pri_mem << endl; //‘int Base::pri_mem’ is private
		cout << "pro_mem: " << pro_mem << endl;//仍能正常访问protected成员
	}
	void print2()
	{
		cout << "sub test" << endl;
		print3();
	}
	~PriSub(){cout << "prisub destructor" << endl;}
	
	//using Base::print3;
	
	protected:
	int sub_pro_men;
	
	
	//注意,将其在protected使用using, 则本类的派生类可使用Base的这两个成员
	//对外部来说这两个成员已经是PriSub类的protected成员了
	using Base::pro_mem;
	using Base::print3;
	
	
	private:
	int sub_pri_men;
};

class PriSub2 : public PriSub
{
	public:
	PriSub2():PriSub(){}
	//PriSub2():Base(1){}
	//两个错误: 1.‘class Base Base::Base’ is inaccessible
	//		   2.type ‘Base’ is not a direct base of ‘PriSub2’
	void test()
	{
		
		//如果PriSub是public继承,那么以下除了第一条语句,其余三条语句均可执行
		//或者加上line71 72两行using于protected或public也可使三条语句正常调用
		//cout << sub_pri_men << endl;//‘int PriSub::sub_pri_men’ is private
		cout << sub_pro_men << endl;
		cout << pro_mem << endl;//‘int Base::pro_mem’ is protected
		print3();//‘void Base::print3()’ is inaccessible
		
	}
};

//探讨派生类自定义的复制构造和operator=
class PubSub: public Base
{
	public:
	PubSub():Base(-99), sub_pri_men(1), sub_pro_men(1){ cout << "pubsub constructor" << endl; }
	PubSub(int i):Base(i), sub_pri_men(i), sub_pro_men(i){ cout << "pubsub constructor" << endl; }
	//复制构造函数版本1:基类显式构造
	//PubSub(const PubSub &s):Base(s), sub_pri_men(s.sub_pri_men), sub_pro_men(s.sub_pro_men){ cout << "pubsub copyconstructor" << endl;}
	//复制构造函数版本2:基类默认构造
		//这种形式的复制构造函数是错误的,因为只有派生部分是参数s的成员,基类部分被默认初始化了
	PubSub(const PubSub &s):sub_pri_men(s.sub_pri_men), sub_pro_men(s.sub_pro_men){cout << "pubsub copyconstructor" << endl;}
	//赋值符重载函数版本1:基类显式赋值
	PubSub &operator=(const PubSub &s)
	{
		cout << "pubsub operator=" << endl;
		Base::operator=(s);
		sub_pri_men = s.sub_pri_men;
		sub_pro_men = s.sub_pro_men;
		return *this;
	}
	//赋值符重载函数版本2:基类无显式赋值
		//这种形式的赋值函数是错误的,因为只有派生部分成员被赋值,基类部分仍不变
//	PubSub &operator=(const PubSub &s)
//	{
//		cout << "pubsub operator=" << endl;
//		sub_pri_men = s.sub_pri_men;
//		sub_pro_men = s.sub_pro_men;
//		return *this;
//	}

	//如果没有重写,也仍是动态绑定,但调用的都是基类的print()
	void print() override
	{
		cout << "====sub call print====" << endl;
		//cout << "pro_mem: " << pro_mem << " pri_mem" << pri_mem << endl; //‘int Base::pri_mem’ is private
		cout << "pro_mem: " << pro_mem << " sub_pri_men: " << sub_pri_men << " sub_pro_men: " << sub_pro_men << endl;//正常访问protected成员
		Base::print();
	}
	
	void print2()
	{
		cout << "sub test" << endl;
		print3();
	}
	
	~PubSub(){cout << "pubsub destructor" << endl;}
	protected:
	int sub_pro_men;
	private:
	int sub_pri_men;
};


void test(Base *p)
{
	cout << "=========test========" << endl;
	p->print();//动态绑定
	p->print2();//静态绑定,编译时绑定,都调用Base的print2;
	//print2仅仅是覆盖隐藏了函数名而不是覆写需函数.
	cout << "=========end test========" << endl;
}


int main(void)
{
	PriSub s;
	s.print();
	//private继承中,基类的所有成员对于该的类外访问者/要派生该类的类来说都是private的,不可访问
	//s.print3();//void Base::print3() is inaccessible
	//如果在PriSub类里的public中加上using Base::print3, 则s.print3可正常调用
	
	cout << "=====================end====================" << endl;
	//探讨派生类自定义构造函数
	PubSub ps;
	ps.print();
	Base b;
	
	//测试运行时绑定
	test(&b);
	test(&ps);
	
	cout << "=====================end2====================" << endl;
	//测试2个版本的复制构造函数和operator=
	//方法为去掉注释两次编译
	PubSub tmp = ps;
	tmp.print();
	PubSub tmp2(101);
	tmp2.print();
	tmp = tmp2;
	tmp.print();
	
	
}
