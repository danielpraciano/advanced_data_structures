#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include <lists/bank_ordered_singly_linked_list.h>

//#include <bank_account.h>
//#include <savings_account.h>
//#include <loyalty_account.h>

//struct list {
//    int acc_kind;
//    Account *acc;
//    BankOrderedSinglyLinkedList *next;
//};

//union account {
//    BankAccount *bank;       //0
//    SavingsAccount *savings; //1
//    LoyaltyAccount *loyalty; //2
//};

BankOrderedSinglyLinkedList *bank_ordered_singly_create() {
    return NULL;
}

BankOrderedSinglyLinkedList *bank_ordered_singly_insert(BankOrderedSinglyLinkedList *osll, int acc_kind, Account *acc) {
    assert(acc != NULL);
    assert(acc_kind >= 0);
    assert(acc_kind <= 2);

    BankOrderedSinglyLinkedList *new_element = (BankOrderedSinglyLinkedList*) malloc(sizeof(BankOrderedSinglyLinkedList));

    assert(new_element != NULL);

    new_element->acc_kind = acc_kind;
    new_element->acc      = acc;

    int data;

    switch (acc_kind) {
    case 0:
        data = acc->bank->key;
        break;
    case 1:
        data = acc->savings->key;
        break;
    case 2:
        data = acc->loyalty->key;
        break;
    }

    int osll_data;

    if (osll != NULL) {

    switch (osll->acc_kind) {
    case 0:
        osll_data = acc->bank->key;
        break;
    case 1:
        osll_data = acc->savings->key;
        break;
    case 2:
        osll_data = acc->loyalty->key;
        break;
    }
}
    if (osll == NULL || osll_data >= data) {
        new_element->next = osll;
        osll              = new_element;
    } else {
        BankOrderedSinglyLinkedList *osll_current = osll->next, *osll_previous = osll;

        switch (osll_current->acc_kind) {
        case 0:
            osll_data = acc->bank->key;
            break;
        case 1:
            osll_data = acc->savings->key;
            break;
        case 2:
            osll_data = acc->loyalty->key;
            break;
        }

        while (osll_current != NULL && data > osll_data) {
            osll_previous = osll_current;
            osll_current = osll_current->next;

            switch (osll_current->acc_kind) {
            case 0:
                osll_data = acc->bank->key;
                break;
            case 1:
                osll_data = acc->savings->key;
                break;
            case 2:
                osll_data = acc->loyalty->key;
                break;
            }

        }

        osll_previous->next = new_element;
        new_element->next   = osll_current;
    }

    return osll;
}

void bank_ordered_singly_iterative_print(const BankOrderedSinglyLinkedList *const osll) {
    const BankOrderedSinglyLinkedList *osll_to_print;

    for (osll_to_print = (const BankOrderedSinglyLinkedList*) osll; osll_to_print != NULL; osll_to_print = osll_to_print->next) {
        int osll_data;
        double balance;

        switch (osll_to_print->acc_kind) {
        case 0:
            osll_data = osll_to_print->acc->bank->key;
            balance = osll_to_print->acc->bank->balance;
            break;
        case 1:
            osll_data = osll_to_print->acc->savings->key;
            balance = osll_to_print->acc->savings->balance;
            break;
        case 2:
            osll_data = osll_to_print->acc->loyalty->key;
            balance = osll_to_print->acc->loyalty->balance;
            break;
        }

        printf("Account %d: $ %f\n", osll_data, balance);
    }

}

void bank_ordered_singly_recursive_print(const BankOrderedSinglyLinkedList *const osll) {
    if (osll == NULL)
        return;

//    printf("Data: %d\n", osll->data);
    bank_ordered_singly_recursive_print(osll->next);
}

void bank_ordered_singly_reverse_print(const BankOrderedSinglyLinkedList *const osll) {
    if (osll == NULL)
        return;

    bank_ordered_singly_reverse_print(osll->next);
//    printf("Data: %d\n", osll->data);
}

int bank_ordered_singly_is_empty(const BankOrderedSinglyLinkedList *const osll) {
    return osll == NULL;
}

BankOrderedSinglyLinkedList *bank_ordered_singly_search(const BankOrderedSinglyLinkedList *const osll, int key) {
    const BankOrderedSinglyLinkedList *osll_to_search = (const BankOrderedSinglyLinkedList*) osll;

    int osll_data;

    if (osll_to_search != NULL) {
        switch (osll_to_search->acc_kind) {
        case 0:
            osll_data = osll_to_search->acc->bank->key;
            break;
        case 1:
            osll_data = osll_to_search->acc->savings->key;
            break;
        case 2:
            osll_data = osll_to_search->acc->loyalty->key;
            break;
        }
    }

    while (osll_to_search != NULL && osll_data != key) {
        osll_to_search = osll_to_search->next;

        if (osll_to_search != NULL) {

            switch (osll_to_search->acc_kind) {
            case 0:
                osll_data = osll_to_search->acc->bank->key;
                break;
            case 1:
                osll_data = osll_to_search->acc->savings->key;
                break;
            case 2:
                osll_data = osll_to_search->acc->loyalty->key;
                break;
            }

        }

    }

    return (BankOrderedSinglyLinkedList*) osll_to_search;
}

BankOrderedSinglyLinkedList *bank_ordered_singly_iterative_remove(BankOrderedSinglyLinkedList *osll, int key) {
    BankOrderedSinglyLinkedList *osll_to_remove = osll, *osll_to_remove_before = NULL;

    int osll_data;

    if (osll_to_remove != NULL) {
        switch (osll_to_remove->acc_kind) {
        case 0:
            osll_data = osll_to_remove->acc->bank->key;
            break;
        case 1:
            osll_data = osll_to_remove->acc->savings->key;
            break;
        case 2:
            osll_data = osll_to_remove->acc->loyalty->key;
            break;
        }
    }

    while (osll_to_remove != NULL && osll_data != key) {
        osll_to_remove_before = osll_to_remove;
        osll_to_remove = osll_to_remove->next;

        if (osll_to_remove != NULL) {
            switch (osll_to_remove->acc_kind) {
            case 0:
                osll_data = osll_to_remove->acc->bank->key;
                break;
            case 1:
                osll_data = osll_to_remove->acc->savings->key;
                break;
            case 2:
                osll_data = osll_to_remove->acc->loyalty->key;
                break;
            }
        }

    }

    if (osll_to_remove != NULL) {
        if (osll_to_remove_before == NULL) {
            osll = osll_to_remove->next;
        } else {
            osll_to_remove_before->next = osll_to_remove->next;
        }

        free(osll_to_remove);
    }

    return osll;
}

BankOrderedSinglyLinkedList *bank_ordered_singly_recursive_remove(BankOrderedSinglyLinkedList *osll, int key) {
    if (osll == NULL)
        return NULL;

    int osll_data;

    switch (osll->acc_kind) {
    case 0:
        osll_data = osll->acc->bank->key;
        break;
    case 1:
        osll_data = osll->acc->savings->key;
        break;
    case 2:
        osll_data = osll->acc->loyalty->key;
        break;
    }

    if (osll_data == key) {
        BankOrderedSinglyLinkedList *osll_to_remove = osll;

        osll = osll->next;
        free(osll_to_remove);
    } else {
        osll->next = bank_ordered_singly_recursive_remove(osll->next, key);
    }

    return osll;
}

void bank_ordered_singly_free(BankOrderedSinglyLinkedList *osll) {
    BankOrderedSinglyLinkedList *osll_to_free = osll;

    while (osll_to_free != NULL) {
        osll = osll_to_free->next;

        free(osll_to_free);
        osll_to_free = osll;
    }
}
