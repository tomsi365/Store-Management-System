#pragma warning(disable: 4996)

#include <iostream>
#include <string>
#include "feedback.h"
#include "date.h"
#include "order.h"
#include "product.h"
#include "seller.h"
#include "ui.h"

using namespace std;

//constructor .
Feedback::Feedback(int day, int month, int year, const string& input, const Product& product, const Buyer& buyer):
 m_date(Date(day,month,year)) , m_input(input) , m_product(&product) , m_buyer(&buyer) 
{}

//destructor .
Feedback::~Feedback()
{
}

//returns a day .
int Feedback::getDay() const
{
	return this->m_date.getDay();
}

//returns a month .
int Feedback::getMonth() const
{
	return this->m_date.getMonth();
}

//returns a year .
int Feedback::getYear() const
{
	return this->m_date.getYear();
}

//returns a input .
const string& Feedback::getInput() const
{
	return this->m_input;

}

//returns feedback's seller .
Seller* Feedback:: getSeller() const 
{
	return this->m_product->getSeller();
}