#include "iostream"
using namespace std;

class Car {
    public:
    float mileage;
    string model;
    int year;
    Car(string model, float mileage, int year){
        this->model = model;
        this->mileage = mileage;
        this->year = year;
    }
    void updateMileage(float mileage){
        this->mileage = mileage;
    }
    void display (){
        cout << "Model: " << model << endl << "Mileage: " << mileage << endl << "Year: " << year << endl;
    }
    
};

int main(){
    Car c1("Koenigsegg", 40.3, 2017);
    c1.display();
    c1.updateMileage(32.5);
    c1.display();
    return 0;
}