#pragma warning(disable: 4996)

#include <iostream>
#include <string>
#include <vector>
#include "ui.h"
#include "product.h"
#include "seller.h"
#include "buyer.h"
#include "buyerSeller.h"
#include "feedback.h"
#include "order.h"

using namespace std;

//creates a product , by details that has been received from the keyboard .
Product* UI::createProduct(Seller& seller)
{
	int category;
	cout << "choose a product category (1-4).\n"
		<< "note - 1 for Children, 2 for Office, 3 for Electric, 4 for Cloths.\n" << endl;
	General::getIndexNumber(category, General::c_minimal_index, General::c_maximal_product_index);

	cout << "enter a product name (use only correct words/space/'-') ." << endl;
	string name;
	cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
	getline(cin,name);
	while (General::isOnlyWords(name.c_str()) == false)
	{
		cout << "invalid name ! try again ." << endl;
		getline(cin, name);
	}

	cout << "enter a product price ." << endl;
	int price;
	cin >> price;
	while (price < 0)
	{
		cout << "invalid price ! try again ." << endl;
		cin >> price;
	}

	Product* p = new Product((Item)category, name, price, seller);
	return p;
}

//static function , handles input and creation of the buyer object . .
Feedback* UI::createFeedback(vector<Order*>& orders)
{
	vector<Order*> payedOrders;
	makePayedOrdersArray(orders, payedOrders);
	if (payedOrders.size() == 0)
	{
		cout << "there aren't paid orders ," << endl;
		cout << "return to main menu ." << endl;
		return nullptr;
	}
	Order* chosenOrder = UI::getPayedOrder(payedOrders);
	vector <Product*> nonFeedbackedProducts;
	vector <int> bools;
	makeNonFeedbackedProductsArray(chosenOrder, nonFeedbackedProducts,bools);
	if (nonFeedbackedProducts.size() == 0)
	{
		cout << "there aren't non-feednbacked products ," << endl;
		cout << "return to main menu ." << endl;
		return nullptr;
	}
	
	int screen_index;
	Product* chosenProduct = UI::getNonFeedbackedProduct( nonFeedbackedProducts, screen_index);

	chosenOrder->feedbackProduct(bools[screen_index - 1]);
	
	int day, month, year;
	cout << "enter a day (" << Date::c_min_day << "-" << Date::c_max_day << ") ." << endl;
	General::getIndexNumber(day, Date::c_min_day, Date::c_max_day);
	cout << "enter a month (" << Date::c_min_month << "-" << Date::c_max_month << ") ." << endl;
	General::getIndexNumber(month, Date::c_min_month, Date::c_max_month);
	cout << "enter a year (" << Date::c_minimal_year << "-" << Date::c_current_year << ") ." << endl;
	General::getIndexNumber(year, Date::c_minimal_year, Date::c_current_year);

	cout << "enter a feedback !" << endl;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	string input;
	getline(cin, input);

	Feedback* feedback = new Feedback(day,month,year, input, *chosenProduct, *(chosenOrder->getBuyer()));


	return feedback;
}

//returns a payed orders array .
void UI::makePayedOrdersArray(vector<Order*>& ordersList ,vector<Order*>& payedOrders)
{
	vector<Order*>::iterator begin = ordersList.begin();
	vector<Order*>::iterator end = ordersList.end();
	for (;begin != end;++begin)
	{
		if ((*begin)->orderStatus() == true)
		{
			payedOrders.push_back(*begin);
		}
	}
}

//returns a payed order that has been chosen from the user .
Order* UI::getPayedOrder(vector<Order*>& payedOrders)
{
	vector<Order*>::iterator begin = payedOrders.begin();
	vector<Order*>::iterator end = payedOrders.end();

	int screen_index;
	cout << "choose a paid order :" << endl;
	int i = 1;

	for (;begin != end;++begin)
	{
		cout << i << ". order's id : " << (*begin)->getId() << endl;
		i++;
	}

	General::getIndexNumber(screen_index, General::c_minimal_index, (int)payedOrders.size());
	return payedOrders[screen_index - 1];
}

