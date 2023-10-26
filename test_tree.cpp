using namespace std;
#include <memory>
#include <iostream>
#include "tree.h"

bool test()
{
    vector<Point> points = {
        Point(0, 0, 0),
        Point(0, 0.75, 0),
        Point(0, 1, 0)};

    shared_ptr<Node> root = buildTree(points);

    if (root->left->points[0] == Point(0, 0, 0) && root->right->points[0] == Point(0, 0.75, 0) && root->right->points[1] == Point(0, 1, 0))
    {
        return 1;
    }
    else 
    {
        return 0;
    }
}