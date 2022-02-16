#include <iostream>
#include <string>
#include <vector>
#include "bank_account.h"

int main()
{
    std::string ch;
    std::string b_name;
    unsigned int n_contributors;
    unsigned int depositor;
    unsigned long long b_account;
    double b_balance;
    double cash;
    static unsigned int count_contributors;

    std::cout << "How many contributors need to be added: ";

    std::cin >> n_contributors;

    std::cout << std::endl;

    std::vector<Bank_Account*> contributors;

    for (count_contributors = 0; count_contributors < n_contributors; count_contributors++)
    {
        std::cout << count_contributors << ")Enter contributor name: ";
        std::cin.ignore();
        std::getline(std::cin, b_name);

        std::cout << count_contributors << ")Enter account number: ";
        std::cin >> b_account;

        std::cout << count_contributors << ")Enter balance: ";
        std::cin >> b_balance;

        std::cout << std::endl;

        Bank_Account* s = new Bank_Account(b_name, b_account, b_balance);
        contributors.push_back(s);
    }

    std::cout << std::endl << "Account number for transactions: ";
    std::cin >> depositor;

    std::cout << "Please enter C to add depositor, enter A to add money, enter W to withdraw money "
        << "enter S to show, or Q to quit." << std::endl;

    while (std::cin >> ch && ch != "Q" && (ch >= "A" && ch <= "Z" || ch >= "a" && ch <= "z"))
    {
        if (ch == "C")
        {
            std::cout << count_contributors << ")Enter contributor name: ";
            std::cin.ignore();
            std::getline(std::cin, b_name);

            std::cout << count_contributors << ")Enter account number: ";
            std::cin >> b_account;

            std::cout << count_contributors << ")Enter balance: ";
            std::cin >> b_balance;

            std::cout << std::endl;

            Bank_Account* s = new Bank_Account(b_name, b_account, b_balance);
            contributors.push_back(s);

            count_contributors++;
        }
        else if (ch == "A")
        {
            std::cout << "Enter cash: ";
            std::cin >> cash;
            contributors[depositor]->add(cash);
        }
        else if (ch == "W")
        {
            bool val = false;

            while (val == false)
            {
                std::cout << "Enter cash: ";
                std::cin >> cash;
                val = contributors[depositor]->withdrawal(cash);

                if (val == false)
                {
                    std::cout << "There are no such funds in the account" << std::endl;
                }
            }
        }
        else if (ch == "S")
        {
            contributors[depositor]->show();
        }

        std::cout << std::endl << "Account number for transactions: ";
        std::cin >> depositor;

        std::cout << "Please enter C to add depositor, enter A to add money, enter W to withdraw money "
            << "enter S to show, or Q to quit." << std::endl;
    }

    std::cout << "Buy";
}