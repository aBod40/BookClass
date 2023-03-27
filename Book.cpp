#include "Book.h"

#include <iostream>
#include <algorithm>
#include <ranges>

Book::Book(unsigned long id, std::string title, std::string author, std::array<unsigned, Book::isbnSize>isbn, GenreE genre, unsigned loanPeriod):
    Book::Book(id, title, std::vector<std::string>(1, author), isbn, genre, loanPeriod) {}

Book::Book(unsigned long id, std::string title, std::vector<std::string> authors, std::array<unsigned, 13>isbn, GenreE genre, unsigned loanPeriod):
    id(id), title(title), authors(authors), isbn(isbn), genre(genre), loanPeriod(loanPeriod)
{
    if (id == 0)
    {
        throw std::invalid_argument("Book id must be a value differen from 0.");
    }

    if (title.empty())
    {
        throw std::invalid_argument("Book title must be specified.");
    }
    
    if (authors.empty())
    {
        throw std::invalid_argument("Book must have at least one author.");
    }
    
    auto authorsIt = std::find_if(authors.begin(), authors.end(), [] (const auto& element) { return element.empty(); } );
    if (authorsIt != authors.end())
    {
        throw std::invalid_argument("Every specified author must be a non-empty string.");
    }

    auto isbnIt = std::find_if(isbn.begin(), isbn.end(), [] (const auto& element) { return (element < 0 || element > 9); } );
    if (isbnIt != isbn.end())
    {
        throw std::invalid_argument("Non (single) digit element detected in isbn.");
    }
}

bool Book::operator==(Book const& rhs) const { return id == rhs.id; }
bool Book::operator!=(Book const& rhs) const { return id != rhs.id; }

std::ostream& operator<<(std::ostream& os, std::optional<LoanDetails> const& opt)
{
    return opt ? os<<opt.value() : os<<"  Book is not checked out";
}

void Book::printBookInfo() const
{
    std::cout
    <<"Book Id: "<<id<<std::endl
    <<"Title: \""<<title<<"\""<<std::endl
    <<"Authors: "<<authorsToString()<<std::endl
    <<"ISBN("<<getIsbnSize()<<"): "<<isbnToString()<<std::endl
    <<"Genre: "<<Book::genreEToString(genre)<<std::endl
    <<"Loan period: "<<loanPeriod<<" days"<<std::endl
    <<loanDetails
    <<std::endl<<std::endl;
}

bool Book::checkOutBook(std::string person)
{
    if (!isCheckedOut() && loanPeriod > 0 && !person.empty())
    {
        loanDetails = LoanDetails(person, loanPeriod);

        return true;
    }
    return false;
}

int Book::returnBook()
{
    using namespace std::literals;
    using namespace std::chrono;

    if (isCheckedOut())
    {
        auto d = loanDetails.value().daysOverdue();
        loanDetails.reset();

        return d;
    }
    return 0;
}

std::string Book::isbnToString() const
{
    std::string retVal;
    for(auto const & i : isbn)
    {
        retVal.push_back(i + '0');
    }
    return retVal;
}

std::string Book::authorsToString() const
{
    std::string retVal;
    for(auto const & author : authors)
    {
        retVal += (author);
        retVal += (", ");
    }
    return retVal;
}

//Setters
void Book::setLoanPeriod(unsigned val) { loanPeriod = val; }

// Getters
unsigned long Book::getId () const { return id; }
std::string Book::getTitle () const { return title; }
uint Book::numberOfAuthors () const { return authors.size(); }
std::vector<std::string> Book::getAuthors () const { return authors; }
std::string Book::getAuthor (unsigned n) const
{
    if ( authors.size() < n )
    {
        return "";
    }
    return authors[n];
}
uint Book::getIsbnSize () const { return Book::isbnSize; }
std::array<unsigned, Book::isbnSize> Book::getIsbn () const { return isbn; }
Book::GenreE Book::getGenre () const { return genre; }
unsigned Book::getLoanPeriod() const { return loanPeriod; }
bool Book::isCheckedOut () const { return loanDetails.has_value(); }
LoanDetails Book::getLoanDetails () const { return loanDetails.value(); }

void Book::printByAuthor(std::string authorName, const std::vector<Book>& bookList)
{
    auto matchingAuthor = std::views::filter(bookList, [authorName](const auto& book)
    {
        auto it = std::find_if(book.authors.begin(), book.authors.end(), [authorName] (const auto& author)
        {
            return author == authorName;
        });

        return it != book.authors.end();
    });

    if(matchingAuthor.empty())
    {
        std::cout<<"Found no books by "<<authorName<<": "<<std::endl;
    }
    else
    {
        std::cout<<"Books by "<<authorName<<": "<<std::endl;
        for (auto const & bookByAuthor : matchingAuthor)
        {
            bookByAuthor.printBookInfo();
        }
        std::cout<<std::endl;
    }
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