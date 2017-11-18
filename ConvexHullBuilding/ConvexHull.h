#include <vector>
struct Point {
	Point():x(0), y(0) {};
	Point(float a, float b):x(a), y(b) {};
	float x, y;
};

struct EdgeVertex {
	EdgeVertex() :x(0), y(0) {};
	EdgeVertex(EdgeVertex*a) :x(0), y(0), next(a) {};
	EdgeVertex(float a, float b) :x(a), y(b) {};
	float x, y;
	EdgeVertex* next = nullptr;
};

struct Vect {
	Vect() :x(0), y(0) {};
	Vect(float a, float b) :x(a), y(b) {};
	float x, y;
};

void customSet(float, float);

std::vector<EdgeVertex> getResEdges();