#include "iostream"
using namespace std;

void pay(float amount){
    cout<<"Purchased using Cash: "<<amount<<endl;
}

void pay(float amount, string cardType){
    cout<<"Purchased using "<<cardType<<" card: "<<amount<<endl;
}

void pay(float amount, string accountName, int accountNumber){
    cout<<"Purchased using Bank Account: "<<accountName<<" ("<<accountNumber<<") : "<<amount<<endl;
}

int main(){
    pay(9200);
    pay(1890, "debit");
    pay(155420, "Qasim keerio", 123456789);
    return 0;
}