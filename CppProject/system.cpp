#pragma warning(disable: 4996)

#include "system.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "buyer.h"
#include "seller.h"
#include "buyerSeller.h"
#include "general.h"
#include "product.h"
#include "order.h"
#include "feedback.h"
#include "array.h"
#include "ui.h"

using namespace std;

// Step 1 - functions : 

// main constructor
System::System(const string& name, const string& fileName)
	: m_systemName(name), m_users(Array<User*>(General::c_initial_array_size,'\n')),
	  m_buyerCount(0), m_sellerCount(0), m_buyerSellerCount(0)
{
	loadData(fileName);
	this->m_orderList.reserve(General::c_initial_array_size);
}

// destructor
System::~System()
{ 
	this->saveData("systemUserData.txt");
	deleteAllUsers();
	deleteAllOrders();
}

// prints the system menu
void System::printMenu() const
{
	cout << "Please choose an option from the menu:\n" << "1) add a buyer\n" << "2) add a seller\n"
		<< "3) add a product to a seller\n" << "4) give feedback to a seller\n" << "5) add a product to the buyer's cart\n"
		<< "6) make an order for the buyer\n" << "7) order payment for the buyer\n" << "8) view all buyer information\n"
		<< "9) view all seller information\n" << "10) view all product details (name specific)\n" << "11) add a buyer-seller\n" 
		<< "12) view all buyer-seller information\n" << "13) view all users by type\n" << "14) test operators\n" << "15) exit\n" << endl;
}

// system menu
void System::startMenu()
{
	cout << "system started" << endl;
	bool flag = true;
	int index;
	printMenu();

	while (flag)
	{
		General::getIndexNumber(index, General::c_minimal_index, General::c_maximal_index_menu);
			switch (index)
			{
			case(Add_Buyer):
				cout << "adding buyer" << endl;
				addBuyer();
				break;
			case(Add_Seller):
				cout << "adding seller" << endl;
				addSeller();
				break;
			case(Add_Product_toSeller):
				cout << "adding a product to seller" << endl;
				addProductToSeller();
				break;
			case(Add_Feedback):
				addFeedback();
				break;
			case(Add_Product_toCart):
				cout << "adding a product to cart" << endl;
				addProductToCart();
				break;
			case(Make_Order):
				makeOrder();
				break;
			case(Make_Payment):
				makePayment();
				break;
			case(View_All_Buyers):
				cout << "view all buyers" << endl;
				printAllBuyers();
				break;
			case(View_All_Sellers):
				cout << "view all seller" << endl;
				printAllSellers();
				break;
			case(View_All_Products):
				cout << "view all products by name" << endl;
				printAllProductsFilteredByName();
				break;
			case(Add_BuyerSeller):
				cout << "add buyer-seller" << endl;
				addBuyerSeller();
				break;
			case(View_All_BuyerSellers):
				cout << "view all buyer-sellers" << endl;
				printAllBuyersSellers();
				break;
			case(View_All_ByType):
				cout << "view all users by type" << endl;
				printAllUsersByType(); 
				break;
			case(Test_Operators):
				cout << "check operators" << endl;
				testOperators();
				break;
			case(Exit):
				flag = false;
				break;
			}
			if(flag)
				cout << "\nPlease choose another option from the menu or press 15 to exit.\n";
	}
	cout << "system exit" << endl;
}

//function no1
void System::addBuyer()
{
	Buyer* buyer = nullptr;
	buyer = UI::createUser(*this, buyer);
	m_users += buyer;
	this->m_buyerCount++;
	this->m_userCount++;
}

//function no2
void System::addSeller()
{
	Seller* seller = nullptr;
	seller = UI::createUser(*this, seller);
	m_users += seller;
	this->m_sellerCount++;
	this->m_userCount++;
}

//function no3
void System::addProductToSeller()
{
	Seller* seller = nullptr;
	if (!getSellerFromScreen(seller)) // failed to choose seller
		return;
	Product* p = UI::createProduct(*seller);
	seller->addProduct(p);
}

//function no4
void System::addFeedback()
{
	Feedback* feedback = UI::createFeedback(m_orderList); 
	if (feedback != nullptr)
	{
	feedback->getSeller()->addFeedback(feedback);
	}
}

// function no5 
void System::addProductToCart()
{
	int index;
	Buyer* buyer = nullptr;
	Seller* seller = nullptr;
	if (!getBuyerFromScreen(buyer) || !getSellerFromScreen(seller))
		return;
	cout << "please choose a product from the list :" << endl;
	if (!seller->printProdcutsByName()) // no products
	{
		cout << "this seller has no products, returning to menu.\n";
		return;
	}
	General::getIndexNumber(index, General::c_minimal_index, seller->getStockSize());
	buyer->addProductToCart(seller->getProductInIndex(index - 1));
}

