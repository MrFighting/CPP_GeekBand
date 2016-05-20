#include <iostream>
#include "Rectangle.h"
using namespace std;

int main() {
    Point p(1,2);
    cout << -p << endl;
    Rectangle r1(10,20,7,8);
    cout <<"r1 :  "<< r1 << endl;

    Rectangle r2(100,200,300,400);
    cout <<"r2 :  " <<r2 << endl;
    r1 = r2;
    cout << "After asignment r1 ="<< endl;
    cout << r1 << endl;
    Rectangle r3(10,20,7,8);
    cout<< "now is r1 == r2? : " << (r1 == r2 ? "true" : "false") << endl;
    cout<< "now is r1 == r3? : " << (r1 == r3 ? "true" : "false") << endl;
    return 0;
}