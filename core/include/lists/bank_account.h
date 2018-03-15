#pragma once

struct bankaccount {
    int key;
    double balance;
};

typedef struct bankaccount BankAccount;


BankAccount *bank_account_create(int key, double balance);

void bank_account_credit(BankAccount *account, double value);

void bank_account_withdraw(BankAccount *account, double value);

void bank_account_close(BankAccount *account);
