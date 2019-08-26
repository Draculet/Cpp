#include <iostream>

//总结:  ::运算符是全局命名空间,当我们在全局区域定义变量val,则::val访问的是这个变量val
//       当我们using namespace某个命名空间中也有同名变量val时,::val访问的依旧是它
//       如果我们没有定义该变量val,而using namespace的某个命名空间中有val,则::val访问的是namespace里的变量

//int i = -9;放在这效果相同
namespace Test
{
	int i = -1;
}

namespace Test2
{
	int i = 11;
}
using namespace Test;
//using namespace Test2;
//int i = -9;

int main(void)
{
	using namespace std;
	cout << ::i << endl;//打印-9,::表示全局命名空间
	//如果注释掉 line14 int i = -9; 则此处打印-1.因为全局命名空间里只有Test里的i.
	//如果注释掉 line14 int i = -9,去掉line13 using namespace Test2;的注释，则编译报错,reference to ‘i’ is ambiguous

	int i = 10;
	cout << i << endl;//打印10,main函数里的局部变量
	
	
	using namespace Test2;
	cout << ::i << endl;//结果于line19相同
}
