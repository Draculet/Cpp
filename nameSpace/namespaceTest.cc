#include "namespaceTest.h"
//总结:main函数的变量是局部变量,优先级高
//使用using namespace的命名空间中的变量等函数会被引入全局命名空间
//当全局命名空间与当前命名空间有同名变量时,优先访问的是全局命名空间中的变量,使用::val访问全局命名空间中的同名变量、函数、类等
//using namespace要求using的几个命名空间,在访问同名变量,同名命名空间,同名函数不会造成混淆,否则编译不通过
//未命名的namespace是直接定义并自动使用的
//当using namespace引入的命名空间和全局区域(命名空间)中有同名元素时，::访问的是全局区域(命名空间)的元素,如果全局区域没有该元素,则::访问的是using namespace引入的命名空间的元素

namespace MainSpace
{
	int i = 13;
	void func(){std::cout << "MainSpace func()" << std::endl;}
	namespace Sub
	{
		int i = 20;
	}
	namespace Inner
	{
		int i = 21;
	}
}

namespace Another
{
	int k = -1;
	namespace Inner
	{
		int i = -2;
	}
}

namespace Another2
{
	int k = -1;
	namespace Inner2
	{
		int i = -2;
	}
}

//namespace
//{
//	int i = 15;
//} 编译出错, 无名namespace定义后就直接using了,两个namespace都有i.
using namespace std;

namespace
{
	int j = 10;
}

void func()
{
	cout << "fuck up all" << endl;
}

using namespace Outer;

//using namespace Another; 编译出错, 有两个Inner命名空间
using namespace Another2;

//void func(){cout << "" << endl;}编译不通过,  call of overloaded ‘func()’ is ambiguous

//using namespace MainSpace; 编译出错,两个namespace都有i

//int i = -999;
//如果定义了全局变量,则所有::i都输出-999

int main(void)
{
	
	cout << i << endl;//打印11(Outer命名空间)
	cout << ::i << endl;//打印11(全局命名空间)
	//由于没有定义全局变量i,所以::全局命名空间访问的是using namespace里的i
	::func();
	//func();//无法调用,call of overloaded ‘func()’ is ambiguous
	int i = 14;
	cout << i << endl;//打印14(main函数的局部变量)
	cout << ::i << endl;//打印11(全局命名空间):由于没有定义全局变量i,所以::全局命名空间访问的是using namespace里的i
	cout << j << endl;//打印10(无名命名空间)
	cout << Inner::i << endl;//打印12(Inner命名空间)
	//cout << Sub::i << endl; 编译出错
	cout << MainSpace::Sub::i << endl;//打印20(Sub命名空间)
	cout << MainSpace::Inner::i << endl;//打印21(MainSpace::Inner命名空间)
	using namespace MainSpace;//同名变量似乎无效,但能达到引入变量的效果
	using namespace MainSpace::Inner;//似乎无效
	cout << ::i << endl;//打印11(Outer命名空间)
	cout << i << endl;//打印14(main函数的局部变量)
	cout << k << endl;//打印-1(Another2命名空间)
	int k = 1;
	cout << k << endl;//打印1(主命名空间)
	cout << ::k << endl;//打印-1(Another2命名空间)
	cout << Inner2::i << endl;//打印-2(Inner2命名空间)
	
}
