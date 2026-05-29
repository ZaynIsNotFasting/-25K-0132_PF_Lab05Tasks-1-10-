#include "iostream"
using namespace std;

class University {
    private:
        static int totalStudents;
        string universityName;
    public:
        University(string universityName){
            this->universityName = universityName;
            totalStudents++;
        }

        static int getTotalStudents(){
            return totalStudents;
        }

        void display(){
            cout<<"University Name: "<<universityName<<endl<<"Total Students: "<<totalStudents<<endl;
        }
};

int University :: totalStudents = 0;

int main()
{
    University u1("FAST");
    u1.display();
    University u2("UET");
    u2.display();
    University u3("NUST");
    u3.display();
    return 0;
}