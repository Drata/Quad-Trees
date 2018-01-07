#pragma once
#include "Circunference.h"
#include <list>

using namespace std;

class Quad
{
private:
	const int MAX_OBJECTS = 5;
	Quad * _q1;
	Quad * _q2;
	Quad * _q3;
	Quad * _q4;
	int _horizontal;
	int _vertical;
	int _level;
	list<Circunference> _objects;

public:
	Quad(int level, int horizontal, int vertical);
	~Quad();
	void clear();
	void split();
	int getQuadrant(Circunference c);
	int getQuadrant(pair<int, int> ray);
	void insert(Circunference c);
	void retrieve(list<Circunference> * returnObjects, pair<int, int> ray);
};

