#pragma once

struct loyaltyaccount {
    int key;
    double balance, bonus;
};

typedef struct loyaltyaccount LoyaltyAccount;


LoyaltyAccount *loyalty_account_create(int key, double balance);

void loyalty_account_credit(LoyaltyAccount *account, double value);

void loyalty_account_withdraw(LoyaltyAccount *account, double value);

void loyalty_account_earn_bonus(LoyaltyAccount *account);

void loyalty_account_close(LoyaltyAccount *account);
