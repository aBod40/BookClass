#include "Book.h"

Book::Book(unsigned int bookId, string bookTittle, string bookAuthor, unsigned long ISBN){}

void Book::printBookInfo() const
{
    cout<<id<<tittle<<author<<ISBN<<genre<<loaned;
}