#ifndef TICKETSPARSER_H
#define TICKETSPARSER_H

#include "list.h"
#include "airticket.h"
#include "pair.h"

List<AirTicket> getTicketsList(string);

Pair<List<string>, double> findOptimalSolution(List<AirTicket>&, string, string);

#endif