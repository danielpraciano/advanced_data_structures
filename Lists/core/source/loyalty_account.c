#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include <loyalty_account.h>


//struct loyaltyaccount {
//    int key;
//    double balance, bonus;
//};


LoyaltyAccount *loyalty_account_create(int key, double balance) {
    LoyaltyAccount *new_account = (LoyaltyAccount*) malloc(sizeof(LoyaltyAccount));

    new_account->key     = key;
    new_account->balance = balance;
    new_account->bonus   = 0.0;

    return new_account;
}

void loyalty_account_credit(LoyaltyAccount *account, double value) {
    assert(value > 0.0);
    assert (account != NULL);

    account->balance += value;
    account->bonus   += value*0.01;
}

void loyalty_account_withdraw(LoyaltyAccount *account, double value) {
    assert(value > 0.0);
    assert (account != NULL);

    account->balance -= value;
}

void loyalty_account_earn_bonus(LoyaltyAccount *account) {
    assert (account != NULL);

    account->balance += account->bonus;
    account->bonus    = 0.0;
}

void loyalty_account_close(LoyaltyAccount *account) {
    assert (account != NULL);

    free(account);
}
