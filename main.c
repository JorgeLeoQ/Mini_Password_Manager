#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "manager.h"

#define DATA_FILE "data.txt"

int main() {
    Account *accounts = NULL;
    int count = 0;
    int choice;

    loadFromFile(&accounts, &count, DATA_FILE);

    do {
        printf("\nMini Password Manager\n");
        printf("1. Add account\n");
        printf("2. View accounts\n");
        printf("3. Remove account\n");
        printf("4. Search account\n");
        printf("5. Sort accounts (A-Z)\n");
        printf("6. Sort accounts (Z-A)\n");
        printf("0. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addAccount(&accounts, &count);
                break;
            case 2:
                printAccounts(accounts, count);
                break;
            case 3:
                removeAccount(&accounts, &count);
                break;
            case 4: {
                char service[MAX_LEN];
                printf("Enter service to search: ");
                scanf("%s", service);
                searchAccount(accounts, count, service);
                break;
            }
            case 5:
                sortAccounts(accounts, count, compareAscending);
                printf("Accounts sorted A-Z.\n");
                break;
            case 6:
                sortAccounts(accounts, count, compareDescending);
                printf("Accounts sorted Z-A.\n");
                break;
            case 0:
                saveToFile(accounts, count, DATA_FILE);
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 0);

    free(accounts);
    return 0;
}