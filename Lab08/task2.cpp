#include <iostream>
#include <string>
using namespace std;

class Payment {
protected:
    double amount;
public:
    Payment(double amt) : amount(amt) {}

    virtual void processPayment() = 0;
    virtual void generateReceipt() = 0;

    virtual ~Payment() {}
};

class CreditCard : public Payment {
    string cardNumber;
    string cardHolder;
public:
    CreditCard(double amt, string num, string holder)
        : Payment(amt), cardNumber(num), cardHolder(holder) {}

    void processPayment() override {
        cout << "\n[Credit Card] Validating card details..." << endl;
        cout << "Card Number : " << cardNumber << endl;
        cout << "Card Holder : " << cardHolder << endl;
        cout << "Payment of Rs." << amount << " processed successfully." << endl;
    }

    void generateReceipt() override {
        cout << "--- Credit Card Receipt ---" << endl;
        cout << "Holder  : " << cardHolder << endl;
        cout << "Amount  : Rs." << amount << endl;
        cout << "Status  : Approved" << endl;
    }
};

class Cash : public Payment {
public:
    Cash(double amt) : Payment(amt) {}

    void processPayment() override {
        cout << "\n[Cash] Confirming cash payment..." << endl;
        cout << "Amount of Rs." << amount << " received in cash." << endl;
    }

    void generateReceipt() override {
        cout << "--- Cash Receipt ---" << endl;
        cout << "Amount  : Rs." << amount << endl;
        cout << "Status  : Paid" << endl;
    }
};

class DigitalWallet : public Payment {
    string walletId;
public:
    DigitalWallet(double amt, string id)
        : Payment(amt), walletId(id) {}

    void processPayment() override {
        cout << "\n[Digital Wallet] Processing online transaction..." << endl;
        cout << "Wallet ID : " << walletId << endl;
        cout << "Rs." << amount << " transferred successfully." << endl;
    }

    void generateReceipt() override {
        cout << "--- Digital Wallet Receipt ---" << endl;
        cout << "Wallet  : " << walletId << endl;
        cout << "Amount  : Rs." << amount << endl;
        cout << "Status  : Transferred" << endl;
    }
};

int main() {
    Payment* payments[] = {
        new CreditCard(5000.0, "4111-1111-1111-1111", "Ali Raza"),
        new Cash(1500.0),
        new DigitalWallet(2500.0, "easypaisa_03001234567")
    };

    for (int i = 0; i < 3; i++) {
        payments[i]->processPayment();
        payments[i]->generateReceipt();
        cout << endl;
        delete payments[i];
    }

    return 0;
}
