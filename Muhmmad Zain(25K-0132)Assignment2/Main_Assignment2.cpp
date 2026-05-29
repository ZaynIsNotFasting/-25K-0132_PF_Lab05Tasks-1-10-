#include <iostream>
#include <cmath>
#include <string>

using namespace std;

class Vehicle;
class Account;
class Message;
class Review;
class Listing;
class Seller;
class Buyer;
class Admin;
class InspectionReport;
class Marketplace;

class IDisplayable
{
public:
    virtual void displayDetails() const = 0;
    virtual ~IDisplayable() {}
};

class ISearchable
{
public:
    virtual bool matchesQuery(const string &keyword) const = 0;
    virtual ~ISearchable() {}
};

class IReportable
{
public:
    virtual void generateReport() const = 0;
    virtual ~IReportable() {}
};

class IVerifiable
{
public:
    virtual bool verify() const = 0;
    virtual ~IVerifiable() {}
};

class Vehicle : public IDisplayable, public ISearchable
{
    string brand;
    string model;
    int year;
    int mileage;
    string colour;
    string transmission;

public:
    Vehicle() : brand(""), model(""), year(0), mileage(0), colour(""), transmission("") {}

    Vehicle(string brand, string model, int year, int mileage, string colour, string transmission)
    {
        this->brand = brand;
        this->model = model;
        this->year = year;
        this->mileage = mileage;
        this->colour = colour;
        this->transmission = transmission;
    }

    void displayDetails() const override
    {
        cout << "Brand: " << brand << endl;
        cout << "Model: " << model << endl;
        cout << "Year: " << year << endl;
        cout << "Mileage: " << mileage << " km" << endl;
        cout << "Colour: " << colour << endl;
        cout << "Transmission: " << transmission << endl;
    }

    bool matchesQuery(const string &keyword) const override
    {
        return (brand == keyword || model == keyword);
    }

    bool isEligibleForInspection() const { return (year > 2014 && mileage < 150000); }
    void updateMileage(int newMileage) { mileage = newMileage; }
    void updateColour(string newColour) { colour = newColour; }

    string getBrand() const { return brand; }
    string getModel() const { return model; }
    int getYear() const { return year; }
    int getMileage() const { return mileage; }
    string getColour() const { return colour; }
    string getTransmission() const { return transmission; }

    bool operator==(const Vehicle &other) const
    {
        return (brand == other.brand && model == other.model && year == other.year);
    }

    friend ostream &operator<<(ostream &out, const Vehicle &v)
    {
        out << v.year << " " << v.brand << " " << v.model
            << " (" << v.transmission << ", " << v.mileage << " km, " << v.colour << ")";
        return out;
    }

    friend istream &operator>>(istream &in, Vehicle &v)
    {
        cout << "  Enter brand: ";
        in >> v.brand;
        cout << "  Enter model: ";
        in >> v.model;
        cout << "  Enter year: ";
        in >> v.year;
        cout << "  Enter mileage: ";
        in >> v.mileage;
        cout << "  Enter colour: ";
        in >> v.colour;
        cout << "  Enter transmission: ";
        in >> v.transmission;
        return in;
    }
};

class Message : public IDisplayable
{
    int messageId;
    Account *sender;
    Account *receiver;
    string content;
    string timestamp;
    bool isRead;

public:
    static int totalMessages;

    Message(Account *from, Account *to, string text)
    {
        this->messageId = totalMessages++;
        this->sender = from;
        this->receiver = to;
        this->content = text;
        this->timestamp = "01/01/1970 00:00 PKT";
        this->isRead = false;
    }

    void markAsRead() { isRead = true; }
    void editContent(string newContent) { content = newContent + " (Edited)"; }
    bool getReadStatus() const { return isRead; }
    int getMessageId() const { return messageId; }
    string getContent() const { return content; }

    void displayDetails() const override { displayMessage(); }

    void displayMessage() const
    {
        cout << "\n--- Message #" << messageId << " ---" << endl;
        cout << "Date: " << timestamp << (isRead ? " [Read]" : " [Unread]") << endl;
        cout << "Message: " << content << endl;
        cout << "-------------------" << endl;
    }

    bool operator==(const Message &other) const
    {
        return (content == other.content);
    }

    friend ostream &operator<<(ostream &out, const Message &m)
    {
        out << "[Msg#" << m.messageId << "] " << m.content
            << (m.isRead ? " [Read]" : " [Unread]");
        return out;
    }
};

class Review : public IDisplayable
{
private:
    int reviewId;
    Account *reviewer;
    Account *reviewee;
    double rating;
    string comment;
    int helpfulVotes;

public:
    static int totalReviews;

    Review(Account *from, Account *to, double stars, string text)
    {
        this->reviewId = totalReviews++;
        this->reviewer = from;
        this->reviewee = to;
        this->rating = max(1.0, min(stars, 5.0));

        if (stars < 1.0 || stars > 5.0)
            cout << "Invalid rating. Must be 1–5. Defaulting to 3 stars." << endl;

        this->comment = text;
        this->helpfulVotes = 0;
    }

    void addHelpfulVote() { helpfulVotes++; }
    void updateComment(string newText) { comment = newText; }
    double getRating() const { return rating; }

    void displayDetails() const override { displayReview(); }

    void displayReview() const
    {
        cout << "\n[User Review #" << reviewId << "]" << endl;
        cout << "Rating: " << rating << "/5.0 Stars" << endl;
        cout << "Comment: \"" << comment << "\"" << endl;
        cout << "Helpful Votes: " << helpfulVotes << endl;
    }

