#include "iostream"
using namespace std;

class Customer;

class Account{
    private:
        int accountNum;
        float balance;
    public:
        Account(int accountNum, float balance) : accountNum(accountNum), balance(balance){}
        friend bool verifyAccount(Account& a, Customer& c);
};

class Customer{
    private:
        string name;
        int accountNum;
    public:
        Customer(string name, int accountNum) : name(name), accountNum(accountNum){   
        }
        friend bool verifyAccount(Account& a, Customer& c);
};

bool verifyAccount(Account& a, Customer& c){
    if(a.accountNum == c.accountNum && a.balance > 0){
        cout << "Account Verified" << endl;
        return true;
    }
    else{
        cout << "Account Not Verified" << endl;
        return false;
    }
}

int main(){
    Account a(233, 450000);
    Customer c("Elz", 233);
    Customer c2("Swainz", 333);
    cout<<"First verification: \n";
    verifyAccount(a, c);
    cout<<" "<<endl;
    cout<<"Second verification: \n";
    verifyAccount(a, c2);

    return 0;
}
