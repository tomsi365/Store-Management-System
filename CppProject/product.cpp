#pragma warning(disable: 4996)

#include <iostream>
#include <string>
#include "product.h"
#include "general.h"

using namespace std;

const char* Product::categories[] = {"Children","Office","Electricity","Clothes"};

int Product::s_counter = 0;

//constructor .
Product::Product(Item e_category, const string& itemName, int price,Seller& itemSeller) :
	m_serialNum(Product::s_counter), e_category(e_category), m_itemSeller(&itemSeller), m_price(price), m_itemName(itemName)
{
	Product::s_counter++;
}

//destructor .
Product::~Product() 
{
}

//returns a category .
const char* Product::getCategory() const
{
	return Product::categories[e_category-1];
}

//returns a name .
const string& Product::getName() const
{
	return this->m_itemName;
}

//returns a price .
int Product::getPrice() const
{
	return this->m_price;
}

//returns a id .
int Product::getId() const
{
	return this->m_serialNum;
}

// returns a pointer to a seller of an item
Seller* Product::getSeller() const
{
	return this->m_itemSeller;
}

// overloaded ostream, prints product info
std::ostream& operator<<(std::ostream& out, const Product& product)
{
	out << "Product Name: " << product.m_itemName << "\nProduct Category: " << product.getCategory() << "\nProdcut ID: " <<
		product.getId() << "\nProduct Price: " << product.getPrice() << endl;
	return out;
}