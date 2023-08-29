#include <iostream>
#include <fstream>
using namespace std;

int main(){
    int n;
    cout << "How many books you wanna enter :";
    cin >> n;
    ofstream my;
    my.open("/Users/namangupta/Desktop/Library/Books.txt", ios::app);
    for(int i = 0;i < n; i++)
    {
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
        my << title << endl;
        my << author << endl;
        my << ISBN << endl;
        my << publicationDate << endl;
    }
    my.close();
}