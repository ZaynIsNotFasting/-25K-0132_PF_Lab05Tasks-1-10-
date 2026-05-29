#include "iostream"
using namespace std;

class BankAccount{
    private:
    float balance = 1000.00;
    public:

    void deposit(float amount);
    void withdraw(float amount);
    void showBalance();
};
void BankAccount :: deposit(float amount){
    cout<<"Deposit successful. You are rich now. rich boiiiiii :P"<<endl;
    balance += amount;
}
void BankAccount :: withdraw(float amount){
    if(amount > balance){
        cout<<"Insufficient balance duffus(no offense)."<<endl;
    }else{
        cout<<"Withdrawal successful. Spend away all those mula :P"<<endl;
        balance -= amount;
    }
}
void BankAccount :: showBalance(){
    cout<<"Balance is: "<<balance<<endl;
}

int main(){
    BankAccount ba;

    ba.showBalance();
    ba.deposit(50000.00);
    ba.showBalance();
    ba.withdraw(1000.00);
    ba.showBalance();
}