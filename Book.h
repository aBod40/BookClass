#ifndef BOOK_H
#define BOOK_H

#include <iostream>
#include <string>

class Book
{
    private:
        unsigned int id;
        std::string tittle;
        std::string author;
        unsigned long ISBN;
        std::string genre;
        bool checkedOut;
    public:
        //Constructors
        Book() = delete;
        Book(unsigned int bookId, std::string bookTittle, std::string bookAuthor, unsigned long ISBN);
        Book(const Book&) = delete;
        
        void operator=(const Book&) = delete;
        
        void printBookInfo() const;
        void chcekOutBook();
        void returnBook();
};
#endif