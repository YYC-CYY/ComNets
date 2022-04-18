#include <iostream>
#include <math.h>
#include "posmethod.hpp"

using namespace std;



/******************************************
 * 
 *  假设三个圆两两相交
 *  使用加权三角质心的思路
 *  直接默认三个圆没有交于一点
 *  先求出三个交点，确定区域
 *  根据求出的三个交点，求三角形质心，作为定位点
 * 
 ******************************************/

// 假设三个圆是两两相交的
pair<double, double> triangulation(Node* node){
    pair<double, double> points[3];
    points[0] = intersection(node[0], node[1], node[2]);
    points[1] = intersection(node[1], node[2], node[0]);
    points[2] = intersection(node[2], node[0], node[1]);

    // 使用加权三角质心算法
    double w0 = 1 / (node[0]->r + node[1]->r),
           w1 = 1 / (node[1]->r + node[2]->r),
           w2 = 1 / (node[2]->r + node[0]->r);
    double w = w0 + w1 + w2;

    // cout << "权值: " << w0 << ", " << w1 << ", " << w2 << endl;
    // cout << "总权值: " << w << endl;

    double x = (w0 * points[0].first + w1 * points[1].first + w2 * points[2].first) / w;
    double y = (w0 * points[0].second + w1 * points[1].second + w2 * points[2].second) / w;

    return make_pair<double, double>(x,y);
}


// 给定两个圆 A、B，求他们的一个交点，这个交点与圆心 C 在直线 AB 的同一侧
pair<double, double> intersection(Node A, Node B, Node C){
    double x1 = A->x, y1 = A->y, r1 = A->r;
    double x2 = B->x, y2 = B->y, r2 = B->r;
    double AB = sqrt((x1 - x2)*(x1 - x2) +(y1 - y2)*(y1 - y2));

    // 垂足 D 的坐标
    double x0, y0;

    double area = Heron(r1, r2, AB);
    double OD = area * 2 / AB;
    double AD = sqrt(r1 * r1 - OD * OD);
    double BD = sqrt(r2 * r2 - OD * OD);

    double t;

    // D 与 B 在 A 的同一侧
    if((AD <= AB && BD <= AB) || (AD > BD && AD > AB)){
        t = AD / AB;
        x0 = x1 + t * (x2 - x1);
        y0 = y1 + t * (y2 - y1);
    }
    else{
        t = BD / AB;
        x0 = x2 + t * (x1 - x2);
        y0 = y2 + t * (y1 - y2);
    }

    t = OD / AB;

    double dy = t * (x2 - x1);
    double dx = t * (y1 - y2);

    double x, y;
    x = x0 + dx;
    y = y0 + dy;

    // (x, y) 是否与 C 在 AB 的同一侧
    double ddy = C->y - y0;
    double ddx = C->x - x0;
    if(dx * ddx + dy * ddy <= 0){
        x = x0 - dx;
        y = y0 - dy;
    }
    cout << "交点: " << "(" << x << ", " << y <<")" << endl;
    return make_pair<double, double>(x, y);
}


// 海伦公式，返回面积
double Heron(double a, double b, double c){
    double p = (a + b + c) / 2;
    return sqrt(p * (p - a) * (p - b) * (p - c));
}

// int main(){
//     Node* node = new Node[3];
//     node[0] = new _Node(); node[0]->r = 2; node[0]->x = 0; node[0]->y = 0;
//     node[1] = new _Node(); node[1]->r = 2; node[1]->x = 2; node[1]->y = 0;
//     node[2] = new _Node(); node[2]->r = 2; node[2]->x = 1; node[2]->y = 2;

//     pair<double,double> point = triangulation(node);
//     cout << "(" << point.first << ", " << point.second << ")" << endl;
//     delete node[0];
//     delete node[1];
//     delete node[2];
//     delete []node;
//     return 0;
// }