    bool operator==(const Review &other) const
    {
        return (rating == other.rating && comment == other.comment);
    }

    bool operator>(const Review &other) const
    {
        return rating > other.rating;
    }

    bool operator<(const Review &other) const
    {
        return rating < other.rating;
    }

    friend ostream &operator<<(ostream &out, const Review &r)
    {
        out << "Review#" << r.reviewId << " | " << r.rating << "/5 | \"" << r.comment << "\"";
        return out;
    }
};

class Account : public IDisplayable, public IVerifiable
{
protected:
    string email;
    string encryptedpassword;
    string phone;
    string firstName;
    string lastName;
    char gender;
    string dob;
    int accountId;
    bool isBanned;
    Message **inbox;
    int messageCount;
    string memberSince;
    bool emailVerified;

public:
    static int totalAccountsCreated;

    Account() : email(""), encryptedpassword(""), phone(""), firstName(""),
                lastName(""), gender('U'), dob(""), accountId(0), isBanned(false),
                inbox(nullptr), messageCount(0), memberSince("1/1/1970"), emailVerified(false) {}

    Account(string email, string firstName, string lastName, string phone, char gender, string dob)
    {
        this->email = email;
        this->firstName = firstName;
        this->lastName = lastName;
        this->phone = phone;
        this->gender = gender;
        this->dob = dob;
        this->isBanned = false;
        this->accountId = totalAccountsCreated++;
        this->inbox = nullptr;
        this->messageCount = 0;
        this->memberSince = "1/1/1970";
        this->emailVerified = false;
    }

    Account(const Account &other)
    {
        email = other.email;
        encryptedpassword = other.encryptedpassword;
        phone = other.phone;
        firstName = other.firstName;
        lastName = other.lastName;
        gender = other.gender;
        dob = other.dob;
        accountId = totalAccountsCreated++;
        isBanned = other.isBanned;
        messageCount = other.messageCount;

        if (other.messageCount > 0)
        {
            inbox = new Message *[other.messageCount];
            for (int i = 0; i < other.messageCount; i++)
                inbox[i] = other.inbox[i];
        }
        else
            inbox = nullptr;
    }

    Account &operator=(const Account &other)
    {
        if (this == &other)
            return *this;
        delete[] inbox;

        email = other.email;
        encryptedpassword = other.encryptedpassword;
        phone = other.phone;
        firstName = other.firstName;
        lastName = other.lastName;
        gender = other.gender;
        dob = other.dob;
        isBanned = other.isBanned;
        messageCount = other.messageCount;

        if (other.messageCount > 0)
        {
            inbox = new Message *[other.messageCount];
            for (int i = 0; i < other.messageCount; i++)
                inbox[i] = other.inbox[i];
        }
        else
            inbox = nullptr;

        return *this;
    }

    string encryptPassword(string rawpassword)
    {
        string encrypted = "";
        for (char c : rawpassword)
            encrypted += char(c + 3);
        return encrypted;
    }

    bool authenticate(string inputEmail, string inputPassword)
    {
        return (inputEmail == email && encryptPassword(inputPassword) == encryptedpassword);
    }

    void updateContact(string newPhone) { phone = newPhone; }

    void verifyEmail()
    {
        cout << "Are you Human? (Y/N): ";
        char response;
        cin >> response;
        if (response == 'Y' || response == 'y')
        {
            emailVerified = true;
            cout << "Email verified!" << endl;
        }
        else
            cout << "Verification failed." << endl;
    }

    void resetPassword(string oldPassword, string newPassword)
    {
        if (authenticate(email, oldPassword))
        {
            setPassword(newPassword);
            cout << "Password reset successful!" << endl;
        }
        else
            cout << "Incorrect current password." << endl;
    }

    void setPassword(string password) { encryptedpassword = encryptPassword(password); }
    void setBannedStatus(bool status) { isBanned = status; }
    bool getIsBanned() const { return isBanned; }
    int getAccountId() const { return accountId; }
    string getFirstName() const { return firstName; }
    string getLastName() const { return lastName; }
    string getEmail() const { return email; }

    bool verify() const override
    {
        return (emailVerified && !isBanned);
    }

    virtual void displayDetails() const override
    {
        cout << "Logged in as: " << endl;
        cout << firstName << " " << lastName << endl;
        cout << "ID: " << accountId << endl;
        cout << "Email: " << email << endl;
        cout << "Phone: " << phone << endl;
    }

    void receiveMessage(Message *incomingMsg)
    {
        Message **temp = new Message *[messageCount + 1];
        for (int i = 0; i < messageCount; i++)
            temp[i] = inbox[i];
        temp[messageCount] = incomingMsg;
        delete[] inbox;
        inbox = temp;
        messageCount++;
        cout << "Notification for " << firstName << ": New message! (Total: " << messageCount << ")" << endl;
    }

    bool operator==(const Account &other) const
    {
        return (accountId == other.accountId);
    }

    friend ostream &operator<<(ostream &out, const Account &a)
    {
        out << "[Account#" << a.accountId << "] " << a.firstName << " " << a.lastName
            << " <" << a.email << ">";
        return out;
    }

    friend void compareSellerRatings(const Seller &s1, const Seller &s2);

    virtual ~Account() { delete[] inbox; }
};

class Listing : public IDisplayable, public ISearchable
{
private:
    int listingId;
    double price;
    string location;
    string description;
    Account *seller;
    string status;
    Vehicle car;

public:
    static int totalListings;

