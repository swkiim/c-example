#include<iostream>
using namespace std;

#include "circle.h"

int main(){
    circle donut;
    double area = donut.get_area();
    cout << "donut's area ";
    cout << area << endl;

    circle pizza;
    area = pizza.get_area();
    cout << "pizza's area ";
    cout << area << endl;
}