#ifndef __GENERAL_H
#define __GENERAL_H

//class prototypes
class Address;
class Buyer;
class Seller;
class Feedback;
class Product;
class User;
class Order;
class Date;
class System;
class BuyerSeller;

enum Item 
{
Children=1 ,
Office ,
Electricity ,
Clothes
};


enum UserType
{
	BUYER = 1,
	SELLER,
	BUYER_SELLER
};

enum Action
{
	Add_Buyer=1,
	Add_Seller,
	Add_Product_toSeller, 
	Add_Feedback,
	Add_Product_toCart,
	Make_Order,
	Make_Payment,
	View_All_Buyers,
	View_All_Sellers,
	View_All_Products,
	Add_BuyerSeller,
	View_All_BuyerSellers,
	View_All_ByType,
	Test_Operators,
	Exit
};

enum testOperator
{
	Add_Buyer_Test = 1,
	Add_Seller_Test,
	Compare_Test,
	Cout_Test,
	Exit_Test
};

class General 
{
public:
	static const int c_initial_array_size = 10;
	static const int c_minimal_index = 1;
	static const int c_maximal_index_menu = 15;
	static const int c_maximal_product_index = 4;
	static const int c_maximal_operator_index = 5;
	static bool isOnlyWords(const char* str);
	static void getIndexNumber(int& index, int min, int max);
};


#endif