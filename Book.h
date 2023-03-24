#pragma once

#include <iostream>
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
            novel,
            unspecified
        };

        const static unsigned short isbnSize = 13; // After 2007.

    private:

        ulong id = 0;
        std::string tittle = "";
        std::string author = "";
        std::array<ushort, isbnSize> isbn = {0};
        GenreE genre = GenreE::unspecified;
        bool checkedOut = false;
        std::optional<std::string> checkedOutToPerson = std::nullopt;
        std::optional<std::chrono::time_point<std::chrono::system_clock>> checkoutDate = std::nullopt;

    public:
        //Constructors
        Book() = delete;
        Book(ulong id, std::string tittle, std::string author, std::array<ushort, 13>isbn, GenreE genre = GenreE::unspecified);
        Book(const Book&) = delete;

        void operator=(const Book&) = delete;

        void printBookInfo() const;
        std::string isbnToString() const;
        void checkOutBook(std::string person);
        void returnBook();

        static void printByAuthor(std::string authorName, std::vector<Book> bookList);
        static std::string genreEToString(GenreE val); // could be usefull even wihout an instance
};
