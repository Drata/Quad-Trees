#include "stdafx.h"
#include "Circunference.h"

Circunference::Circunference(pair<int, int> center, int id, int depth) : _center(center), _id(id), _depth(depth) {}

pair<int, int> Circunference::getCenter()
{
	return _center;
}

int Circunference::getDepth() 
{
	return _depth;
}

int Circunference::getId()
{
	return _id;
}

bool Circunference::collisionWith(pair<int, int> ray) 
{
	if (abs(ray.first - _center.first) <= RADIUS && abs(ray.second - _center.second) <= RADIUS) 
	{
		return true;
	}

	return false;
}
