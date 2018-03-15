#pragma once

struct savingsaccount {
    int key;
    double balance;
};

typedef struct savingsaccount SavingsAccount;


SavingsAccount *savings_account_create(int key, double balance);

void savings_account_credit(SavingsAccount *account, double value);

void savings_account_withdraw(SavingsAccount *account, double value);

void savings_account_earn_interest(SavingsAccount *account, double percent);

void savings_account_close(SavingsAccount *account);
