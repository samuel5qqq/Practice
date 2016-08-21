// p3.cpp : 定義主控台應用程式的進入點。
//

#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <stack>
using std::ifstream;
using std::ofstream;
using namespace std;

const int m = 11;
const int p = 15;
enum directions { N, NE, E, SE, S, SW, W, NW };
int maze[m+2][p+2];
int mark[m+2][p+2];
template<class Type> 
ostream & operator<<(ostream & os, stack<Type>& s) {
	os << "top=" << s.top << endl;
	for (int i = 0; i <= s.top; i++)
		os << i << ":" << s.stack[i] << endl;
	return os;
}
struct offsets
{
public:
	int a;
	int b;
};
offsets Move[8] = { { -1,0 },{ -1,1 },{ 0,1 },{ 1,1 },{ 1,0 },{ 1,-1 },{ 0,-1 },{ -1,-1 } };
struct Items
{
public:
	int x, y, dir;
	Items(int i, int j, int d) {
		x = i;
		y = j;
		dir = d;
	}

};
ostream&operator<<(ostream&os, Items&item) {
	return os << item.x << "," << item.y << "," << item.dir;
}
void print() {
	ofstream outputfile;
	outputfile.open("p3.out.txt");
	outputfile << "-----Given a 11x15 maze-----" << endl;
	outputfile << "Marking the positions using '*' for the path in the maze" << endl;
	for (int i = 0; i < 13; i++) {
		for (int j = 0; j < 17; j++) {
			if (i == 1 && j == 1)
				outputfile << 's' << " ";
			else if (maze[i][j] == 2)
				outputfile << '*' << " ";
			else if (i == 11 && j == 15)
				outputfile << 'd' << " ";
			else
				outputfile << maze[i][j] << " ";
		}
		outputfile << endl;
	}
	outputfile.close();
}
void path(const int m,const int p) {
	mark[1][1] = 1;
	stack<Items> stack;
	Items temp(1, 1, N);
	stack.push(temp);
	while (!stack.empty())
	{
		temp = stack.top();
		stack.pop();
		int i = temp.x;
		int j = temp.y;
		int d = temp.dir;
		while (d < 8) {
			int g = i + Move[d].a;
			int h = j + Move[d].b;
			if ((g == m) && (h == p)) {
				maze[i][j] = 2;
				print();
					return;
			}
			if ((!maze[g][h]) && (!mark[g][h])) {
				mark[g][h] = 1;
				temp.x = i;
				temp.y = j;
				temp.dir = d + 1;
				maze[temp.x][temp.y] = 2;
				stack.push(temp);
				i = g; j = h; d = N;
			}
			else
				d++;
		}
	}
};

int main()
{
	ifstream inputfile;

	inputfile.open("p3.in.txt");
	for (int i = 0; i < 13; i++)
		for (int j = 0; j < 17; j++)
			inputfile >> maze[i][j];
	path(m, p);

	inputfile.close();
	return 0;
}

