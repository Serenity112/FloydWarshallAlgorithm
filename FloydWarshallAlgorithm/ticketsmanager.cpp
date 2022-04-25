#include "ticketsmanager.h"
#include "graph.h"
#include "airticket.h"

#include <limits.h>
#include <iostream>
#include <fstream>
#include <string>

#define inf DBL_MAX

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
	List<string>* splittedLines = new List<string>();

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
	
	for (int i = 0; i < graph->size; i++)
	{
		graph->matrix[i][i] = 0;
	}

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

List<string> findOptimalPath(Graph& pathGraph, Map<string, int>& cityNumerics, int i, int j)
{
	List<string>* optimalPath = new List<string>();

 	optimalPath->push_back(cityNumerics.FindKeysByData(i)->getHead());

	double** pathMatrix = pathGraph.matrix;

	int k = i;
	while (pathMatrix[k][j] != j)
	{
		string subCity = cityNumerics.FindKeysByData(pathMatrix[k][j])->getHead();
		optimalPath->push_back(subCity);
		k = pathMatrix[k][j];
	}

	optimalPath->push_back(cityNumerics.FindKeysByData(j)->getHead());
	return *optimalPath;
}

Pair<List<string>, double> findOptimalSolution(List<AirTicket>& ticketsList, string city1, string city2)
{
	Map<string, int> cityNumerics = giveCitiesUniqueNumbers(ticketsList);
	int size = cityNumerics.size;

	int numCity1 = cityNumerics.Find(city1);
	int numCity2 = cityNumerics.Find(city2);

	Graph graph = buildGraphByTickets(ticketsList, cityNumerics);

	Graph pathGraph(size);
	FloydWarshall(graph, pathGraph);

	Pair<List<string>, double> optimalSoulution;


	double optimalWay = graph.matrix[numCity1][numCity2];
	if (optimalWay == inf)
		throw invalid_argument("No way");

	optimalSoulution.second = optimalWay;

	List<string> optimalPath = findOptimalPath(pathGraph, cityNumerics, numCity1, numCity2);
	optimalSoulution.first = optimalPath;

	

	return optimalSoulution;
}