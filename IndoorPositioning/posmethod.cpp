#include <iostream>
#include <math.h>
#include "posmethod.hpp"

using namespace std;


/******************************************
 * 
 *  给定三个圆，对于任意两个圆，先找出一个代表点
 *  如果两圆相交：
 *      i.  选择与第三圆在圆心连线的同一侧的点 (x)
 *      ii. 选择到第三圆距离与第三圆半径最接近的点 
 *  如果两圆不相交：
 *      选择圆心连线上到两圆心距离比等于半径比的点
 *      这里需要考虑两圆外离和两圆内含的情况
 * 
 ******************************************/

// 三角定位
Point triangulation(Node* node){
    pair<double, double> points[3];
    // 计算三个代表点
    points[0] = representPoint(node[0], node[1], node[2]);
    points[1] = representPoint(node[1], node[2], node[0]);
    points[2] = representPoint(node[2], node[0], node[1]);

    // 使用加权三角质心算法
    double w0 = 1 / (node[0]->r + node[1]->r),
           w1 = 1 / (node[1]->r + node[2]->r),
           w2 = 1 / (node[2]->r + node[0]->r);
    double w = w0 + w1 + w2;

    // cout << "权值: " << w0 << ", " << w1 << ", " << w2 << endl;
    // cout << "总权值: " << w << endl;

    double x = (w0 * points[0].first + w1 * points[1].first + w2 * points[2].first) / w;
    double y = (w0 * points[0].second + w1 * points[1].second + w2 * points[2].second) / w;

    return Point(x,y);
}


// represent point
Point representPoint(Node A, Node B, Node C){
    double r1 = A->r;
    double r2 = B->r;
    double AB = dis(A->p, B->p);

    // 两圆相交或相切
    if(AB <= r1 + r2 && AB >= abs(r1 - r2)){
        return intersection(A, B, C);
    }

    double x1 = A->p.first, y1 = A->p.second;
    double x2 = B->p.first, y2 = B->p.second;
    double t;
    Point p;

    // 两圆外离
    if(r1 + r2 < AB){
        t = r1/(r1 + r2);
        cout << "外离: " ;
    }
    // 两圆内含
    if(AB < abs(r1 - r2)){
        t = r1 / (r1 - r2);
        cout << "内含: " ;
    }

    p.first = x1 + t * (x2 - x1);
    p.second = y1 + t * (y2 - y1);
    cout << "(" << p.first << ", " << p.second <<")" << endl;
    return p;
}


// 给定两个相交或相切的圆 A、B，求他们的一个交点，这个交点与 C 的距离是否更接近 C 的半径 r
Point intersection(Node A, Node B, Node C){
    double x1 = A->p.first, y1 = A->p.second, r1 = A->r;
    double x2 = B->p.first, y2 = B->p.second, r2 = B->r;
    double AB = dis(A->p, B->p);

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

    Point p = make_pair<double, double>(x0+dx,y0+dy);
    Point _p = make_pair<double, double>(x0-dx,y0-dy);

    double d = dis(p, C->p) - C->r;
    double _d = dis(_p, C->p) - C->r;

    // (x, y) 与 C 的距离是否更接近 C 的半径 r
    if(abs(d) < abs(_d)){
        cout << "交点: " << "(" << p.first << ", " << p.second <<")" << endl;
        return p;
    }
    else{
        cout << "交点: " << "(" << _p.first << ", " << _p.second <<")" << endl;
        return _p;
    }
}


// 海伦公式，返回面积
double Heron(double a, double b, double c){
    double p = (a + b + c) / 2;
    return sqrt(p * (p - a) * (p - b) * (p - c));
}

// 求两点距离
double dis(Point x, Point y){
    return sqrt((x.first - y.first)*(x.first - y.first) +(x.second - y.second)*(x.second - y.second));
}

// int main(){
//     Node* node = new Node[3];
//     // node[0] = new _Node(); node[0]->r = 4; node[0]->p.first = 0; node[0]->p.second = 0;
//     // node[1] = new _Node(); node[1]->r = 4; node[1]->p.first = 4; node[1]->p.second = 0;
//     // node[2] = new _Node(); node[2]->r = 4; node[2]->p.first = 2; node[2]->p.second = 2;
//     node[0] = new _Node(); node[0]->r = 6; node[0]->p.first = 0; node[0]->p.second = 0;
//     node[1] = new _Node(); node[1]->r = 6; node[1]->p.first = 6; node[1]->p.second = 0;
//     node[2] = new _Node(); node[2]->r = 0.5; node[2]->p.first = 0; node[2]->p.second = 4;

//     Point p = triangulation(node);
//     cout << "定位: " ;
//     cout << "(" << p.first << ", " << p.second << ")" << endl;
//     delete node[0];
//     delete node[1];
//     delete node[2];
//     delete []node;
//     return 0;
// }