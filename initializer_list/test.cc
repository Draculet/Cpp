#include <iostream>
using namespace std;

//总结:
//print2无法通过编译,因为initializer_list中的对象为const,不能改变,需要常引用才行
//原因并不是范围for产生的对象是临时对象
//根据下面的测试,范围for的对象是左值,可以直接赋值给引用

void print(const initializer_list<string> &il)
{
	for (const string &tmp : il)//临时对象,去掉const无法通过编译
		cout << tmp << endl;
	return;
}

//无法通过编译,因为initializer_list中的对象为const,不能改变,需要常引用才行
//原因并不是范围for产生的对象是临时对象
//根据下面的测试,范围for的对象是左值,可以直接赋值给引用
/*void print2(const initializer_list<string> &il)
{
	for (string &tmp : il)
		cout << tmp << endl;
	return;
}*/
int main(void)
{
	print({"abc", "vda", "qwe"});
	int arr[5] = {1,2,3,4,5};
	for (int i = 0; i < 5; i++)
	{
		printf("Address %x\n", &arr[i]);
	}
	for (int &i : arr)
	{
		cout << ((int &)i = 5) << endl;
		printf("address %x\n", &i);
	}
	for (auto &i : arr)
		cout << i << endl;
		
	string str[5] = {"he", "ha", "re", "gg", "cc"};
	for (int i = 0; i < 5; i++)
	{
		printf("Address %x\n", &str[i]);
	}
	for (string &i : str)
	{
		cout << (i = "acc") << endl;
		printf("address %x\n", &i);
	}
	for (auto &i : str)
		cout << i << endl;
	
}
