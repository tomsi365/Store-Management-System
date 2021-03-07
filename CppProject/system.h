#ifndef __SYSTEM_H
#define __SYSTEM_H

#include "general.h"
#include "array.h"
#include <iostream>
#include <vector>
using namespace std;

class System
{
private:
	const string m_systemName;
	vector<Order*> m_orderList;

	int m_buyerCount;
	int m_sellerCount;
	
	//private functions
	//step 1 :
	void addOrderToArray(Order* order);
	void addBuyer();
	void addSeller();
	void deleteAllOrders();
	void addProductToSeller();
	void addProductToCart();
	void makeOrder();
	void makePayment();
	void printAllBuyers()						const;
	void printAllSellers()						const;
	void printSellersByUsernameField()			const;
	void printBuyersByUsernameField()			const; 
	void printAllProductsFilteredByName()		const;
	void printMenu()							const;
	bool getSellerFromScreen(Seller*& seller)	const;
	bool getBuyerFromScreen(Buyer*& buyer)		const;
	void addFeedback();

	//step 2 :
	int m_buyerSellerCount;
	int m_userCount;
	User* getUser(int index, UserType  e_type) const;
	void deleteAllUsers();
	Seller** createSellerArrayCopy();
	void addBuyerSeller();
	void printAllBuyersSellers() const;
	void printAllUsersByType() const;
	void testOperators();
	void operatorAddBuyerTest();
	void operatorAddSellerTest();
	const System& operator+=(Buyer& buyer);
	const System& operator+=(Seller& seller);
	static void compareBuyers();
	void coutTester();

	//step3
	Array<User*> m_users;
	void saveData(const string& fileName);
	void loadData(const string& fileName);

public:
	//step 1 
	System(const string& name, const string& fileName);
	~System();
	System(const System&) = delete;
	const System& operator=(const System& other) = delete;
	void startMenu();
	bool isUsernameExist(const string& str) const;

	//step 2 : 
	friend std::ostream& operator<<(std::ostream& out, const System& system_info);

};

#endif