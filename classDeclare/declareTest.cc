#include <iostream>
#include "outer.h"
using namespace std;

int main(void)
{
	outer o;
	o.setOuter();
	cout << o.num << endl;
}
