#include "iostream"
using namespace std;

class Vehicle{
    public:
        virtual void startEngine(){
            cout<<"Vehicle engine is pumping power..."<<endl;
        }
        virtual ~Vehicle() {}
};

class Car: public Vehicle{
    public:
        void startEngine() override{
            cout<<"Car engine is pumping power..."<<endl;
        }
};

class Bike: public Vehicle{
    public:
        void startEngine() override{
            cout<<"Bike engine is pumping power..."<<endl;
        }
};

class Truck : public Vehicle{
    public:
        void startEngine() override{
            cout<<"Truck engine starts with loud dromh dromh.."<<endl;
        }
};

int main(){
    Car c;
    Bike b;
    Truck t;
    
    Vehicle *v;
    v = &c;
    v->startEngine();
    v = &b;
    v->startEngine();
    v = &t;
    v->startEngine();
    return 0;
}