    Listing() : listingId(0), price(0), location(""),
                description(""), seller(nullptr), status("Pending"), car(Vehicle()) {}

    Listing(double price, string location, string description, Account *seller, const Vehicle &v) : car(v)
    {
        this->listingId = totalListings++;
        this->price = price;
        this->location = location;
        this->description = description;
        this->seller = seller;
        this->status = "Pending";
    }

    void approve() { status = "Active"; }
    void forceRemove() { status = "Removed by admin"; }

    virtual void displayDetails() const override
    {
        cout << "\n====================" << endl;
        cout << "Listing#" << listingId << endl;
        cout << "====================" << endl;
        if (seller != nullptr)
            seller->displayDetails();
        cout << "Price: PKR " << price << endl;
        cout << "Location: " << location << endl;
        cout << "Description: " << description << endl;
        cout << "Status: " << status << endl;
        cout << "Vehicle Details:" << endl;
        car.displayDetails();
    }

    bool matchesQuery(const string &keyword) const override
    {
        return (car.matchesQuery(keyword) || location == keyword);
    }

    void updatePrice(double newPrice) { price = newPrice; }

    void toggleStatus()
    {
        if (status == "Active")
            status = "Sold";
        else
            status = "Active";
    }

    void calculateInstallment(double downPaymentPercent, int years, double annualInterestRate) const
    {
        double principal = price * (1 - (downPaymentPercent / 100));
        double monthlyRate = annualInterestRate / 12 / 100;
        int months = years * 12;

        if (monthlyRate == 0)
        {
            cout << "Invalid interest rate." << endl;
            return;
        }

        double emi = (principal * monthlyRate * pow(1 + monthlyRate, months)) /
                     (pow(1 + monthlyRate, months) - 1);

        cout << "\n--- Financing Estimate ---" << endl;
        cout << "Down Payment: PKR " << price * (downPaymentPercent / 100) << endl;
        cout << "Financed Amount: PKR " << principal << endl;
        cout << "Monthly Installment: PKR " << emi << " for " << months << " months" << endl;
    }

    int getListingId() const { return listingId; }
    const Vehicle &getVehicle() const { return car; }
    double getPrice() const { return price; }
    string getLocation() const { return location; }
    Account *getSeller() const { return seller; }
    string getStatus() const { return status; }
    bool operator==(const Listing &other) const
    {
        return (listingId == other.listingId);
    }

    bool operator<(const Listing &other) const
    {
        return (price < other.price);
    }

    bool operator>(const Listing &other) const
    {
        return (price > other.price);
    }
    double operator+(const Listing &other) const
    {
        return (price + other.price);
    }

    friend ostream &operator<<(ostream &out, const Listing &l)
    {
        out << "Listing#" << l.listingId << " | " << l.car << " | PKR " << l.price
            << " | " << l.location << " | Status: " << l.status;
        return out;
    }

    friend istream &operator>>(istream &in, Listing &l)
    {
        cout << "  Enter price: ";
        in >> l.price;
        cout << "  Enter location: ";
        in >> l.location;
        cout << "  Enter description: ";
        in.ignore();
        getline(in, l.description);
        return in;
    }
    friend class Marketplace;
    friend void comparePrices(const Listing &a, const Listing &b);
};

class Seller : public Account
{
    double sellerRating;
    int totalSales;
    string city;
    string preferredContactMethod;
    int totalListings;
    int activeListings;
    string memberSince;
    bool verified;
    int messages;
    Review **reviews;
    int reviewCount;

public:
    Seller(string email, string firstName, string lastName, string phone,
           char gender, string dob, string city, string preferredContactMethod, int messages)
        : Account(email, firstName, lastName, phone, gender, dob)
    {
        this->city = city;
        this->preferredContactMethod = preferredContactMethod;
        this->sellerRating = 5.0;
        this->totalSales = 0;
        this->totalListings = 0;
        this->activeListings = 0;
        this->memberSince = "1/1/1970";
        this->verified = false;
        this->messages = 0;
        this->reviews = nullptr;
        this->reviewCount = 0;
    }

    Seller(const Seller &other) : Account(other)
    {
        sellerRating = other.sellerRating;
        totalSales = other.totalSales;
        city = other.city;
        preferredContactMethod = other.preferredContactMethod;
        totalListings = other.totalListings;
        activeListings = other.activeListings;
        memberSince = other.memberSince;
        verified = other.verified;
        messages = other.messages;
        reviewCount = other.reviewCount;

        if (other.reviewCount > 0)
        {
            reviews = new Review *[other.reviewCount];
            for (int i = 0; i < other.reviewCount; i++)
                reviews[i] = other.reviews[i];
        }
        else
            reviews = nullptr;
    }

    Seller &operator=(const Seller &other)
    {
        if (this == &other)
            return *this;
        Account::operator=(other);
        delete[] reviews;

        sellerRating = other.sellerRating;
        totalSales = other.totalSales;
        city = other.city;
        preferredContactMethod = other.preferredContactMethod;
        totalListings = other.totalListings;
        activeListings = other.activeListings;
        memberSince = other.memberSince;
        verified = other.verified;
        messages = other.messages;
        reviewCount = other.reviewCount;

        if (other.reviewCount > 0)
        {
            reviews = new Review *[other.reviewCount];
            for (int i = 0; i < other.reviewCount; i++)
                reviews[i] = other.reviews[i];
        }
        else
            reviews = nullptr;
        return *this;
    }

