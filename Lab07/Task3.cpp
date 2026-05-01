#include "iostream"
using namespace std;

class Student{
    private:
        string name;
        float grades[5];
    public:
        Student(string name) : name(name) {}

        void input(){
            for(int i = 0; i<5; i++){
                cout<<"Enter Grade "<<i+1<<": ";
                cin>>grades[i];
            }
        }
    friend double calculateAverage(Student& s);
    friend double findHighestGrade(Student& s);
};

double calculateAverage(Student& s){
    float sum = 0;
    for(int i = 0; i<5; i++){
        sum += s.grades[i];
    }
    return sum/5;
}

double findHighestGrade(Student& s){
    float max = s.grades[0];
    for(int i = 0; i< 5; i++){
        if(s.grades[i] > max){max = s.grades[i];}
    }
    return max;
}

int main(){
    Student s("Rogeve");

    s.input();
    cout<<"Average Grade: "<<calculateAverage(s)<<endl;
    cout<<"Highest Grade: "<<findHighestGrade(s)<<endl;
}