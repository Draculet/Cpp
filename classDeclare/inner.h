#include <iostream>
class outer;
class inner
{
	public:
		inner(){std::cout << "inner" << std::endl;}
		void setOuter(outer *p){o = p;}
	private:
		int i;
		outer *o;
};
