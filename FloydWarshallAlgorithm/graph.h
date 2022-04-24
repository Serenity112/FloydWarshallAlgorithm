#ifndef GRAPH_H
#define GRAPH_H

using namespace std;
#include <string>
#include "list.h"
#include "airticket.h"
#include "map.h"

struct Graph
{
	double** matrix;
	int size;

	Graph(int);
};

void FloydWarshall(Graph&);

#endif