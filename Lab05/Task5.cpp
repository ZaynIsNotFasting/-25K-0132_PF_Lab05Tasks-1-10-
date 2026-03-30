#include "iostream"
using namespace std;

class Person {
    private:
        int age;
        string name;
    public:
        Person(string name, int age) : name(name), age(age) {}
        void display() {
            cout << "Person's Name: " << name << endl;
            cout << "Person's Age: " << age << endl;
        }
};

class Student : virtual public Person {
    private:
        int studentID;
    protected:
        Student(string name, int age, int studentID) : Person(name, age), studentID(studentID) {}
    public:
        void displayStudent() {
            cout << "Student ID: " << studentID << endl;
        }
};

class Teacher : virtual public Person {
    private:
        string subject;
    protected:
        Teacher(string name, int age, string subject) : Person(name, age), subject(subject) {}
    public:
        void displayTeacher() {
            cout << "Teacher's Subject: " << subject << endl;
        }
};

class TeachingAssistant : public Student, public Teacher {
    private:
        string department;
    public:
        TeachingAssistant(string name, int age, int studentID, string subject, string department) 
        : Person(name, age), Student(name, age, studentID), Teacher(name, age, subject), department(department) {}

        void displayTA() {
            display();  
            displayStudent(); 
            displayTeacher(); 
            cout << "Department: " << department << endl;
        }
};

int main() {
    TeachingAssistant ta("Elowen", 23, 553456, "Cyber Security", "AI");
    ta.displayTA();
    return 0;
}