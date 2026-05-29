#include "iostream"
using namespace std;

class Student{
    private:
    int rollNum;
    float cgpa;
    public:

    void setData(int r, float c){
        rollNum = r;
        cgpa = c;
    }

    void display(){
        cout<<"Roll Number of Student is: "<<rollNum<<endl<<"CGPA of that Student is: "<<cgpa<<endl;
    }
};

int main(){
    Student s1;
    s1.setData(132, 3.95);
    s1.display();

    s1.rolNum  = 213;
    s1.cgpa = 4.0;
    s1.display();
    return 0;
}