// function no6
void System::makeOrder()
{
	int cartSize, orderCartSize = 0;
	Buyer* buyer = nullptr;
	if (!getBuyerFromScreen(buyer))
	{
		cout << "there are no buyers, returning to menu.\n";
		return;
	}
	cartSize = buyer->getCartSize();
	if (!cartSize)
	{
		cout << "there are no products in the cart, returning to menu.\n";
		return;
	}
	vector<Product*> orderCart = UI::createOrderCart(buyer, cartSize, orderCartSize);
	if (!orderCartSize)
	{
		cout << "no products were chosen, returning to menu.\n";
		return;
	}
	Order* order = new Order(*buyer, orderCartSize, orderCart);
	buyer->addOrder(); // buyer has active order now
	this->addOrderToArray(order); 	// add order to system order array
	cout << "order made! returning to menu." << endl;
}

//function no7
void System::makePayment()
{
	int numOfOrders, count = 0, index;
	Buyer* buyer = nullptr;
	if (!getBuyerFromScreen(buyer))
	{
		cout << "there are no buyers, returning to menu.\n";
		return;
	}
	if (!(buyer->getOrderNum())) // no orders
	{
		cout << "there are no open orders for this buyer, returning to menu.\n";
		return;
	}
	numOfOrders = buyer->getOrderNum();
	vector<Order*> displayOrder = UI::createDisplayOrder(buyer, this->m_orderList, numOfOrders, &count);

	// display 
	cout << "the chosen buyer has " << numOfOrders << " open orders:\n";
	UI::printOrdersArray(displayOrder, count);
	cout << "please choose the order from the list to make the payment.\n" << endl;
	General::getIndexNumber(index, General::c_minimal_index, numOfOrders);

	// mark order as paid
	displayOrder[index - 1]->orderPaid();
	buyer->removeOrder(); // delete here items from cart
	vector<Product*> tempProd = displayOrder[index - 1]->returnCart();
	buyer->removeFromCart(tempProd); // remove items from buyers cart
	cout << "order paid! returning to menu." << endl;
}

//function no8
void System::printAllBuyers() const
{
	if (this->m_buyerCount == 0)
	{
		cout << "there are no buyers" << endl;
	}
	else
	{
		for (int i = 0; i < m_buyerCount; i++)
		{
			getUser(i, UserType::BUYER)->print();
		}
	}

}

//function no9
void System::printAllSellers() const
{
	if (this->m_sellerCount == 0)
	{
		cout << "there are no sellers" << endl;
	}
	else
	{
		for (int i = 0; i < m_sellerCount; i++)
		{
			getUser(i, UserType::SELLER)->print();
		}
	}
}

//function no10
void System::printAllProductsFilteredByName() const
{
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << "enter a product name (use only correct words/space/'-') ." << endl;
	string name;
	getline(cin, name);
	while (General::isOnlyWords(name.c_str()) == false)
	{
		cout << "invalid name ! try again ." << endl;
		getline(cin, name);
	}

	cout << "products filtered by name :" << endl;

	for (int i = 0;i < this->m_sellerCount;i++)
	{
		dynamic_cast<Seller*>(getUser(i, UserType::SELLER))->printProductsFilteredByName(name);
	}
}


// adding a order to orders array
void System::addOrderToArray(Order* order)
{
	this->m_orderList.push_back(order);
}

// free all allocations in order list
void System::deleteAllOrders()
{
	vector<Order*>::iterator begin = this->m_orderList.begin();
	vector<Order*>::iterator end = this->m_orderList.end();
	for (;begin!=end; ++begin)
	{
		delete (*begin);
	}
}

//prints all the sellers by username field only .
void System::printSellersByUsernameField() const 
{
	for (int i = 0;i < this->m_sellerCount;i++)
	{
		cout
			<< i+1 << " : " << getUser(i,UserType::SELLER)->getUsername() << " . " << endl;
	}
}

//prints all the buyers by username field only.
void System::printBuyersByUsernameField() const
{
	for (int i = 0;i < this->m_buyerCount;i++)
	{
		cout
			<< i + 1 << " : " << getUser(i, UserType::BUYER)->getUsername() << " . " << endl;
	}
}

//returns buyer that has been chosen.
bool System::getBuyerFromScreen(Buyer*& buyer) const
{
	int index;
	if (this->m_buyerCount == 0)
	{
		cout << "there are no avaliable buyers." << endl;
		return false;
	}
	cout << "please choose a buyer from the list :" << endl;
	printBuyersByUsernameField();
	General::getIndexNumber(index, General::c_minimal_index, this->m_buyerCount);
	buyer = dynamic_cast<Buyer*>(getUser(index-1, UserType::BUYER));
	return true;
}

