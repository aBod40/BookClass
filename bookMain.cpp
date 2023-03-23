#include <iostream>
#include <vector>

#include "Book.h"

using namespace std;

int main()
{
    Book b1(235378, "Hamlet", "W. Shakepear", 3253718573),
         b2(135779, "Don Quixote", "Miguel de Cervantes", 4833576);
    
    b1.printBookInfo();
    b1.checkOutBook("John Smith");
    b1.printBookInfo();
    b1.checkOutBook("James Camera");
    b1.printBookInfo();
    b1.returnBook();
    b1.printBookInfo();
    
    try
    {
        Book b3(23537, "", "W. Shakepear", 3253718573);
    }
    catch (const char* msg)
    {
        cerr << msg << endl;
    }
    
    return 0;
}