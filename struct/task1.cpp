#include <iostream>
#include <cmath>

using namespace std;

struct Point {
    double x;
    double y;
};

Point xy{5.3, 7.8};

void Points_distance(double x, double y){
    double x2 = pow(x, 2);
    double y2 = pow(y, 2);
    double d = pow((x2 + y2), 0.5);
    cout << "Distance: " << d;
};

int main(){
Points_distance(xy.x, xy.y);
};