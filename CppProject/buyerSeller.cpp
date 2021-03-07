#pragma warning(disable: 4996)

#include "buyerSeller.h"

// main user constuctor 
BuyerSeller::BuyerSeller(const string& username, const string& password, const string& country, const string& city, const string& street, int street_number) :
	User(username, password, country, city, street, street_number), Buyer(username, password, country, city, street, street_number), Seller(username, password, country, city, street, street_number) {}

// destructor 
BuyerSeller::~BuyerSeller()
{

}


