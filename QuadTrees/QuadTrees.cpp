// QuadTrees.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"
#include <iostream>
#include "Circunference.h"
#include "Quad.h"
#define N 100

using namespace std;
int main()
{
	Circunference c = Circunference(pair<int, int>(6000, 6000), 1, 1);
	Quad q = Quad(1, 5000, 5000);
	int index = q.getQuadrant(c);

	cout << "La circunferencia pertenece al cuadrante " << index << "." << endl;

    return 0;
}

