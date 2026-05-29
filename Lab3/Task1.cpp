#include <iostream>
using namespace std;

class Book {
    private:
    string title;
    string author;
    float price;
    public:
    Book(){
        title = "Lord of Mysteries";
        author = "Cuttlefish that loves diving";
        price = 10.2;
    }
    Book(string title, string author, float price){
        this->title = title;
        this->author = author;
        this->price = price;
    }

    void display(){
        cout<<"Title: "<<title<<endl<<"Author: "<< author<<endl<<"Cost: "<<price<<endl;
    }

};

int main(){
    Book b1;
    cout<<"Default Constructor: "<<endl;
    b1.display();
    
    Book b2("Reverend Insanity", "Ren Zhu", 11.5);
    cout<<"Parametrized Constructor: "<<endl;
    b2.display();
}