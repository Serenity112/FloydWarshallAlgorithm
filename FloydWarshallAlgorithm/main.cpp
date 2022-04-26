#include <string>
#include <iostream>

#include "ticketsmanager.h"
#include "map.h"
#include "graph.h"

using namespace std;


int main()
{
	List<AirTicket> ticketsList = getTicketsList("tickets.txt");

	try
	{
		Pair<List<string>, double> optimalSolution = findOptimalSolution(ticketsList, "Omsk", "Florida");

		cout << "Optimal price: " << optimalSolution.second << endl;

		cout << "Optimal way: " << endl;
		auto itr = optimalSolution.first.create_iterator();
		while (itr->has_next())
		{
			cout << itr->next();
			if(itr->has_next())
				cout << " -> ";
		}
	}
	catch (const invalid_argument& exception)
	{
		cout << exception.what() << endl;
	}
}