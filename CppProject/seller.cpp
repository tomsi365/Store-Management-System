#pragma warning(disable: 4996)

#include <string>
#include <iostream>
#include "seller.h"
#include "product.h"
#include "feedback.h"

using namespace std;


//constructor .
Seller::Seller(const string& username, const string& password, const string& country, const string& city, const string& street, int street_number) :
	User(username, password, country, city, street, street_number) 
{
	this->m_stock.reserve(General::c_initial_array_size);
	this->m_feedbacks.reserve(General::c_initial_array_size);
}

//destructor .
Seller::~Seller()
{
	deleteStockDeeply();
	deleteFeedbacksDeeply();
}

//adds a product dynamically to the seller's stock .
void Seller::addProduct(Product* product) 
{
	this->m_stock.push_back(product);
}

//adds a feedback dynamically to the feedbaks array .
void Seller::addFeedback(Feedback* feedback)
{
	this->m_feedbacks.push_back(feedback);
}

//deletes seller's stock deeply .
void Seller::deleteStockDeeply()
{
	vector<Product*>::iterator begin = this->m_stock.begin();
	vector<Product*>::iterator end = this->m_stock.end();
	for (;begin != end;++begin)
	{
		delete *begin;
	}
}

//deletes feedbaks array deeply .
void Seller::deleteFeedbacksDeeply()
{
	vector<Feedback*>::iterator begin = this->m_feedbacks.begin();
	vector<Feedback*>::iterator end = this->m_feedbacks.end();
	for (;begin != end;++begin)
	{
		delete *begin;
	}
}

//prints seller's products that are filtered by name .
void Seller::printProductsFilteredByName(const string& name) const
{

	vector<Product*>::const_iterator begin = this->m_stock.begin();
	vector<Product*>::const_iterator end = this->m_stock.end();
	for (;begin != end;++begin)
	{
		if (name.compare((*begin)->getName()) == 0 )
		{
			cout <<"id : "<< (*begin)->getId() << " , name : " << (*begin)->getName()
				<< " , price : " << (*begin)->getPrice() << " , category : " << (*begin)->getCategory()
				<<" ."<< endl;
		}
	}
}

// print product list
bool Seller::printProdcutsByName() const
{
	vector<Product*>::const_iterator begin = this->m_stock.begin();
	vector<Product*>::const_iterator end = this->m_stock.end();
	int i = 0;
	for (;begin != end;++begin)
	{
		cout << i + 1 << " : " << (*begin)->getName() << " . " << endl;
		i++;
	}
	if (m_stock.size())
		return true;

	return false;
}
// get max stock size
int Seller::getStockSize() const
{
	return (int)this->m_stock.size();
}

// return product pointer
Product* Seller::getProductInIndex(int index) const
{
	return this->m_stock[index];
}
