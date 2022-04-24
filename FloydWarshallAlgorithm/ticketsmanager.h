#ifndef TICKETSPARSER_H
#define TICKETSPARSER_H

#include "list.h"
#include "airticket.h"

List<AirTicket> getTicketsList(string);

double buildOptimalWay(List<AirTicket>&, string, string);

#endif