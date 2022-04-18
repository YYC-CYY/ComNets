#include <iostream>
#include <math.h>

using namespace std;

typedef struct _Node{
    double x, y;
    double r;
} *Node;

double Heron(double a, double b, double c);
Node helper_point(Node A, Node B, Node D);
pair<double, double> intersection(Node A, Node B, Node C);
// 三角质心算法
pair<double, double> triangulation(Node* node);

