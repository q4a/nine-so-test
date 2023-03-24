
#include "d3dtester.h"
#include <iostream>

bool checkD3D()
{
	CHW hw;
	hw.CreateD3D();
	const bool result = hw.pD3D;
	hw.DestroyD3D();
	return result;
}

int main()
{
	if (checkD3D())
		std::cout << "all good" << std::endl;
	else
		std::cout << "D3D failed" << std::endl;

	return 0;
}