    void updateSellerRating(double newRating) { sellerRating = newRating; }
    void incrementSales() { totalSales++; }
    void incrementListings()
    {
        totalListings++;
        activeListings++;
    }
    void applyForVerification() { verified = true; }
    void decrementActiveListings()
    {
        if (activeListings > 0)
            activeListings--;
    }
    double getSellerRating() const { return sellerRating; }
    string getCity() const { return city; }

    bool verify() const override
    {
        return verified;
    }

    void displayDetails() const override
    {
        cout << firstName << " " << lastName << endl;
        cout << "ID: " << accountId << endl;
        cout << "Email: " << email << endl;
        cout << "Phone: " << phone << endl;
        cout << "Seller Rating: " << sellerRating << "/5" << endl;
        cout << "Total Sales: " << totalSales << endl;
        cout << "City: " << city << endl;
        cout << "Preferred Contact: " << preferredContactMethod << endl;
        cout << "Verified: " << (verified ? "Yes" : "No") << endl;
    }

    void addReview(Review *newReview)
    {
        Review **temp = new Review *[reviewCount + 1];
        for (int i = 0; i < reviewCount; i++)
            temp[i] = reviews[i];
        temp[reviewCount] = newReview;
        delete[] reviews;
        reviews = temp;
        reviewCount++;

        double totalScore = 0;
        for (int i = 0; i < reviewCount; i++)
            totalScore += reviews[i]->getRating();
        sellerRating = totalScore / reviewCount;

        cout << "Review added for " << firstName << ". Rating: " << sellerRating << "/5.0" << endl;
    }

    void displayReviews() const
    {
        cout << "\n--- Seller Reviews ---" << endl;
        if (reviewCount == 0)
        {
            cout << "No reviews yet." << endl;
            return;
        }
        for (int i = 0; i < reviewCount; i++)
        {
            reviews[i]->displayReview();
            cout << "--------------------" << endl;
        }
    }

    bool operator==(const Seller &other) const
    {
        return (accountId == other.accountId);
    }

    bool operator>(const Seller &other) const
    {
        return sellerRating > other.sellerRating;
    }

    bool operator<(const Seller &other) const
    {
        return sellerRating < other.sellerRating;
    }

    friend ostream &operator<<(ostream &out, const Seller &s)
    {
        out << "[Seller] " << s.firstName << " " << s.lastName
            << " | Rating: " << s.sellerRating << "/5 | City: " << s.city;
        return out;
    }

    friend void compareSellerRatings(const Seller &s1, const Seller &s2);

    ~Seller()
    {
        for (int i = 0; i < reviewCount; i++)
            delete reviews[i];
        delete[] reviews;
    }
};

class Buyer : public Account
{
    Listing **favourites;
    int favouritesT;
    string city;
    int messages;
    string memberSince;
    bool verified;

public:
    Buyer(string email, string firstName, string lastName, string phone,
          char gender, string dob, int favourites, string city, int messages)
        : Account(email, firstName, lastName, phone, gender, dob)
    {
        this->favourites = nullptr;
        this->favouritesT = 0;
        this->city = city;
        this->messages = 0;
        this->memberSince = "1/1/1970";
        this->verified = false;
    }

    Buyer(const Buyer &other) : Account(other)
    {
        city = other.city;
        messages = other.messages;
        memberSince = other.memberSince;
        verified = other.verified;
        favouritesT = other.favouritesT;

        if (other.favouritesT > 0)
        {
            favourites = new Listing *[other.favouritesT];
            for (int i = 0; i < other.favouritesT; i++)
                favourites[i] = other.favourites[i];
        }
        else
            favourites = nullptr;
    }

    Buyer &operator=(const Buyer &other)
    {
        if (this == &other)
            return *this;
        Account::operator=(other);
        delete[] favourites;

        city = other.city;
        messages = other.messages;
        memberSince = other.memberSince;
        verified = other.verified;
        favouritesT = other.favouritesT;

        if (other.favouritesT > 0)
        {
            favourites = new Listing *[other.favouritesT];
            for (int i = 0; i < other.favouritesT; i++)
                favourites[i] = other.favourites[i];
        }
        else
            favourites = nullptr;
        return *this;
    }

    void addToFavourites(Listing **listing)
    {
        Listing **temp = new Listing *[favouritesT + 1];
        for (int i = 0; i < favouritesT; i++)
            temp[i] = favourites[i];
        temp[favouritesT] = *listing;
        delete[] favourites;
        favourites = temp;
        favouritesT++;
    }

    void removeFromFavourites(int listingId)
    {
        int removeId = -1;
        for (int i = 0; i < favouritesT; i++)
            if (favourites[i]->getListingId() == listingId)
            {
                removeId = i;
                break;
            }

        if (removeId == -1)
        {
            cout << "Listing not found in favourites." << endl;
            return;
        }

        Listing **temp = new Listing *[favouritesT - 1];
        int j = 0;
        for (int i = 0; i < favouritesT; i++)
        {
            if (i == removeId)
                continue;
            temp[j++] = favourites[i];
        }
        delete[] favourites;
        favourites = temp;
        favouritesT--;
    }

    void applyForVerification() { verified = true; }
    string getCity() const { return city; }

    bool verify() const override { return verified; }

    void displayFavourites() const
    {
        cout << "Favourite Listings:" << endl;
        if (favouritesT == 0)
        {
            cout << "No favourite listings yet." << endl;
            return;
        }
        for (int i = 0; i < favouritesT; i++)
        {
            favourites[i]->displayDetails();
            cout << "--------------------" << endl;
        }
    }

