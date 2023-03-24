#include "Book.h"

Book::Book(ulong id, std::string tittle, std::string author, std::array<ushort, Book::isbnSize>isbn, GenreE genre):
    id(id), tittle(tittle), author(author), isbn(isbn), genre(genre)
{
    if (tittle.empty())
    {
        throw std::invalid_argument("Book title must be specified");
    }
    
    if (author.empty())
    {
        throw std::invalid_argument("Book author must be specified");
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
    <<"Tiitle: "<<tittle<<std::endl
    <<"Author: "<<author<<std::endl
    <<"ISBN: "<<isbnToString()<<std::endl
    <<"Genre: "<<Book::genreEToString(genre)<<std::endl
    <<"Checked out: "<<(checkedOut ? "Book is currently checkedout:" : "Book is currently not checkedout")<<std::endl
    <<"Checkedout to: "<<checkedOutToPerson<<std::endl<<std::endl;
}

void Book::checkOutBook(std::string person)
{
    if (!checkedOut)
    {
        checkedOut = true;
        checkedOutToPerson = person;
        checkoutDate = std::chrono::system_clock::now();
    }
}

void Book::returnBook()
{
    using namespace std::literals;
    if (checkedOut)
    {
        if (std::chrono::system_clock::now() - 5 * 24h > checkoutDate.value())
        {
            std::cout<<"Late!!"<<std::endl;
        }
        checkedOut = false;
        checkedOutToPerson = std::nullopt;
        checkoutDate = std::nullopt;
    }
}
std::string Book::isbnToString() const
{
    std::string retVal;
    for(unsigned short i : isbn)
    {
        retVal.push_back(i + '0');
    }
    return retVal;
}

void Book::printByAuthor(std::string authorName, std::vector<Book> bookList)
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
        default:
            return "Unspecified";
    }
}