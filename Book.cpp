#include "Book.h"

Book::Book(unsigned int bookId, std::string bookTittle, std::string bookAuthor, unsigned long ISBN)
{
    if (bookTittle.empty())
    {
        throw "Book tiitle must be specified";
    }
    
}

template<typename T>
std::ostream& operator<<(std::ostream& os, std::optional<T> const& opt)
{
    return opt ? os << opt.value() : os;
}

void Book::printBookInfo() const
{
    std::cout
    <<"Book Id: "<<id<<"\n"
    <<"Tiitle: "<<tittle<<"\n"
    <<"Author: "<<author<<"\n"
    <<"ISBN: "<<ISBN<<"\n"
    <<"Genre: "<<genre<<"\n"
    <<"Checked out: "<<(checkedOut ? "Book is currently checkedout:" : "Book is currently not checkedout")<<"\n"
    <<"Checkedout to: "<<checkedOutToPerson<<"\n\n";
}

void Book::checkOutBook(std::string person)
{
    if (!checkedOut)
    {
        checkedOut = true;
        checkedOutToPerson = person;
    }
}

void Book::returnBook() { checkedOut = false; }

void Book::printByAuthor(std::string authorName, std::vector<Book> bookList)
{
}