    void displayDetails() const override
    {
        cout << firstName << " " << lastName << endl;
        cout << "ID: " << accountId << endl;
        cout << "Email: " << email << endl;
        cout << "Phone: " << phone << endl;
        cout << "City: " << city << endl;
        cout << "Member Since: " << memberSince << endl;
        cout << "Verified: " << (verified ? "Yes" : "No") << endl;
    }

    bool operator==(const Buyer &other) const
    {
        return (accountId == other.accountId);
    }

    int operator+(const Buyer &other) const
    {
        return (favouritesT + other.favouritesT);
    }

    friend ostream &operator<<(ostream &out, const Buyer &b)
    {
        out << "[Buyer] " << b.firstName << " " << b.lastName
            << " | City: " << b.city << " | Favourites: " << b.favouritesT;
        return out;
    }

    ~Buyer() { delete[] favourites; }
};

class Admin : public Account
{
    int adminLevel;
    string department;
    int actionsTaken;
    string officeLocation;
    string shift;
    bool canManageAdmins;

public:
    Admin(string email, string firstName, string lastName, string phone,
          char gender, string dob, int level, string dept)
        : Account(email, firstName, lastName, phone, gender, dob)
    {
        this->adminLevel = level;
        this->department = dept;
        this->actionsTaken = 0;
        this->officeLocation = "Karachi HQ";
        this->shift = "Standard";
        this->canManageAdmins = (level == 2);
    }

    void approveListing(Listing *ad)
    {
        if (ad != nullptr)
        {
            ad->approve();
            actionsTaken++;
            cout << "Admin " << firstName << " approved listing." << endl;
        }
    }

    void removeListing(Listing *ad)
    {
        if (ad != nullptr)
        {
            ad->forceRemove();
            actionsTaken++;
            cout << "Admin " << firstName << " removed listing." << endl;
        }
    }

    void banUserAccount(Account *user)
    {
        if (user != nullptr)
        {
            user->setBannedStatus(true);
            actionsTaken++;
            cout << "USER BANNED. Action logged." << endl;
        }
    }

    int getAdminLevel() const { return adminLevel; }
    int getActionsTaken() const { return actionsTaken; }
    string getDepartment() const { return department; }

    bool verify() const override { return !isBanned; }

    void displayDetails() const override
    {
        cout << "\n[ADMINISTRATOR PROFILE]" << endl;
        cout << "Name: " << firstName << " " << lastName << endl;
        cout << "Department: " << department << " | Level: " << adminLevel << endl;
        cout << "Actions Taken: " << actionsTaken << endl;
        cout << "Can Manage Admins: " << (canManageAdmins ? "Yes" : "No") << endl;
    }

    bool operator==(const Admin &other) const
    {
        return (accountId == other.accountId);
    }

    bool operator>(const Admin &other) const
    {
        return (actionsTaken > other.actionsTaken);
    }

    friend ostream &operator<<(ostream &out, const Admin &a)
    {
        out << "[Admin] " << a.firstName << " " << a.lastName
            << " | Level: " << a.adminLevel << " | Dept: " << a.department;
        return out;
    }
};

class Car : public Vehicle
{
    int doors;
    string fuelType;
    int engineCC;

public:
    Car() : Vehicle(), doors(4), fuelType("Petrol"), engineCC(1000) {}

    Car(string brand, string model, int year, int mileage,
        string colour, string transmission,
        int doors, string fuelType, int engineCC)
        : Vehicle(brand, model, year, mileage, colour, transmission)
    {
        this->doors = doors;
        this->fuelType = fuelType;
        this->engineCC = engineCC;
    }

    void displayDetails() const override
    {
        cout << "--- Car Details ---" << endl;
        Vehicle::displayDetails();
        cout << "Doors: " << doors << endl;
        cout << "Fuel Type: " << fuelType << endl;
        cout << "Engine: " << engineCC << " cc" << endl;
    }

    int getDoors() const { return doors; }
    string getFuelType() const { return fuelType; }
    int getEngineCC() const { return engineCC; }

    bool operator==(const Car &other) const
    {
        return (getBrand() == other.getBrand() &&
                getModel() == other.getModel() &&
                engineCC == other.engineCC);
    }

    friend ostream &operator<<(ostream &out, const Car &c)
    {
        out << "[Car] " << c.getYear() << " " << c.getBrand() << " " << c.getModel()
            << " | " << c.engineCC << "cc | " << c.fuelType << " | " << c.doors << " doors";
        return out;
    }
};

class Bike : public Vehicle
{
    string bikeType;
    bool hasFairing;
    int engineCC;

public:
    Bike() : Vehicle(), bikeType("Standard"), hasFairing(false), engineCC(125) {}

    Bike(string brand, string model, int year, int mileage,
         string colour, string transmission,
         string bikeType, bool hasFairing, int engineCC)
        : Vehicle(brand, model, year, mileage, colour, transmission)
    {
        this->bikeType = bikeType;
        this->hasFairing = hasFairing;
        this->engineCC = engineCC;
    }

    void displayDetails() const override
    {
        cout << "--- Bike Details ---" << endl;
        Vehicle::displayDetails();
        cout << "Type: " << bikeType << endl;
        cout << "Engine: " << engineCC << " cc" << endl;
        cout << "Fairing: " << (hasFairing ? "Yes" : "No") << endl;
    }

