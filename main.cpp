#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

class Book {
private:
    string title, author, type, location;
    bool isAvailable;
public:
    string getTitle() {
        return title;
    }

    string getAuthor() {
        return author;
    }

    bool getIsAvailable(){
        return isAvailable;
    }

    void rentBook(){
        this->isAvailable = false;
    }

    Book()  { this->isAvailable = true; }

    Book(string title, string author, string type, string location, bool isAvailable = true){
        this->title = title;
        this->author = author;
        this->type = type;
        this->location = location;
        this->isAvailable = isAvailable;
    }

    friend istream& operator>>(ifstream &in, Book &b) {
        return in >> b.title >> b.author >> b.type >> b.location >> b.isAvailable;
    }

    friend ostream& operator<<(ostream &out, const Book &b) {
        return out << b.title << " " << b.author << " " << b.type << " " << b.location << " " << b.isAvailable;
    }
};

vector<Book> readBooksFromDb(string filename);
void writeBooksToDb(const vector<Book>& books, const string& filename);

void addBook(vector<Book>& books);
void rentBook(vector<Book>& books);
void displayBooks(const vector<Book>& books);
void findBooks(const vector<Book>& books);

int main(int argc, char *argv[]) {
    if(argc < 2){
        cout<<"Not enough arguments!";
        return 1;
    }
    string filename = argv[1];
    vector<Book> books = readBooksFromDb(filename);

    int choice;
    do {
        cout << "1. Add Book\n2. Rent Book\n3. Display All Books\n4. Find Book\n5. Exit\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addBook(books);
                break;
            case 2:
                rentBook(books);
                break;
            case 3:
                displayBooks(books);
                break;
            case 4:
                findBooks(books);
                break;
            case 5:
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);

    writeBooksToDb(books, filename);

    return 0;
}

vector<Book> readBooksFromDb(string filename){
    ifstream db(filename);
    vector<Book> books;
    Book b;

    while (db >> b) {
        books.push_back(b);
    }

    db.close();
    return books;
}

void writeBooksToDb(const vector<Book>& books, const string& filename) {
    ofstream db(filename);
    for (const auto& book : books) {
        db << book << endl;
    }
    db.close();
}

void addBook(vector<Book>& books) {
    string title, author, type, location;
    cout << "Enter title: ";
    cin >> title;
    cout << "Enter author: ";
    cin >> author;
    cout << "Enter type: ";
    cin >> type;
    cout << "Enter location: ";
    cin >> location;

    Book b(title, author, type, location);
    books.push_back(b);
}

void rentBook(vector<Book>& books) {
    string title;
    cout << "Enter the title of the book to rent: ";
    cin >> title;
    for (auto& book : books) {
        if (book.getTitle() == title && book.getIsAvailable()) {
            book.rentBook();
            cout << "Book rented." << endl;
            return;
        }
    }
    cout << "Book not available or not found." << endl;
}

void displayBooks(const vector<Book>& books) {
    for (const auto& book : books) {
        cout << book << endl;
    }
}

void findBooks(const vector<Book>& books) {
    string searchQuery;
    cout << "Enter author or title to search: ";
    cin >> searchQuery;

    bool found = false;
    for (auto book : books) {
        if (book.getTitle() == searchQuery || book.getAuthor() == searchQuery) {
            cout << book << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "No books found matching the query." << endl;
    }
}