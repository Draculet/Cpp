#include <memory>
#include <iostream>
using namespace std;

class Test
{
	public:
	Test(int n):num(n){cout << "Test" << endl;}
	~Test(){cout << "~Test" << endl;}
	void print(){cout << "print: " << num << endl;}
	private:
	int num = 0;
};
int main(void)
{
	Test *t = new Test(1);
	unique_ptr<Test> up(t);
	unique_ptr<Test> up2(t);//违规操作,两个unique_ptr共享一个裸指针,但编译器不会报错
	//这种情况会造成double free错误,因此不推荐暴露裸指针
	//推荐使用形如unique_ptr<Test> up(new Test(3))的方式构造
	
	
	//unique_ptr<Test> up5 = new Test(1);//explicit,不能隐式转换
	//up = up2;//禁止复制
	//unique_ptr<Test> up4(up);//禁止复制构造
	
	
	
	t->print();
	unique_ptr<Test> up3 = move(up);//存在移动构造
	//up交出所有权,且变为nullptr
	if (up != nullptr)
		up->print();//调用会有Segmentation fault (core dumped)错误
	//此时up3和up2都拥有t的所有权
	Test *tmp = up3.release();//up3放弃所有权,返回原指针
	//注意release是不会释放内存的,只是使unique_ptr不再维护裸指针
	//如果不将暴露出来的指针重新管理(unique_ptr up5(up3.release())),则会造成泄漏
	//此处还有up2持有t的所有权
	unique_ptr<Test> up5(up2.release());
	if (up2 == nullptr)
		up2.reset(t);
		
	//最终up5和up2都维护t指针,double free错误.
	cout << "============" << endl;
}
