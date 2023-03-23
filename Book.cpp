#include "Book.h"

Book::Book(unsigned int bookId, std::string bookTittle, std::string bookAuthor, unsigned long ISBN){}

void Book::printBookInfo() const
{
    std::cout
    <<"Book Id: "<<id<<"\n"
    <<"Tiitle: "<<tittle<<"\n"
    <<"Author: "<<author<<"\n"
    <<"ISBN: "<<ISBN<<"\n"
    <<"Genre: "<<genre<<"\n"
    <<"Checked out: "<<checkedOut<<"\n\n";
}

void Book::chcekOutBook() { checkedOut = true; }
void Book::returnBook() { checkedOut = false; }