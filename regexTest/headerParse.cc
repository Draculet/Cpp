#include <regex>
#include <iostream>
#include <vector>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> 

using namespace std;

void parseHead(string line)
{
    int begin = 0;
    int cur = 0;
    cur = line.find(" ", begin);
    string method = string(line, begin, cur - begin);
    cout << method << endl;
    begin = cur + 1;
    cur = line.find(" ", begin);
    string path = string(line, begin, cur - begin);
    cout << path << endl;
    begin = cur + 1;
    string version = string(line, begin);
    cout << version << endl;
}
int main()
{
    map<string, string> req;
    char buf[1024 * 5] = {0};
    int fd = open("header/requestPost.txt", O_RDONLY);
    int total = read(fd, buf, 1024 * 5);
    cout << total << endl;
    string s(buf);
    close(fd);
    int begin = 0;
    int cur = 0;
    string head;
    string body;
    int reqtail = s.find("\r\n\r\n", 0);
    if (reqtail != string::npos)
    {
        head = string(s, 0, reqtail);
        cout << head << endl;
        cout << head.size() << endl;
    }
    cout << "start" << endl << endl;
    while (true)
    {
        cur = head.find("\r\n", begin);
        if (cur != string::npos)
        {
            string line(s, begin, cur - begin);
            cout << line << endl;
            int ret = line.find(':');
            if (ret == string::npos)
            {
                parseHead(line);
            }
            else
            {
                 string key = string(line, 0, ret);
                 string value = string(line, ret + 2);
                 req[key] = value;
                 cout << "key: " << key << endl;
                 cout << "value: " << value << endl;
            }
            begin = cur + 2;
        }
        else
            break;
    }
    auto iter = req.find("Content-Length");
    if (iter != req.end())
    {
        cout << iter->second << endl;
    }
    int num = atoi(iter->second.c_str());
    body = string(s, head.size() + 4, num);
    cout << body << endl;
}