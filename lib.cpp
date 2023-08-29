#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <stdlib.h>
using namespace std;

class Book {
private:
    string title, author, ISBN, publicationDate, user;
    bool checkedOut;
public:
    Book(string title, string author, string ISBN, string publicationDate) {
        this->title = title;
        this->author = author;
        this->ISBN = ISBN;
        this->publicationDate = publicationDate;
        this->checkedOut = false;
        this->user = "";
    }

    string getTitle() {
        return title;
    }

    string getAuthor() {
        return author;
    }

    string getISBN() {
        return ISBN;
    }

    string getPublicationDate() {
        return publicationDate;
    }

    string getUser() {
        return user;
    }

    bool isCheckedOut() {
        return checkedOut;
    }

    void setCheckedOut(bool checkedOut) {
        this->checkedOut = checkedOut;
    }

    void setUser(string user) {
        this->user = user;
    }
};

class Library {
public:
    vector<Book> books;
    string adminUsername, adminPassword;
    vector< vector<string> > users;

    Library(string adminUsername, string adminPassword) {
        this->adminUsername = adminUsername;
        this->adminPassword = adminPassword;
        importAllBooks();
    }

    void importAllBooks() {
        ifstream my;
        my.open("/Users/namangupta/Desktop/Library/Books.txt");
        string title, author, ISBN, publicationDate;
        while (getline(my, title)) {
            getline(my, author);
            getline(my, ISBN);
            getline(my, publicationDate);
            Book book(title, author, ISBN, publicationDate);
            addBook(book);
        }
    }

    bool checkUser(string& user, string& password) {
        for(int i = 0; i < users.size(); i++){
            if(users[i][0] == user && users[i][1] == password)
                return true;
        }
        return false;
    }

    bool checkUser(string& user) {
        for(int i = 0; i < users.size(); i++){
            if(users[i][0] == user)
                return true;
        }
        return false;
    }

    bool addUser(string& username, string& password) {
        vector<string> s;
        if(checkUser(username) == true)
            return false;
        s.push_back(username);
        s.push_back(password);
        users.push_back(s);
        return true;
    }

    bool removeUser(string& username) {
        for(int i = 0; i < users.size(); i++) {
            if(users[i][0] == username){
                users.erase(users.begin() + i);
                return true;
            }
        }
        return false;
    }

    void displayAllUsers() {
        cout << endl;
        for(int i = 0; i < users.size(); i++) {
            cout << "Username : " << users[i][0] << endl;
            cout << "Password : " << users[i][1] << endl;
            cout << endl;
        }
        if(users.size() == 0)
            cout << "No users in the system.";
    }

    void addBook(Book book) {
        books.push_back(book);
    }

    void borrowBook(string ISBN, string user) {
        for (int i = 0; i < books.size(); i++) {
            if (books[i].getISBN() == ISBN) {
                if (!books[i].isCheckedOut()) {
                    books[i].setCheckedOut(true);
                    books[i].setUser(user);
                    cout << "Book checked out successfully!" << endl;
                } else {
                    cout << "Book is already checked out!" << endl;
                }
                return;
            }
        }
        cout << "Book not found" << endl;
    }

    void returnBook(string ISBN) {
        for (int i = 0; i < books.size();i++){
            if (books[i].getISBN() == ISBN) {
                if (books[i].isCheckedOut()) {
                    books[i].setCheckedOut(false);
                    books[i].setUser("");
                    cout << "Book returned successfully!" << endl;
                } else {
                    cout << "Book is already in the library." << endl;
                }
                return;
            }
        }
        cout << "Book not found!" << endl;
    }

    void searchBook(string title) {
        for (int i = 0; i < books.size(); i++) {
            if (books[i].getTitle() == title || books[i].getISBN() == title || books[i].getAuthor() == title) {
                cout << "Title: " << books[i].getTitle() << endl;
                cout << "Author: " << books[i].getAuthor() << endl;
                cout << "ISBN: " << books[i].getISBN() << endl;
                cout << "Publication Date: " << books[i].getPublicationDate() << endl;
                if (books[i].isCheckedOut()) {
                    cout << "Status: Checked Out" << endl;
                } else {
                    cout << "Status: Available" << endl;
                }
                return;
            }
        }
        cout << "Book not found" << endl;
    }

    void displayAllBooks() {
        cout << endl;
        for (int i = 0; i < books.size(); i++) {
            cout << "Title: " << books[i].getTitle() << endl;
            cout << "Author: " << books[i].getAuthor() << endl;
            cout << "ISBN: " << books[i].getISBN() << endl;
            cout << "Publication Date: " << books[i].getPublicationDate() << endl;
            if (books[i].isCheckedOut()) {
                cout << "Status: Checked Out" << endl;
            } else {
                cout << "Status: Available" << endl;
            }
            cout << endl;
        }
    }

    void borrowedBook(string user) {
        cout << endl;
        int count = 0;
        for (int i = 0; i < books.size(); i++) {
            if(books[i].getUser() != user)
                continue;
            cout << "Title: " << books[i].getTitle() << endl;
            cout << "Author: " << books[i].getAuthor() << endl;
            cout << "ISBN: " << books[i].getISBN() << endl;
            cout << "Publication Date: " << books[i].getPublicationDate() << endl;
            cout << endl;
            count++;
        }
        if(count == 0)
            cout << "No books issued under this username." << endl;
        else 
            cout << "Total " << count << " books are issued under this user." << endl;
    }
};

