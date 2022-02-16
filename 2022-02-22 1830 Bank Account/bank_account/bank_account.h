#pragma once
#ifndef BANK_ACCOUNT_H_
#define BANK_ACCOUNT_H_

class Bank_Account
{
private:
    std::string name;
    unsigned long long account;
    double balance;

public:
    Bank_Account(const std::string& b_name, const unsigned long long& b_account, const double& b_balance);
    ~Bank_Account();
    void show();
    void add(const double& cash);
    bool withdrawal(const double& cash);
};

#endif