#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include <lists/savings_account.h>


//struct savingsaccount {
//    int key;
//    double balance;
//};


SavingsAccount *savings_account_create(int key, double balance) {
    SavingsAccount *new_account = (SavingsAccount*) malloc(sizeof(SavingsAccount));

    new_account->key     = key;
    new_account->balance = balance;

    return new_account;
}

void savings_account_credit(SavingsAccount *account, double value) {
    assert(value > 0.0);
    assert (account != NULL);

    account->balance += value;
}

void savings_account_withdraw(SavingsAccount *account, double value) {
    assert(value > 0.0);
    assert (account != NULL);

    account->balance -= value;
}

void savings_account_earn_interest(SavingsAccount *account, double percent) {
    assert (percent >  0.0);
    assert (percent <= 1.0);
    assert (account != NULL);

    account->balance += account->balance * percent;
}

void savings_account_close(SavingsAccount *account) {
    assert (account != NULL);

    free(account);
}
