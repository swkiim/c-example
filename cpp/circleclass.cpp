#include <iostream>
using namespace std;

class circle{
    public:
    int radius;
    double get_area();
};

double circle::get_area(){
    return 3.14 * radius * radius;
}

int main(void){
    circle donut;
    cout << "insert radius";
    cin >> donut.radius;
    double area = donut.get_area();
    cout << "donut's area is " << area << endl;

    circle pizza;
    pizza.radius = 30;
    area = pizza.get_area();
    cout << "pizza's area is " << area << endl;
}
