using namespace std;
#include <memory>
#include <iostream>
#include "tree.h"

static double eps = std::numeric_limits<double>::epsilon();

bool Point::operator==(const Point &b) const
{
    if (fabs(this->x - b.x) < eps && fabs(this->y - b.y) < eps && fabs(this->z - b.z) < eps)
    {
        return 1;
    }
    return 0;
}

bool compareX(const Point &a, const Point &b)
{
    return a.x < b.x;
}

bool compareY(const Point &a, const Point &b)
{
    return a.y < b.y;
}

bool compareZ(const Point &a, const Point &b)
{
    return a.z < b.z;
}

int plane(vector<Point> p, double d1, double d2, double d3)
{
    int res = 0;
    double value = 0.0, delta = 0.0, r = 0.0;
    if (d1 >= d2 && d1 >= d3)
    {
        sort(p.begin(), p.end(), compareX);
        value = d1 / 2;
        delta = fabs(p[0].x - value);
        for (int i = 1; i < static_cast<int>(p.size()); i++)
        {
            r = fabs(p[i].x - value);
            if (r < delta)
            {
                delta = r;
                res = i;
            }
        }
        return res;
    }
    if (d2 >= d1 && d2 >= d3)
    {
        sort(p.begin(), p.end(), compareY);
        value = d2 / 2;
        delta = fabs(p[0].y - value);
        for (int i = 1; i < static_cast<int>(p.size()); i++)
        {
            r = fabs(p[i].y - value);
            if (r < delta)
            {
                delta = r;
                res = i;
            }
        }
        return res;
    }
    else
    {
        sort(p.begin(), p.end(), compareZ);
        value = d3 / 2;
        delta = fabs(p[0].z - value);
        for (int i = 1; i < static_cast<int>(p.size()); i++)
        {
            r = fabs(p[i].z - value);
            if (r < delta)
            {
                delta = r;
                res = i;
            }
        }
        return res;
    }
}

shared_ptr<Node> buildTree(vector<Point> &points)
{
    if (points.empty())
    {
        return nullptr;
    }
    delRepeats(points);
    sort(points.begin(), points.end(), compareX);
    double d1 = fabs(points[0].x - points[points.size() - 1].x);
    sort(points.begin(), points.end(), compareY);
    double d2 = fabs(points[0].y - points[points.size() - 1].y);
    sort(points.begin(), points.end(), compareZ);
    double d3 = fabs(points[0].z - points[points.size() - 1].z);
    int mid = plane(points, d1, d2, d3);
    shared_ptr<Node> root = make_shared<Node>(Node(points));
    if (points.size() == 1)
    {
        return root;
    }
    else if (points.size() == 2)
    {
        vector<Point> lPoints = {points[0]};
        vector<Point> rPoints = {points[1]};
        root->left = buildTree(lPoints);
        root->right = buildTree(rPoints);
    }
    else
    {
        vector<Point> lPoints(points.begin(), points.begin() + mid);
        vector<Point> rPoints(points.begin() + mid, points.end());
        root->left = buildTree(lPoints);
        root->right = buildTree(rPoints);
    }
    return root;
}

void printTree(shared_ptr<Node> &root)
{
    if (root == nullptr)
    {
        cout << "Empty!" << endl;
        return;
    }
    for (int i = 0; i < static_cast<int>(root->points.size()); i++)
    {
        cout << "(" << root->points[i].x << ", " << root->points[i].y << ", " << root->points[i].z << ")" << endl;
    }
    cout << "Left subtree:\n";
    printTree(root->left);
    cout << "Right subtree:\n";
    printTree(root->right);
}

void AddElement(shared_ptr<Node> &prev_root, Point el)
{
    if (prev_root == nullptr)
    {
        vector<Point> points = {el};
        shared_ptr<Node> root = buildTree(points);
        prev_root = root;
    }
    vector<Point> points(prev_root->points.begin(), prev_root->points.end());
    points.push_back(el);
    shared_ptr<Node> root = buildTree(points);
    prev_root = root;
}

bool FindElement(shared_ptr<Node> &root, Point el)
{
    vector<Point> points(root->points.begin(), root->points.end());
    for (int i = 0; i < static_cast<int>(points.size()); i++)
    {
        if (points[i] ==  el)
        {
            return 1;
        }
    }
    return 0;
}

void PopElement(shared_ptr<Node> &prev_root, Point el)
{
    if (prev_root == nullptr)
    {
        return;
    }
    vector<Point> points(prev_root->points.begin(), prev_root->points.end());
    if (!FindElement(prev_root, el))
    {
        return;
    }
    else
    {
        for (int i = 0; i < static_cast<int>(points.size()); i++)
        {
            if (points[i] == el)
            {
                points.erase(points.begin() + i);
                break;
            }
        }
    }
    shared_ptr<Node> root = buildTree(points);
    prev_root = root;
}

void delRepeats(vector<Point> &points)
{
    auto end = points.end();
    for (auto it = points.begin(); it != end; ++it)
    {
        end = remove(it + 1, end, *it);
    }
    points.erase(end, points.end());
}