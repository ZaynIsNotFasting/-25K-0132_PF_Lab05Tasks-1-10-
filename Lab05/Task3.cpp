#include "iostream"
using namespace std;

class Person {
    private:
        int age;
        string name;
    public:
        Person(string name, int age) : name(name), age(age) {}

        void display(){
            cout<<"Person Name: "<<name<<endl;
            cout<<"Person Age: "<<age<<endl;
        }
};

class Student : public Person {
    private:
        int studentID;
        string program;
    public:
        Student(string name, int age, int studentID, string program) : Person(name, age), studentID(studentID), program(program) {}

        void displayStudent(){
            display();
            cout<<"Student ID: "<<studentID<<endl;
            cout<<"Student Program: "<<program<<endl;
        }
};

class GraduateStudent : public Student {
    private:
        string researchTopic;
        string supervisorName;
    public:
        GraduateStudent(string name, int age, int studentID, string program, string researchTopic, string supervisorName)
        : Student(name, age, studentID, program), researchTopic(researchTopic), supervisorName(supervisorName) {}
        
        void displayGraduate(){
            displayStudent();
            cout<<"Research Topic: "<<researchTopic<<endl;
            cout<<"Supervisor Name: "<<supervisorName<<endl;
        }
};

int main(){
    GraduateStudent gs("Fahad", 21, 123456, "Computer Science", "Artificial Intelligence", "Dr. Smexy");
    gs.displayGraduate();
    return 0;
}