#include <iostream>
#include "posmethod.hpp"

using namespace std;

int main(){
    Node* node = new Node[3];
    node[0] = new _Node(); node[0]->r = 2; node[0]->x = 0; node[0]->y = 0;
    node[1] = new _Node(); node[1]->r = 2; node[1]->x = 2; node[1]->y = 0;
    node[2] = new _Node(); node[2]->r = 2; node[2]->x = 1; node[2]->y = 2;

    pair<double,double> point = triangulation(node);
    cout << "(" << point.first << ", " << point.second << ")" << endl;
    delete node[0];
    delete node[1];
    delete node[2];
    delete []node;
    return 0;
}