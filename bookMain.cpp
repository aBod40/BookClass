#include <iostream>
#include <vector>
#include <array>

#include "Book.h"

using namespace std;

int main()
{
    array<ushort, Book::isbnSize> arr1 = {1,2,3}, arr2 = {4,7,8,9,9,5,4,4,4,4,};
    Book b1(235378, "Hamlet", "W. Shakespear", arr1),
         b2(135779, "Don Quixote", "Miguel de Cervantes", arr2, Book::GenreE::novel);
    
    b1.printBookInfo();
    b2.printBookInfo();
    b1.checkOutBook("John Smith");
    b1.printBookInfo();
    b1.checkOutBook("James Camera");
    b1.printBookInfo();
    b1.returnBook();
    b1.printBookInfo();

    try
    {
        Book b3(23537, "", "W. Shakepear", arr1);
    }
    catch (const std::invalid_argument e)
    {
        cerr << e.what() << endl;
    }

    cout<<endl<<Book::genreEToString(Book::GenreE::album)<<endl;
    cout<<Book::genreEToString(Book::GenreE::novel)<<endl;

    return 0;
}