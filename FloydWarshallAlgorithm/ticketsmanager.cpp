#include "ticketsmanager.h"
#include "graph.h"
#include "airticket.h"

#include <iostream>
#include <fstream>
#include <string>

Map<string, int> giveCitiesUniqueNumbers(List<AirTicket>& ticketsList)
{
	Map<string, int>* cityNumerics = new Map<string, int>();

	auto itr = ticketsList.create_iterator();
	int cityCount = 0;
	while (itr->has_next())
	{
		AirTicket ticket = itr->next();

		try
		{
			cityNumerics->Insert(ticket.departure, cityCount);
			cityCount++;	
		}
		catch (const std::exception&){}

		try
		{
			cityNumerics->Insert(ticket.arrival, cityCount);
			cityCount++;
		}
		catch (const std::exception&){}
	}
	delete itr;

	return *cityNumerics;
}

List<string> tokenize(string line, string separator = " ")
{
	int start = 0;
	int end = line.find(separator);
	List<string>* splittedLines = new List<string>;

	while (end != -1)
	{
		splittedLines->push_back(line.substr(start, end - start));
		start = end + separator.size();
		end = line.find(separator, start);
	}

	splittedLines->push_back(line.substr(start, end - start));

	return *splittedLines;
}

List<AirTicket> getTicketsList(string filename)
{
	List<AirTicket>* ticketsList = new List<AirTicket>();

	ifstream finput;
	finput.open(filename);

	string line;
	while (getline(finput, line))
	{
		List<string> newTicket = tokenize(line, ";");

		auto newTicket_itr = newTicket.create_iterator();
		string token1 = newTicket_itr->next();
		string token2 = newTicket_itr->next();
		string token3 = newTicket_itr->next();
		string token4 = newTicket_itr->next();
		delete newTicket_itr;

		AirTicket ticket(token1, token2, token3, token4);
		ticketsList->push_back(ticket);
	}

	return *ticketsList;
}

Graph buildGraphByTickets(List<AirTicket>& ticketsList, Map<string, int>& cityNumerics)
{
	Graph* graph = new Graph(cityNumerics.size);
	
	auto ticket_itr = ticketsList.create_iterator();
	while (ticket_itr->has_next())
	{
		AirTicket ticket = ticket_itr->next();

		string city1 = ticket.departure;
		string city2 = ticket.arrival;

		cout << "Search: " << city1 << " " << city2 << endl;

		int numCity1 = cityNumerics.Find(city1);
		int numCity2 = cityNumerics.Find(city2);

		cout << "Found: " << numCity1 << " " << numCity2 << endl;

		if (ticket.price1 == "N/A")
			graph->matrix[numCity1][numCity2] = inf;
		else
			graph->matrix[numCity1][numCity2] = stod(ticket.price1);

		if (ticket.price2 == "N/A")
			graph->matrix[numCity2][numCity1] = inf;
		else
			graph->matrix[numCity2][numCity1] = stod(ticket.price2);
	}
	delete ticket_itr;

	return *graph;
}

double buildOptimalWay(List<AirTicket>& ticketsList, string city1, string city2)
{
	Map<string, int> cityNumerics = giveCitiesUniqueNumbers(ticketsList);

	auto itr = cityNumerics.create_iterator();
	while(itr->has_next())
	{
		Pair<string, int> pair = itr->next();
		cout << pair.first << " " << pair.second << endl;
	}


	Graph graph = buildGraphByTickets(ticketsList, cityNumerics);

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			cout << graph.matrix[i][j] << " ";
		cout << endl;
	}

	FloydWarshall(graph);


	int numCity1 = cityNumerics.Find(city1);
	int numCity2 = cityNumerics.Find(city2);

	if (graph.matrix[numCity1][numCity2] == inf)
		throw invalid_argument("No way");

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			cout << graph.matrix[i][j] << " ";
		cout << endl;
	}

	return graph.matrix[numCity1][numCity2];


}