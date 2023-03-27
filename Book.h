#pragma once

#include <string>
#include <optional>
#include <vector>
#include <array>
#include <chrono>

#include "LoanDetails.h"

class Book
{
    public:
        enum class GenreE
        {
            album,
            biography,
            comicBook,
            lexicon,
            novel
        };

        const static unsigned isbnSize = 13; // After 2007.

    private:

        unsigned long id = 0;
        std::string title = "";
        std::vector<std::string> authors;
        std::array<unsigned, isbnSize> isbn = {0};
        GenreE genre;
        unsigned loanPeriod = 10; // number of days; 0 signifies that a book is not to be checked out
        bool checkedOut = false;
        std::optional<std::string> checkedOutToPerson = std::nullopt;
        std::optional<std::chrono::time_point<std::chrono::system_clock>> checkoutDate = std::nullopt;
        std::optional<LoanDetails> loanDetails = std::nullopt;

    public:
        //Constructors
        Book() = delete;
        Book(unsigned long id, std::string title, std::string author, std::array<unsigned, 13>isbn, GenreE genre, unsigned loanPeriod = 10);
        Book(unsigned long id, std::string title, std::vector<std::string> author, std::array<unsigned, 13>isbn, GenreE genre, unsigned loanPeriod = 10);
        Book(const Book&) = delete;
        Book(Book&&) = default;

        // Operators
        Book& operator= (const Book&) = delete;
        Book& operator= (Book&& ) = default;
        bool operator==(Book const& rhs) const;
        bool operator!=(Book const& rhs) const;

        void printBookInfo() const;
        std::string isbnToString() const;
        std::string authorsToString() const;
        bool checkOutBook(std::string person);
        unsigned returnBook();

        // Setters
        void setLoanPeriod(unsigned val);

        // Getters
        unsigned long getId () const;
        std::string getTitle () const;
        uint numberOfAuthors () const;
        std::vector<std::string> getAuthors () const;
        std::string getAuthor (uint n = 1) const;  // get the n-th author ( !!! zero-based indexing !!)
        std::array<unsigned, isbnSize> gtIsbn () const;
        GenreE getGenre () const;
        unsigned getLoanPeriod() const;
        bool isCheckedOut () const;

        //Static methods
        static void printByAuthor(std::string authorName, const std::vector<Book>& bookList);
        static std::string genreEToString(GenreE val); // could be usefull even wihout an instance
};