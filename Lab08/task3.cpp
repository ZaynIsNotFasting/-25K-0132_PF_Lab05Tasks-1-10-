#include <iostream>
#include <cmath>
using namespace std;

const double PI = 3.14159265358979;

class Shape {
public:
    virtual double calculateArea() = 0;
    virtual double calculatePerimeter() = 0;
    virtual void display() = 0;
    virtual ~Shape() {}
};

class Circle : public Shape {
    double radius;
public:
    Circle(double r) : radius(r) {}

    double calculateArea() override {
        return PI * radius * radius;
    }

    double calculatePerimeter() override {
        return 2 * PI * radius;
    }

    void display() override {
        cout << "\n[Circle] Radius = " << radius << endl;
        cout << "Area      : " << calculateArea() << endl;
        cout << "Perimeter : " << calculatePerimeter() << endl;
    }
};

class Rectangle : public Shape {
    double length, width;
public:
    Rectangle(double l, double w) : length(l), width(w) {}

    double calculateArea() override {
        return length * width;
    }

    double calculatePerimeter() override {
        return 2 * (length + width);
    }

    void display() override {
        cout << "\n[Rectangle] Length = " << length << ", Width = " << width << endl;
        cout << "Area      : " << calculateArea() << endl;
        cout << "Perimeter : " << calculatePerimeter() << endl;
    }
};

class Triangle : public Shape {
    double a, b, c;
public:
    Triangle(double a, double b, double c) : a(a), b(b), c(c) {}

    double calculateArea() override {
        double s = (a + b + c) / 2.0;
        return sqrt(s * (s - a) * (s - b) * (s - c));
    }

    double calculatePerimeter() override {
        return a + b + c;
    }

    void display() override {
        cout << "\n[Triangle] Sides = " << a << ", " << b << ", " << c << endl;
        cout << "Area      : " << calculateArea() << endl;
        cout << "Perimeter : " << calculatePerimeter() << endl;
    }
};

int main() {
    Shape* shapes[] = {
        new Circle(7.0),
        new Rectangle(10.0, 4.0),
        new Triangle(3.0, 4.0, 5.0)
    };

    for (int i = 0; i < 3; i++) {
        shapes[i]->display();
        delete shapes[i];
    }

    return 0;
}
