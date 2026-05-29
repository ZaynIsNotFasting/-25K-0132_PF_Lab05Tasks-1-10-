#include "iostream"
using namespace std;

class Book {
    private:
        const int ISBN;
        string title;
    public:
        Book(const int ISBN, string title) : ISBN(ISBN), title(title) {}

        void displayDetails() const{
            cout<<"ISBN: "<<ISBN<<endl;
            cout<<"Title of Book: "<<title<<endl;
        }

        void updateTitle(const string newTitle){
            title = newTitle;
            cout<<"Book Title is now: "<<title<<endl;
        }

};

int main()
{
    cout<<"Without const"<<endl;
    Book b1(6942067, "Copywriting masterclass by tomsonic");
    b1.displayDetails();
    b1.updateTitle("The Subtle Art of Not Giving a F*ck");
    b1.displayDetails();

    cout<<"\nWith const"<<endl;

    const Book b2(89824898, "Reality transurfing");
    b2.displayDetails();
    // b2.updateTitle("How not to have a bad day");
    // b2.displayDetails();
    return 0;
}
