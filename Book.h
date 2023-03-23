#ifndef BOOK_H
#define BOOK_H

#include <iostream>
#include <string>
#include <optional>
#include <vector>

class Book
{
    private:
        unsigned int id = 0;
        std::string tittle = "";
        std::string author = "";
        unsigned long ISBN = 0;
        std::string genre = "";
        bool checkedOut = false;
        std::optional<std::string> checkedOutToPerson = std::nullopt;
    public:
        //Constructors
        Book() = delete;
        Book(unsigned int bookId, std::string bookTittle, std::string bookAuthor, unsigned long ISBN);
        Book(const Book&) = delete;
        
        void operator=(const Book&) = delete;
        
        void printBookInfo() const;
        void checkOutBook(std::string person);
        void returnBook();
        
        static void printByAuthor(std::string authorName, std::vector<Book> bookList);
};
#endif