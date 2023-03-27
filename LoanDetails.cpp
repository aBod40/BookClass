#include "LoanDetails.h"

#include <chrono>

LoanDetails::LoanDetails(std::string name, unsigned loanPeriod):
    name(name), checkoutDate(std::chrono::system_clock::now()), loanPeriod(loanPeriod)
{
    
}

// Getters
std::string LoanDetails::getName () const { return name; }
unsigned LoanDetails::getLoanPeriod () const { return loanPeriod; }
std::chrono::time_point<std::chrono::system_clock> LoanDetails::getCheckoutDate () const { return checkoutDate; }
std::chrono::time_point<std::chrono::system_clock> LoanDetails::getExpectedReturnDate () const
{
    using namespace std::literals;
    
    return checkoutDate + loanPeriod * 24h;
}
//unsigned LoanDetails::isOverdue () const

std::ostream& operator<<(std::ostream& stream,  std::chrono::time_point<std::chrono::system_clock> const & tp)
{
    using namespace std::chrono;

    year_month_day ymd{floor<days>(tp)};
    stream<<unsigned(ymd.day())<<"."<<unsigned(ymd.month())<<"."<<int(ymd.year())<<".";
    
    return stream;
}

// Friends
std::ostream& operator<<(std::ostream& stream, const LoanDetails& loanDetails)
{
    stream
    <<"Loan details :"<<std::endl
    <<"  Name: "<<loanDetails.name<<std::endl
    <<"  Checkout Date: "<<loanDetails.checkoutDate<<std::endl
    <<"  Expected Retrun Date: "<<loanDetails.getExpectedReturnDate()<<std::endl;
    
    return stream;
}