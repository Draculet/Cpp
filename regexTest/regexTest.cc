#include <regex>
#include <iostream>
using namespace std;

int main(void)
{
    regex reg("([a-z]{3}-[1-3])-([1-9])");
    string s = "asc-2-3-423423-423";
    smatch r1;
    if (regex_search(s, r1, reg))
    {
        cout << r1.str() << endl;
        cout << r1[1] << endl;
        cout << r1[2] << endl;
        cout << r1[3] << endl;
    }
}