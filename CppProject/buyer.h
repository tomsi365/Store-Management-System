#ifndef __BUYER_H
#define __BUYER_H

#include "general.h"
#include "user.h"
#include <vector>

class Buyer : virtual public User
{
private:
	vector<Product*> m_cart;
	vector<bool> m_isProductInOrder;
	int m_openOrders;
	// private methods
	int findEmptyIndex() const;
	bool printProdcutsByName() const;

public:
	Buyer(const string& username, const string& password, const string& country, const string& city, const string& street, int street_number);
	Buyer(const Buyer&) = delete;
	const Buyer& operator=(const Buyer& other) = delete;
	virtual ~Buyer();
	int getCartSize()						const;
	Product* getProductInIndex(int index)	const;
	int getOrderNum()						const;
	bool isProductInOrder(int index)		const;
	void addProductToCart(Product* product);
	void addOrder();
	void removeOrder();
	void removeFromCart(vector<Product*>& orderProducts);
	void setProductInOrder(int index);
	bool operator>(const Buyer& other) const;
	bool operator<(const Buyer& other) const;
	int getCartSum() const;

};


#endif