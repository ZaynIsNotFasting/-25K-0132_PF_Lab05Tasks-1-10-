#include "iostream"
using namespace std;

class Car {
    private:
    int speed=90;
    public:
        void setSpeed(int s)
        {
            if(s >= 0 && s <= 200){
                speed = s;
                cout<<"Absolutely correct speed range my nilla!"<<endl;
            }else{
                cout<<"Wrong speed bruv. get gud!"<<endl;
            }
        }
        int getSpeed(){
            return speed;
        }
};

int main(){
    Car see;
    see.setSpeed(69);
    cout<<see.getSpeed()<<endl;
    see.setSpeed(2233);
    cout<<see.getSpeed()<<endl;
    return 0;
}