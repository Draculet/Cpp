#include <iostream>
#include <vector>

//总结: 不同命名空间在定义时,同名类在使用了using namespace会可能造成编译错误,因为构建类时会混淆.(如本例中的vector和std::vector, Common::Test和class Test),报错位置在调用构造函数时.
//当类在实体化之后,全局命名空间和局部区域同名实体优先访问局部实体,访问全局命名空间需要用::val来访问.

class vector
{
	public:
	vector(){std::cout << "vector()" <<std::endl;}
};


namespace Common
{
	class Test
	{
		public:
		Test(int i):_i(i){}
		
		Test()
		{
			using namespace std;
			//限定using namespace的作用域
			cout << "Test()" << endl;
		}
		
		void print()
		{
			using namespace std;
			//限定using namespace的作用域
			cout << _i << endl;
		}
		int _i;
	};
}


	class Test
	{
		public:
		Test(int i):_i(i){}
		Test(){std::cout << "Main Test()" << std::endl;}
		void print(){std::cout << "Main " <<  _i << std::endl;}
		int _i;
	};
//如果不注释namespace Space2就会编译错误: reference to ‘Test’ is ambiguous
//原因是Space2中using namespace Common
//在Space2中的Test指代不明,可能是全局命名空间中的Test,也可能是Common中的Test.


/*
namespace Space2
{
	using namespace Common;
	//限定using namespace的作用域
	Test t(-4);
}
*/

namespace Space
{
	Common::Test t(-3);
}


namespace Space3
{
	Test t2(-5);
}

namespace Space4
{
	using namespace Common;
	//限定using namespace的作用域
	::Test t(-4);//此处为全局Test
}
//using namespace Common; 编译错误

Test t(-9999);

using namespace std;
//using namespace Space2; //编译错误,Space2命名空间和Space有同名Test对象.reference to ‘t’ is ambiguous
using namespace Space;
using namespace Space3;
using namespace Space4;
int main(void)
{
	//vector v;//编译错误,std命名空间和全局命名空间vector同名.reference to ‘vector’ is ambiguous;出错位置在调用处,编译错误,std命名空间和全局命名空间vector同名.reference to ‘vector’ is ambiguous
	::vector v;//访问全局中的vector
	//::t.print();//注释掉line80 Test t(-9999),编译错误,因为Space4, Space都有t
	//t.print();//注释掉line80 Test t(-9999),编译错误,因为Space4, Space都有t
	//t.print();//输出-9999,全局命名空间
	Common::Test t;
	t.print();//未初始化输出不定,局部变量
	::t.print();//输出-9999,全局命名空间
	t2.print();//输出Main -5,Space3命名空间
	//Test t2;//编译不通过,因为Space4的using namespace Common;引入Common命名空间,而我们又using namespace Space4;所以此处Test是悬而未决的.
	::Test t2;//Main Test()
	t2.print();//Main -1020819568(数字不定)
}