    string getBikeType() const { return bikeType; }
    int getEngineCC() const { return engineCC; }

    bool operator==(const Bike &other) const
    {
        return (getBrand() == other.getBrand() &&
                getModel() == other.getModel() &&
                engineCC == other.engineCC);
    }

    friend ostream &operator<<(ostream &out, const Bike &b)
    {
        out << "[Bike] " << b.getYear() << " " << b.getBrand() << " " << b.getModel()
            << " | " << b.engineCC << "cc | " << b.bikeType;
        return out;
    }
};

class InspectionReport : public IReportable, public IDisplayable
{
private:
    int reportId;
    Vehicle *inspectedCar;
    int engineScore;
    int exteriorScore;
    int interiorScore;
    int suspensionScore;
    string inspectorRemarks;
    string inspectionDate;

public:
    static int totalReports;

    InspectionReport(Vehicle *car, int engine, int exterior,
                     int interior, int suspension, string remarks)
    {
        this->reportId = totalReports++;
        this->inspectedCar = car;
        this->engineScore = engine;
        this->exteriorScore = exterior;
        this->interiorScore = interior;
        this->suspensionScore = suspension;
        this->inspectorRemarks = remarks;
        this->inspectionDate = "01/01/1970";
    }

    double getOverallScore() const
    {
        return (engineScore + exteriorScore + interiorScore + suspensionScore) / 4.0;
    }

    bool isCertified() const
    {
        return (getOverallScore() >= 80.0 && engineScore >= 85);
    }

    void updateRemarks(string newRemarks) { inspectorRemarks = newRemarks; }

    void generateReport() const override { displayReport(); }

    void displayDetails() const override { displayReport(); }

    void displayReport() const
    {
        cout << "\n=======================================" << endl;
        cout << "  PAKWHEELS 200+ POINT INSPECTION" << endl;
        cout << "=======================================" << endl;
        cout << "Report ID: " << reportId << " | Date: " << inspectionDate << endl;

        if (inspectedCar != nullptr)
        {
            cout << "Vehicle: ";
            inspectedCar->displayDetails();
        }

        cout << "\n--- SCORES ---" << endl;
        cout << "Engine & Transmission: " << engineScore << "/100" << endl;
        cout << "Exterior & Body:       " << exteriorScore << "/100" << endl;
        cout << "Interior:              " << interiorScore << "/100" << endl;
        cout << "Suspension & Steering: " << suspensionScore << "/100" << endl;
        cout << "\nOverall Score: " << getOverallScore() << "/100" << endl;

        if (isCertified())
            cout << "*** OFFICIAL PAKWHEELS CERTIFIED ***" << endl;

        cout << "Inspector Remarks: " << inspectorRemarks << endl;
        cout << "=======================================\n"
             << endl;
    }

    bool operator==(const InspectionReport &other) const
    {
        return (getOverallScore() == other.getOverallScore());
    }

    bool operator>(const InspectionReport &other) const
    {
        return (getOverallScore() > other.getOverallScore());
    }

    bool operator<(const InspectionReport &other) const
    {
        return (getOverallScore() < other.getOverallScore());
    }

    friend ostream &operator<<(ostream &out, const InspectionReport &r)
    {
        out << "Report#" << r.reportId
            << " | Score: " << r.getOverallScore() << "/100"
            << (r.isCertified() ? " [CERTIFIED]" : " [NOT CERTIFIED]");
        return out;
    }
};

void comparePrices(const Listing &a, const Listing &b)
{
    cout << "\n--- Price Comparison ---" << endl;
    cout << "Listing #" << a.listingId << ": PKR " << a.price << endl;
    cout << "Listing #" << b.listingId << ": PKR " << b.price << endl;

    if (a.price < b.price)
        cout << "Listing #" << a.listingId << " is cheaper by PKR " << (b.price - a.price) << endl;
    else if (b.price < a.price)
        cout << "Listing #" << b.listingId << " is cheaper by PKR " << (a.price - b.price) << endl;
    else
        cout << "Both listings are priced the same." << endl;
}

void compareSellerRatings(const Seller &s1, const Seller &s2)
{
    cout << "\n--- Seller Rating Comparison ---" << endl;
    cout << s1.firstName << ": " << s1.sellerRating << "/5" << endl;
    cout << s2.firstName << ": " << s2.sellerRating << "/5" << endl;

    if (s1.sellerRating > s2.sellerRating)
        cout << s1.firstName << " has the higher rating." << endl;
    else if (s2.sellerRating > s1.sellerRating)
        cout << s2.firstName << " has the higher rating." << endl;
    else
        cout << "Both sellers have the same rating." << endl;
}

class Marketplace : public IReportable
{
    Account **users;
    int userCount;
    Listing **listings;
    int listingCount;

public:
    const string PLATFORM_NAME = "PakWheels";
    const int MAX_LISTINGS_PER_USER = 10;

    Marketplace() : users(nullptr), userCount(0), listings(nullptr), listingCount(0) {}

    Marketplace(const Marketplace &) = delete;

    void registerAccount(Account *newAccount)
    {
        Account **temp = new Account *[userCount + 1];
        for (int i = 0; i < userCount; i++)
            temp[i] = users[i];
        temp[userCount] = newAccount;
        delete[] users;
        users = temp;
        userCount++;
    }

