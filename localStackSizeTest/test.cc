#include <cstdio>
#include <cstring>
int main(void)
{
    char arry[1024 * 1024 * 4];
    memset(arry, 0, sizeof(arry));
    int pos = 0;
    char str[10];
    for (int i = 0; i < 10; i++)
        str[i] = static_cast<char>(i + 48);
    while (pos < sizeof(arry) - 10)
    {
        memcpy(arry + pos, str, 10);
        pos += 10;
    }
    printf("sizeof arry: %d\n", sizeof arry);
    //for (int i = 0; i < sizeof arry; i++)
    printf("%s\n", arry);
}