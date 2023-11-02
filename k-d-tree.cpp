#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <memory>
#include <set>
#include "tree.h"

int main()
{
    if (test())
    {
        cout << "Test passed!" << endl;
    }
    else
    {
        cout << "Test failed!" << endl;
    }
    {
        vector<Point> points = {
            Point(0, 0, 0),
            Point(0, 0, 0),};

        shared_ptr<Node> root = buildTree(points);

        cout << "K-d Tree 1:\n";
        printTree(root);
        cout << "*********" << endl;
        vector<Point> p = {Point(0, 1, 0), Point(0, 0, 0), Point(0, 1, 1)};
        cout << findNode(root, p) << endl;
        cout << FindElement(root, Point(0, 0, 0)) << endl;
        cout << "*********" << endl;
        cout << "-----------------" << endl;
        AddElement(root, Point(0, 5, 0));
        AddElement(root, Point(0, 5, 1));
        cout << "K-d Tree 2:\n";
        printTree(root);
        cout << "-----------------" << endl;
        PopElement(root, Point(0, 5, 1));
        cout << "K-d Tree 3:\n";
        printTree(root);
    }
    return 0;
}