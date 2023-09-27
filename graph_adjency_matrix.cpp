//
//  main.cpp
//  3.10_graph_adjacency_matrix
//
//  Created by Sophia Mikhaylova on 03.06.2023.
//


#include <iostream>
using namespace std;

int get_edges_count(int (*matrix)[8], int n)
{
    int count = 0;
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (matrix[i][j] == 0)
            {
                count++;
            }
        }
    }
    
    return count;
}

int main()
{
    int adjacency_matrix[8][8] = {{0, 1, 1, 0, 1, 0, 0, 0},
                                    {1, 0, 0, 0, 1, 0, 0, 0},
                                    {1, 0, 0, 1, 0, 0, 1, 0},
                                    {0, 0, 1, 0, 0, 0, 0, 0},
                                    {1, 1, 0, 0, 0, 1, 1, 0},
                                    {0, 0, 0, 0, 1, 0, 0, 0},
                                    {0, 0, 1, 0, 1, 0, 0, 0},
                                    {0, 0, 0, 0, 0, 0, 0, 0}};
    int n = 8;

    int complement_edge_count = get_edges_count(adjacency_matrix, n);
    cout << "Edges: " << complement_edge_count << endl;

    return 0;
}






/*
 int main()
 {
 int matrix[10][10] =
 {{0, 1, 1, 0, 1, 0, 0, 0},
 {1, 0, 0, 0, 1, 0, 0, 0},
 {1, 0, 0, 1, 0, 0, 1, 0},
 {0, 0, 1, 0, 0, 0, 0, 0},
 {1, 1, 0, 0, 0, 1, 1, 0},
 {0, 0, 0, 0, 1, 0, 0, 0},
 {0, 0, 1, 0, 1, 0, 0, 0},
 {0, 0, 0, 0, 0, 0, 0, 0}};
 
 return 0;
 
 {{0, 1, 1, 0},
                             {1, 0, 1, 1},
                             {1, 1, 0, 1},
                             {0, 1, 1, 0}};
 }
 */
