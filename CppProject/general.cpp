#pragma warning(disable: 4996)

#include <iostream>
#include <string.h>
#include "general.h"
using namespace std;


//checks if the String containes only correct words .
bool General::isOnlyWords(const char* str) 
{
	int size = (int)(strlen(str));
	for (int i = 0;i < size;i++) 
	{
		if (!((str[i] >= 'a'&& str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') || (str[i] == ' ')|| (str[i] == '-'))) 
		{
			return false;
		}
	}
	return true;
}

// gets an index number according to a specific range for menus
void General::getIndexNumber(int& index, int min, int max) 
{
	cin >> index;
	while (index < min || index> max)
	{
		cout << "invalid input choice! try again." << endl;
		cin >> index;
	}
}