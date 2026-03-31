#include <iostream>
using namespace std;

class Employee {
    protected:
        string name;
        int id;
        float salary;
    public:
        Employee(string name, int id, float salary) : name(name), id(id), salary(salary) {}
        virtual void calculateSalary(){
            cout<<"Salary of "<<name<<" is "<<salary<<endl;
        }
        virtual ~Employee() {}
};

class Manager : public Employee{
    private: 
        float bonus;
    public:
        Manager(string name, int id, float salary, float bonus) : Employee(name, id, salary), bonus(bonus) {}
        void calculateSalary() override{
            cout<<"Salary of Manager "<<name<<" is "<<salary+bonus<<endl;
        }
};
class Developer : public Employee{
    private:
        float bonus;
    public:
        Developer(string name, int id, float salary, float bonus) : Employee(name, id, salary), bonus(bonus) {}
        void calculateSalary() override{
            cout<<"Salary of Developer "<<name<<" is: "<<salary+bonus<<endl;
        }
};

int main(){
    Employee *e;
    Manager m("Ahmed", 1, 10000, 2000);
    Developer d("Ali", 2, 12000, 2500);

    e = &m;
    e->calculateSalary();

    e = &d;
    e->calculateSalary();


    return 0;
}

