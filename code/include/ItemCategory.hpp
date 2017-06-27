#pragma once

#include <iostream>
#include <string>


class ItemCategory
{

public:
	int category; // 1, 2, 3, 4 or 5
	std::string a;
	std::string C;
	std::string alpha_prim;

	ItemCategory(int category, std::string a, std::string C, std::string alpha_prim)
		:category(category), a(a), C(C), alpha_prim(alpha_prim) {};

	
};

