#include <iostream>
#include <cstdio>
using namespace std;

//结论:将临时变量以引用的形式返回是不可取的
//返回的最终是临时变量的引用
class Integer
{
	public:
	Integer():num(0){cout << "Integer()" << endl;}
	//~Integer() =delete;
	Integer(int n):num(n){cout << "Integer(int)" << endl;}
	Integer& incre()
	{
		num++;
		return *this;
	}
	Integer& increTmp()
	{
		int tmp = num + 1;
		Integer i(tmp);
		printf("tmp Address %x\n", &i);
		return i;
	}
	
	int num;
	private:
	~Integer(){};
};



int main(void)
{
	Integer t;
	//
	Integer &r = t.increTmp();
	printf("Ref Address %x\n", &r);
	cout << "value: " << r.num << endl;
	//
	//
	//const Integer &cr = t.increTmp();
	const Integer &cr = t.increTmp();
	printf("cr Ref Address %x\n", &cr);//结果是0
	cout << "cr " << cr.num << endl;
	//Segmentation fault (core dumped)
	Integer &r2 = t.increTmp();
	printf("Ref Address %x\n", &r2);//结果是0
	cout << "r2 " << r2.num << endl;
	//Segmentation fault (core dumped)

}
