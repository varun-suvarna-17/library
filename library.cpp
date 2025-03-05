#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

struct Book {
    string title;
    string author;
    string isbn;
    bool isAvailable;
};

// Function to read books from file
vector<Book> readBooksFromFile(const string& filename) {
    vector<Book> books;
    ifstream file(filename);
    if (!file) return books; // If file doesn't exist, return empty list

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        Book book;
        string availability;
        getline(ss, book.title, ',');
        getline(ss, book.author, ',');
        getline(ss, book.isbn, ',');
        getline(ss, availability, ',');
        book.isAvailable = (availability == "1");
        books.push_back(book);
    }
    file.close();
    return books;
}

// Function to write books to file
void writeBooksToFile(const string& filename, const vector<Book>& books) {
    ofstream file(filename);
    for (const auto& book : books) {
        file << book.title << "," << book.author << "," << book.isbn << "," 
             << (book.isAvailable ? "1" : "0") << endl;
    }
    file.close();
}

// Function to add a new book
void addBook(const string& filename) {
    Book book;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, book.title);
    cout << "Enter author name: ";
    getline(cin, book.author);
    cout << "Enter ISBN: ";
    getline(cin, book.isbn);
    book.isAvailable = true;

    vector<Book> books = readBooksFromFile(filename);
    books.push_back(book);
    writeBooksToFile(filename, books);
    cout << "Book added successfully!\n";
}

// Function to borrow a book
void borrowBook(const string& filename) {
    vector<Book> books = readBooksFromFile(filename);
    string isbn;
    cout << "Enter ISBN of the book to borrow: ";
    cin >> isbn;

    for (auto& book : books) {
        if (book.isbn == isbn) {
            if (book.isAvailable) {
                book.isAvailable = false;
                writeBooksToFile(filename, books);
                cout << "Book borrowed successfully!\n";
                return;
            } else {
                cout << "Book is already borrowed!\n";
                return;
            }
        }
    }
    cout << "Book not found!\n";
}

// Function to return a book
void returnBook(const string& filename) {
    vector<Book> books = readBooksFromFile(filename);
    string isbn;
    cout << "Enter ISBN of the book to return: ";
    cin >> isbn;

    for (auto& book : books) {
        if (book.isbn == isbn) {
            if (!book.isAvailable) {
                book.isAvailable = true;
                writeBooksToFile(filename, books);
                cout << "Book returned successfully!\n";
                return;
            } else {
                cout << "Book is already available in the library!\n";
                return;
            }
        }
    }
    cout << "Book not found!\n";
}

// Function to display all books
void displayBooks(const string& filename) {
    vector<Book> books = readBooksFromFile(filename);
    if (books.empty()) {
        cout << "No books available!\n";
        return;
    }

    cout << "\nList of Books:\n";
    cout << "-----------------------------------------\n";
    for (const auto& book : books) {
        cout << "Title: " << book.title << "\n";
        cout << "Author: " << book.author << "\n";
        cout << "ISBN: " << book.isbn << "\n";
        cout << "Availability: " << (book.isAvailable ? "Available" : "Borrowed") << "\n";
        cout << "-----------------------------------------\n";
    }
}

int main() {
    string filename = "books.txt";
    int choice;
    do {
        cout << "\nBook Management System\n";
        cout << "1. Add Book\n";
        cout << "2. Borrow Book\n";
        cout << "3. Return Book\n";
        cout << "4. Display Books\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addBook(filename); break;
            case 2: borrowBook(filename); break;
            case 3: returnBook(filename); break;
            case 4: displayBooks(filename); break;
            case 5: cout << "Exiting program...\n"; break;
            default: cout << "Invalid choice, try again.\n";
        }
    } while (choice != 5);

    return 0;
}