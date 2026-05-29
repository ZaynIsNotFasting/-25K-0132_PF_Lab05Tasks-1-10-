#include "iostream"

using namespace std;

class Employee{
    private:
    string name;
    int age;
    float salary;
    string company;
    public:
    void setInput(string n, int a, float s, string c){
        name = n;
        age = a;
        salary = s;
        company = c;
    }
    int getAge(){
        return age;
    }
    string getName(){
        return name;
    }
    float getSalary(){
        return salary;
    }
    string getCompany(){
        return company;
    }
    void showOutput(){
        cout<<"Name: "<<getName()<<endl;
        cout<<"Age: "<<getAge()<<endl;
        cout<<"Salary: "<<getSalary()<<endl;
        cout<<"Company: "<<getCompany()<<endl;
    }
};

struct EmployeeStruct{
int age;
string name;
float salary;
string company;
};

int main(){
     Employee e1;
     cout<<"Using Class: "<<endl;

     e1.setInput("John", 25, 50000.00, "Google");
     e1.showOutput();

     cout<<endl;
     cout<<"-------------------------------------------"<<endl;
     cout<<"Using Struct: "<<endl;
     struct EmployeeStruct e2;

      e2.age = 25;
      e2.name = "Bilawal Bhutto";
      e2.salary = 500000.00;
      e2.company = "PPP";

      cout<<"Name: "<<e2.name<<endl;
      cout<<"Age: "<<e2.age<<endl;
      cout<<"Salary: "<<e2.salary<<endl;
     cout<<"Company: "<<e2.company<<endl;
     return 0;
}