#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

struct book
{
    int id, quantity, borrowed;
    string name;

    book()
    {
        id = -1, quantity = 0, borrowed = 0, name = "";
    }

    void add()
    {
        cout << "\n\nEnter Book ID : ";
        cin >> id;
        cout << "\n\nEnter Book Name : ";
        cin >> name;
        cout << "\n\nEnter Quantity : ";
        cin >> quantity;
    }

    void print()
    {
        cout << "id " << id << " name " << name << " totlat quantity " << quantity << " borrowed " << borrowed << endl;
    }

    bool prefix_check(string str)
    {
        if (str.size() > name.size())
            return false;
        for (int i = 0; i < (int)str.size(); i++)
        {

            if (str[i] != name[i])
                return false;
        }
        return true;
    }

    bool ability_to_borrow()
    {
        if (quantity - borrowed == 0)
            return false;
        borrowed++;
        return true;
    }

    void return_book()
    {
        borrowed--;
    }
};

bool compareById(book &b1, book &b2)
{
    return b1.id < b2.id;
}

bool compareByName(book &b1, book &b2)
{
    return b1.name < b2.name;
}

struct user
{
    int id, bookIds[10], total_id;
    string name;

    user()
    {
        id = -1, total_id = 0, name = "";
    }

    void add()
    {
        cout << " enter user name and id : ";
        cin >> name >> id;
    }

    void print()
    {
        cout << "user " << name << " id " << id;
        if (total_id != 0)
        {
            cout << "borrowed id : ";
            for (int i = 0; i < total_id; i++)
            {
                cout << bookIds[i] << " , ";
            }
            cout << endl;
        }
        else
            cout << " no borrowed books \n";
    }

    void borrowed(int book_id)
    {
        bookIds[total_id++] = book_id;
    }

    int is_borrowed(int id)
    {
        for (int i = 0; i < total_id; ++i)
        {
            if (bookIds[i] == id)
                return i;
        }
        return -1;
    }

    void return_id(int idx)
    {
        for (int i = idx; i < total_id - 1; i++)
        {
            bookIds[i] = bookIds[i + 1];
        }

        total_id--;
    }
};

struct library
{
    int total_book, total_user;
    book books[20];
    user users[20];

    library()
    {
        total_book = 0, total_user = 0;
    }

    void Whole()
    {

        while (true)
        {

            int pick = menu();

            if (pick == 1)
                add_book();
            if (pick == 2)
                search_book_by_prefix();
            if (pick == 3)
                print_who_borrowed();
            if (pick == 4)
                print_book_by_id();
            if (pick == 5)
                print_library_by_name();
            if (pick == 6)
                add_user();
            if (pick == 7)
                user_borrow();
            if (pick == 8)
                user_return();
            if (pick == 9)
                print_user();
            if (pick == 10)
            {
                cout << "\n\n\t\t\tThanks for visiting us";
                break;
            }
        }
    }

    int menu()
    {

        int pick = -1;

        while (pick == -1)
        {
            system("Color 0A");
            cout << "\n\n\t\t\t=========================================";
            cout << "\n\n\t\t\t===========  Library System  ============";
            cout << "\n\n\t\t\t=========================================";
            cout << "\n\n\t\t\tLibrary Menu";
            cout << "\n\n\t\t\t1) add book";
            cout << "\n\n\t\t\t2) search books by prefix";
            cout << "\n\n\t\t\t3) print who borrowed book by name";
            cout << "\n\n\t\t\t4) print library by id";
            cout << "\n\n\t\t\t5) print library by name";
            cout << "\n\n\t\t\t6) add user";
            cout << "\n\n\t\t\t7) user borrow book";
            cout << "\n\n\t\t\t8) user return book";
            cout << "\n\n\t\t\t9) print users";
            cout << "\n\n\t\t\t10) Exit";
            cout << "\n\n\t\t\tEnter Your Choice : ";
            cin >> pick;

            if (!(pick >= 1 && pick <= 10))
            {
                cout << "invalid chiose, please enter agian . ";
                pick = -1;
            }
        }
        return pick;
    }

    void add_book()
    {
        books[total_book++].add();
    }

    void print_book_by_id()
    {
        sort(books, books + total_book, compareById);
        for (int i = 0; i < total_book; ++i)
        {
            books[i].print();
        }
    }

    void print_library_by_name()
    {
        sort(books, books + total_book, compareByName);
        for (int i = 0; i < total_book; ++i)
        {

            books[i].print();
        }
    }

    void add_user()
    {
        users[total_user].add();
        total_user++;
    }

    void search_book_by_prefix()
    {
        cout << "Enter Book Name : ";
        string str;
        cin >> str;

        for (int i = 0; i < total_book; i++)
        {
            if (books[i].prefix_check(str))
            {
                cout << books[i].name << endl;
                break;
            }
        }
    }

    int find_user_index(string str_user)
    {

        for (int i = 0; i < total_user; ++i)
        {
            if (users[i].name == str_user)
                return i;
        }
        return -1;
    }

    int find_book_index(string str_book)
    {

        for (int i = 0; i < total_book; i++)
        {
            if (books[i].name == str_book)
                return i;
        }
        return -1;
    }

    void user_borrow()
    {

        string str_user, str_book;
        cin >> str_user >> str_book;
        int ibook = find_book_index(str_book), iuser = find_user_index(str_user);

        if (ibook == -1)
            cout << "invalid book \n";

        if (iuser == -1)
            cout << "invalid user \n";
        else if (!(books[ibook].ability_to_borrow()))
            cout << "no coppies are available \n";
        else
        {
            users[iuser].borrowed(books[ibook].id);
        }
    }

    void print_user()
    {

        for (int i = 0; i < total_user; i++)
        {
            users[i].print();
        }
    }

    void print_who_borrowed()
    {

        string str;
        cout << "enter name book : ";
        cin >> str;
        int ibook = find_book_index(str);
        int idBook = books[ibook].id;
        if (ibook == -1)
            cout << "invalid book \n";
        else
        {

            for (int i = 0; i < total_user; i++)
            {
                if (users[i].is_borrowed(idBook) != -1)
                    cout << users[i].name << endl;
            }
        }
    }

    void user_return()
    {
        string str_user, str_book;
        cout << "enter user name and book name : ";
        cin >> str_user >> str_book;

        int id_book = find_book_index(str_book), id_user = find_user_index(str_user);

        if (id_book == -1)
            cout << "invalid book \n";
        if (id_user == -1)
            cout << "invalid user \n";
        int indx = users[id_user].is_borrowed(books[id_book].id);
        if (indx == -1)
            cout << "This guy didn't buy this book \n";

        else
        {
            users[id_user].return_id(indx);
            books[id_book].return_book();
        }
    }
};

int main()
{
    library lib;
    lib.Whole();

    return 0;
}