int main() {
    Library library("admin", "password");

    while (true) {
        system("clear");
        string username, password;
        cout<<"Enter username :";
        getline(cin,username);
        cout<<"Enter password :";
        getline(cin,password);
        if (username == library.adminUsername && password == library.adminPassword) {
            // User has entered correct admin credentials

            while (true) {
                system("clear");
                cout << "Welcome, administrator. What would you like to do?" << endl;
                cout << "1. Add a book" << endl;
                cout << "2. Display all books" << endl;
                cout << "3. Add a user" << endl;
                cout << "4. Remove a user" << endl;
                cout << "5. Display all users" << endl;
                cout << "6. Books issued by a user" << endl;
                cout << "7. Log out" << endl;
                int choice;
                cout<<"Enter your choice :";
                cin>>choice;

                if (choice == 1) {
                    // Administrator wants to add a book
                    string title, author, ISBN, publicationDate;
                    cin.ignore();
                    cout << "Enter title: ";
                    getline(cin, title);
                    cout << "Enter author: ";
                    getline(cin, author);
                    cout << "Enter ISBN: ";
                    getline(cin, ISBN);
                    cout << "Enter publication date: ";
                    getline(cin, publicationDate);
                    Book book(title, author, ISBN, publicationDate);
                    library.addBook(book);
                    cout << "Book added successfully!" << endl;
                    getchar();

                } else if (choice == 2) {
                    // Administrator wants to display all books
                    library.displayAllBooks();
                    cout << flush;
                    getchar();
                    getchar();

                } else if (choice == 3) {
                    // Administrator wants to add a User
                    string user,pass;
                    cin.ignore();
                    cout << "Enter credintials of the user to be added:"  << endl;
                    cout << "Username:";
                    getline(cin,user);
                    cout << "Password:";
                    getline(cin,pass);
                    if(library.addUser(user,pass))
                        cout << "User added successfully!" << endl;
                    else
                        cout << "User already exists!" << endl;
                    getchar();

                } else if (choice == 4) {
                    // Administrator wants to remove a User
                    string user;
                    cin.ignore();
                    cout << "Enter credintials of the user to be removed:"  << endl;
                    cout << "Username:";
                    getline(cin,user);
                    if(library.removeUser(user))
                        cout << "User removed successfully!" << endl;
                    else
                        cout << "User doesn't exists!" << endl;
                    getchar();

                } else if (choice == 5) {
                    // Administrator wants to diaplay all Users
                    library.displayAllUsers();
                    getchar();
                    getchar();

                } else if (choice == 6) {
                    // Administrator wants a list of a user's borrowed books
                    string user;
                    cin.ignore();
                    cout << "Enter credintials of the user to be removed:"  << flush << endl;
                    cout << "Username:";
                    getline(cin,user);
                    if(library.checkUser(user) == true)
                        library.borrowedBook(user);
                    else
                        cout << "Not a valid username";
                    getchar();

                } else if (choice == 7) {
                    // Administrator wants to log out
                    cin.ignore();
                    break;

                } else {
                    cout << "Invalid choice. Please enter a valid option." << endl;
                    getchar();
                }
            }

        } else {
            // Now check if the user is a user
            if (library.checkUser(username, password)) {
                // User has entered correct user credentials
                while (true) {
                    system("clear");
                    cout << "Welcome, " << username << ". What would you like to do?" << endl;
                    cout << "1. Search for a book" << endl;
                    cout << "2. Borrow a book" << endl;
                    cout << "3. Return a book" << endl;
                    cout << "4. Borrowed books" << endl;
                    cout << "5. Display all books" << endl;
                    cout << "6. Log out"  <<endl;
                    cout<<"Enter your choice : ";
                    int choice;
                    cin>>choice;
                    cin.ignore();

                    if (choice == 1) {
                        // User wants to search for a book
                        string searchTerm;
                        cout << "Enter search term: ";
                        getline(cin, searchTerm);
                        library.searchBook(searchTerm);
                        getchar();

                    } else if (choice == 2) {
                        // User wants to borrow a book
                        string ISBN;
                        cout << "Enter ISBN of book to borrow: ";
                        getline(cin, ISBN);
                        library.borrowBook(ISBN,username);
                        getchar();

                    } else if (choice == 3) {
                        // User wants to return a book
                        string ISBN;
                        cout << "Enter ISBN of book to return: ";
                        getline(cin, ISBN);
                        library.returnBook(ISBN);
                        getchar();

                    } else if (choice == 4) {
                        // User wants a list of his borrowed books
                        library.borrowedBook(username);
                        getchar();

                    } else if (choice == 5) {
                        // User wants to display all books
                        library.displayAllBooks();
                        cout << flush;
                        getchar();
                        getchar();

                    } else if (choice == 6) {
                        // User wants to log out
                        cin.ignore();
                        break;

                    } else {
                        cout << "Invalid choice. Please enter a valid option." << endl;
                        getchar();
                    }
                }

            } else {
                cout << "Incorrect username or password. Please try again." << endl;
                getchar();
            }
        }
    }
    return 0;
}