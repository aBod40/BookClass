#include "Book.h"

#include <iostream>
#include <algorithm>
#include <ranges>

Book::Book(ulong id, std::string title, std::string author, std::array<ushort, Book::isbnSize>isbn, GenreE genre, ushort loanPeriod):
    id(id), title(title), authors(1, author), isbn(isbn), genre(genre), loanPeriod(loanPeriod)
{
    if (title.empty())
    {
        throw std::invalid_argument("Book title must be specified");
    }

    if (author.empty())
    {
        throw std::invalid_argument("Author must be specified");
    }
    
    auto it = std::find_if(isbn.begin(), isbn.end(), [] (const ushort& element) { return (element < 0 || element > 9); } );
    if (it != isbn.end())
    {
        throw std::invalid_argument("Non (single) digit element detected in isbn");
    }
}

Book::Book(ulong id, std::string title, std::vector<std::string> authors, std::array<ushort, 13>isbn, GenreE genre, ushort loanPeriod):
    id(id), title(title), authors(authors), isbn(isbn), genre(genre), loanPeriod(loanPeriod)
{
    if (title.empty())
    {
        throw std::invalid_argument("Book title must be specified");
    }
    
    if (authors.empty() || authors[0].empty())  // First author can not be an empty string, others can
    {
        throw std::invalid_argument("At least one author must be specified");
    }
    
    auto it = std::find_if(isbn.begin(), isbn.end(), [] (const ushort& element) { return (element < 0 || element > 9); } );
    if (it != isbn.end())
    {
        throw std::invalid_argument("Non (single) digit element detected in isbn");
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
    <<"Book Id: "<<id<<std::endl
    <<"Title: "<<title<<std::endl
    <<"Authors: "<<authorsToString()<<std::endl
    <<"ISBN: "<<isbnToString()<<std::endl
    <<"Genre: "<<Book::genreEToString(genre)<<std::endl
    <<"Checked out: "<<(checkedOut ? "Book is currently checkedout:" : "Book is currently not checkedout")<<std::endl
    <<"Checkedout to: "<<checkedOutToPerson.value_or("none")<<std::endl<<std::endl;
}

bool Book::checkOutBook(std::string person)
{
    if (!checkedOut && loanPeriod > 0)
    {
        checkedOut = true;
        checkedOutToPerson = person;
        checkoutDate = std::chrono::system_clock::now();
        return true;
    }
    return false;
}

ushort Book::returnBook()
{
    using namespace std::literals;
    if (checkedOut)
    {
        ushort i;
        if (std::chrono::system_clock::now() - 1ns /*1ns for testing purposes*/ > checkoutDate.value())
        {
            i = (std::chrono::system_clock::now() - 1ns - checkoutDate.value()).count();
        }
        checkedOut = false;
        checkedOutToPerson = std::nullopt;
        checkoutDate = std::nullopt;
        return i;
    }
    return 0;
}
std::string Book::isbnToString() const
{
    std::string retVal;
    for(auto i : isbn)
    {
        retVal.push_back(i + '0');
    }
    return retVal;
}
std::string Book::authorsToString() const
{
    std::string retVal;
    for(auto author : authors)
    {
        retVal += (author);
        retVal += (", ");
    }
    return retVal;
}

void Book::printByAuthor(std::string authorName, std::vector<Book> &bookList)
{
    
}

std::string Book::genreEToString(GenreE val)
{
    switch(val)
    {
        case Book::GenreE::album:
            return "Album";
        case Book::GenreE::biography:
            return "Biography";
        case Book::GenreE::comicBook:
            return "Comic Book";
        case Book::GenreE::lexicon:
            return "Lexicon";
        case Book::GenreE::novel:
            return "Novel";
        default:    // should be imposible now
            return "Unspecified";
    }
}