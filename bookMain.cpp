#include <iostream>
#include <vector>
#include <array>

#include "Book.h"

using namespace std;

int main()
{
    array<ushort, Book::isbnSize> 
        arr1 = {1,2,3},
        arr2 = {4,7,8,9,9,5,4,4,4,4,},
        arr3 = {2,4,5,4,},
        arr4 = {1,2,7,5},
        arr5 = {7,5,8,8,1,3,5};
    vector<string> authors3 = {"James O'Ryan", "Joseph T. Eckstein", "Juliana Jones"};
    Book b1(235378, "Hamlet", "W. Shakespeare", arr1, Book::GenreE::lexicon),  /* not really an lexicon */
         b2(135779, "Don Quixote", "Miguel de Cervantes", arr2, Book::GenreE::novel),
         b3(135779, "Picture album of NY", {"James O'Ryan", "Joseph T. Eckstein", "Juliana Jones"}, arr2, Book::GenreE::album),
         b4(278339, "Othello", "W. Shakespeare", arr4, Book::GenreE::novel),
         b5(789435, "Good Peter Quince", {"Juliana Jones", "W. Shakespeare", "Leon Uris"}, arr5, Book::GenreE::biography);
    
    b1.printBookInfo();
    b2.printBookInfo();
    b3.printBookInfo();
    b4.printBookInfo();
    b5.printBookInfo();
    
    if (b1.checkOutBook("John Smith"))
    {
        b1.printBookInfo();
    }
    else
    {
        cout<<"Book couldn't be checked out"<<endl;
    }
    if(b1.checkOutBook("James Camera"))
    {
        b1.printBookInfo();
    }
    else
    {
        cout<<"Book couldn't be checked out"<<endl;
        b1.printBookInfo();
        
    }
    cout<<"Late by "<<b1.returnBook()<<endl;
    b1.printBookInfo();
    if(b1.checkOutBook("James Camera"))
    {
        b1.printBookInfo();
    }
    else
    {
        cout<<"Book couldn't be checked out"<<endl;
        b1.printBookInfo();
    }

    try
    {
        //vector<string> authors4(1,"");  // "Authors must be provided" exception
        vector<string> authors4(1,"Me");
        array<ushort, Book::isbnSize> arrBad = {1,20,3};
        Book bBad(23537, "Romeo & Juliet", authors4, arrBad, Book::GenreE::comicBook);
        bBad.printBookInfo();
    }
    catch (const std::invalid_argument e)
    {
        cerr << e.what() << endl;
    }

    cout<<endl<<Book::genreEToString(Book::GenreE::album)<<endl;
    cout<<Book::genreEToString(Book::GenreE::novel)<<endl;

    vector<Book> bookList;
    bookList.push_back(std::move(b1));
    bookList.push_back(std::move(b2));
    bookList.push_back(std::move(b3));
    bookList.push_back(std::move(b5));
    bookList.push_back(std::move(b4));

    Book::printByAuthor("Juliana Jones", bookList);

    return 0;
}