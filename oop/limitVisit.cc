#include <iostream>
//* 测试派生类的访问受限相关问题
//* 访问同类型对象的private成员
using namespace std;
class Base
{
	public:
	//Base()=delete;
	Base(int n = -1, int i = -1):_n(n), _i(i){}
	virtual void print(){cout << _n << " " << " " << _i << endl;}
	void print(Base *p){cout << "_n1 : " << p->_n << " _i1: " << p->_i << endl;}//以指针做参数可访问其他同类型类的private对象!!
	protected:
	int _n;
	private:
	int _i;
};

//_i对Sub来说是不可访问的

class Sub : public Base
{
	public:
	//Sub()=delete;//因为已有一个构造函数,不合成该构造函数
	Sub(int n1 = -3, int i1 = -3, int n2 = -2, int i2 = -2):Base(n1, i1), _n2(n2), _i2(i2){}
	void print() override {cout << _n << " "  <<  " " << _n2 << " " << _i2 << endl;} 
	//void print() override {cout << _i <<  endl;}//因为有_i, ‘int Base::_i’ is private
	//void print(Sub *p){cout << "_i : " << p->_i << endl;}// _i is private
	//注意即使在Sub类中也无法对Base类继承来的基类中的private部分访问.
	void print(Sub *p){cout << "_n : " << p->_n << endl;}//派生类成员能访问protected对象
	void printSelf(Sub *p){cout << "_n2 : " << p->_n2 << " _i2: " << p->_i2 << endl;}//以指针做参数可访问其他同类型类的private对象!!
	
	//注意点
	//void print(Base *p){cout << "_n : " << p->_n << "_i: " << p->_i << endl;}//等同于类外直接访问
	
	
	//两处报错:‘int Base::_i’ is private
	//‘int Base::_n’ is protected
	
	
	private:
	int _n2;
	int _i2;
};

int main(void)
{
	Sub s;
	//cout << s._n;//‘int Base::_n’ is protected
	//cout << s._i;//‘int Base::_i’ is private
	
	s.print();
	Sub t;
	t.print(&s);
	//cout << t._n << endl; //Base::_n is protected
	Sub s2(2, 2, 2, 2);
	t.print(&s2);
	t.printSelf(&s2);
	Base b;
	//cout << b._n; //protected
	//cout << b._i; //private
	b.print(&s2);//用Base类的print函数访问Sub类s2的基类private部分,此处有派生类向基类的隐式转换.
	//注意即使在Sub类中也无法对Base类继承来的基类中的private部分访问.
}