//returns a non feedbacked product that has been chosen from the user .
Product* UI::getNonFeedbackedProduct(vector<Product*>& nonFeedbackedProducts, int& screen_index)
{
	vector<Product*>::iterator begin = nonFeedbackedProducts.begin();
	vector<Product*>::iterator end = nonFeedbackedProducts.end();

	cout << "choose a paid product :" << endl;
	int i = 1;
	for (;begin != end;++begin)
	{
		cout
			<< i << "."
			<< "product's id : " << (*begin)->getId() << " , "
			<< "product's name : " << (*begin)->getName() << " , "
			<< "product's seller name : " << (*begin)->getSeller()->getUsername()
			<< endl;
		i++;
	}
	General::getIndexNumber(screen_index, General::c_minimal_index, (int)nonFeedbackedProducts.size());
	return nonFeedbackedProducts[screen_index - 1];
}

//returns a non feedbacked products array .
void UI::makeNonFeedbackedProductsArray(Order* order, vector <Product*>& nonFeedbackedProducts, vector <int>& bools)
{
	for (int i = 0;i < order->getNumOfProducts();i++)
	{
		if (order->isProductFeedback(i) == false)
		{
			nonFeedbackedProducts.push_back(order->getProductInIndex(i));
			bools.push_back(i);
		}
	}
}

// creates and returns an order cart
vector<Product*> UI::createOrderCart(Buyer*& buyer, int& cartSize, int& size) 
{
	int counter, index = 1, displayCartLogicalSize = 0, orderCartLogicalSize = 0;
	vector<Product*> orderCart;
	vector<Product*> displayCart;
	vector<int> displayIndexInBuyer;
	vector<bool> isInDisplay;
	// copy
	for (int i = 0; i < cartSize; i++)
	{
		if (buyer->isProductInOrder(i) == false)
		{
			displayCart.push_back(buyer->getProductInIndex(i));
			displayIndexInBuyer.push_back(i);

			isInDisplay.push_back(true);
			displayCartLogicalSize++; // this actual display end
		}

	}

	counter = displayCartLogicalSize;
	// display
	cout << "choose from the following menu the products to add to the order: \n" << "note - you can exit at anything by pressing 0.\n";
	while (counter && index)
	{

		vector<Product*>::iterator begin = displayCart.begin();
		vector<Product*>::iterator end = displayCart.end();

		for (int i = 0; begin != end; ++begin)
		{
			if ((*begin) != nullptr)
				cout << i + 1 << ") " << (*begin)->getName() << endl;
			i++;
		}

		General::getIndexNumber(index, General::c_minimal_index - 1, displayCartLogicalSize);
		if (index == 0)
			break;
		while (index && !isInDisplay[index-1])
		{
			cout << "invalid input, try again." << endl;
			General::getIndexNumber(index, General::c_minimal_index - 1, displayCartLogicalSize);
		}
		if (index)
		{
			cout << "added to order!\n";
			orderCart.push_back(displayCart[index - 1]); // move product into order cart
			displayCart[index - 1] = nullptr; // remove from display cart
			isInDisplay[index-1] = false;
			buyer->setProductInOrder(displayIndexInBuyer[index - 1]); // mark product as in order

			orderCartLogicalSize++;
			counter--;
		}
		else
		{
			break;
		}
	}
	size = orderCartLogicalSize;
	return orderCart;
}

//prints all orders by a certain array.
void UI::printOrdersArray(vector<Order*>& orders, int size)
{
	vector<Order*>::const_iterator begin = orders.begin();
	vector<Order*>::const_iterator end = orders.end();
	int i = 0;
	for (; begin != end; ++begin)
	{
		cout << "order number " << i + 1 << " details:\n" << "number of products: " << (*begin)->getNumOfProducts()
			<< "\n" << "product details: \n";
		for (int j = 0; j < (*begin)->getNumOfProducts(); j++)
		{
			cout << j + 1 << ") " << (*begin)->getProductInIndex(j)->getName() << endl;
		}
		cout << "total sum: " << (*begin)->getSum() << endl;
		i++;
	}
}

// creates a temporary cart to display cart items that can be added to an order
vector<Order*> UI::createDisplayOrder(Buyer*& buyer, vector<Order*>& orderList, int numOfOrders, int* count)
{
	vector<Order*>::const_iterator begin = orderList.begin();
	vector<Order*>::const_iterator end = orderList.end();
	vector<Order*> tempOrder;
	int i = 0;
	for (; begin!=end ; ++begin)
	{
		if ((*begin)->getBuyer() == buyer && ((*begin)->orderStatus() == false)) // open order for this buyer
		{
			tempOrder.push_back((*begin));
			(*count)++;
		}
		i++;
	}

	return tempOrder;
}