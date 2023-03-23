#ifndef BOOK_H
#define BOOK_H

#include <iostream>
#include <string>

using namespace std;

class Book
{
    private:
        unsigned int id;
        string tittle;
        string author;
        unsigned long ISBN;
        string genre;
        bool loaned;
    public:
        //Constructors        
        Book(unsigned int bookId, string bookTittle, string bookAuthor, unsigned long ISBN);
        
        void printBookInfo() const;
};
#endif