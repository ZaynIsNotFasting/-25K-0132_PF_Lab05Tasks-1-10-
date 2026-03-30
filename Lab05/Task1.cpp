#include "iostream"
using namespace std;

class Employee {
    private:
        int empID;
        string name;
        float salary;
    
        public:
            void setEmpData(int empID, string name, float salary){
                this->empID = empID;
                this->name = name;
                this->salary = salary;
            }

            void display(){
                cout<<"Employee ID: "<<empID<<endl;
                cout<<"Employee Name: "<<name<<endl;
                cout<<"Employee Salary: "<<salary<<endl;
            }
};

class Manager : public Employee{
    private:
        string department;
        int bonus;
    public:
        void setManagerData(int empID, string name, float salary, string department, int bonus){
            setEmpData(empID, name, salary);
            this->department = department;
            this->bonus = bonus;
        }

        void displayManager(){
            display();
            cout<<"Manager Department: "<<department<<endl;
            cout<<"Manager Bonus: %"<<bonus<<endl;
        }

};

int main(){

    Manager man;
    man.setManagerData(1233214, "Smexy", 6942021.0, "Shadow Controller", 51);
    man.displayManager();
    return 0;
}