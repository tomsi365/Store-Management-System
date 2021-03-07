#ifndef __SELLER_H
#define __SELLER_H

#include "general.h"
#include "user.h"
#include <vector>

class Seller: virtual public User
{
private:
	vector<Product*> m_stock;
	vector<Feedback*> m_feedbacks;
	// private functions
	void deleteStockDeeply();
	void deleteFeedbacksDeeply();

public:
	Seller(const string& username, const string& password, const string& country, const string& city, const string& street, int street_number);
	Seller(const Seller&) = delete;
	const Seller& operator=(const Seller& other) = delete;
	virtual ~Seller();
	void printProductsFilteredByName(const string& name)	const;
	bool printProdcutsByName()							const;
	int getStockSize()									const;
	Product* getProductInIndex(int index)				const;
	void addProduct(Product* product);
	void addFeedback(Feedback* feedback) ;

};

#endif