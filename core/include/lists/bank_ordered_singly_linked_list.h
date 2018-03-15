#pragma once

#include <lists/bank_account.h>
#include <lists/savings_account.h>
#include <lists/loyalty_account.h>

typedef struct list BankOrderedSinglyLinkedList;
typedef union  account Account;

struct list {
    int acc_kind;
    Account *acc;
    BankOrderedSinglyLinkedList *next;
};

union account {
    BankAccount *bank;       //0
    SavingsAccount *savings; //1
    LoyaltyAccount *loyalty; //2
};

BankOrderedSinglyLinkedList *bank_ordered_singly_create();

BankOrderedSinglyLinkedList *bank_ordered_singly_insert(BankOrderedSinglyLinkedList *osll, int acc_kind, Account *acc);

void bank_ordered_singly_iterative_print(const BankOrderedSinglyLinkedList *const osll);

void bank_ordered_singly_recursive_print(const BankOrderedSinglyLinkedList *const osll);

void bank_ordered_singly_reverse_print(const BankOrderedSinglyLinkedList *const osll);

int bank_ordered_singly_is_empty(const BankOrderedSinglyLinkedList *const osll);

BankOrderedSinglyLinkedList *bank_ordered_singly_search(const BankOrderedSinglyLinkedList *const osll, int key);

BankOrderedSinglyLinkedList *bank_ordered_singly_iterative_remove(BankOrderedSinglyLinkedList *osll, int key);

BankOrderedSinglyLinkedList *bank_ordered_singly_recursive_remove(BankOrderedSinglyLinkedList *osll, int key);

void bank_ordered_singly_free(BankOrderedSinglyLinkedList *osll);
