#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include <bank_account.h>


//struct bankaccount {
//    int key;
//    double balance;
//};


BankAccount *bank_account_create(int key, double balance) {
    BankAccount *new_account = (BankAccount*) malloc(sizeof(BankAccount));

    new_account->key     = key;
    new_account->balance = balance;

    return new_account;
}

void bank_account_credit(BankAccount *account, double value) {
    assert(value > 0.0);
    assert (account != NULL);

    account->balance += value;
}

void bank_account_withdraw(BankAccount *account, double value) {
    assert(value > 0.0);
    assert (account != NULL);

    account->balance -= value;
}

void bank_account_close(BankAccount *account) {
    assert (account != NULL);

    free(account);
}