//returns seller that has been chosen .
bool System::getSellerFromScreen(Seller*& seller) const
{
	int index;
	if (this->m_sellerCount == 0)
	{
		cout << "there are no avaliable sellers." << endl;
		return false;
	}
	cout << "please choose a seller from the list :" << endl;
	printSellersByUsernameField();
	General::getIndexNumber(index, General::c_minimal_index, this->m_sellerCount);
	seller = dynamic_cast<Seller*>(getUser(index - 1, UserType::SELLER));
	return true;
}

//prevents duplicate usernames .
bool System::isUsernameExist(const string& str) const
{
	for (int i = 0;i < this->m_buyerCount;i++)
	{
		if (str.compare(getUser(i, UserType::BUYER)->getUsername()) == 0)
		{
			return true;
		}
	}

	for (int j = 0;j < this->m_sellerCount;j++)
	{
		if (str.compare(getUser(j, UserType::SELLER)->getUsername()) == 0)
		{
			return true;
		}
	}

	return false;
}

// Step 2 - functions : 

//function no11
void System::addBuyerSeller()
{
	BuyerSeller* buyer_seller = nullptr;
	buyer_seller = UI::createUser(*this, buyer_seller);
	m_users += buyer_seller;
	this->m_userCount++;
	this->m_buyerCount++;
	this->m_sellerCount++;
	this->m_buyerSellerCount++;
}

//function no12
void System::printAllBuyersSellers() const
{
	if (this->m_buyerSellerCount == 0)
	{
		cout << "there are no buyers-sellers" << endl;
		return;
	}
	else
	{
		for (int i = 0; i < m_buyerSellerCount; i++)
		{
			getUser(i, UserType::BUYER_SELLER)->print();
		}
	}
}

//function no13
void System::printAllUsersByType() const
{
	int index = 0;
	cout << "choose a type: \n" << "1) buyer\n" << "2) seller\n" << "3) buyer-seller" << endl;
	General::getIndexNumber(index, General::c_minimal_index, 3);

	UserType e_type = (UserType)index;
	if (this->m_userCount == 0)
	{
		cout << "there are no users" << endl;
		return;
	}
	if (e_type == UserType::BUYER)
	{
		printAllBuyers();
	}
	else if (e_type == UserType::SELLER)
	{
		printAllSellers();
	}
	else if (e_type == UserType::BUYER_SELLER)
	{

		printAllBuyersSellers();
	}
}

//function no14
void System::testOperators()
{
	bool flag = true;
	int index = 0;
	cout << "choose an option: \n" << "1) add buyer operator += \n" << "1) add seller operator += \n"
		<< "3) compare two buyers > operator\n" << "4) cout operator <<\n" << "5) return to menu\n" << endl;
	while (flag)
	{
		General::getIndexNumber(index, General::c_minimal_index, General::c_maximal_operator_index);
		switch (index)
		{
		case(Add_Buyer_Test):
			operatorAddBuyerTest();
			break;
		case(Add_Seller_Test):
			operatorAddSellerTest();
			break;
		case(Compare_Test):
			compareBuyers();
			break;
		case(Cout_Test):
			coutTester();
			break;
		case(Exit_Test):
			flag = false;
			break;
		}
		if (flag)
			cout << "\nPlease choose another option from the operator test menu or press 5 to return to main menu.\n";
	}
}


// returns the correct user from general users array , by it's type and index .
User* System::getUser(int index, UserType e_type) const
{
	int counter = -1;
	for (int i = 0;i < (m_buyerCount + m_sellerCount - m_buyerSellerCount);i++) 
	{
		User* user = this->m_users.At(i);
		Buyer* buyer = dynamic_cast<Buyer*>(user);
		Seller* seller = dynamic_cast<Seller*>(user);
		BuyerSeller* buyerSeller = dynamic_cast<BuyerSeller*>(user);
		
		if (e_type == UserType::BUYER&&buyer != nullptr) 
		{
			counter++;
		}
		else 
		{
			if (e_type == UserType::SELLER&&seller != nullptr)
			{
				counter++;
			}
			else
			{
				if (e_type == UserType::BUYER_SELLER&&buyerSeller != nullptr)
				{
					counter++;
				}
			}
		}

		if (counter == index) 
		{
			return this->m_users.At(i);
		}
	}
	return nullptr;
}

// free all allocations in user list
void System::deleteAllUsers()
{
	for (int i = 0;i < (m_buyerCount + m_sellerCount - m_buyerSellerCount);i++)
	{
		delete this->m_users[i];
	}
	this->m_buyerCount = 0;
	this->m_sellerCount = 0;
	this->m_buyerSellerCount = 0;
}

// creates sellers array copy .
Seller** System::createSellerArrayCopy() 
{
	return nullptr;
}

// operator += adding buyer to system
const System& System::operator+=(Buyer& buyer)
{
	m_users += &buyer;
	this->m_buyerCount++;
	this->m_userCount++;

	return *this;
}

