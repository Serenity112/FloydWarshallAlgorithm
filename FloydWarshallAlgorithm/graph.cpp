using namespace std;
#include <string>
#include "graph.h"
#include <limits.h>

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

void FloydWarshall(Graph& graph)
{
    int size = graph.size;
    double** matrix = graph.matrix;

    for (int k = 0; k < size; k++)
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                if (matrix[i][j] > (matrix[i][k] + matrix[k][j])
                    && (matrix[k][j] != inf
                    && matrix[i][k] != inf))
                {
                    matrix[i][j] = matrix[i][k] + matrix[k][j];
                }
            }
        }
    }
}