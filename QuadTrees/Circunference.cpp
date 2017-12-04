#include "stdafx.h"
#include "Circunference.h"


Circunference::Circunference(pair<int, int> center, int id, int depth) : _center(center), _id(id), _depth(depth) {}

pair<int, int> Circunference::getCenter()
{
	return _center;
}
