#include "iostream"
using namespace std;

class Shape {
    public:
        double calculateArea(double radius){
            return (radius*radius)*3.14;
        }
        double calculateArea(double length, double width){
            return length*width;
        }
        double calculateArea(float base, float height){
            return (base*height)*0.5;
        }
};

int main(){
    Shape s;
    cout<<"Area of Circle: "<<s.calculateArea(10)<<endl;
    cout<<"Area of Rectangle: "<<s.calculateArea(1.20, 2.40)<<endl;
    cout<<"Area of Triangle: "<<s.calculateArea(2.20, 23.40)<<endl;
    return 0;
}