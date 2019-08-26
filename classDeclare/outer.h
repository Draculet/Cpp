#include <iostream>
#include "inner.h"

class outer
{
	public:
		outer(){std::cout << "constructor" << std::endl;}
		void setOuter(){i.setOuter(this);}
		int num;
	private:
		inner i;
};
