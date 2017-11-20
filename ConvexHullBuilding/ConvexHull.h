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

class Builder {
public:
	virtual std::vector<EdgeVertex> getResEdges() = 0;
};
class GrahamHull : public Builder{
public:
	struct compareVertexes {
		bool operator() (Point i, Point j) { return (getAngle(i.x, i.y) < getAngle(j.x, j.y)); }
	} compareObj;

	struct compareForMin {
		bool operator() (Point i, Point j) { return (i.x < j.x); }
	} compareMin;

	static float getAngle(float x, float y);
	void printCos();
	void printVectors();
	void setVectors();
	bool isConvergent(float x1, float y1, float x2, float y2);
	std::vector<EdgeVertex> getResEdges();


private:
	std::vector<Vect> vectors;
	static Point leftDot;
};
//std::vector<EdgeVertex> getResEdges();