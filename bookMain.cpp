#include <iostream>
#include <vector>
#include <list>
#include <array>
#include <memory>

#include "Book.h"
#include "LoanDetails.h"

using namespace std;

int main()
{
    try
    {
        Book
            b1(235378, "Hamlet", "W. Shakespeare", {1,2,3,3,2,7,0,0,5,6,8,2,4}, Book::GenreE::lexicon),  /* not really a lexicon */
            b2(135779, "Don Quixote", "Miguel de Cervantes", {4,7,8,9,9,5,4,4,4,4,9,6,1}, Book::GenreE::novel),
            b3(135779, "Picture album of NY", {"James O'Ryan", "Joseph T. Eckstein", "Juliana Jones"}, {2,4,5,4,7,9,1,2,2,3,5,3,1}, Book::GenreE::album),
            b4(278339, "Othello", "W. Shakespeare", {1,2,7,5}, Book::GenreE::novel),
            b5(789435, "Good Peter Quince", {"Juliana Jones", "W. Shakespeare", "Leon Uris"}, {7,5,8,8,1,3,5,7,7,8,9,1,2}, Book::GenreE::biography),
            b6(135788, "Don Quixote", "Miguel de Cervantes", {4,7,8,9,9,5,4,4,4,4,9,6,1}, Book::GenreE::novel); // The library has 2 copies, same ISBN


        cout<<"Data set (book list):"<<endl;
        b1.printBookInfo();
        b2.printBookInfo();
        b3.printBookInfo();
        b4.printBookInfo();
        b5.printBookInfo();
        b6.printBookInfo();
        cout<<"___________________________________________"<<endl<<endl;


        cout<<"Comparison operators demo:"<<endl;
        cout<<"Hamelt == Othello ?          "<< (b1 == b4) <<endl;
        cout<<"Hamelt == Hamlet  ?          "<< (b1 == b1) <<endl;
        cout<<"Hamelt != Othello ?          "<< (b1 != b4) <<endl;
        cout<<"Don Quixote1 == Don Quixote2 ? "<< (b2 == b6) <<endl;
        cout<<"___________________________________________"<<endl<<endl;


        cout<<"Checkout and return demo (Hamlet): "<<endl;
        if (b1.checkOutBook("John Smith"))
        {
            cout<<"Checked out:"<<endl;
            b1.printBookInfo();
        }
        else
        {
            cout<<"Book couldn't be checked out"<<endl;
            b1.printBookInfo();
        }

        b1.setLoanPeriod(3);    // Loan period for the book changes while it's checked out - the expectedReturn date for the LoanDetails remains the same
        if (b1.isCheckedOut()) 
        {
            cout<<"For the book \""<<b1.getTitle()<<"\" (id = "<<b1.getId()<<", ISBN = "<<b1.isbnToString()<<") (the new) loan period is "
            <<b1.getLoanPeriod()<<" days."<<endl;
            cout<<"For person: "<<b1.getLoanDetails().getName()<<", the loan period for the book \""
            <<b1.getTitle()<<"\" (id = "<<b1.getId()<<", ISBN = "<<b1.isbnToString()<<") is "<<b1.getLoanDetails().getLoanPeriod()<<" days."<<endl<<endl;
        }

        if (b1.checkOutBook("James Camera"))    // try to check out an alaready checked out book
        {
            cout<<"Checked out:"<<endl;
            b1.printBookInfo();
        }   
        else
        {
            cout<<"Book couldn't be checked out"<<endl;
            b1.printBookInfo();
        }

        int overdue = b1.returnBook();  // return book
        cout<<"Book returned; days left: "<< (overdue * -1)<<endl;
        b1.printBookInfo();

        if (b1.checkOutBook("James Camera"))    // Now that the book has been returned, James can get to it 
                                                // (but now only for 3 days, since the loan period has been chenged)
        {
            cout<<"Checked out:"<<endl;
            b1.printBookInfo();
        }
        else
        {
            cout<<"Book couldn't be checked out"<<endl;
            b1.printBookInfo();
        }
        cout<<"___________________________________________"<<endl<<endl;


        cout<<"Get LoanDetails demo: "<<endl;
        // bad practice
        try 
        {
            b6.getLoanDetails(); // book not checked out, exception is thrown
        }
        catch (const bad_optional_access& e)
        {
            cerr << e.what() << endl;
        }
        
        // good practice (extra safe would include try/catch despite the check)
        if (b6.isCheckedOut())
        {
            cout<<b6.getLoanDetails();
        }
        else
        {
            cout<<"This book is not checked out: there are no loan details"<<endl;
        }
        
        if (b1.isCheckedOut())
        {
            cout<<b1.getLoanDetails();
        }

        LoanDetails ld("Mark Johnson", 10);
        cout<<"___________________________________________"<<endl<<endl;


        cout<<"Get Author(s) demo: "<<endl;
        cout<<"The authors("<<b3.numberOfAuthors()<<") of the book \""<<b3.getTitle()<<"\" (id = "<<b3.getId()
        <<", ISBN = "<<b3.isbnToString()<<") are: "<<b3.authorsToString()<<endl;
        cout<<"The 2. author is: "<<b3.getAuthor(2-1)<<"; while the 5. author is: "<<(b3.getAuthor(5-1).empty() ? "none" : b3.getAuthor(5-1))<<endl;
        cout<<"___________________________________________"<<endl<<endl;


        cout<<"Print all books by a given atuhor demo: "<<endl;
        vector<Book> bookList;
        bookList.push_back(std::move(b1));  // since not copyable, the books must be moved; shouldn't use b1-b6 vars any more
        bookList.push_back(std::move(b2));
        bookList.push_back(std::move(b3));
        bookList.push_back(std::move(b5));
        bookList.push_back(std::move(b4));
        bookList.push_back(std::move(b6));

        Book::printByAuthor("Juliana Jones", bookList);
        Book::printByAuthor("W. Shakespeare", bookList);
        Book::printByAuthor("Miguel de Cervantes", bookList);
        Book::printByAuthor("W. Faulkner", bookList);
        cout<<"___________________________________________"<<endl<<endl;


        cout<<"Faulty book initialization demo: "<<endl;
        Book bFaultyInit1(657183, "Die Leiden des jungen Werther", {"Johann Wolfgang von Goethe", "", "Mistery Author Num3"}, {2,5,3,4,0,7,3,6,9,3,3,2,1}, Book::GenreE::novel);
        
    }
    catch (const invalid_argument& e)
    {
        cerr << e.what() << endl;
    }

    return 0;
}