#include <iostream>
using namespace std;
//* 测虚继承相关特性
//* 要点:虚继承是为了解决基类被多次继承而在一个类中产生多个相同实例而出现的,通过虚继承保证一个类中虚基类只有一份.
//* 1.虚基类成员可见性
//* 2.虚基类构造函数(析构函数相反)
//* 3.虚继承与需函数

class vBase
{
	public:
	vBase(){cout << "vBase()" << endl;}
	vBase(int n){cout << n << ":vBase()" << endl;}
	
	//用于虚函数测试
	virtual void vfun(){cout << "base vfun" << endl;} 
	virtual void vfun2(){cout << "base vfun2" << endl;}
	virtual void vfun3(){cout << "base vfun3" << endl;}
	//用于可见性测试
	int x = -1;
	int y = -1;
};

class D1: virtual public vBase//虚继承,vBase为虚基类
{
	public:
	D1():vBase(1){cout << "D1()" << endl;}	
	
	virtual void vfun(){cout << "d1 vfun" << endl;}
	virtual void vfun2(){cout << "d1 vfun2" << endl;}
	virtual void vfun3(){cout << "d1 vfun3" << endl;}
	//用于可见性测试
	int x = -2;
	int y = -2;
};

class D2: public virtual vBase//虚继承,vBase为虚基类
{
	public:
	D2():vBase(2){cout << "D2()" << endl;}
	
	virtual void vfun(){cout << "d2 vfun" << endl;}
	virtual void vfun3(){cout << "d2 vfun3" << endl;} 
	//用于可见性测试
	int y = -3;
};

class D3: public D1, public D2//普通继承
{
	public:
	D3():vBase(3){cout << "D3()" << endl;}
	D3(int){cout << "D3()" << endl;}
	
	virtual void vfun(){cout << "d3 vfun" << endl;} 
};

int main(void)
{
	//构造函数测试
	D3 d;
	//结果输出:
	//3:vBase()//注意
	//D1()
	//D2()
	//D3()
	//即首先构造虚基类,且有虚基类的构造函数以继承树的最低位置的类的构造为准(本例中最低的类为D3),之后按顺序构造继承表中的各类
	cout << "===============" << endl;
	D3 d2(1);
	//结果输出:
	//vBase()
	//D1()
	//D2()
	//D3()
	//最低层的类构造函数没有提供虚基类的显式构造,因此虚基类默认构造.
	
	cout << "===============" << endl;
	D2 d3;
	D1 d4;
	//结果输出:
	//2:vBase()
	//D2()
	//1:vBase()
	//D1()
	//对于这两个语句,继承树的最低位置类分别为D2和D1,虚基类构造函数分别以D2和D1为主

	cout << "===============" << endl;
	//成员可见性测试
	cout << d.x << endl;//输出-2,派生类优先级比共享基类高
	//cout << d.y << endl;//二异性错误D2::y和D1::y
	
	//虚函数测试
	cout << "===============" << endl;
	D3 t3;
	D2 t2;
	D1 t1;
	vBase t4;
	vBase *bp;
	bp = &t3;
	bp->vfun();
	bp = &t2;
	bp->vfun();
	bp = &t1;
	bp->vfun();
	bp = &t4;
	bp->vfun();
	//结果输出:
	//d3 vfun
	//d2 vfun
	//d1 vfun
	//base vfun
	cout << "===============" << endl;
	bp = &t3;
	bp->vfun2();
	bp = &t2;
	bp->vfun2();
	bp = &t1;
	bp->vfun2();
	bp = &t4;
	bp->vfun2();
	//结果输出:
	//d1 vfun2 //派生类D1优先级比共享基类高,因此优先匹配D1的vfun2
	//base vfun2//D2继承自vBase类且未重写基类虚函数
	//d1 vfun2
	//base vfun2
	cout << "===============" << endl;
	bp = &t3;
	//bp->vfun3();//报错:no unique final overrider for ‘virtual void vBase::vfun3()’ in ‘D3’
	//D3继承自D1,D2,这两个类都覆写了共享基类的虚函数,造成编译错误
}
