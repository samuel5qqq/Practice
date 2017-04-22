// HW5_A1014114.cpp : 定義主控台應用程式的進入點。
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

string temp;
char a[26];
int number[26];

struct node {
	char word;
	int frequency;
	int use;
	string code;
	struct node* Rptr;
	struct node* Lptr;
};
int getnumber() {
	int b;
	ifstream input;
	input.open("p5.in.txt");
	for (int i = 0; i < 25; i++) {
		input >> a[i];
		input >> number[i];
		for (int j = 0; j != i; j++) {
			if (a[i] == a[j]) {
				b = i;
				i = 25;
				break;
			}
		}
	}

	return b;
}
struct node** TreeList = new node *[getnumber()*2 - 1];

void build(int capacity,char order[]) {
	ifstream input;
	input.open("p5.in.txt");
	for (int i = 0; i < 2 * capacity-1; i++) {
		TreeList[i] = new node;
	}
	for (int i = capacity-1; i >= 0; i--) {                  /*Construct TreeList*/
		input >> TreeList[i]->word;
		input >> TreeList[i]->frequency;
		TreeList[i]->use = 0;
		TreeList[i]->Lptr = NULL;
		TreeList[i]->Rptr = NULL;
	}
	for (int i = 0; i < capacity; i++) {
		input >> order[i];
	}
	input.close();

}

void huff(int capacity) {
	int min = -1, s_min= -1;
	int min_f = 99, s_min_f = 100;
	int boundary = capacity;
	for (int i = capacity; i < 2 * capacity-1; i++) {
		for (int j = 0; j < boundary ; j++) {                  /*Find the minimun number*/
			if (TreeList[j]->use == 0)
				if (min_f > TreeList[j]->frequency) {
					min = j;
					min_f = TreeList[j]->frequency;
				}
		}
		TreeList[min]->use = 1;
		for (int j = 0; j < boundary; j++) {                    /*Find the second minimun number*/
			if (TreeList[j]->use == 0)
				if (s_min_f > TreeList[j]->frequency) {
					s_min = j;
					s_min_f = TreeList[j]->frequency;
				}
		}
		TreeList[s_min]->use = 1;

		if ((min < capacity) && (s_min >= capacity))
			swap(min, s_min);

		TreeList[i]->frequency = TreeList[s_min]->frequency + TreeList[min]->frequency;  /*Get parent node*/
		TreeList[i]->Rptr = TreeList[min];
		TreeList[i]->Lptr = TreeList[s_min];
		TreeList[i]->use = 0;
		min = 0; s_min = 0;
		min_f = 99; s_min_f = 100;
		boundary++;
	}
}

void getcode(struct node* root, char c, string code) {                 /*Use recursive to traverse Huffman Tree*/
	if (root != NULL) {
		if (root->Lptr != NULL) {
			getcode(root->Lptr, c, code+"0");
		}
		if (root->Rptr != NULL) {
			getcode(root->Rptr, c, code+"1");
		}
		if ((root->Lptr == NULL) && (root->Rptr == NULL) && (root->word == c)) {
			temp = code;
		}
	}
}

void swap(int &a, int &b) {
	int temp;
	temp = a;
	a = b;
	b = temp;
}
int main(){
	int capacity=0;
	ofstream output;
	output.open("p5.out.txt");
	capacity = getnumber();
	char *order;
	order = new char[capacity];
	build(capacity,order);
	huff(capacity);
	string encode;
	for (int i = capacity-1; i >= 0; i--) {                           /*Assign Huffman code to correspond node*/
		getcode(TreeList[2 * capacity - 2], TreeList[i]->word, encode);
		TreeList[i]->code = temp;
		output << TreeList[i]->word << " " << TreeList[i]->code << endl;
	}
	output << endl;
	for (int i = 0; i < capacity; i++) {
		for (int j = 0; j < capacity; j++) {
			if (order[i] == TreeList[j]->word) {
				output << TreeList[j]->code;
			}
		}
	}
	system("pause");
	return 0;
}

