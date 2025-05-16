#ifndef MANAGER_H
#define MANAGER_H

#define MAX_LEN 100

typedef struct {
    char service[MAX_LEN];
    char username[MAX_LEN];
    char password[MAX_LEN];
} Account;

void addAccount(Account **accounts, int *count);
void printAccounts(const Account *accounts, int count);
void saveToFile(const Account *accounts, int count, const char *filename);
void loadFromFile(Account **accounts, int *count, const char *filename);

void removeAccount(Account **accounts, int *count);
void searchAccount(const Account *accounts, int count, const char *service);
void sortAccounts(Account *accounts, int count, int (*cmp)(const char *, const char *));
int compareAscending(const char *a, const char *b);
int compareDescending(const char *a, const char *b);

#endif
