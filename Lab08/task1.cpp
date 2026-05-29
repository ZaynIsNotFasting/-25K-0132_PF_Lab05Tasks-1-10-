#include <iostream>
#include <string>
using namespace std;

class Person {
protected:
    string name;
public:
    void getName() {
        cout << "Enter name: ";
        cin >> name;
    }

    void putName() {
        cout << "Name: " << name << endl;
    }

    virtual void getData() = 0;
    virtual bool isOutstanding() = 0;

    virtual ~Person() {}
};

class Student : public Person {
    float gpa;
public:
    void getData() override {
        getName();
        cout << "Enter GPA: ";
        cin >> gpa;
    }

    bool isOutstanding() override {
        return gpa > 3.5;
    }
};

class Professor : public Person {
    int publications;
public:
    void getData() override {
        getName();
        cout << "Enter number of publications: ";
        cin >> publications;
    }

    bool isOutstanding() override {
        return publications > 100;
    }
};

int main() {
    char choice;

    do {
        cout << "\nEnter data for (S)tudent or (P)rofessor: ";
        cin >> choice;

        Person* person = nullptr;

        if (choice == 'S' || choice == 's') {
            person = new Student();
        } else if (choice == 'P' || choice == 'p') {
            person = new Professor();
        } else {
            cout << "Invalid choice." << endl;
            continue;
        }

        person->getData();
        person->putName();
        cout << "Outstanding: " << (person->isOutstanding() ? "Yes" : "No") << endl;

        delete person;

        cout << "Continue? (y/n): ";
        cin >> choice;

    } while (choice == 'y' || choice == 'Y');

    return 0;
}
