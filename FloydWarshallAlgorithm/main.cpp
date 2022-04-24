#include <string>
#include <iostream>
#include <limits.h>

#include "ticketsmanager.h"
#include "map.h"
#include "graph.h"

#define inf DBL_MAX
using namespace std;


int main()
{
	AirTicket ticket;

	List<AirTicket> ticketsList = getTicketsList("tickets.txt");

	try
	{
		double optimalWay = buildOptimalWay(ticketsList, "Spb", "Kingisepp");

		cout << "Found optimal way: " << optimalWay;
	}
	catch (const invalid_argument& exception)
	{
		cout << exception.what() << endl;
	}
}