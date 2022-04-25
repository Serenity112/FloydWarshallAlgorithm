#include "pch.h"
#include "CppUnitTest.h"
#include <string>
#include <iostream>

#include "..\FloydWarshallAlgorithm\map.h"
#include "..\FloydWarshallAlgorithm\graph.h"
#include "..\FloydWarshallAlgorithm\ticketsmanager.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace FloydWarshallAlgorithmTest
{
	TEST_CLASS(FloydWarshallAlgorithmTest)
	{
	public:
		TEST_METHOD(TicketsList1)
		{
			List<AirTicket> ticketsList;
			ticketsList.push_back(AirTicket("Spb", "Kingisepp", "100", "N/A"));
			ticketsList.push_back(AirTicket("Spb", "Omsk", "1", "2"));
			ticketsList.push_back(AirTicket("Omsk", "Kirov", "90", "170"));
			ticketsList.push_back(AirTicket("Kirov", "Kingisepp", "7", "8"));
			ticketsList.push_back(AirTicket("Spb", "Kingisepp", "300", "400"));
			ticketsList.push_back(AirTicket("Florida", "Spb", "N/A", "16"));
			ticketsList.push_back(AirTicket("Florida", "Kirov", "1", "1"));

			Pair<List<string>, double> optimalSolution = findOptimalSolution(ticketsList, "Spb", "Kingisepp");

			Assert::AreEqual(optimalSolution.second, 24.0);
		}

		TEST_METHOD(TicketsList2)
		{
			List<AirTicket> ticketsList;
			ticketsList.push_back(AirTicket("Spb", "Kingisepp", "100", "12"));
			ticketsList.push_back(AirTicket("Spb", "Omsk", "N/A", "2"));
			ticketsList.push_back(AirTicket("Omsk", "Kirov", "90", "11"));
			ticketsList.push_back(AirTicket("Kirov", "Kingisepp", "1", "8"));
			ticketsList.push_back(AirTicket("Spb", "Kingisepp", "300", "N/A"));
			ticketsList.push_back(AirTicket("Florida", "Spb", "N/A", "16"));
			ticketsList.push_back(AirTicket("Florida", "Kirov", "1", "N/A"));

			Pair<List<string>, double> optimalSolution = findOptimalSolution(ticketsList, "Florida", "Spb");

			Assert::AreEqual(optimalSolution.second, 14.0);
		}
	};
}
