#ifndef __ADDRESS_H
#define __ADDRESS_H
using namespace std;

class Address 
{
private :
	string m_country;
	string m_city;
	string m_street;
	int m_streetNumber;
	
public :
	Address(const string& country, const string& city, const string& street, int street_number);
	~Address();

	friend std::ostream& operator<<(std::ostream& out, const Address& address);

};

#endif 
