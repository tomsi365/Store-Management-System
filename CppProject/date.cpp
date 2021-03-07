#pragma warning(disable: 4996)

#include "date.h"

//constructor .
Date::Date(int day, int month, int year) : m_day(day), m_month(month), m_year(year) {}

//returns a day .
int Date::getDay() const 
{
	return this->m_day;
}

//returns a month .
int Date::getMonth() const 
{
	return this->m_month;
}

//return a year .
int Date::getYear()const 
{
	return this->m_year;
}
