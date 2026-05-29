#include "iostream"
using namespace std;

class Rectangle{
    public:
    float length;
    float width;
    const float area;
   Rectangle(float w, float l) : length(l), width(w), area(l*w){}

    void display(){
        cout<<"Length: "<<length<<endl<<"Width: "<<width<<endl<<"Area: "<<area<<endl;
    }
};

int main(){
    cout<<"Before modifying: "<<endl;
    Rectangle r1(4.2, 5.6);
    r1.display();
    cout<<"\n";
    cout<<"After modifying: "<<endl;
    r1.width = 6.9;
    r1.display();
    return 0;
}