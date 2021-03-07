#ifndef  __USER_H
#define __USER_H

#include <iostream>
#include "general.h"
#include "address.h"
using namespace std;

class User
{
protected :
	const string m_username;
	const string m_password;
	const Address m_address;
	User(const string& username, const string& password, const string& country, const string& city, const string& street, int street_number);
public :
	virtual ~User();
	User(const User& other) = delete;
	const User& operator=(const User& other) = delete;
	void print()			  const;
	const string& getUsername() const;

	friend ostream& operator<<(ostream& os, const User& user);
};



#endif 
