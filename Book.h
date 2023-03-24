#pragma once

#include <string>
#include <optional>
#include <vector>
#include <array>
#include <chrono>

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

        const static unsigned short isbnSize = 13; // After 2007.

    private:

        ulong id = 0;
        std::string title = "";
        std::vector<std::string> authors;
        std::array<ushort, isbnSize> isbn = {0};
        GenreE genre;
        ushort loanPeriod = 10; // number of days
        bool checkedOut = false;
        std::optional<std::string> checkedOutToPerson = std::nullopt;
        std::optional<std::chrono::time_point<std::chrono::system_clock>> checkoutDate = std::nullopt;

    public:
        //Constructors
        Book() = delete;
        Book(ulong id, std::string title, std::string author, std::array<ushort, 13>isbn, GenreE genre, ushort loanPeriod = 10);
        Book(ulong id, std::string title, std::vector<std::string> author, std::array<ushort, 13>isbn, GenreE genre, ushort loanPeriod = 10);
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
        ushort returnBook();

        //Static methods
        static void printByAuthor(std::string authorName, const std::vector<Book>& bookList);
        static std::string genreEToString(GenreE val); // could be usefull even wihout an instance
};