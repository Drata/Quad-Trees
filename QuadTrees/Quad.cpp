#include "stdafx.h"
#include "Quad.h"


Quad::Quad(int level, int horizontal, int vertical) : _level(level), _horizontal(horizontal), _vertical(vertical), 
													  _q1(nullptr), _q2(nullptr), _q3(nullptr), _q4(nullptr) {}


Quad::~Quad()
{
}

/*
 * Clears the quadtree.
 */
void Quad::clear()
{
	_objects.clear();
	
	if (_q1 != nullptr) {
		_q1->clear();
	}
	
	if (_q2 != nullptr) {
		_q2->clear();
	}

	if (_q3 != nullptr) {
		_q3->clear();
	}

	if (_q4 != nullptr) {
		_q4->clear();
	}
}

/*
* Creates the child quadrants.
*/
void Quad::split()
{
	int subHorizontal = _horizontal / 2;
	int subVertical = _vertical / 2;
	
	_q1 = new Quad(_level++, subHorizontal, subVertical);
	_q2 = new Quad(_level++, subHorizontal, subVertical + _vertical);
	_q3 = new Quad(_level++, subHorizontal + _horizontal, subVertical);
	_q4 = new Quad(_level++, subHorizontal + _horizontal, subVertical + _vertical);
}

/*
* Gives you the index of the Quadrant of a given Circunference.
*/
int Quad::getQuadrant(Circunference c)
{
	int quadrant = -1;
	pair<int, int> center = c.getCenter();

	//Checks if it can fit entirely in Q1 or Q3.
	if (center.first + RADIUS < _vertical) {
		if (center.second + RADIUS < _horizontal) {
			quadrant = 1;
		}

		if (center.second - RADIUS > _horizontal) {
			quadrant = 3;
		}
	}

	//Checks if it can fit entirely in Q2 or Q4.
	if (center.first - RADIUS > _vertical) {
		if (center.second + RADIUS < _horizontal) {
			quadrant = 2;
		}

		if (center.second - RADIUS > _horizontal) {
			quadrant = 4;
		}
	}

	return quadrant;
}

/*
* Gives you the index of the Quadrant of a given ray.
*/
int Quad::getQuadrant(pair<int, int> ray)
{
	int quadrant = -1;

	//Checks if it can fit entirely in Q1 or Q3.
	if (ray.first < _vertical) {
		if (ray.second < _horizontal) {
			quadrant = 1;
		}

		if (ray.second > _horizontal) {
			quadrant = 3;
		}
	}

	//Checks if it can fit entirely in Q2 or Q4.
	if (ray.first > _vertical) {
		if (ray.second < _horizontal) {
			quadrant = 2;
		}

		if (ray.second > _horizontal) {
			quadrant = 4;
		}
	}

	return quadrant;
}

/*
 * Inserts a circunference in the correct node.
 */
void Quad::insert(Circunference c)
{

	list<Circunference> fatherObjects;

	//Checks if the node its a leaf or a branch.
	if (_q1 != nullptr) {
		int quadrant = getQuadrant(c);

		//Checks if it can fit entirely within a quadrant,
		// if so it inserts the circunference in said quadrant.
		if (quadrant != -1) {
			switch (quadrant) {
			case 1:
				_q1->insert(c);
				break;
			case 2:
				_q2->insert(c);
				break;
			case 3:
				_q3->insert(c);
				break;
			case 4:
				_q4->insert(c);
				break;
			}

			return;
		}
	}

		//It adds the circunferent to the parent node.
		_objects.push_back(c);

		//Checks if the max object limit has been exceded.
		if (_objects.size() > MAX_OBJECTS) {
			if (_q1 == nullptr) {
				split();
			}

			for (Circunference cir : _objects) {
				int quadrant = getQuadrant(cir);
				
				if (quadrant != -1) {
					switch (quadrant) {
					case 1:
						_q1->insert(c);
						break;
					case 2:
						_q2->insert(c);
						break;
					case 3:
						_q3->insert(c);
						break;
					case 4:
						_q4->insert(c);
						break;
					}
				}
				else {
					fatherObjects.push_back(c);
				}
			}

			//Copys the objects that doesn't fit entirely within 
			// a quadrant in the father node objects.
			_objects.clear();
			_objects = fatherObjects;
		}
	}

/*
* Return all circunference within the quadrant of the ray.
*/
void Quad::retrieve(list<Circunference> * returnObjects, pair<int, int> ray)
{
	int quadrant = getQuadrant(ray);
	
	if (quadrant != -1 && _q1 != nullptr) {
		
		switch (quadrant) {
		case 1:
			_q1->retrieve(returnObjects, ray);
		case 2:
			_q2->retrieve(returnObjects, ray);
		case 3:
			_q3->retrieve(returnObjects, ray);
		case 4:
			_q4->retrieve(returnObjects, ray);
		}
	}

	for(Circunference c : _objects) 
	{
		returnObjects->push_back(c);
	}
	
	return;
}


