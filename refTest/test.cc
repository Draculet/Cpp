#include <iostream>
#include <functional>
using namespace std;

class Test
{
	public:
	Test(){}
	~Test(){}
	Test(const Test &) = delete;
	Test(Test &&) = delete;
	void print(){cout << "hello" << endl;}
};

void print(Test &)
{
}

int main(void)
{
	Test t;
	print(t);
	bind(print, t);//bind会复制,而复制构造函数被delete
}
