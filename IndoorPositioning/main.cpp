#include <iostream>
#include "posmethod.hpp"

using namespace std;

int main(){
    Node* node = new Node[3];
    // node[0] = new _Node(); node[0]->r = 4; node[0]->p.first = 0; node[0]->p.second = 0;
    // node[1] = new _Node(); node[1]->r = 4; node[1]->p.first = 4; node[1]->p.second = 0;
    // node[2] = new _Node(); node[2]->r = 4; node[2]->p.first = 2; node[2]->p.second = 2;
    node[0] = new _Node(); node[0]->r = 6; node[0]->p.first = 0; node[0]->p.second = 0;
    node[1] = new _Node(); node[1]->r = 6; node[1]->p.first = 6; node[1]->p.second = 0;
    node[2] = new _Node(); node[2]->r = 0.5; node[2]->p.first = 0; node[2]->p.second = 4;

    Point p = triangulation(node);
    cout << "(" << p.first << ", " << p.second << ")" << endl;
    delete node[0];
    delete node[1];
    delete node[2];
    delete []node;
    return 0;
}