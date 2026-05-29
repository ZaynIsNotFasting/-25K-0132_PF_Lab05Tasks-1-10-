#include "iostream"
using namespace std;

class Teller;

class BankAccount{
    private:
        string accountHolder;
        int pin;
        float balance;
    public:
    BankAccount(string accountHolder, int pin, float balance) : accountHolder(accountHolder), pin(pin), balance(balance) {}

    friend class Teller;
};

class Teller{
    public:
        void display(BankAccount& b){
            cout << "Account Holder: " << b.accountHolder << endl;
            cout << "Balance: " << b.balance << endl;
        }

        void deposit(BankAccount& b, int amount){
            if(amount < 0) return;
         b.balance += amount;
        }

        void withdraw(BankAccount& b, int amount){
            if(b.balance >= amount && amount > 0){
                b.balance -= amount;
                cout<<"Remaining Balance: "<<b.balance<<endl;
            }else{
                cout<<"Withdrawal is not possible"<<endl;
            }
        }

        bool validatePin(BankAccount& b, int inputPin){
            if(b.pin == inputPin){
                cout<<"Pin Validated"<<endl;
                return true;
            }
            else{
                cout<<"Pin Invalidated"<<endl;
                return false;
            }
        }
        
};

class NonFriend{
    public:
        // void display(BankAccount& b){//won't be able to access cuz not friend(bro's left alone sadly)
        //     cout << "Account Holder: " << b.accountHolder << endl;
        //     cout << "Balance: " << b.balance << endl;
        // }
};

int main(){
    BankAccount b1("Fahad", 1234, 10000);
    Teller t1;
    NonFriend nf;
    cout<<"\nDemonstrating Friend Class\n";
    t1.display(b1);
    t1.validatePin(b1, 1234);
    cout<<"\nDemonstrating Non-Friend Class\n";
    // nf.display(b1);

    return 0;
}
