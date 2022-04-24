#ifndef AIRTICKET_H
#define AIRTICKET_H

using namespace std;

#include <string>
#include <limits.h>

#define inf DBL_MAX

struct AirTicket
{
public:
	string departure;
	string arrival;

	string price1;
	string price2;

	AirTicket(string departure, string arrival, string price1, string price2)
	{
		this->departure = departure;
		this->arrival = arrival;
		this->price1 = price1;
		this->price2 = price2;
	}

	AirTicket()
	{
		this->departure = "";
		this->arrival = "";
		this->price1 = "N/A";
		this->price2 = "N/A";
	}
};

#endif