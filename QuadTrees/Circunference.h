#pragma once
#include <utility>
#define RADIUS 100

using namespace std;

class Circunference
{
private:
	std::pair<int, int> _center;
	int _id;
	int _depth;

public:
	Circunference(pair<int, int> center, int id, int depth);
	pair <int, int> getCenter();
};

