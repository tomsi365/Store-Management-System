#ifndef __ORDER_H
#define __ORDER_H

#include "general.h"
#include <vector>
using namespace std;

class Order
{
private:
	int m_feedbackedProducts;
	const int m_total;
	const int m_sum;
	bool m_paid;
	const Buyer* const m_buyer;
	vector<Seller*> const m_sellers;
	vector<Product*> const m_products;
	vector<bool> m_productsFeedback;
	static int s_paidOrders;
	static int s_count;
	const int m_id;
	// private methods
	const vector<Seller*> createSellerList(vector<Product*>& products);
	int getOrderSum(const vector<Product*>& products) const;
	vector<bool> initBoolArray();

public:
	Order(const Buyer& buyer, int cartSize, vector<Product*>& m_cart);
	Order(const Buyer& other) = delete;
	const Order& operator=(const Order& other) = delete;
	~Order();
	static int getPaidOrdersCount();

	const Buyer* getBuyer()					const;
	Product* getProductInIndex(int index)	const;
	int getNumOfProducts()					const;
	int getNumOfFeedbackedProducts()		const;
	bool orderStatus()						const;
	vector<Product*> returnCart()			const;
	bool isProductFeedback(int index)		const;
	int getId()								const;
	int getSum()							const;
	void orderPaid();
	void feedbackProduct(int index);

};

#endif