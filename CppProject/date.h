#ifndef __DATE_H
#define __DATE_H

#include "general.h"

class Date
{
private :
	int m_day;
	int m_year;
	int m_month;

public:
	static const int c_minimal_year = 2000;
	static const int c_current_year = 2020;
	static const int c_min_day = 1;
	static const int c_max_day = 31;
	static const int c_min_month = 1;
	static const int c_max_month = 12;

	Date(int day, int month, int year);
	int getDay()	const;
	int getMonth()	const;
	int getYear()	const;
};

#endif