#include <iostream>

#include "Book.h"

using namespace std;

int main()
{
    Book b1(23537, "Hamlet", "W. Shakepear", 3253718573);
    
    b1.printBookInfo();

    return 0;
}