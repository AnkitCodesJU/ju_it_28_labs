#include <iostream>
#include <string>
using namespace std;

const int MAX_AUTHORS = 5;

class Book {
private:
        string isbn;
        string title;
        string authors[MAX_AUTHORS];
        int authorCount;
        double price;

public:
        Book() : isbn(""), title(""), authorCount(0), price(0.0) {}

        Book(const string& isbn_, const string& title_, const string authors_[], int count, double price_)
                : isbn(isbn_), title(title_), authorCount(count), price(price_) {
                for (int i = 0; i < authorCount && i < MAX_AUTHORS; i++) {
                        authors[i] = authors_[i];
                }
        }

        string getISBN() const { return isbn; }
        string getTitle() const { return title; }
        int getAuthorCount() const { return authorCount; }

        string getAuthor(int index) const {
                if (index >= 0 && index < authorCount)
                        return authors[index];
                else
                        return "";
        }

        double getPrice() const { return price; }
};

class BookStore {
private:
        Book* bookList;
        int* copies;      
        int numBooks;
        int capacity;

        int findBookIndexByISBN(const string& isbn) const {
                for (int i = 0; i < numBooks; i++) {
                        if (bookList[i].getISBN() == isbn)
                                return i;
                }
                return -1;
        }

        void resize() {
                int newCapacity = capacity * 2;
                Book* newBookList = new Book[newCapacity];
                int* newCopies = new int[newCapacity];

                for (int i = 0; i < numBooks; i++) {
                        newBookList[i] = bookList[i];
                        newCopies[i] = copies[i];
                }

                delete[] bookList;
                delete[] copies;

                bookList = newBookList;
                copies = newCopies;
                capacity = newCapacity;
        }

public:
        BookStore(int initialCapacity = 10) {
                capacity = initialCapacity;
                numBooks = 0;
                bookList = new Book[capacity];
                copies = new int[capacity];
        }

        ~BookStore() {
                delete[] bookList;
                delete[] copies;
        }

        void addBook(const Book& book, const int& count) {
                int idx = findBookIndexByISBN(book.getISBN());
                if (idx == -1) {
                        if (numBooks == capacity)
                                resize();

                        bookList[numBooks] = book;
                        copies[numBooks] = count;
                        numBooks++;
                } else {
                        copies[idx] += count;
                }
        }

        void getUniqueISBNs(string uniqueISBNs[], int& count) const {
                count = numBooks;
                for (int i = 0; i < numBooks; i++) {
                        uniqueISBNs[i] = bookList[i].getISBN();
                }
        }

        int noOfCopies(const string& isbn) const {
                int idx = findBookIndexByISBN(isbn);
                if (idx == -1)
                        return 0;
                return copies[idx];
        }

        double totalPrice() const {
                double total = 0.0;
                for (int i = 0; i < numBooks; i++) {
                        total += copies[i] * bookList[i].getPrice();
                }
                return total;
        }

        string getTitleByISBN(const string& isbn) const {
                int idx = findBookIndexByISBN(isbn);
                if (idx == -1)
                        return "";
                return bookList[idx].getTitle();
        }

        void display() const {
                for (int i = 0; i < numBooks; i++) {
                        cout << "Title: " << bookList[i].getTitle()
                             << ", ISBN: " << bookList[i].getISBN()
                             << ", Copies: " << copies[i] << endl;
                }
        }
};

int main() {
        BookStore store;

        string authors1[] = {"Author A"};
        Book b1("ISBN001", "Book One", authors1, 1, 200.0);
        store.addBook(b1, 3);

        string authors2[] = {"Author B", "Author C"};
        Book b2("ISBN002", "Book Two", authors2, 2, 350.0);
        store.addBook(b2, 2);

        string authors3[] = {"Author D"};
        Book b3("ISBN003", "Book Three", authors3, 1, 150.0);
        store.addBook(b3, 5);

        store.display();

        cout << "Total price of all books in store: " << store.totalPrice() << endl;

        return 0;
}

