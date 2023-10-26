
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <memory>

using namespace std;

class Point
{
public:
    double x = 0, y = 0, z = 0;

    Point() = default;

    Point(double x_c, double y_c, double z_c) : x(x_c), y(y_c), z(z_c) {}

    bool operator==(const Point &b)const;

    ~Point() = default;
};

class Node
{
public:
    vector<Point> points;
    shared_ptr<Node> left = nullptr;
    shared_ptr<Node> right = nullptr;

    Node() : points() {}

    Node(vector<Point> point_) : points(point_) {}

    Node(Node &p) = default;

    Node(Node &&p) = default;

    ~Node() = default;
};

bool compareX(const Point &a, const Point &b);

bool compareY(const Point &a, const Point &b);

bool compareZ(const Point &a, const Point &b);

int plane(vector<Point> p, double d1, double d2, double d3);

shared_ptr<Node> buildTree(vector<Point> &points);

void printTree(shared_ptr<Node> &root);

void AddElement(shared_ptr<Node> &prev_root, Point el);

bool FindElement(shared_ptr<Node> &root, Point el);

void PopElement(shared_ptr<Node> &prev_root, Point el);

void delRepeats(vector<Point> &points);

bool test();