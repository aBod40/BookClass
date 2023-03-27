 #pragma once
 
 #include <string>
 #include <chrono>
 #include <iostream>
 
 class LoanDetails
 {
    private:
        std::string name;
        unsigned loanPeriod;
        std::chrono::time_point<std::chrono::system_clock> checkoutDate;
    public:
        LoanDetails() = delete;
        LoanDetails(std::string name, unsigned loanPeriod);
        
        // Getters
        std::string getName () const;
        unsigned getLoanPeriod () const;
        std::chrono::time_point<std::chrono::system_clock> getCheckoutDate () const;
        std::chrono::time_point<std::chrono::system_clock> getExpectedReturnDate () const;
        unsigned isOverdue () const;
        
        // Friends
        friend std::ostream& operator<<(std::ostream& stream, const LoanDetails& loanDetails);
 };