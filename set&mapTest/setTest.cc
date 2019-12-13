#include <set>
#include <iostream>
#include <memory>

using namespace std;

/*
    set对于自定义类是根据重载的<运算符来插入红黑树的
    set是键值相同的map

    shared_ptr重载了比较运算符,且重载依据的是shared_ptr指向对象的地址,而非shared_ptr本身

 */

class A
{
    public:
    int i = 0;  
};

bool operator<(A a, A b)
{
    return a.i < b.i;
}



int main(void)
{
    //测试普通重载类
    set<A> s;
    A a;
    A a2;
    s.insert(a);
    s.insert(a2);
    cout << s.size() << endl;
    a.i = 23;
    s.insert(a);
    cout << s.size() << endl;


    //测试shared_ptr
    set<shared_ptr<A> > s2;
    shared_ptr<A> p(new A());
    shared_ptr<A> p2(new A());
    shared_ptr<A> p3(new A());
    printf("%0x %0x %0x\n", &p, &p2, &p3);
    printf("%0x %0x %0x\n", &*p, &*p2, &*p3);
    s2.insert(p);
    s2.insert(p2);
    s2.insert(p3);
    cout << "before:" << s2.size() << endl;
    shared_ptr<A> p4 = p3;
    p4->i = 100;
    s2.insert(p4);
    cout << "after:" << s2.size() << endl;
    p4.reset(new A());
    s2.insert(p4);
    cout << "then:" << s2.size() << endl;
    cout << s2.size() << endl;
    for (auto p : s2)
    {
        printf("%0x ", &p);
    }
    cout << endl;
    for (auto p : s2)
    {
        printf("%0x ", &*p);
    }
    cout << endl;

    cout << "========================" << endl;
    //验证是否是以指向对象的地址作为键
    set<shared_ptr<A> > s3;
    A *b = new A();
    printf("%0x ", b);
    A *b2 = new A();
    b2->i = 199;
    printf("%0x ", b2);
    A *b3 = new A();
    printf("%0x ", b3);
    A *b4 = new A();
    printf("%0x ", b4);
    cout << endl;
    shared_ptr<A> pp(b);
    s3.insert(pp);
    pp.reset(b4);
    s3.insert(pp);
    pp.reset(b2);
    s3.insert(pp);
    pp.reset(b3);
    s3.insert(pp);
    
    for (auto p : s3)
    {
        printf("%0x ", &*p);
    }
    cout << endl;
    pp.reset(b2);
    auto iter = s3.find(pp);
    cout << (*iter)->i << endl;
}
