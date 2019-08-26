#include <iostream>
#include <cstdio>
using namespace std;
class Test
{
	public:
	Test():num(10){cout << "Test()" << endl;}
	int& incre()
	{
		num++;
		return num;
	}
	int& increTmp()
	{
		int tmp = num + 1;
		printf("tmp Address %x\n", &tmp);
		return tmp;
	}
	int increTmp2()
	{
		int tmp = num + 1;
		printf("tmp Address %x\n", &tmp);
		return tmp;
	}
	int *increTmpPtr()
	{
		int tmp = num + 1;
		printf("tmp Address %x\n", &tmp);
		return &tmp;
	}
	
	int num;
};

int main(void)
{
	//int &num = 1;
	const int &num = 1;
	Test t;
	int n = 1;
	printf("Before Address %x\n", &n);
	n = t.incre();
	printf("Stack Address %x\n", &n);
	printf("Address %x\n", &t.num);
	cout << n << endl;
	//
	int *p = t.increTmpPtr();
	printf("ptr Address %x\n", p);
	printf("Value: %d\n", *p);
	//
	//
	const int &r3 = t.increTmp2();
	printf("Ref Address %x\n", &r3);
	printf("Value: %d\n", r3);
	//
	//
	int &r = t.incre();
	printf("Ref Address %x\n", &r);
	printf("Address %x\n", &t.num);
	//
	//const int &cr = t.increTmp();
	int cr = t.increTmp();
	printf("cr Ref Address %x\n", &cr);
	cout << "cr " << cr << endl;
	//临时对象在return被销毁,不管cr是const int* 和int 都会core dump;
	//无法延长对象生命周期
	int &r2 = t.increTmp();
	printf("Ref Address %x\n", &r2);
	cout << "r2 " << r2 << endl;
	//Segmentation fault (core dumped)
	n = t.increTmp();
	//Segmentation fault (core dumped)
	cout << n << endl;
}
