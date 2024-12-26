#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>
#include <ctime>

using namespace std;

struct Book
{
    string title;
    string author;
    string isbn;
    bool isAvailable;

    Book(string t, string a, string i) : title(t), author(a), isbn(i), isAvailable(true) {}
};

struct Transaction
{
    string borrowerName;
    string isbn;
    time_t checkoutDate;
    time_t dueDate;
    bool isReturned;

    Transaction(string name, string bookISBN, int loanPeriodDays)
        : borrowerName(name), isbn(bookISBN), isReturned(false)
    {
        time(&checkoutDate);
        dueDate = checkoutDate + loanPeriodDays * 86400;
    }
};

vector<Book> books;
vector<Transaction> transactions;

void displayMenu();
void addBook();
void searchBook();
void checkoutBook();
void returnBook();
void calculateFine(Transaction &transaction);
void displayBooks();
Book *findBookByISBN(const string &isbn);

int main()
{
    int choice;
    cout << "===== Welcome to Library Management System =====" << endl;

    do
    {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice)
        {
        case 1:
            addBook();
            break;
        case 2:
            searchBook();
            break;
        case 3:
            checkoutBook();
            break;
        case 4:
            returnBook();
            break;
        case 5:
            displayBooks();
            break;
        case 6:
            cout << "Exiting the system. Have a great day!" << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 6);

    return 0;
}

void displayMenu()
{
    cout << "\n===== Library Menu =====" << endl;
    cout << "1. Add a New Book" << endl;
    cout << "2. Search for a Book" << endl;
    cout << "3. Check Out a Book" << endl;
    cout << "4. Return a Book" << endl;
    cout << "5. Display All Books" << endl;
    cout << "6. Exit" << endl;
}

void addBook()
{
    string title, author, isbn;
    cout << "Enter book title: ";
    getline(cin, title);
    cout << "Enter author name: ";
    getline(cin, author);
    cout << "Enter ISBN: ";
    getline(cin, isbn);

    books.push_back(Book(title, author, isbn));
    cout << "Book added successfully!" << endl;
}

void searchBook()
{
    int searchChoice;
    string query;

    cout << "Search by: 1. Title  2. Author  3. ISBN" << endl;
    cout << "Enter choice: ";
    cin >> searchChoice;
    cin.ignore();

    cout << "Enter search query: ";
    getline(cin, query);

    cout << "\nSearch Results:" << endl;
    bool found = false;

    for (const Book &book : books)
    {
        if ((searchChoice == 1 && book.title == query) ||
            (searchChoice == 2 && book.author == query) ||
            (searchChoice == 3 && book.isbn == query))
        {
            cout << "Title: " << book.title
                 << ", Author: " << book.author
                 << ", ISBN: " << book.isbn
                 << ", Availability: " << (book.isAvailable ? "Available" : "Checked Out")
                 << endl;
            found = true;
        }
    }

    if (!found)
        cout << "No books found matching your query." << endl;
}

void displayBooks()
{
    if (books.empty())
    {
        cout << "No books in the library yet!" << endl;
        return;
    }

    cout << "\n===== Book List =====" << endl;
    for (const Book &book : books)
    {
        cout << "Title: " << book.title
             << ", Author: " << book.author
             << ", ISBN: " << book.isbn
             << ", Availability: " << (book.isAvailable ? "Available" : "Checked Out")
             << endl;
    }
}

void checkoutBook()
{
    string isbn, borrowerName;
    cout << "Enter ISBN of the book to check out: ";
    getline(cin, isbn);

    Book *book = findBookByISBN(isbn);
    if (book && book->isAvailable)
    {
        cout << "Enter borrower's name: ";
        getline(cin, borrowerName);

        transactions.push_back(Transaction(borrowerName, isbn, 14));
        book->isAvailable = false;
        cout << "Book checked out successfully for 14 days!" << endl;
    }
    else
    {
        cout << "Book not found or not available!" << endl;
    }
}

void returnBook()
{
    string isbn;
    cout << "Enter ISBN of the book to return: ";
    getline(cin, isbn);

    for (Transaction &transaction : transactions)
    {
        if (transaction.isbn == isbn && !transaction.isReturned)
        {
            transaction.isReturned = true;
            Book *book = findBookByISBN(isbn);
            if (book)
                book->isAvailable = true;

            calculateFine(transaction);
            return;
        }
    }

    cout << "No such transaction found!" << endl;
}

void calculateFine(Transaction &transaction)
{
    time_t now;
    time(&now);

    double overdueDays = difftime(now, transaction.dueDate) / 86400.0;

    if (overdueDays > 0)
    {
        double fine = overdueDays * 1.0;
        cout << "Book returned late. Overdue days: " << (int)overdueDays
             << ". Fine: $" << fixed << setprecision(2) << fine << endl;
    }
    else
    {
        cout << "Book returned on time. No fine!" << endl;
    }
}

Book *findBookByISBN(const string &isbn)
{
    for (Book &book : books)
    {
        if (book.isbn == isbn)
        {
            return &book;
        }
    }
    return nullptr;
}
