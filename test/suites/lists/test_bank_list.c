#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include <lists/bank_ordered_singly_linked_list.h>

#include <lists/bank_account.h>
#include <lists/savings_account.h>
#include <lists/loyalty_account.h>


int main(int argc, char *argv[]) {

    int op;

    BankOrderedSinglyLinkedList *list = bank_ordered_singly_create();

    do {
        printf("Select an option: ");
        printf("-1: Exit.\n");
        printf(" 0: Insert an bank account.\n");
        printf(" 1: Insert an savings account.\n");
        printf(" 2: Insert an loyalty account.\n");
        printf(" 3: Credit in account.\n");
        printf(" 4: Withdraw in account.\n");
        printf(" 5: View balance of an account.\n");
        printf(" 6: View bonus of a loyalty account.\n");
        printf(" 7: Transfer between accounts.\n");
        printf(" 8: Earn interest in a savings account.\n");
        printf(" 9: Earn bonus in a loyalty account.\n");
        printf("10: Remove an account.\n");
        printf("11: View all accounts.\n");

        scanf("%d", &op);

//        op = 3;

        assert(op >= -1);
        assert(op <= 11);

        int key;

        float value, balance;

        switch (op) {
        case -1:
            break;
        case 0: {
            printf("Enter the number: ");
            scanf("%d", &key);
//            key = 1;
            printf("Enter the balance: ");
            scanf("%f", &balance);
//            balance = 20.0;
            BankAccount *bank = bank_account_create(key, balance);

            Account *acc = malloc(sizeof(Account));

            acc->bank = bank;

            list = bank_ordered_singly_insert(list, 0, acc);

            printf("Bank account created...\n");

//            bank_ordered_singly_iterative_print(list);

            break;
        }
        case 1: {
            printf("Enter the number: ");
            scanf("%d", &key);
            printf("Enter the balance: ");
            scanf("%f", &balance);

            SavingsAccount *savings = savings_account_create(key, balance);
            Account *acc = malloc(sizeof(Account));

            acc->savings = savings;
            list = bank_ordered_singly_insert(list, 1, acc);

            printf("Savings account created...\n");

            break;
        }
        case 2: {
            printf("Enter the number: ");
            scanf("%d", &key);
            printf("Enter the balance: ");
            scanf("%f", &balance);

            LoyaltyAccount *loyalty = loyalty_account_create(key, balance);
            Account *acc = malloc(sizeof(Account));

            acc->loyalty = loyalty;
            list = bank_ordered_singly_insert(list, 2, acc);

            printf("Loyalty account created...\n");

            break;
        }
        case 3: {
            printf("Enter the number of account to credit: ");
            scanf("%d", &key);

            BankOrderedSinglyLinkedList *acc_list = bank_ordered_singly_search(list, key);

            if (acc_list != NULL) {
                printf("Enter the value that you want to credit: ");
                scanf("%f", &value);

                switch(acc_list->acc_kind) {
                case 0:
                    bank_account_credit(acc_list->acc->bank, value);
                    break;

                case 1:
                    savings_account_credit(acc_list->acc->savings, value);
                    break;

                case 2:
                    loyalty_account_credit(acc_list->acc->loyalty, value);
                    break;
                }

                printf("Account was credited.\n");
            } else {
                printf("Account doesn't exists!\n");
            }

            break;
        }
        case 4: {
            printf("Enter the number of account to withdraw: ");
            scanf("%d", &key);

            BankOrderedSinglyLinkedList *acc_list = bank_ordered_singly_search(list, key);

            if (acc_list != NULL) {
                printf("Enter the value that you want to withdraw: ");
                scanf("%f", &value);

                switch(acc_list->acc_kind) {
                case 0:
                    bank_account_withdraw(acc_list->acc->bank, value);
                    break;

                case 1:
                    savings_account_withdraw(acc_list->acc->savings, value);
                    break;

                case 2:
                    loyalty_account_withdraw(acc_list->acc->loyalty, value);
                    break;
                }

                printf("Account was withdrawn.\n");
            } else {
                printf("Account doesn't exists!\n");
            }

            break;
        }
        case 5: {
            printf("Enter the number of account to query: ");
            scanf("%d", &key);

            BankOrderedSinglyLinkedList *acc_list = bank_ordered_singly_search(list, key);

            if (acc_list != NULL) {
                switch(acc_list->acc_kind) {
                case 0:
                    balance = acc_list->acc->bank->balance;
                    break;

                case 1:
                    balance = acc_list->acc->savings->balance;
                    break;

                case 2:
                    balance = acc_list->acc->loyalty->balance;
                    break;
                }

                printf("Account %d: $ %f.\n", key, balance);
            } else {
                printf("Account doesn't exists!\n");
            }

            break;
        }
        case 6: {
            printf("Enter the number of loyalty account to query: ");
            scanf("%d", &key);

            BankOrderedSinglyLinkedList *acc_list = bank_ordered_singly_search(list, key);

            if (acc_list != NULL) {
                switch(acc_list->acc_kind) {
                case 0:
                    printf("This account isn't loyalty!\n");
                    break;

                case 1:
                    printf("This account isn't loyalty!\n");
                    break;

                case 2:
                    value = acc_list->acc->loyalty->bonus;
                    printf("Bonus of account %d: $ %f.\n", key, value);
                    break;
                }

            } else {
                printf("Account doesn't exists!\n");
            }

            break;
        }
        case 7: {
            printf("Enter the number of account to withdraw: ");
            scanf("%d", &key);

            BankOrderedSinglyLinkedList *acc_list = bank_ordered_singly_search(list, key);

            if (acc_list != NULL) {
                printf("Enter the amount to withdraw: ");
                scanf("%f", &value);

                switch(acc_list->acc_kind) {
                case 0:
                    balance = acc_list->acc->bank->balance;
                    break;

                case 1:
                    balance = acc_list->acc->savings->balance;
                    break;

                case 2:
                    balance = acc_list->acc->loyalty->balance;
                    break;
                }

                if (value <= balance) {
                    printf("Enter the number of account to credit: ");
                    scanf("%d", &key);

                    BankOrderedSinglyLinkedList *acc_credit_list = bank_ordered_singly_search(list, key);

                    if (acc_credit_list != NULL) {
                        switch(acc_credit_list->acc_kind) {
                        case 0:
                            bank_account_credit(acc_credit_list->acc->bank, value);
                            break;

                        case 1:
                            savings_account_credit(acc_credit_list->acc->savings, value);
                            break;

                        case 2:
                            loyalty_account_credit(acc_credit_list->acc->loyalty, value);
                            break;
                        }

                        switch(acc_list->acc_kind) {
                        case 0:
                            bank_account_withdraw(acc_list->acc->bank, value);
                            break;

                        case 1:
                            savings_account_withdraw(acc_list->acc->savings, value);
                            break;

                        case 2:
                            loyalty_account_withdraw(acc_list->acc->loyalty, value);
                            break;
                        }

                        printf("Transfer was OK.\n");

                    } else {
                        printf("This account doesn't exists!\n");
                    }

                } else {
                    printf("This account hasn't balance enough.\n");
                }

            } else {
                printf("Account doesn't exists!\n");
            }

            break;
        }
        case 8: {
            printf("Enter the number of savings account to earn interest: ");
            scanf("%d", &key);

            BankOrderedSinglyLinkedList *acc_list = bank_ordered_singly_search(list, key);

            if (acc_list != NULL) {
                switch(acc_list->acc_kind) {
                case 0:
                    printf("This account isn't saving one!\n");
                    break;

                case 1:
                    savings_account_earn_interest(acc_list->acc->savings, 0.05);
                    printf("Interest was added in balance.\n");
                    break;

                case 2:
                    printf("This account isn't saving one!\n");
                    break;
                }

            } else {
                printf("Account doesn't exists!\n");
            }

            break;
        }
        case 9: {
            printf("Enter the number of loyalty account to earn bonus: ");
            scanf("%d", &key);

            BankOrderedSinglyLinkedList *acc_list = bank_ordered_singly_search(list, key);

            if (acc_list != NULL) {
                switch(acc_list->acc_kind) {
                case 0:
                    printf("This account isn't loyalty!\n");
                    break;

                case 1:
                    printf("This account isn't loyalty!\n");
                    break;

                case 2:
                    loyalty_account_earn_bonus(acc_list->acc->loyalty);
                    printf("Bonus was added in balance.\n");
                    break;
                }

            } else {
                printf("Account doesn't exists!\n");
            }

            break;
        }
        case 10: {
            printf("Enter the number of account to remove: ");
            scanf("%d", &key);

            list = bank_ordered_singly_iterative_remove(list, key);

            printf("Account removed.\n");

            break;
        }
        case 11: {
            printf("\nALL ACCOUNTS:\n");
            bank_ordered_singly_iterative_print(list);
            printf("\n========\n");
            break;
        }
        }


    } while (op != -1);

    return EXIT_SUCCESS;
}
