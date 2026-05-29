#include "iostream"
using namespace std;

class Student {
    private:
    static int idCount;
    string name;
    int studentID;
    int marks[5];
    float average;

    public:

    Student(){
        studentID = idCount++;
    }

    void input(){
        cout << "Enter name: ";
        cin >> name;
        int sum = 0;
        for(int i = 0; i < 5; i++){
            cout << "Enter marks: ";
            cin >> marks[i];
            sum += marks[i];
        }
        average = sum / 5;
    }

    void show(){
        cout << "Name: " << name << endl;
        cout << "ID: " << studentID << endl;
        cout << "Average: " << average << endl;
    }
};

int Student::idCount = 0;

int main(){
    int n;
    cout << "Enter number of students: ";
    cin >> n;
    Student s[n];
    for(int i = 0; i < n; i++){
        s[i].input();
    }
    for(int i = 0; i < n; i++){
        s[i].show();
    }
    return 0;
}