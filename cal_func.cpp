#include<stdio.h>
#include<iostream>
using namespace std;

int add(int x, int y); 
int sub(int x, int y);
int mul(int x, int y);
int divd(int x, int y);
int rem(int x, int y);

int main()
{
    int x_val;
    int y_val;
    
    cout << "Enter the x value " << endl;
    cin >> x_val;
    cout << "x value : " << x_val << endl;

    cout << "Enter the y value " << endl;
    cin >> y_val;
    cout << "y value : " << y_val <<endl;

    int result_add = add(x_val, y_val);
    int result_sub = sub(x_val, y_val);
    int result_mul = mul(x_val, y_val);
    int result_div = divd(x_val, y_val);
    int result_rem = rem(x_val, y_val);

    cout << "x + y = " << result_add << endl;
    cout << "x - y = " << result_div << endl;
    cout << "x * y = " << result_mul << endl;
    cout << "x / y = " << result_div << endl;
    cout << "x % y = " << result_rem << endl;
}

int add(int x, int y)
{
    return x + y;
};

int sub(int x, int y)
{
    return x - y;
};

int mul(int x, int y)
{
    return x * y;
};

int divd(int x, int y)
{
    return x / y;
};

int rem(int x, int y)
{
    return x % y;
};

