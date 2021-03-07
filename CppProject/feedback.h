#ifndef __FEEDBACK_H
#define __FEEDBACK_H

#include "general.h"
#include "date.h"
#include <iostream>
using namespace std;

class Feedback
{
private:
	const Date m_date;
	const string m_input;
	const Product* const m_product;
	const Buyer* const m_buyer;

public:
	Feedback(int day,int month,int year, const string& input, const Product& product, const Buyer& buyer);
	Feedback(const Feedback& other) = delete;
	const Feedback& operator=(const Feedback& other) = delete;
	~Feedback();
	int getDay()			const;
	int getMonth()			const;
	int getYear()			const;
	Seller* getSeller()		const;
	const string& getInput()	const;
};

#endif