#include <iostream>


class Test
{
	public:
	static void func();
	//static int num = -1;//error
	static int num;
};

void Test::func()
{
	std::cout << "No problem" << std::endl;
}

//Test::num = -1;//error
int Test::num = -1;
int main(void)
{
	Test::func();
	std::cout << Test::num << std::endl;
}
