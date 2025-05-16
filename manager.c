#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "manager.h"
#include "utils.h"

#define XOR_KEY 0x5A  // chiave di cifratura XOR

void addAccount(Account **accounts, int *count) {
    (*count)++;
    *accounts = realloc(*accounts, (*count) * sizeof(Account));
    if (*accounts == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(1);
    }

    printf("Enter service: ");
    scanf("%s", (*accounts)[*count - 1].service);
    printf("Enter username: ");
    scanf("%s", (*accounts)[*count - 1].username);
    printf("Enter password: ");
    scanf("%s", (*accounts)[*count - 1].password);

    // Cifra la password prima di salvarla in memoria
    xorEncryptDecrypt((*accounts)[*count - 1].password, XOR_KEY);
}

void printAccounts(const Account *accounts, int count) {
    printf("\nSaved Accounts:\n");
    for (int i = 0; i < count; i++) {
        char decrypted[MAX_LEN];
        strcpy(decrypted, accounts[i].password);
        xorEncryptDecrypt(decrypted, XOR_KEY);  // decifra per visualizzare

        printf("%d. %s - %s - %s\n", i + 1,
               accounts[i].service,
               accounts[i].username,
               decrypted);
    }
}

void saveToFile(const Account *accounts, int count, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Error opening file for writing");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%s;%s;%s\n",
                accounts[i].service,
                accounts[i].username,
                accounts[i].password);  // password già cifrata in memoria
    }

    fclose(file);
    printf("Accounts saved to '%s'\n", filename);
}

void loadFromFile(Account **accounts, int *count, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("No data file found. Starting with empty list.\n");
        return;
    }

    char line[3 * MAX_LEN];
    while (fgets(line, sizeof(line), file)) {
        *accounts = realloc(*accounts, (*count + 1) * sizeof(Account));
        if (*accounts == NULL) {
            fprintf(stderr, "Memory allocation failed.\n");
            exit(1);
        }

        Account *acc = &(*accounts)[*count];
        sscanf(line, "%99[^;];%99[^;];%99[^\n]",
               acc->service, acc->username, acc->password);

        // Decifra subito dopo aver letto
        xorEncryptDecrypt(acc->password, XOR_KEY);

        (*count)++;
    }

    fclose(file);
    printf("Loaded %d account(s) from '%s'\n", *count, filename);
}

void removeAccount(Account **accounts, int *count) {
    if (*count == 0) {
        printf("No accounts to remove.\n");
        return;
    }

    char service[MAX_LEN];
    printf("Enter service name to remove: ");
    scanf("%s", service);

    int found = 0;
    for (int i = 0; i < *count; i++) {
        if (strcmp((*accounts)[i].service, service) == 0) {
            found = 1;
            for (int j = i; j < *count - 1; j++) {
                (*accounts)[j] = (*accounts)[j + 1];
            }
            (*count)--;
            *accounts = realloc(*accounts, (*count) * sizeof(Account));
            printf("Account removed.\n");
            break;
        }
    }

    if (!found) {
        printf("Service not found.\n");
    }
}

void searchAccount(const Account *accounts, int count, const char *service) {
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (strcmp(accounts[i].service, service) == 0) {
            char decrypted[MAX_LEN];
            strcpy(decrypted, accounts[i].password);
            xorEncryptDecrypt(decrypted, XOR_KEY);  // decifra per mostrare

            printf("Found: %s - %s - %s\n",
                   accounts[i].service,
                   accounts[i].username,
                   decrypted);
            found = 1;
        }
    }

    if (!found) {
        printf("No account found for service: %s\n", service);
    }
}

void sortAccounts(Account *accounts, int count, int (*cmp)(const char *, const char *)) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (cmp(accounts[i].service, accounts[j].service) > 0) {
                Account temp = accounts[i];
                accounts[i] = accounts[j];
                accounts[j] = temp;
            }
        }
    }
}

int compareAscending(const char *a, const char *b) {
    return strcmp(a, b);
}

int compareDescending(const char *a, const char *b) {
    return strcmp(b, a);
}
