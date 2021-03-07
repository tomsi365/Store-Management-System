#ifndef  __BUYERSELLER_H
#define  __BUYERSELLER_H

#include "general.h"
#include "buyer.h"
#include "seller.h"


class BuyerSeller: public Buyer, public Seller
{
public:
	BuyerSeller(const string& username, const string& password, const string& country, const string& city, const string& street, int street_number);
	virtual ~BuyerSeller();
	BuyerSeller(const User& other) = delete;
	const BuyerSeller& operator=(const BuyerSeller& other) = delete;
};



#endif 

