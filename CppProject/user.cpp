#pragma warning(disable: 4996)

#include <iostream>
#include <string>
#include "user.h"
using namespace std;

// main user constuctor 
User::User(const string& username, const string& password, const string& country, const string& city, const string& street, int street_number):
	m_username(username) , m_password(password) , m_address(Address(country, city, street, street_number)){}

// destructor 
User::~User() 
{
}

//prints user's full data .
void User::print() const 
{
	cout << "User's details :\n"
		<< "username : " << this->m_username << " .\n"
		<< "password : " << this->m_password << " .\n";
	cout << m_address << endl;
	cout << endl;
}

//returns User's username
const string& User::getUsername() const
{
	return m_username;
}

ostream& operator<<(ostream& os, const User& user)
{
	os << user.m_username << " " << user.m_password << " " << user.m_address;

	return os;
}