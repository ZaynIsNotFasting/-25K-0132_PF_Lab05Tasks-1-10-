#include "iostream"
using namespace std;

class Author{
    private:
        string name;
        int authorID;
    public:
    Author(string name, int authorID) : name(name), authorID(authorID) {}
    void display(){
        cout<<"Author Name: "<<name<<endl;
        cout<<"Author ID: "<<authorID<<endl;
    }
    ~Author(){
        cout<<"Author destroyed: "<<this->name<<endl;
    }
};

class Book{
    private:
        string title;
        Author *author;
    public:
        Book(string title, Author *author) : title(title), author(author) {}
        void display(){
            cout<<"Book Title: "<<title<<endl;
            author->display();
        }
        void addAuthor(Author *author){
            this->author = author;
        }
        ~Book(){
            cout<<"Book destroyed: "<<this->title<<endl;
        }
};

int main(){
    Author a1("John Doe", 1);
    Book b1("The Great Gatsby", &a1);
    b1.display();
    return 0;
}