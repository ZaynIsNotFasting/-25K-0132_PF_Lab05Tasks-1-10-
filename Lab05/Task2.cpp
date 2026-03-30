#include "iostream"
using namespace std;

class Person {
    protected:
        string name;
        int age;
    public:
        void setPerson(string name, int age){
            this->name = name;
            this->age = age;
        }

        void display(){
            cout<<"Person's Name: "<<name<<endl;
            cout<<"Person's Age: "<<age<<endl;
        }
};

class StudentPublic : public Person {
    public:
    void displayPublic(){
        display();
    }
};

class StudentProtected : protected Person {
    public:
    void displayProtected(){
        display();
    }
};

class StudentPrivate : private Person {
    public:
    void displayPrivate(){
        display();
    }
};

int main(){
    
    cout<<"Public Access: \n";
    StudentPublic sp;
    sp.setPerson("Fahad", 21);
    sp.displayPublic();

    cout<<"Protected Access: \n";
    StudentProtected sp;
    sp.setPerson("Hania Amir", 26);
    sp.displayProtected();

    cout<<"Private Access: \n"; // comment these and also the private class then it'll work
    StudentPrivate sp;
    sp.setPerson("Ryan Gosling", 44);
    sp.displayPrivate();

    return 0;
}