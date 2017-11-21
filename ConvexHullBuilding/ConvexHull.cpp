#include <iostream>
#include <algorithm>
#include <functional>
#include "ConvexHull.h"

#define M_PI           3.14159265358979323846

using namespace std;

vector<Point> init;
vector<EdgeVertex> edges;

Point GrahamHull::leftDot = Point();
Point JarvisHull::mainDot = Point();

void printDots() {
	cout << "\n\n>----- Printing dots ------<\n";
	for (auto i = init.cbegin(); i != init.cend(); ++i) {
		cout << i->x << " " << i->y << endl;
	}
	cout << ">---------- End -----------<\n";
}

void customSet(float x, float y) {
	init.push_back(Point(x, y));
}


float GrahamHull::getAngle(float x, float y) {
	float result = acos((x - GrahamHull::leftDot.x) / (sqrt((x - GrahamHull::leftDot.x)*(x - GrahamHull::leftDot.x) + (y - GrahamHull::leftDot.y)*(y - GrahamHull::leftDot.y))));
	return y - GrahamHull::leftDot.y < 0 ? -result : result;
};

void GrahamHull::printCos() {
	for (auto i = init.cbegin(); i != init.cend(); ++i) {
		cout << getAngle(i->x, i->y) << endl;
	}
}

void GrahamHull::printVectors() {
	cout << "\n\n>----- Printing vectors ------<\n";
	for (auto i = vectors.cbegin(); i != vectors.cend(); ++i) {
		cout << i->x << " " << i->y << endl;
	}
	cout << ">---------- End -----------<\n";
}

void GrahamHull::setVectors() {
	float px = init.cbegin()->x, py = init.cbegin()->y;
	for (auto i = init.cbegin() + 1; i != init.cend(); ++i) {
		vectors.push_back(Vect(i->x - px, i->y - py));
		px = i->x;
		py = i->y;
	}
}

bool GrahamHull::isConvergent(float x1, float y1, float x2, float y2) {
	float l1 = sqrt(x1*x1 + y1*y1);
	float l2 = sqrt(x2*x2 + y2*y2);
	float asinBetween = asin((x1*y2 - y1*x2) / (l1*l2));
	cout << "\nCoords to check: \n";
	cout << x1 << " " << y1 << endl;
	cout << x2 << " " << y2 << endl;
	cout << "ASIN: " << asinBetween << endl;
	if (asinBetween > 0)
		return false;
	return true;
};

vector<EdgeVertex> GrahamHull::getResEdges() {
	printDots();
	auto mainEl = min_element(init.begin(), init.end(), compareMin);
	Point mainDot(mainEl->x, mainEl->y);
	GrahamHull::leftDot = mainDot;
	init.erase(mainEl);
	sort(init.begin(), init.end(), compareObj);
	cout << "\n---------------------------------------------------------------\n\n";
	printCos();

	init.insert(init.begin(), mainDot);
	init.push_back(mainDot);
	setVectors();
	cout << "\n\nInitial setting:\n";
	printDots();
	printVectors();
	auto j = init.begin() + 1;

	bool skip1 = false;
	if (vectors.size() > 3) {
		for (auto i = vectors.begin(); i != vectors.end() - 1;) {
			auto prev = i;
			skip1 = false;
			++i;

			if (isConvergent(prev->x, prev->y, i->x, i->y)) {
				prev = i - 2;
				Vect newV((i - 1)->x + i->x, (i - 1)->y + i->y);
				auto t = vectors.erase(i - 1, i + 1);
				vectors.insert(t, newV);
				skip1 = true;
				i = prev;
				j = init.erase(j) - 1;
			}
			else
				--i;

			if (!skip1) {
				++i;
			}
			if (!skip1) {
				++j;
			}
		}
	}
	else if (vectors.size() <= 2) {
		cout << "Wronq qunatity of vertexes!\n";
	}
	printVectors();
	printDots();
	auto previous = init.cbegin();
	for (auto i = init.cbegin() + 1; i != init.cend(); ++i) {
		EdgeVertex a(i->x, i->y);
		a.next = new EdgeVertex(previous->x, previous->y);
		edges.push_back(a);
		previous = i;
	}
	return edges;
};


/*--------------------------------------------------------------------------------------------*/

float JarvisHull::getPolarAngle(float x1, float y1, float x2, float y2) {
	float l1 = sqrt(x1*x1 + y1*y1);
	float l2 = sqrt(x2*x2 + y2*y2);
	return acos((x1*x2+y1*y2)/(l1*l2));
};


vector<EdgeVertex> JarvisHull::getResEdges() {
	printDots();
	if (init.size() < 3) {
		cout << "Insufficient quantity of initial vertexes, try again\n";
		return edges;
	}
	auto mainEl = min_element(init.begin(), init.end(), compareMin);
	mainDot.x = mainEl->x;
	mainDot.y = mainEl->y;
	init.erase(mainEl);
	init.insert(init.begin(), mainDot);
	init.push_back(mainDot);
	auto next = init.begin() + 1;
	auto b = init.begin() + 1;
	cout << mainDot.x << " " << mainDot.y << endl;

	float minInitAngle = M_PI;
	for (auto i = init.begin() + 1; i != init.end() - 1; ++i) {
		if (getPolarAngle(1, 0, i->x - mainDot.x, i->y - mainDot.y) < minInitAngle) {
			minInitAngle = getPolarAngle(1, 0, i->x, i->y);
			next = i;
		}
	}
	Point temp(next->x, next->y);
	init.erase(next);
	init.insert(init.begin() + 1, temp);
	b = init.begin() + 1;
	printDots();
	while (b->x != mainDot.x || b->y != mainDot.y) {
		auto c = b - 1;
		float px, py;
		px = b->x - c->x;
		py = b->y - c->y;
		float minAngle = M_PI;
		for (auto i = b; i != init.end(); ++i) {
			if (getPolarAngle(px, py, i->x - b->x, i->y - b->y) < minAngle) {
				minAngle = getPolarAngle(px, py, i->x - b->x, i->y - b->y);
				next = i;
			}
		}
		Point temp(next->x, next->y);
		init.erase(next);
		init.insert(b + 1, temp);
		++b;
	}
	auto prev = init.cbegin();
	auto prevIt = init.cbegin();
	for (auto j = init.cbegin() + 1; j != b + 1; ++j) {
		EdgeVertex * second = new EdgeVertex(j->x, j->y);
		EdgeVertex first(second);
		first.x = prevIt->x;
		first.y = prevIt->y;
		++prevIt;
		edges.push_back(first);
	}
	printDots();
	return edges;
};
