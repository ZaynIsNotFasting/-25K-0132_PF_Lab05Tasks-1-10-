#include <iostream>
using namespace std;

class Student{
    public:
    string name;
    string *grades;
    int numOfGrades;
    Student(string name, int numOfGrades){
        this->name = name;
        grades = new string[numOfGrades];
        this->numOfGrades = numOfGrades;
    }
    void setNumOfGrades(int numOfGrades){
        this->numOfGrades = numOfGrades;
    }
    Student(const Student &s){
        name = s.name;
        numOfGrades = s.numOfGrades;
        grades = new string[numOfGrades];
        for(int i = 0; i < numOfGrades; i++){
            grades[i] = s.grades[i];
        }
    }
    ~Student(){
        delete []grades;
    }

    void show() {
        cout << "Name: " << name << endl;
        cout << "Grades: "<<&grades<<endl;
        cout << "GPA (Number of grades): " << numOfGrades << endl;
        cout<<endl;
    }
};

int main(){

    Student s1("Cattleya", 3);
    s1.show();
    cout<<"Deep Copy Constructor: "<<endl;
    Student s2(s1);
    s2.show();
    cout<<"After Modifying: "<<endl;
    s1.setNumOfGrades(4);
    s1.show();
    return 0;
}