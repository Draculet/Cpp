#include <iostream>
namespace Outer
{
	int i = 11;
	void func();
	void func2(){std::cout << "Out hello" << std::endl;}
	namespace Inner
	{
		int i = 12;
		void func();
		void func2(){std::cout << "In hello" << std::endl;};
		void func3(){std::cout << "In hello func3" << std::endl;};;
	}
}

void Outer::func()
{
	std::cout << "Default func()" << std::endl;
}

void Outer::Inner::func()
{
	std::cout << "Default func2()" << std::endl;
}
