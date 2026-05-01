#include <iostream>
#include <string>
using namespace std;

class Employee {
protected:
    string name;
    int id;
public:
    Employee(string n, int i) : name(n), id(i) {}

    virtual double calculateSalary() = 0;
    virtual void displayDetails() = 0;

    virtual ~Employee() {}
};

class FullTimeEmployee : public Employee {
    double monthlySalary;
public:
    FullTimeEmployee(string n, int i, double salary)
        : Employee(n, i), monthlySalary(salary) {}

    double calculateSalary() override {
        return monthlySalary;
    }

    void displayDetails() override {
        cout << "\n[Full-Time Employee]" << endl;
        cout << "Name           : " << name << endl;
        cout << "ID             : " << id << endl;
        cout << "Monthly Salary : Rs." << calculateSalary() << endl;
    }
};

class PartTimeEmployee : public Employee {
    double hourlyRate;
    int hoursWorked;
public:
    PartTimeEmployee(string n, int i, double rate, int hours)
        : Employee(n, i), hourlyRate(rate), hoursWorked(hours) {}

    double calculateSalary() override {
        return hourlyRate * hoursWorked;
    }

    void displayDetails() override {
        cout << "\n[Part-Time Employee]" << endl;
        cout << "Name         : " << name << endl;
        cout << "ID           : " << id << endl;
        cout << "Hours Worked : " << hoursWorked << endl;
        cout << "Hourly Rate  : Rs." << hourlyRate << endl;
        cout << "Total Salary : Rs." << calculateSalary() << endl;
    }
};

class ContractEmployee : public Employee {
    double payPerProject;
    int projectsCompleted;
public:
    ContractEmployee(string n, int i, double pay, int projects)
        : Employee(n, i), payPerProject(pay), projectsCompleted(projects) {}

    double calculateSalary() override {
        return payPerProject * projectsCompleted;
    }

    void displayDetails() override {
        cout << "\n[Contract Employee]" << endl;
        cout << "Name               : " << name << endl;
        cout << "ID                 : " << id << endl;
        cout << "Projects Completed : " << projectsCompleted << endl;
        cout << "Pay Per Project    : Rs." << payPerProject << endl;
        cout << "Total Earned       : Rs." << calculateSalary() << endl;
    }
};

int main() {
    Employee* employees[] = {
        new FullTimeEmployee("Sara Khan", 101, 85000.0),
        new PartTimeEmployee("Bilal Ahmed", 102, 500.0, 60),
        new ContractEmployee("Zara Ali", 103, 15000.0, 3)
    };

    for (int i = 0; i < 3; i++) {
        employees[i]->displayDetails();
        delete employees[i];
    }

    return 0;
}
