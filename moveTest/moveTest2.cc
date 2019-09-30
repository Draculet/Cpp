#include <iostream>
#include <functional>
using namespace std;

//这种默认移动构造函数并没有移动效果,行为类似复制构造函数

class Test
{
    public:
    Test(){}
    ~Test(){cout << "~Test()" << endl;}
    Test(Test &){cout << "Test(&)" << endl;}
    Test(Test&&)=default;
    void call(){cout << "hello " << i << endl;}
    private:
    int i;
};

void functest(Test t)
{
    printf("In func address %0x\n", &t);
    t.call();
}

int main(void)
{
	int i = 1;
    Test t;
	printf("address %0x\n", &t);
	Test tmp = std::move(t);
	t.call();
    //while(1)
    //{}
}
