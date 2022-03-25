#include<iostream>
using namespace std;

#include "circle.h"

circle::circle(){
    radius = 1;
    cout << "radius " << radius;
    cout << "create circle" << endl;
}

circle::circle(int r){
    radius = r;
    cout << "radius " << radius;
    cout << "create circle" << endl;
}

double circle::get_area(){
    return 3.14 * radius * radius;
}