    void postListing(Listing *newListing)
    {
        if (newListing == nullptr || newListing->getSeller() == nullptr)
        {
            cout << "Invalid listing." << endl;
            return;
        }

        int sellerListings = 0;
        int targetId = newListing->getSeller()->getAccountId();
        for (int i = 0; i < listingCount; i++)
            if (listings[i]->getSeller()->getAccountId() == targetId)
                sellerListings++;

        if (sellerListings >= MAX_LISTINGS_PER_USER)
        {
            cout << "Maximum listings reached (" << MAX_LISTINGS_PER_USER << ")." << endl;
            return;
        }

        Listing **temp = new Listing *[listingCount + 1];
        for (int i = 0; i < listingCount; i++)
            temp[i] = listings[i];
        temp[listingCount] = newListing;
        delete[] listings;
        listings = temp;
        listingCount++;
        cout << "Listing posted to " << PLATFORM_NAME << "!" << endl;
    }

    void removeListing(int listingId)
    {
        int removeId = -1;
        for (int i = 0; i < listingCount; i++)
            if (listings[i]->getListingId() == listingId)
            {
                removeId = i;
                break;
            }

        if (removeId == -1)
        {
            cout << "Listing not found." << endl;
            return;
        }

        Listing **temp = new Listing *[listingCount - 1];
        int j = 0;
        for (int i = 0; i < listingCount; i++)
        {
            if (i == removeId)
            {
                delete listings[i];
                continue;
            }
            temp[j++] = listings[i];
        }
        delete[] listings;
        listings = temp;
        listingCount--;
    }

    void searchListings(string brand)
    {
        cout << "Search results for brand: " << brand << endl;
        for (int i = 0; i < listingCount; i++)
            if (listings[i]->getVehicle().getBrand() == brand)
            {
                listings[i]->displayDetails();
                cout << "--------------------" << endl;
            }
    }

    void filterSearchResults(double minPrice = -1, double maxPrice = 1000000000,
                             string model = "", string location = "",
                             int year = -1, int mileage = -1)
    {
        int matchCount = 0;
        for (int i = 0; i < listingCount; i++)
        {
            Listing *current = listings[i];
            bool isMatch = true;

            if (minPrice != -1 && current->getPrice() < minPrice)
                isMatch = false;
            if (maxPrice != -1 && current->getPrice() > maxPrice)
                isMatch = false;
            if (location != "" && current->getLocation() != location)
                isMatch = false;

            const Vehicle &v = current->getVehicle();
            if (model != "" && v.getModel() != model)
                isMatch = false;
            if (year != -1 && v.getYear() < year)
                isMatch = false;
            if (mileage != -1 && v.getMileage() > mileage)
                isMatch = false;

            if (isMatch && current->getListingId() != -1)
            {
                current->displayDetails();
                matchCount++;
            }
        }

        if (matchCount == 0)
            cout << "No listings matched your criteria." << endl;
        else
            cout << "Total matches: " << matchCount << endl;
    }

    Listing **getListings() { return listings; }
    int getListingCount() { return listingCount; }

    void generateReport() const override
    {
        cout << "\n========================================" << endl;
        cout << "  " << PLATFORM_NAME << " PLATFORM REPORT" << endl;
        cout << "========================================" << endl;
        cout << "Total Users:    " << userCount << endl;
        cout << "Total Listings: " << listingCount << endl;
        cout << "========================================\n"
             << endl;
    }

    Marketplace &operator+(Listing *newListing)
    {
        postListing(newListing);
        return *this;
    }

    friend ostream &operator<<(ostream &out, const Marketplace &mp)
    {
        out << "[" << mp.PLATFORM_NAME << "] Users: " << mp.userCount
            << " | Listings: " << mp.listingCount;
        return out;
    }

    ~Marketplace()
    {
        if (users != nullptr)
        {
            for (int i = 0; i < userCount; i++)
                delete users[i];
            delete[] users;
        }
        if (listings != nullptr)
        {
            for (int i = 0; i < listingCount; i++)
                delete listings[i];
            delete[] listings;
        }
    }
};

int Account::totalAccountsCreated = 0;
int Listing::totalListings = 0;
int InspectionReport::totalReports = 0;
int Message::totalMessages = 0;
int Review::totalReviews = 0;

