#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ACCOUNTS 100
#define DATA_FILE "accounts.txt"

typedef struct {
    int id;
    char name[50];
    double balance;
} Account;

static Account g_accounts[MAX_ACCOUNTS];
static int g_count = 0;

static void clear_stdin(void) {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {}
}

static void load_accounts(void);
static void save_accounts(void);
static int find_account_index(int id);
static int next_account_id(void);

static void create_account(void);
static void deposit_money(void);
static void withdraw_money(void);
static void show_balance(void);
static void list_accounts(void);

int main(void) {
    int choice;

    load_accounts();

    while (1) {
        printf("\n==== Simple Bank Menu ====\n");
        printf("1. Create Account\n");
        printf("2. Deposit\n");
        printf("3. Withdraw\n");
        printf("4. Show Account Balance\n");
        printf("5. List All Accounts\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            clear_stdin();
            printf("Invalid input. Please enter a number.\n");
            continue;
        }

        switch (choice) {
            case 1:
                create_account();
                break;
            case 2:
                deposit_money();
                break;
            case 3:
                withdraw_money();
                break;
            case 4:
                show_balance();
                break;
            case 5:
                list_accounts();
                break;
            case 0:
                printf("Saving data and exiting...\n");
                save_accounts();
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

/* Reads accounts from the data file into memory if present. */
static void load_accounts(void) {
    FILE *fp = fopen(DATA_FILE, "r");
    if (!fp) {
        return; // No file yet; will be created on first save.
    }

    char line[256];
    while (fgets(line, sizeof(line), fp)) {
        if (g_count >= MAX_ACCOUNTS) {
            printf("Warning: maximum number of accounts reached. Some may not be loaded.\n");
            break;
        }
        Account a;
        if (sscanf(line, "%d|%49[^|]|%lf", &a.id, a.name, &a.balance) == 3) {
            g_accounts[g_count++] = a;
        }
    }

    fclose(fp);
}

/* Writes all in-memory accounts back to the data file. */
static void save_accounts(void) {
    FILE *fp = fopen(DATA_FILE, "w");
    if (!fp) {
        printf("Error: could not open %s for writing.\n", DATA_FILE);
        return;
    }

    for (int i = 0; i < g_count; i++) {
        fprintf(fp, "%d|%s|%.2f\n", g_accounts[i].id, g_accounts[i].name, g_accounts[i].balance);
    }

    fclose(fp);
}

/* Returns the array index for a given account ID, or -1 if missing. */
static int find_account_index(int id) {
    for (int i = 0; i < g_count; i++) {
        if (g_accounts[i].id == id) return i;
    }
    return -1;
}

/* Computes the next unique account ID as 1 + current maximum. */
static int next_account_id(void) {
    int max_id = 0;
    for (int i = 0; i < g_count; i++) {
        if (g_accounts[i].id > max_id) max_id = g_accounts[i].id;
    }
    return max_id + 1;
}

/* Creates a new account with holder name and initial deposit (>= 0). */
static void create_account(void) {
    if (g_count >= MAX_ACCOUNTS) {
        printf("Cannot create more accounts (limit reached).\n");
        return;
    }

    Account a;
    a.id = next_account_id();

    printf("Enter account holder name: ");
    clear_stdin(); // remove leftover newline before fgets
    if (!fgets(a.name, sizeof(a.name), stdin)) {
        printf("Failed to read name.\n");
        return;
    }
    size_t n = strlen(a.name);
    if (n > 0 && a.name[n - 1] == '\n') a.name[n - 1] = '\0';

    printf("Enter initial deposit amount: ");
    if (scanf("%lf", &a.balance) != 1 || a.balance < 0) {
        clear_stdin();
        printf("Invalid amount. Account not created.\n");
        return;
    }

    g_accounts[g_count++] = a;
    save_accounts();
    printf("Account created successfully! Account ID: %d\n", a.id);
}

/* Adds money to an existing account. Amount must be > 0. */
static void deposit_money(void) {
    int id;
    double amount;

    printf("Enter account ID: ");
    if (scanf("%d", &id) != 1) {
        clear_stdin();
        printf("Invalid account ID.\n");
        return;
    }

    int idx = find_account_index(id);
    if (idx == -1) {
        printf("Account not found.\n");
        return;
    }

    printf("Enter amount to deposit: ");
    if (scanf("%lf", &amount) != 1 || amount <= 0) {
        clear_stdin();
        printf("Invalid amount.\n");
        return;
    }

    g_accounts[idx].balance += amount;
    save_accounts();
    printf("Deposit successful. New balance: %.2f\n", g_accounts[idx].balance);
}

/* Withdraws funds if sufficient balance exists. Amount must be > 0. */
static void withdraw_money(void) {
    int id;
    double amount;

    printf("Enter account ID: ");
    if (scanf("%d", &id) != 1) {
        clear_stdin();
        printf("Invalid account ID.\n");
        return;
    }

    int idx = find_account_index(id);
    if (idx == -1) {
        printf("Account not found.\n");
        return;
    }

    printf("Enter amount to withdraw: ");
    if (scanf("%lf", &amount) != 1 || amount <= 0) {
        clear_stdin();
        printf("Invalid amount.\n");
        return;
    }

    if (amount > g_accounts[idx].balance) {
        printf("Insufficient funds. Current balance: %.2f\n", g_accounts[idx].balance);
        return;
    }

    g_accounts[idx].balance -= amount;
    save_accounts();
    printf("Withdrawal successful. New balance: %.2f\n", g_accounts[idx].balance);
}

/* Displays balance information for a specific account by ID. */
static void show_balance(void) {
    int id;
    printf("Enter account ID: ");
    if (scanf("%d", &id) != 1) {
        clear_stdin();
        printf("Invalid account ID.\n");
        return;
    }

    int idx = find_account_index(id);
    if (idx == -1) {
        printf("Account not found.\n");
        return;
    }

    printf("\nAccount ID: %d\n", g_accounts[idx].id);
    printf("Name      : %s\n", g_accounts[idx].name);
    printf("Balance   : %.2f\n", g_accounts[idx].balance);
}

/* Prints all stored accounts. */
static void list_accounts(void) {
    if (g_count == 0) {
        printf("No accounts found.\n");
        return;
    }

    printf("\n---- All Accounts ----\n");
    for (int i = 0; i < g_count; i++) {
        printf("ID: %d | Name: %s | Balance: %.2f\n",
               g_accounts[i].id, g_accounts[i].name, g_accounts[i].balance);
    }
}
