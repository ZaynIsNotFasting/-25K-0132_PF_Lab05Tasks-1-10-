#include <iostream>
#include <string>
using namespace std;

class Book;
class Member;

void applyDiscount(Book& b, float percent);

class Book {
    string title;
    string author;
    float price;
public:
    Book(string t, string a, float p) : title(t), author(a), price(p) {}

    bool operator==(const Book& other) const {
        return title == other.title;
    }

    friend ostream& operator<<(ostream& os, const Book& b) {
        os << "Title: " << b.title << " | Author: " << b.author << " | Price: Rs." << b.price;
        return os;
    }

    friend void applyDiscount(Book& b, float percent);
    friend class Librarian;
};

class Member {
    string name;
    string borrowedBookTitle;
public:
    Member(string n) : name(n), borrowedBookTitle("None") {}
    friend class Librarian;
};

class Librarian {
public:
    void displayBooks(Book books[], int count) {
        cout << "\n--- Available Books ---" << endl;
        for (int i = 0; i < count; i++)
            cout << books[i] << endl;
    }

    void borrowBook(Member& m, Book& b) {
        m.borrowedBookTitle = b.title;
        cout << m.name << " has borrowed: " << b.title << endl;
    }

    void displayMemberInfo(Member& m) {
        cout << "Member: " << m.name << " | Borrowed: " << m.borrowedBookTitle << endl;
    }
};

void applyDiscount(Book& b, float percent) {
    b.price -= b.price * (percent / 100.0f);
    cout << "Discount applied! New price of \"" << b.title << "\": Rs." << b.price << endl;
}

class NonFriendLibrarian {
public:
    void tryAccess(Book& b) {
        cout << "NonFriendLibrarian cannot access private members of Book." << endl;
    }
};

int main() {
    Book books[] = {
        Book("C++ Primer", "Lippman", 1200.0f),
        Book("Clean Code", "Martin", 950.0f),
        Book("OOP Concepts", "Grady Booch", 800.0f)
    };

    Member m("Zain");
    Librarian lib;

    lib.displayBooks(books, 3);

    lib.borrowBook(m, books[0]);
    lib.displayMemberInfo(m);

    applyDiscount(books[1], 10.0f);

    cout << "\nComparing books:" << endl;
    cout << "Book 0 == Book 1 : " << (books[0] == books[1] ? "Same" : "Different") << endl;
    cout << "Book 0 == Book 0 : " << (books[0] == books[0] ? "Same" : "Different") << endl;

    cout << "\n--- Non-Friend Access Attempt ---" << endl;
    NonFriendLibrarian nfl;
    nfl.tryAccess(books[0]);

    return 0;
}