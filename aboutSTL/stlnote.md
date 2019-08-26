<h2>Chapter1</h2>

* 宏__STL_NULL_TEMPL_ARGS:
<br />用途:<br />在对进行__type_traits进行针对char的特化以提高效率时使用:__STL_NULL_TEMPL_ARGS struct __type_traits< char >{...}展开为:
<br />template<> struct __type_traits< char >{...},不需要指定T即完成explicit specialization

<h2>Chapter2</h2>

* 内存池,freelist等的实现. 

* constructor,destructor等都是传指针(T*),但内存构造工具如uninitialized_copy等都是传迭代器,所以对非POD类型需要逐个迭代器调用constructor,而调用时传入方式为construct(&*i, x); 其中*是迭代器取得实体,&用于取得指针,x则是目标实体,而construct函数
<br />template< class T1, class T2>
<br />void construct(T1 *p, const T2& value){new(p) T1(value);}//placement new, 调用相应构造函数.

* 迭代器一般可由指针构造,或者干脆就是typedef的指针(如vector)，所以allocate得到的指针,返回后一般赋值给迭代器.(如: iterator result = data_allocator::allocate(n);)

<h2>Chapter3</h2>

* 迭代器由相应容器去实现

* traits编程技法

* 迭代器的iterator_category用于指定迭代器类型. iterator_category一般在template< class iterator_category> struct iter{},在iter实例化时以 iter< bidirectional_iteractor_tag> i的方式传入迭代器类型,该类型可帮助设计性能优化的算法.