#include "iostream"
using namespace std;

class Account{
    protected:
        string name;
        int accountNumber;
        float balance;
    public:
        Account(string name, int accountNumber, float balance) : name(name), accountNumber(accountNumber), balance(balance) {}

        virtual void calculateInterest(){
            cout<<"Interest of "<<name<<" is: "<<balance<<endl;
        }

        virtual ~Account() {}
};

class SavingsAccount : public Account{
    private:
        int interest;
    public:
        SavingsAccount(string name, int accountNumber, float balance, int interest) : Account(name, accountNumber, balance), interest(interest) {}

        void calculateInterest() override{
            interest = balance*0.21;
            cout<<"Interest of "<<name<<" is: "<<interest<<endl;
        }
};

class CurrentAccount: public Account{
    private:
        float overLimit;
    public:
        CurrentAccount(string name, int accountNumber, float balance, float overLimit) : Account(name, accountNumber, balance), overLimit(overLimit) {}

        void calculateInterest() override{
            float interest = balance* 0.15;
            cout<<"CurrentAccount interest of "<<name<<" is "<<interest<<endl;
        }
};

int main(){
    SavingsAccount s("Safi", 1, 10000, 2000);
    CurrentAccount c("Sarim", 2, 12000, 2500);
    
    Account *a;
    a = &s;
    a->calculateInterest();

    a = &c;
    a->calculateInterest();

    return 0;
}