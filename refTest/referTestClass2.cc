#include <iostream>
#include <cstdio>
using namespace std;

//结论:将临时变量以引用的形式返回是不可取的
//返回的最终是临时变量的引用
class Integer
{
	public:
	Integer():num(0){cout << "Integer()" << endl;}
	~Integer(){cout << "~Integer" << endl;}
	Integer(int n):num(n){cout << "Integer(int)" << endl;}
	Integer& incre()
	{
		num++;
		return *this;
	}
	
	
	Integer increTmp()
	{
		int tmp = num + 1;
		Integer i(tmp);
		printf("tmp Address %x\n", &i);
		return i;
	}
	
	int num;
};
/*Integer& increTmpOut()
{
	int tmp = 100;
	Integer i(tmp);
	printf("Out tmp Address %x\n", &i);
	return i;
}*/

int main(void)
{
	Integer t;
	/*Integer n;
	printf("Before Address %x\n", &n);
	n = t.incre();
	printf("Stack Address %x\n", &n);
	printf("Address %x\n", &t);
	//
	Integer &r = t.incre();
	printf("Ref Address %x\n", &r);
	*/
	//
	//
	//const Integer &cr = t.increTmp();
	printf("before address %x\nafter address %x\n", &t, &(t.incre()));
	const Integer &cr = t.increTmp();
	printf("cr Ref Address %x\n", &cr);//结果是0
	cout << "cr " << cr.num << endl;
	//Segmentation fault (core dumped)
	cout << "t.increTmp()" << endl;
	t.increTmp();
	//printf("Ref Address %x\n", &r2);//结果是0
	cout << "Whether deconstrust ?"<< endl;
	
	//由结果可看出,const &延长了临时变量的生命周期
	//由于编译器的优化,Integer cr = t.increTmp()也会延长临时变量的周期,且不会发生不必要的拷贝(NVR优化)
	//但是如果不给返回值赋值则临时变量在return时析构.
	
	//Segmentation fault (core dumped)

}