int main()
{
    cout << "============================================" << endl;
    cout << "  Car Marketplace System Assignment 2" << endl;
    cout << "  Muhammad Taha | 25K-0937" << endl;
    cout << "============================================\n"
         << endl;

    cout << "=== INHERITANCE ===" << endl;

    Seller *seller1 = new Seller("ali@gmail.com", "Ali", "Khan", "03001234567",
                                 'M', "01/01/1990", "Lahore", "WhatsApp", 0);
    Seller *seller2 = new Seller("hassan@gmail.com", "Hassan", "Raza", "03119876543",
                                 'M', "05/05/1985", "Karachi", "Phone", 0);

    Buyer *buyer1 = new Buyer("sara@gmail.com", "Sara", "Ahmed", "03331122334",
                              'F', "10/10/1995", 0, "Islamabad", 0);

    Admin *admin1 = new Admin("admin@pakwheels.com", "Admin", "One", "0300000000",
                              'M', "01/01/1980", 1, "Trust & Safety");

    seller1->setPassword("pass123");
    buyer1->setPassword("buypass");
    admin1->setPassword("adminpass");

    cout << "Registered: Seller Ali, Seller Hassan, Buyer Sara, Admin One" << endl;

    Car car1("Toyota", "Corolla", 2020, 45000, "White", "Automatic", 4, "Petrol", 1800);
    Car car2("Honda", "Civic", 2019, 60000, "Black", "Manual", 4, "Petrol", 1500);
    Bike bike1("Suzuki", "GS150", 2022, 12000, "Red", "Manual", "Standard", false, 150);

    cout << car1 << endl;
    cout << car2 << endl;
    cout << bike1 << endl;

    cout << "\n=== POLYMORPHISM ===" << endl;

    Account *users[3] = {seller1, buyer1, admin1};
    string roles[3] = {"Seller", "Buyer", "Admin"};

    for (int i = 0; i < 3; i++)
    {
        cout << "--- " << roles[i] << " ---" << endl;
        users[i]->displayDetails();
        cout << endl;
    }

    Vehicle *vehicles[2] = {&car1, &bike1};
    for (int i = 0; i < 2; i++)
    {
        vehicles[i]->displayDetails();
        cout << endl;
    }

    cout << "\n=== ABSTRACTION ===" << endl;

    IVerifiable *verifiables[3] = {seller1, buyer1, admin1};
    string vNames[3] = {"Seller Ali", "Buyer Sara", "Admin One"};

    for (int i = 0; i < 3; i++)
        cout << vNames[i] << " verified: " << (verifiables[i]->verify() ? "YES" : "NO") << endl;

    seller1->applyForVerification();
    buyer1->applyForVerification();
    cout << "\nAfter applying for verification:" << endl;
    for (int i = 0; i < 2; i++)
        cout << vNames[i] << " verified: " << (verifiables[i]->verify() ? "YES" : "NO") << endl;

    Vehicle plainCar("Honda", "City", 2021, 30000, "Blue", "Automatic");
    InspectionReport report1(&plainCar, 88, 90, 85, 87, "Excellent condition");

    IReportable *rep = &report1;
    rep->generateReport();

    Marketplace marketplace;
    marketplace.registerAccount(seller1);
    marketplace.registerAccount(seller2);
    marketplace.registerAccount(buyer1);
    marketplace.registerAccount(admin1);

    cout << "\n=== OPERATOR OVERLOADING ===" << endl;

    Vehicle v1("Toyota", "Corolla", 2020, 45000, "White", "Automatic");
    Vehicle v2("Toyota", "Corolla", 2020, 50000, "Black", "Manual");
    Vehicle v3("Honda", "Civic", 2019, 60000, "Black", "Manual");
    cout << "v1 == v2 (same brand/model/year): " << (v1 == v2 ? "YES" : "NO") << endl;
    cout << "v1 == v3 (different): " << (v1 == v3 ? "YES" : "NO") << endl;
    cout << "v1 via <<: " << v1 << endl;

    Listing *listing1 = new Listing(3500000, "Lahore", "Low mileage Toyota", seller1, car1);
    Listing *listing2 = new Listing(2800000, "Karachi", "Well maintained Honda", seller2, car2);

    marketplace.postListing(listing1);
    marketplace.postListing(listing2);

    cout << *listing1 << endl;
    cout << *listing2 << endl;

    if (*listing1 > *listing2)
        cout << "Listing1 is more expensive." << endl;
    else
        cout << "Listing2 is more expensive." << endl;

    cout << "Bundle price: PKR " << (*listing1 + *listing2) << endl;

    cout << "listing1 == listing2: " << (*listing1 == *listing2 ? "YES" : "NO") << endl;

    Review *rev1 = new Review(buyer1, seller1, 4.5, "Great seller!");
    Review *rev2 = new Review(buyer1, seller2, 3.0, "Average experience.");
    seller1->addReview(rev1);
    seller2->addReview(rev2);

    cout << *seller1 << endl;
    cout << *seller2 << endl;

    if (*seller1 > *seller2)
        cout << seller1->getFirstName() << " has higher rating." << endl;
    else
        cout << seller2->getFirstName() << " has higher rating." << endl;

    cout << *admin1 << endl;

    admin1->approveListing(listing1);
    admin1->approveListing(listing2);

    Listing **lp1 = &listing1;
    buyer1->addToFavourites(lp1);
    cout << *buyer1 << endl;

    cout << *rev1 << endl;
    cout << *rev2 << endl;
    if (*rev1 > *rev2)
        cout << "Review1 is higher rated." << endl;

    InspectionReport report2(&plainCar, 70, 75, 72, 68, "Needs maintenance");
    cout << report1 << endl;
    cout << report2 << endl;
    cout << "report1 > report2: " << (report1 > report2 ? "YES" : "NO") << endl;

    Listing *listing3 = new Listing(800000, "Lahore", "Suzuki bike good condition", seller1, bike1);
    marketplace + listing3;

    cout << marketplace << endl;

    cout << "\n=== FRIEND FUNCTIONS ===" << endl;

    comparePrices(*listing1, *listing2);
    compareSellerRatings(*seller1, *seller2);

    cout << "\n=== MESSAGING ===" << endl;
    Message *msg1 = new Message(buyer1, seller1, "Is the Toyota still available?");
    seller1->receiveMessage(msg1);
    msg1->displayMessage();

    cout << "\n=== SEARCH & FILTER ===" << endl;
    marketplace.searchListings("Toyota");
    marketplace.filterSearchResults(2000000, 4000000, "", "Lahore");

    cout << "\n=== MARKETPLACE REPORT ===" << endl;
    IReportable *mpReport = &marketplace;
    mpReport->generateReport();

    // msg1 is not owned by Marketplace that is why I am deleting it manually.
    delete msg1;

    return 0;
}
