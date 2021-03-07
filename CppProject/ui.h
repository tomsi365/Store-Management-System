#ifndef __UI_H
#define __UI_H

#include "general.h"
#include "system.h"
#include <iostream>
class UI 
{
private :
	static Order* getPayedOrder(vector<Order*>& payedOrders);
	static void makePayedOrdersArray(vector<Order*>& ordersList,vector<Order*>& payedOrders);
	static Product* getNonFeedbackedProduct( vector<Product*>& nonFeedbackedProducts, int& screen_index);
	static void makeNonFeedbackedProductsArray(Order* order, vector <Product*>& nonFeedbackedProducts, vector <int>& bools);
	UI(){}
public :
	static Product* createProduct(Seller& seller);
	static Feedback* createFeedback(vector<Order*>& orders);
	static void printOrdersArray(vector<Order*>& orders, int size);
	static vector<Order*> createDisplayOrder(Buyer*& buyer, vector<Order*>& orderList, int numOfOrders, int* count);
	static vector<Product*> createOrderCart(Buyer*& buyer, int& cartSize, int& size);
	template<class T>
	static T* createUser(System& system, T* user);
};

//static function , handles input and creation of the buyer object .
template<class T>
T* UI::createUser(System& system, T* user)
{
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	string userName, password, country, street, city;

	cout << "enter a username:" << endl;
	getline(cin, userName);
	while (system.isUsernameExist(userName))
	{
		cout << "the username already exists , try again !" << endl;
		getline(cin, userName);
	}

	cout << "enter a password: " << endl;
	getline(cin, password);

	cout << "enter a country: " << endl;
	getline(cin, country);
	while (General::isOnlyWords(country.c_str()) == false)
	{
		cout << "invalid country, try again!" << endl;
		getline(cin, country);
	}

	cout << "enter a city: " << endl;
	getline(cin, city);
	while (General::isOnlyWords(city.c_str()) == false)
	{
		cout << "invalid city, try again!" << endl;
		getline(cin, city);
	}

	cout << "enter a street: " << endl;
	getline(cin, street);
	while (General::isOnlyWords(street.c_str()) == false)
	{
		cout << "invalid street, try again!" << endl;
		getline(cin, street);
	}

	cout << "enter street number: " << endl;
	int streetNum;
	cin >> streetNum;
	while (streetNum <= 0)
	{
		cout << "invalid street number, try again!" << endl;
		cin >> streetNum;
	}

	user = new T(userName, password, country, city, street, streetNum);
	return user;
}

#endif