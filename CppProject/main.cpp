#pragma warning(disable: 4996)

#include <iostream>
#include "system.h"
using namespace std;

int main()
{
	System main("main", "systemUserData.txt");
	main.startMenu();
	return 0;
}