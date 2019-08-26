#include <iostream>
using namespace std;

struct Test
{
	int i;
	int j;
};

int main(void)
{
	Test t[4];
	Test *s = &t[0];
	Test *b = &t[3];
	cout << b - s << endl;
	cout << reinterpret_cast<size_t>(b) - reinterpret_cast<size_t>(s) << endl;
	return 0;
}
