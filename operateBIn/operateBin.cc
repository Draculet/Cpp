//08 65 12 06 48 65 6C 6C 6F 77
#include <iostream>
#include <cstdio>
#include <string>
using namespace std;

int main(void)
{
	char ch[10] = {0x08, 0x65,     0x12,    0x06,   0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x77};
	
	for (int i = 0; i < 10; i++)
	{
		//printf("%c", ch[i]);
	}
	char c = 0b01000000;
	
	string s = "";
	for (int i = 0; i < 7; i++)
	{
		int res = c & ch[1];
		//printf("%d\n", res);
		if ((c & ch[1]) == 0)
		{
			//s += "0";
			cout << "0";
		}
		else if ((c & ch[1]) == c)
		{
			//s += "1";
			cout << "1";
		}
		//cout << s << endl;
		c = c >> 1;
		//printf("%d\n", c);
	}
	cout << endl;
	
}

