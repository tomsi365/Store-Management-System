#ifndef __PRODCUT_H
#define __PRODCUT_H

#include "general.h"
using namespace std;

class Product
{
private:
	const Item e_category;
	const string m_itemName;
	const int m_serialNum;
	int m_price;
	Seller* const m_itemSeller;
	static int s_counter;

public:
	static const char* categories [];
	Product(Item e_category , const string& itemName,int price, Seller& itemSeller);
	Product(const Product& other) = delete;
	const Product& operator=(const Product& other) = delete;
	~Product();
	const char* getCategory()	const;
	const string& getName()		const;
	int getPrice()				const;
	int getId()					const;
	Seller* getSeller()			const;

	friend std::ostream& operator<<(std::ostream& out, const Product& product);
};

#endif