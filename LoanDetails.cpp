#include "LoanDetails.h"

#include <chrono>

LoanDetails::LoanDetails(std::string name, unsigned loanPeriod):
    name(name), loanDate(std::chrono::system_clock::now()), loanPeriod(loanPeriod)
{
}

// Getters
std::string LoanDetails::getName () const { return name; }
unsigned LoanDetails::getLoanPeriod () const { return loanPeriod; }
std::chrono::time_point<std::chrono::system_clock> LoanDetails::getLoanDate () const { return loanDate; }
std::chrono::time_point<std::chrono::system_clock> LoanDetails::getExpectedReturnDate () const
{
    using namespace std::literals;
    
    return loanDate + loanPeriod * 24h;
}
int LoanDetails::daysOverdue () const
{
    return (floor<std::chrono::days>(std::chrono::system_clock::now() - getExpectedReturnDate())).count();
}

std::ostream& operator<<(std::ostream& stream,  std::chrono::time_point<std::chrono::system_clock> const & tp)  // print date
{
    using namespace std::chrono;

    year_month_day ymd{floor<days>(tp)};
    stream<<unsigned(ymd.day())<<"."<<unsigned(ymd.month())<<"."<<int(ymd.year())<<".";
    
    return stream;
}

std::ostream& operator<<(std::ostream& stream, const LoanDetails& loanDetails)
{
    stream
    <<"Loan details: "<<std::endl
    <<"  Name: "<<loanDetails.getName()<<std::endl
    <<"  Loan Date: "<<loanDetails.getLoanDate()<<std::endl
    <<"  Expected Retrun Date: "<<loanDetails.getExpectedReturnDate()<<std::endl;
    
    return stream;
}