#include <iostream>
#include <functional>
using namespace std;

//functor函数调用了function的移动构造函数
void func(int i)
{
	printf("func address %0x\n", &i);
}

void functor(function<void()> f)
{
	printf("In func address %0x\n", &f);
	//f();
}

int main(void)
{
	int i = 1;
	function<void()> ft = bind(func, i);
	printf("address %0x\n", &ft);
	//func(i);
	functor(std::move(ft));
	ft();
}
