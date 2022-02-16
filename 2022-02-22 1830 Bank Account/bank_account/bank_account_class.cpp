#include <iostream>
#include "bank_account.h"

Bank_Account::Bank_Account(const std::string& b_name, const unsigned long long& b_account, const double& b_balance)
{
    name = b_name;
    account = b_account;
    balance = b_balance;
}

Bank_Account::~Bank_Account() {}

void Bank_Account::show()
{
    std::ios_base::fmtflags orig = std::cout.setf(std::ios_base::fixed, std::ios_base::floatfield);
    std::streamsize prec = std::cout.precision(2);

    std::cout << "Contributor's name: " << name << ". "
        << "Bank account: " << account << ". "
        << "Balance: " << balance << "$ USA." << std::endl;
}

void Bank_Account::add(const double& cash)
{
    balance += cash;
}

bool Bank_Account::withdrawal(const double& cash)
{
    if (cash <= balance)
    {
        balance -= cash;

        return true;
    }
    else
    {
        return false;
    }
}