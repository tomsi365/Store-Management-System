#pragma warning(disable: 4996)

#include <iostream>
#include <fstream>
#include <string>
#include "address.h"
using namespace std;

// constructor
Address::Address(const string& country, const string& city, const string& street, int street_number) :
	m_country(country) , m_city(city) , m_street(street) , m_streetNumber(street_number) {}

// destructor
Address::~Address() 
{
}

// overloaded ostream, prints address
std::ostream& operator<<(std::ostream& out, const Address& address)
{
	if (typeid(out) == typeid(ofstream))
	{
		out << address.m_country << " " << address.m_city << " " << address.m_street << " " << address.m_streetNumber;
	}
	else
	{
	out << "Address:\n"
		<< "country: " << address.m_country << "\n"
		<< "city: " << address.m_city << "\n"
		<< "street: " << address.m_street << "\n"
		<< "street number: " << address.m_streetNumber  << endl;
	}
	return out;
}