// operator += adding seller to system
const System& System::operator+=(Seller& seller)
{
	m_users += &seller;
	this->m_sellerCount++;
	this->m_userCount++;

	return *this;
}

// operator += add buyer test
void System::operatorAddBuyerTest()
{
	cout << "create a buyer first: " << endl;
	Buyer* buyer = nullptr;
	buyer = UI::createUser(*this, buyer);
	*this += *buyer;
	cout << "added buyer, you may now return to menu and view all buyers to view the added buyer.\n" << endl;
}

// operator += add seller test
void System::operatorAddSellerTest()
{
	cout << "create a seller first: " << endl;
	Seller* seller = nullptr;
	seller = UI::createUser(*this, seller);
	*this += *seller;
	cout << "added seller, you may now return to menu and view all sellers to view the added seller.\n" << endl;
}

// system info overloaded ostream
std::ostream& operator<<(std::ostream& out, const System& system_info)
{
	out << "System info:\n"
		<< "System Name: " << system_info.m_systemName
		<< "\nNumber of Users: " << system_info.m_userCount 
		<< "\nNumber of Buyers: " << system_info.m_buyerCount
		<< "\nNumber of Sellers: " << system_info.m_sellerCount
		<< "\nNumber of Buyer-Sellers: " << system_info.m_buyerSellerCount
		<< "\nNumber of Orders: " << system_info.m_orderList.size()
		<< endl;

	return out;
}

// compares two buyer carts using the overloaded > operator
void System::compareBuyers()
{
	cout << "the function will create two pre-defined buyers with products" << endl;

	Buyer buyer1("israeli1", "1234", "israel", "tel-aviv", "somewhere", 1);
	Buyer buyer2("israeli2", "1111", "israel", "tel-aviv", "somewhere", 2);
	Seller israeli3("israeli3", "0000", "israel", "tel-aviv", "somewhere", 3);
	Product a((Item)1, "kids chair", 20, israeli3);
	Product b((Item)3, "electric drier", 100, israeli3);
	Product c((Item)3, "electric killer chair", 220, israeli3);
	Product d((Item)2, "newspaper", 12, israeli3);
	Product e((Item)2, "table", 122, israeli3);

	buyer1.addProductToCart(&a);
	buyer1.addProductToCart(&a);
	buyer1.addProductToCart(&b);
	buyer2.addProductToCart(&c);

	cout << "buyer #1 has cart value of " << buyer1.getCartSum() << endl;
	cout << "buyer #2 has cart value of " << buyer2.getCartSum() << endl;

	if (buyer1 > buyer2)
		cout << "israeli1 cart is bigger" << endl;
	else
		cout << "israeli1 cart is smaller" << endl;


}

// cout test function
void System::coutTester()
{
	cout << "there are 3 overloads for cout\n" << "first one is system info print:\n" << endl;
	cout << *this << endl;
	Seller avi("Avi", "1234", "Israel", "TLV", "Ayalon", 10);
	Product product((Item)1, "kids chair", 20, avi);
	cout << "second one is product print:\n" << endl;
	cout << product << endl;
	cout << "third one is address print:\n" << endl;
	Address address("israel", "tel-aviv", "somewhere", 1);
	cout << address << endl;
}


// step 3 -> functions

// saves user data upon exiting the menu
void System::saveData(const string& fileName)
{
	cout << "saving user data" << endl;
	ofstream outFile(fileName.c_str(), ios::binary | ios::trunc);
	outFile << this->m_userCount << endl;
	for (int i = 0; i < this->m_userCount; i++)
	{
		outFile << typeid(*m_users[i]).name() + 6 << " " << *m_users[i] << endl;
	}
	outFile.close();
}

// loads user data when entering the menu
void System::loadData(const string& fileName)
{
	ifstream inputFile(fileName);
	inputFile >> this->m_userCount;
	string type, username, password, country, city, street;
	int streetNumber;
	for (int i = 0; i < this->m_userCount; i++)
	{
		inputFile >> type >> username >> password >> country >> city >> street >> streetNumber;
		if (type.compare(typeid(Buyer).name() + 6) == 0)
		{
			this->m_buyerCount++;
			Buyer* user = new Buyer(username, password, country, city, street, streetNumber);
			this->m_users += user;
		}
		else if (type.compare(typeid(Seller).name() + 6) == 0)
		{
			this->m_sellerCount++;
			Seller* user = new Seller(username, password, country, city, street, streetNumber);
			this->m_users += user;
		}
		else if (type.compare(typeid(BuyerSeller).name() + 6) == 0)
		{
			this->m_buyerSellerCount++;
			this->m_sellerCount++;
			this->m_buyerCount++;
			BuyerSeller* user = new BuyerSeller(username, password, country, city, street, streetNumber);
			this->m_users += user;
		}
	}

	inputFile.close();
}
