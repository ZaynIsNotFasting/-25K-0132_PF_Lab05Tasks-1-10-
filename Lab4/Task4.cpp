#include "iostream"
using namespace std;

class Processor{
    private:
        string model;
        int speed;
    public:
    Processor(string model, int speed) : model(model), speed(speed) {}
    void display(){
        cout<<"Processor Model: "<<model<<endl;
        cout<<"Processor Speed: "<<speed<<endl;
    }
};

class Ram{
    private:
    int size;
    string type;

    public:
    Ram(int size, string type) : size(size), type(type) {}
    void display(){
        cout<<"Ram Size: "<<size<<endl;
        cout<<"Ram Type: "<<type<<endl;
    }
};

class Computer{
    private:
        Processor p;
        Ram r;

    public:
    Computer(Processor p, Ram r) : p(p), r(r) {}
    void display(){
        p.display();
        r.display();
    }
};

int main(){
    cout<<"Computer Specs: "<<endl;
    Processor p("Intel Core i7", 3.4);
    Ram r(16, "DDR4");
    Computer c(p, r);
    c.display();
    return 0;
}