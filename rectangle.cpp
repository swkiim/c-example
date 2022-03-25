#include<iostream>
using namespace std;

class rectangle{
    public:
    int width, height;
    rectangle();
    rectangle(int w, int h);
    rectangle(int length);
    bool is_square();
};

rectangle::rectangle(){
    width = height = 1;
}

rectangle::rectangle(int w, int h){
    width = w;
    height = h;
}

rectangle::rectangle(int length){
    width = height = length;
}

bool rectangle::is_square(){
    if(width == height){
        return true;
    }else{
        return false;
    }
}

int main(void){
    rectangle rec1;
    rectangle rec2(3, 5);
    rectangle rec3(3);

    if(rec1.is_square()){
        cout << "rect1 is Square" << endl;
    }if(rec2.is_square()){
        cout << "rect2 is Square" << endl;
    }if(rec3.is_square()){
        cout << "rect3 is Square" << endl;
    }
}