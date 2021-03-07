#pragma warning(disable: 4996)

#include <iostream>
#include <vector>
#include "order.h"
#include "product.h"

using namespace std;

int Order::s_paidOrders = 0;
int Order::s_count = 0;

// main order constructor
Order::Order(const Buyer& buyer, int cartSize, vector<Product*>& m_cart) : m_buyer(&buyer), m_total(cartSize),
 m_products(m_cart), m_sellers(createSellerList(m_cart)), m_paid(false), m_sum(getOrderSum(m_cart)),
	m_productsFeedback(initBoolArray()), m_feedbackedProducts(0) , m_id(s_count) 
{
	Order::s_count++;
}

// allocates and creates seller list from which order was taken
const vector<Seller*> Order::createSellerList(vector<Product*>& products) // TEST THIS
{
	vector<Product*>::const_iterator begin = products.begin();
	vector<Product*>::const_iterator end = products.end();
	bool found = false;
	vector<Seller*> sellers;
	sellers.push_back((*begin)->getSeller());


	for (; begin!=end; ++begin)
	{
		vector<Seller*>::const_iterator sellersbegin = sellers.begin();
		vector<Seller*>::const_iterator sellersend = sellers.end();
		for (; sellersbegin!=sellersend; ++sellersbegin)
		{
			if ((*begin)->getSeller() == (*sellersbegin))
				found = true;
		}
		// if reached here then seller doesnt exist in array
		if (!found) // doesnt exist in array yet
		{
			//add
			sellers.push_back((*begin)->getSeller());
		}
		found = false;
	}

	return sellers;
}


// destructor
Order::~Order()
{
}

// returns a buyer
const Buyer* Order::getBuyer() const
{
	return this->m_buyer;
}

// returns a prodcut pointer from a cart
Product* Order::getProductInIndex(int index) const
{
	return this->m_products[index];
}

// returns the amount of products inside an order
int Order::getNumOfProducts() const
{
	return this->m_total;
}
// returns total order sum
int Order::getSum() const
{
	return this->m_sum;
}

// sets order flag as paid
void Order::orderPaid()
{
	this->m_paid = true;
	Order::s_paidOrders++;
}

// returns order status (paid/not paid)
bool Order::orderStatus() const
{
	return this->m_paid;
}

// returns if a product inside an order has been feedbacked yet
bool Order::isProductFeedback(int index) const
{
	return this->m_productsFeedback[index];
}
// returns order cart
vector<Product*> Order::returnCart() const
{
	return this->m_products;
}

//returns how much orders were paid .
int Order::getPaidOrdersCount() 
{
	return s_paidOrders;
}

//sings a product that has got a feedback .
void Order::feedbackProduct(int index) 
{
	this->m_productsFeedback[index] = true;
	this->m_feedbackedProducts++;
}

//returns num of feedbacked products 
int Order::getNumOfFeedbackedProducts() const  
{
	return this->m_feedbackedProducts;
}

//returns order's id .
int Order::getId() const
{
	return this->m_id;
}

// returns total sum of an order 
int Order::getOrderSum(const vector<Product*>& products) const
{
	vector<Product*>::const_iterator begin = products.begin();
	vector<Product*>::const_iterator end = products.end();
	int sum = 0;
	for (; begin!= end; ++begin)
	{
		sum += (*begin)->getPrice();
	}
	return sum;
}

// initilaizes a bool array for the object Order
vector<bool> Order::initBoolArray()
{
	vector<bool> returnArray;
	for (int i = 0; i < m_total; i++)
	{
		returnArray.push_back(false);
	}
	return returnArray;
}