#include <iostream>
#include <vector>
#include <list>
#include <array>
#include <memory>

#include "Book.h"

using namespace std;

int main()
{
    try
    {
        Book
            b1(235378, "Hamlet", "W. Shakespeare", {1,2,3}, Book::GenreE::lexicon),  /* not really a lexicon */
            b2(135779, "Don Quixote", "Miguel de Cervantes", {4,7,8,9,9,5,4,4,4,4,9}, Book::GenreE::novel),
            b3(135779, "Picture album of NY", {"James O'Ryan", "Joseph T. Eckstein", "Juliana Jones"}, {2,4,5,4,}, Book::GenreE::album),
            b4(278339, "Othello", "W. Shakespeare", {1,2,7,5}, Book::GenreE::novel),
            b5(789435, "Good Peter Quince", {"Juliana Jones", "W. Shakespeare", "Leon Uris"}, {7,5,8,8,1,3,5}, Book::GenreE::biography),
            b6(135788, "Don Quixote", "Miguel de Cervantes", {4,7,8,9,9,5,4,4,4,4,9}, Book::GenreE::novel); // The library has 2 copies

        cout<<"Data set (book list):"<<endl;
        b1.printBookInfo();
        b2.printBookInfo();
        b3.printBookInfo();
        b4.printBookInfo();
        b5.printBookInfo();
        cout<<endl<<endl;

        cout<<"Comparison operators demo:"<<endl;
        cout<<"Hamelt == Othello ?          "<< (b1 == b4) <<endl;
        cout<<"Hamelt == Hamlet  ?          "<< (b1 == b1) <<endl;
        cout<<"Hamelt != Othello ?          "<< (b1 != b4) <<endl;
        cout<<"Don Quixote == Don Quixote ? "<< (b2 == b6) <<endl;
        cout<<endl<<endl;

        cout<<"Checkout and return demo (Hamlet): "<<endl;
        if (b1.checkOutBook("John Smith"))
        {
            cout<<"Checked out:"<<endl;
            b1.printBookInfo();
        }
        else
        {
            cout<<"Book couldn't be checked out"<<endl;
            b1.printBookInfo();
        }

        if (b1.checkOutBook("James Camera"))
        {
            cout<<"Checked out:"<<endl;
            b1.printBookInfo();
        }
        else
        {
            cout<<"Book couldn't be checked out"<<endl;
            b1.printBookInfo();
        }

        ushort overdue = b1.returnBook();
        cout<<"Book returned"<<endl;
        b1.printBookInfo();
        if (overdue)
        {
            cout<<"Late by "<<overdue<<" days!!"<<endl;
        }
        
        if (b1.checkOutBook("James Camera"))
        {
            cout<<"Checked out:"<<endl;
            b1.printBookInfo();
        }
        else
        {
            cout<<"Book couldn't be checked out"<<endl;
            b1.printBookInfo();
        }
        cout<<endl<<endl;

        cout<<"Print all books by a given atuhor: "<<endl;
        vector<Book> bookList;
        bookList.push_back(std::move(b1));  // since not copyable, the books must be moved
        bookList.push_back(std::move(b2));
        bookList.push_back(std::move(b3));
        bookList.push_back(std::move(b5));
        bookList.push_back(std::move(b4));
        bookList.push_back(std::move(b6));

        Book::printByAuthor("Juliana Jones", bookList);
        cout<<endl<<endl<<endl;
        Book::printByAuthor("W. Shakespeare", bookList);
        cout<<endl<<endl<<endl;
        Book::printByAuthor("Miguel de Cervantes", bookList);
        cout<<endl<<endl<<endl;
        Book::printByAuthor("W. Faulkner", bookList);
        cout<<endl<<endl;

        cout<<"Faulty book initialization demo: "<<endl;
        Book bFaultyInit(657183, "Die Leiden des jungen Werther", "", {2,5,3,4,0,7,3,6,9,3,3,2,1}, Book::GenreE::novel);
    }
    catch (const std::invalid_argument e)
    {
        cerr << e.what() << endl;
    }

    return 0;
}