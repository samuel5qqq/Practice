// shorted path.cpp : 定義主控台應用程式的進入點。
//

#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <limits>
#include <vector>
#include<iostream>
#include <list>
#include<fstream>

using namespace std;
int counter = 0;
int cost[26][26];

class Graph
{
	int V;
	list<int> *adj;

	void FindAllPath(int, int, bool[], int[], int &);

public:
	Graph(int V);
	void addEdge(int s, int d);
	void Path(int s, int d);
};


Graph::Graph(int V)
{
	this->V = V;
	adj = new list<int>[V];
}
/*將adjacency_matrix的edge放入adj中*/
void Graph::addEdge(int s, int d)
{
	adj[s].push_back(d);
}


void Graph::Path(int s, int d)
{
	bool *visited = new bool[V];

	int *path = new int[V];
	int path_index = 0;

	for (int i = 0; i < V; i++)
		visited[i] = false;

	FindAllPath(s, d, visited, path, path_index);
}

/*使用DFS找尋所有路徑
如果起始=終點及找到路徑
沒有的話繼續DFS直到找到為止*/

void Graph::FindAllPath(int s, int d, bool visited[],
	int path[], int &path_index)
{

	visited[s] = true;
	path[path_index] = s;
	path_index++;

	if (s == d)
	{
		for (int i = 0; i < path_index; i++) {
			cost[counter][i] = path[i];
		}
		counter++;

	}
	else
	{
		list<int>::iterator i;
		for (i = adj[s].begin(); i != adj[s].end(); ++i)
			if (!visited[*i]) {
				FindAllPath(*i, d, visited, path, path_index);
			}
	}

	path_index--;
	visited[s] = false;
}

int main()
{
	int temp, length = 0, tempcount = 0;
	char start, end;
	int sum = 0, k, k1;
	int count1 = 0;
	int nodelength[26] = { 0 };
	int min[26] = { 0 };
	int minimum = 100;
	int startnode, endnode;
	int **adjacency_matrix = new int*[length];
	ifstream input;
	ofstream output;

	input.open("DS4.txt");
	output.open("Ans4.txt");
	while (input >> temp) {
		tempcount++;
	}
	input.close();
	input.open("DS4.txt");


	for (int i = 1;i <= 26;i++) {
		if (i*i == tempcount) {
			length = i;
		}
	}

	for (int i = 0;i < length;i++) {
		adjacency_matrix[i] = new int[length];
	}
	/*將INPUT放入adjacency_matrix*/
	for (int i = 0;i < length;i++) {
		for (int j = 0;j < length;j++) {
			input >> adjacency_matrix[i][j];
		}
	}
	input >> start >> end;
	/*起始,終點*/
	for (int i = 65;i < 90;i++) {
		if ((int)start == i)
			startnode = i - 65;
		if ((int)end == i)
			endnode = i - 65;
	}

	Graph g(length);
	for (int i = 0;i<length;i++)
		for (int j = 0;j<length;j++) {
			if (adjacency_matrix[i][j] != 0)
				g.addEdge(i, j);
		}

	for (int i = 0; i < 26; i++) {
		for (int j = 0; j < 26;j++)
			cost[i][j] = -1;
	}

	g.Path(startnode, endnode);
	/*計算每條可能路徑之cost*/
	for (int i = 0; i < counter; i++) {
		sum = 0;
		for (int j = 0;cost[i][j] != -1;j++) {
			k = cost[i][j]; k1 = cost[i][j + 1];
			if (cost[i][j + 1] != -1)
				sum += adjacency_matrix[k][k1];
		}
		nodelength[i] = sum;
	}

	/*比較每種cost找出最小的
	即為最短路徑*/
	for (int i = 0; i < counter;i++)
		if (nodelength[i] < minimum)
			minimum = nodelength[i];

	/*檢查是否有多條最短路徑*/
	for (int i = 0; i < counter;i++) {
		if (nodelength[i] = minimum) {
			min[count1] = i;
			count1++;
		}
	}
	output << "起點: " << (char)(startnode + 65) << "終點: " << (char)(endnode + 65) << endl;
	output << counter << endl;
	output << sum << endl;
	for (int i = 0; i < count1; i++) {
		for (int j = 0; cost[i][j] != -1; j++) {
			output << (char)(cost[i][j] + 65) << " ";
		}
		output << endl;
		}

	return 0;
}
