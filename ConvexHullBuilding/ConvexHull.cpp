#include <iostream>
#include <algorithm>
#include <functional>
#include "ConvexHull.h"

#define M_PI           3.14159265358979323846

using namespace std;
using namespace placeholders;

vector<Point> init;
vector<EdgeVertex> edges;
vector<Vect> vectors;

Point leftDot;

float getAngle(float x, float y) {
	//cout << x << " " << y << endl;
	float result = acos((x - leftDot.x) / (sqrt((x - leftDot.x)*(x - leftDot.x) + (y - leftDot.y)*(y - leftDot.y))));
	//cout << (y-leftDot.y < 0 ? -result : result) << endl;
	return y - leftDot.y < 0 ? -result : result;
};

struct compareVertexes {
	bool operator() (Point i, Point j) { cout << endl; return (getAngle(i.x, i.y) < getAngle(j.x, j.y)); }
} compareObj;

struct compareForMin {
	bool operator() (Point i, Point j) { return (i.x < j.x); }
} compareMin;

void customSet(float x, float y) {
	init.push_back(Point(x, y));
}

void printCos() {
	for (auto i = init.cbegin(); i != init.cend(); ++i) {
		cout << getAngle(i->x, i->y) << endl;
	}
}

void printDots(){
	cout << "\n\n>----- Printing dots ------<\n";
	for (auto i = init.cbegin(); i != init.cend(); ++i) {
		cout << i->x << " " << i->y << endl;
	}
	cout << ">---------- End -----------<\n";
}

void setVectors() {
	float px = init.cbegin()->x, py = init.cbegin()->y;
	for (auto i = init.cbegin() + 1; i != init.cend(); ++i) {
		vectors.push_back(Vect(i->x - px, i->y - py));
		px = i->x;
		py = i->y;
	}
}

bool isConvergent(float x1, float y1, float x2, float y2) {
	cout << "\n\n-----------------------\n";
	cout << "\nCoords to check: \n";
	cout << x1 << " " << y1 << endl;
	cout << x2 << " " << y2 << endl;
	cout << "End\n\n";
	float l1 = sqrt(x1*x1 + y1*y1);
	float l2 = sqrt(x2*x2 + y2*y2);
	cout << "x1: " << x1 << ", x2: " << x2 << "\n\n";
	cout << "l1: " << l1 << ", l2: " << l2 << "\n\n";
	float acos1 = y1 > 0 ? acos(x1 / l1) : -acos(x1 / l1);
	float acos2 = y2 > 0 ? acos(x2 / l2) : -acos(x2 / l2);
	if (x1 / l1 == -1)acos1 = M_PI;
	if (x2 / l2 == -1)acos2 = M_PI;
	cout << "Result: " << ((acos2 < acos1 && acos2 > acos1 - M_PI) ? true : false) << endl;
	cout << "-----------------------\n\n";
	return (acos2 < acos1 && acos2 > acos1 - M_PI) ? true : false;
};

void printVectors() {
	cout << "\n\n>----- Printing vectors ------<\n";
	for (auto i = vectors.cbegin(); i != vectors.cend(); ++i) {
		cout << i->x << " " << i->y << endl;
	}
	cout << ">---------- End -----------<\n";
}

vector<EdgeVertex> getResEdges() {
	/*leftDot.x = 0;
	leftDot.y = 0;
	cout << getAngle(5, -15) << endl;
	cout << getAngle(2, -10) << endl;
*/

	printDots();
	auto mainEl = min_element(init.begin(), init.end(), compareMin);
	Point mainDot(mainEl->x, mainEl->y);
	
	
	leftDot = mainDot;


	init.erase(mainEl);
	
	sort(init.begin(), init.end(), compareObj);
	cout << "\n---------------------------------------------------------------\n\n";
	printCos();

	init.insert(init.begin(), mainDot);
	init.push_back(mainDot);
	setVectors();

	printDots();
	printVectors();
	auto j = init.begin() + 1;

	bool skip1 = false;
	for (auto i = vectors.begin(); i != vectors.end() - 1;) {
		auto prev = i;
		skip1 = false;
		++i;

		if (isConvergent(prev->x, prev->y, i->x, i->y)) {
			prev = i - 2;

			Vect newV((i - 1)->x + i->x, (i - 1)->y + i->y);

			cout << "Q";
			auto t = vectors.erase(i - 1, i + 1);
			cout << "W\n";
			vectors.insert(t, newV);
			
			cout << "E";
			skip1 = true;
			i = prev;
			//i = prev - 1;
			cout << "R\n";

			j = init.erase(j) - 1;
			//cout << "To erase: " << (j + 1)->x << " " << (j + 1)->y << endl;
			//init.erase(j + 1);
		}
		else
			--i;

		++i;
		--i;
		cout << "A";
		if(!skip1) ++i;
		cout << "B";
		if(!skip1) ++j;
		cout << "C\n";
	}
	printVectors();
	printDots();
	cout << "But it's done!\n";
	auto previous = init.cbegin();
	for (auto i = init.cbegin() + 1; i != init.cend(); ++i) {
		/*cout << "From: " << previous->x << " " << previous->y << "\n";
		cout << "To: " << i->x << " " << i->y << "\n\n";*/
		EdgeVertex a(i->x, i->y);
		a.next = new EdgeVertex(previous->x, previous->y);
		edges.push_back(a);
		previous = i;
	}

	return edges;
};
