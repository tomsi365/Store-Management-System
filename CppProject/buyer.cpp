#pragma warning(disable: 4996)

#include <iostream>
#include <string>
#include <vector>
#include "buyer.h"
#include "product.h"

using namespace std;

// main constructor
Buyer::Buyer(const string& username, const string& password, const string& country, const string& city, const string& street, int street_number)
	:  m_openOrders(0), User(username, password, country, city, street, street_number)
{
	this->m_cart.reserve(General::c_initial_array_size);
	this->m_isProductInOrder.reserve(General::c_initial_array_size);
}

// desturctor
Buyer::~Buyer()
{

}

// add product to cart array
void Buyer::addProductToCart(Product* product) 
{
	// check first if there are empty spots
	int index = findEmptyIndex();
	if (index >= 0 && m_isProductInOrder[index] == true) // found deleted spot
	{
		this->m_cart[index] = product;
		this->m_isProductInOrder[index] = false;
	}
	else // no empty spots - add normally
	{
		this->m_cart.push_back(product);
		this->m_isProductInOrder.push_back(false);

	}
}

// returns an index if there is an empty spot in cart array
int Buyer::findEmptyIndex() const
{
	vector<Product*>::const_iterator begin = this->m_cart.begin();
	vector<Product*>::const_iterator end = this->m_cart.end();
	int i=0, index = -1;
	for (;begin!=end;++begin)
	{
		if (*begin == nullptr) // empty spot
		{
			index = i;
		}
		i++;

		if (index >= 0)
			break;
	}
	return index;
}

// return cart real size
int Buyer::getCartSize() const
{
	return (int)this->m_cart.size();
}

// returns a product pointer inside an array via index
Product* Buyer::getProductInIndex(int index) const
{
	return this->m_cart[index];
}

// prints all prodcuts in a cart by name
bool Buyer::printProdcutsByName() const
{
	vector<Product*>::const_iterator begin = this->m_cart.begin();
	vector<Product*>::const_iterator end = this->m_cart.end();
	int i = 0;
	for (;begin != end;++begin)
	{
		cout << i + 1 << " : " << (*begin)->getName() << " . " << endl;
		i++;
	}
	if (m_cart.size())
		return true;

	return false;
}

// adds an open order to a buyer
void Buyer::addOrder()
{
	this->m_openOrders++;
}
// removes an open order from a buyer
void Buyer::removeOrder()
{
	this->m_openOrders--;
}

// returns the number of open orders
int Buyer::getOrderNum() const
{
	return this->m_openOrders;
}

// removes items from cart after paying for an order
void Buyer::removeFromCart(vector<Product*>& orderProducts)
{
	vector<Product*>::iterator cart_begin = this->m_cart.begin();
	vector<Product*>::iterator cart_end = this->m_cart.end();


	vector<bool>::iterator isProductInOrder_begin = this->m_isProductInOrder.begin();
	for (;cart_begin != cart_end;++cart_begin)
	{
		vector<Product*>::iterator begin = orderProducts.begin();
		vector<Product*>::iterator end = orderProducts.end();
		for (; begin!=end; ++begin)
		{
			if (*cart_begin == (*begin)) // if found in order remove from cart
			{
				*cart_begin = nullptr;
				*isProductInOrder_begin = true;
			}
		}
		++isProductInOrder_begin;
	}
}

// marks product inside an order
void Buyer::setProductInOrder(int index)
{
	this->m_isProductInOrder[index] = true;
}

// returns if a product is inside an order
bool Buyer::isProductInOrder(int index) const
{
	return this->m_isProductInOrder[index];
}

// returns total sum of an order 
int Buyer::getCartSum() const
{
	vector<Product*>::const_iterator begin = this->m_cart.begin();
	vector<Product*>::const_iterator end = this->m_cart.end();
	int sum = 0;
	for (;begin != end;++begin)
	{
		sum += (*begin)->getPrice();
	}
	return sum;
}

// compares two buyer's cart
bool Buyer::operator>(const Buyer& other) const
{
	if (this->getCartSum() > other.getCartSum())
		return true;
	else
		return false;
}

// compares two buyer's cart
bool Buyer::operator<(const Buyer& other) const
{
	if (this->getCartSum() < other.getCartSum())
		return true;
	else
		return false;
}

