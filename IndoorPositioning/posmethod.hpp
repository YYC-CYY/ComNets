#include <iostream>
#include <math.h>

using namespace std;

typedef struct _Node{
    pair<double, double> p;
    double r;
} *Node;


typedef pair<double, double> Point;

double Heron(double a, double b, double c);
Node helper_point(Node A, Node B, Node D);
pair<double, double> intersection(Node A, Node B, Node C);
pair<double, double> representPoint(Node A, Node B, Node C);
// 三角质心算法
pair<double, double> triangulation(Node* node);
double dis(pair<double, double> x, pair<double, double> y);

