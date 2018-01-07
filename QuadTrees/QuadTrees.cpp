// QuadTrees.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "Circunference.h"
#include "Quad.h"
#include <stdlib.h>
#include <time.h> 
#define N 100000
#define BOUNDS 10000

using namespace std;

int main()
{
	Quad quad = Quad(1, BOUNDS, BOUNDS);

	srand(time(NULL));

	//Insertion of the N circunference in the quadtree
	cout << "Creando QuadTree. Este proceso puede tardar unos minutos, por favor espere." << endl;
	for (int i = 0; i < N; i++) {
		int x = rand() % BOUNDS;
		int y = rand() % BOUNDS;

		cout << i << std::endl;

		pair<int, int> center(x, y);
		quad.insert(Circunference(center, i, rand() % 10));
	}

	while(1) {
		int x = -1, y = -1;

		cout << "Introduce la coordenada X del punto." << endl;
		cin >> x;
		cout << "Introduce la coordenada Y del punto." << endl;
		cin >> y;
		
		//Generates a point.
		pair<int, int> ray(x, y);

		const clock_t begin_time = clock();
		
		//Gets the circunferences that can collide with the ray.
		list<Circunference> listCir = list <Circunference>();
		quad.retrieve(&listCir, ray);

		//Gets the circunference with the minimum depth.
		int result = -1;
		int depth = 10;
		pair<int, int> centro;

		for (Circunference c : listCir) {
			if (c.collisionWith(ray) && c.getDepth() <= depth) {
				result = c.getId();
				depth = c.getDepth();
				centro = c.getCenter();
			}
		}

		if (result != -1) {
			cout << "El punto (" << ray.first << ", " << ray.second << ") ha colisionado con la circunferencia " << result 
				 << " con centro en (" << centro.first << ", " << centro.second << ") y profundidad " << depth << endl;
		}
		else {
			cout << "El punto no ha colisionado con ninguna circunferencia." << endl;
		}

		cout << "Tiempo: " << float(clock() - begin_time) / CLOCKS_PER_SEC << endl;
	}

	return 0;
	
}

