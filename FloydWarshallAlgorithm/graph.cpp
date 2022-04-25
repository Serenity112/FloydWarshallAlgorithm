using namespace std;
#include <string>
#include "graph.h"
#include <limits.h>
#include <iostream>
#include <sstream>

#define inf DBL_MAX

Graph::Graph(int size)
{
	this->size = size;
	matrix = new double* [size];
	for (int i = 0; i < size; i++)
	{
		matrix[i] = new double[size];
		for (int j = 0; j < size; j++)
			matrix[i][j] = inf;
	}
}

void FloydWarshall(Graph& graph, Graph& pathGraph)
{
    int size = graph.size;
    double** matrix = graph.matrix;
    double** pathMatrix = pathGraph.matrix;

    for (auto i = 0; i < size; i++)
    {
        for (auto j = 0; j < size; j++)
        {
            if (i == j)
            {
                pathMatrix[i][j] = i;
            }
            else if(matrix[i][j] == inf)
            {
                pathMatrix[i][j] = inf;
            }
            else
            {
                pathMatrix[i][j] = j;
            }
        }
    }

    cout << "Path 1: " << endl;
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                cout << pathMatrix[i][j] << " ";
            }
            cout << endl;
        }
    }

    for (int k = 0; k < size; k++)
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                if (i == j)
                {
                    matrix[i][j] = i;
                } else
                if (matrix[i][j] > (matrix[i][k] + matrix[k][j]))
                {
                    matrix[i][j] = matrix[i][k] + matrix[k][j];
                    pathMatrix[i][j] = k;
                }
            }
        }
    }

    cout << "Path 2: " << endl;
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                cout << pathMatrix[i][j] << " ";
            }
            cout << endl;
        }
    }

}