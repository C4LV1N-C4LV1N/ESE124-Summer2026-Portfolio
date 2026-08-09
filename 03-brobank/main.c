#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "bank.h"

#define BALANCE_FILE "balance.txt"
#define TRANSACTION_FILE "transactions.txt"
#define PIN_CODE "124"
#define MAX_PIN_ATTEMPTS 3
#define ACCOUNT_COUNT 4

static void trim_newline(char *line) {
    size_t len = strlen(line);
    if (len > 0 && line[len - 1] == '\n') {
        line[len - 1] = '\0';
    }
}

static int read_line(char *buffer, size_t size) {
    if (!fgets(buffer, (int)size, stdin)) return 0;
    trim_newline(buffer);
    return 1;
}

static int parse_int(const char *text, int *value) {
    char *end;
    long result = strtol(text, &end, 10);
    if (end == text || *end != '\0') return 0;
    *value = (int)result;
    return 1;
}

static int parse_double(const char *text, double *value) {
    char *end;
    double result = strtod(text, &end);
    if (end == text || *end != '\0') return 0;
    *value = result;
    return 1;
}

static int prompt_int(const char *prompt, int *value) {
    char line[128];
    printf("%s", prompt);
    if (!read_line(line, sizeof line)) return 0;
    return parse_int(line, value);
}

static int prompt_double(const char *prompt, double *value) {
    char line[128];
    printf("%s", prompt);
    if (!read_line(line, sizeof line)) return 0;
    return parse_double(line, value);
}

static int load_balance(BroBank *bank, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) return 0;
    for (int i = 0; i < bank->account_count; ++i) {
        if (fscanf(file, "%lf", &bank->balances[i]) != 1) {
            fclose(file);
            return 0;
        }
    }
    fclose(file);
    return 1;
}

static int save_balance(const BroBank *bank, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) return 0;
    for (int i = 0; i < bank->account_count; ++i) {
        fprintf(file, "%.2f\n", bank->balances[i]);
    }
    fclose(file);
    return 1;
}

static void record_transaction(const char *line) {
    FILE *file = fopen(TRANSACTION_FILE, "a");
    if (!file) return;
    fprintf(file, "%s\n", line);
    fclose(file);
}

static int check_pin(void) {
    char pin[16];
    for (int attempt = 1; attempt <= MAX_PIN_ATTEMPTS; ++attempt) {
        printf("Enter 3-digit PIN: ");
        if (!read_line(pin, sizeof pin)) return 0;
        if (strlen(pin) != 3) {
            printf("PIN must be exactly 3 digits.\n");
            continue;
        }
        int valid = 1;
        for (size_t i = 0; i < strlen(pin); ++i) {
            if (!isdigit((unsigned char)pin[i])) {
                valid = 0;
                break;
            }
        }
        if (!valid) {
            printf("PIN must contain only digits.\n");
            continue;
        }
        if (strcmp(pin, PIN_CODE) == 0) {
            return 1;
        }
        printf("Incorrect PIN.\n");
    }
    return 0;
}

static void print_balances(const BroBank *bank) {
    printf("Current account balances:\n");
    for (int i = 0; i < bank->account_count; ++i) {
        printf("  Account %d: $%.2f\n", i, bank->balances[i]);
    }
}

static int valid_account(int account) {
    return account >= 0 && account < ACCOUNT_COUNT;
}

static void print_menu(void) {
    printf("\nBroBank Menu:\n");
    printf("1) Deposit\n");
    printf("2) Withdraw\n");
    printf("3) Transfer\n");
    printf("4) Interest calculator\n");
    printf("5) Undo last transaction\n");
    printf("6) Quit\n");
}

int main(void) {
    BroBank bank;
    bank_init(&bank, ACCOUNT_COUNT);
    if (!load_balance(&bank, BALANCE_FILE)) {
        bank.balances[0] = 100.0;
        bank.balances[1] = 50.0;
        bank.balances[2] = 25.0;
        bank.balances[3] = 0.0;
        printf("Balance file not found. Starting with default balances.\n");
    } else {
        printf("Loaded balances from %s.\n", BALANCE_FILE);
    }

    FILE *history = fopen(TRANSACTION_FILE, "w");
    if (history) fclose(history);

    if (!check_pin()) {
        printf("Too many invalid PIN attempts. Exiting.\n");
        return 1;
    }

    printf("PIN accepted. Welcome to BroBank!\n");
    print_balances(&bank);

    while (1) {
        int option;
        print_menu();
        if (!prompt_int("Enter choice: ", &option)) {
            printf("Invalid selection. Please enter a number.\n");
            continue;
        }

        if (option == 6) {
            if (save_balance(&bank, BALANCE_FILE)) {
                printf("Balances saved to %s.\n", BALANCE_FILE);
            } else {
                printf("Could not save balances.\n");
            }
            printf("Thank you for using BroBank. Goodbye!\n");
            break;
        }

        if (option == 1) {
            int account;
            double amount;
            if (!prompt_int("Enter account number (0-3): ", &account) || !valid_account(account)) {
                printf("Invalid account number.\n");
                continue;
            }
            if (!prompt_double("Enter deposit amount: ", &amount) || amount <= 0.0) {
                printf("Invalid deposit amount.\n");
                continue;
            }
            Transaction tx = {TX_DEPOSIT, account, account, amount};
            if (bank_submit(&bank, tx) && bank_process_next(&bank)) {
                printf("Deposit successful.\n");
                char line[128];
                snprintf(line, sizeof line, "DEPOSIT account %d amount %.2f", account, amount);
                record_transaction(line);
            } else {
                printf("Deposit failed.\n");
            }
            print_balances(&bank);
            continue;
        }

        if (option == 2) {
            int account;
            double amount;
            if (!prompt_int("Enter account number (0-3): ", &account) || !valid_account(account)) {
                printf("Invalid account number.\n");
                continue;
            }
            if (!prompt_double("Enter withdraw amount: ", &amount) || amount <= 0.0) {
                printf("Invalid withdraw amount.\n");
                continue;
            }
            Transaction tx = {TX_WITHDRAW, account, account, amount};
            if (bank_submit(&bank, tx) && bank_process_next(&bank)) {
                printf("Withdrawal successful.\n");
                char line[128];
                snprintf(line, sizeof line, "WITHDRAW account %d amount %.2f", account, amount);
                record_transaction(line);
            } else {
                printf("Withdrawal failed. Insufficient funds or invalid request.\n");
            }
            print_balances(&bank);
            continue;
        }

        if (option == 3) {
            int from, to;
            double amount;
            if (!prompt_int("Enter source account (0-3): ", &from) || !valid_account(from)) {
                printf("Invalid source account.\n");
                continue;
            }
            if (!prompt_int("Enter destination account (0-3): ", &to) || !valid_account(to)) {
                printf("Invalid destination account.\n");
                continue;
            }
            if (!prompt_double("Enter transfer amount: ", &amount) || amount <= 0.0) {
                printf("Invalid transfer amount.\n");
                continue;
            }
            Transaction tx = {TX_TRANSFER, from, to, amount};
            if (bank_submit(&bank, tx) && bank_process_next(&bank)) {
                printf("Transfer successful.\n");
                char line[128];
                snprintf(line, sizeof line, "TRANSFER %d -> %d amount %.2f", from, to, amount);
                record_transaction(line);
            } else {
                printf("Transfer failed. Insufficient funds or invalid request.\n");
            }
            print_balances(&bank);
            continue;
        }

        if (option == 4) {
            int account;
            double rate, months;
            if (!prompt_int("Enter account number (0-3): ", &account) || !valid_account(account)) {
                printf("Invalid account number.\n");
                continue;
            }
            if (!prompt_double("Enter annual interest rate (percent): ", &rate) || rate < 0.0) {
                printf("Invalid interest rate.\n");
                continue;
            }
            if (!prompt_double("Enter months to calculate: ", &months) || months < 0.0) {
                printf("Invalid number of months.\n");
                continue;
            }
            double interest = bank.balances[account] * (rate / 100.0) * (months / 12.0);
            printf("Estimated interest for account %d: $%.2f\n", account, interest);
            char line[128];
            snprintf(line, sizeof line, "INTEREST account %d rate %.2f months %.1f result %.2f", account, rate, months, interest);
            record_transaction(line);
            continue;
        }

        if (option == 5) {
            if (bank_undo(&bank)) {
                printf("Undo successful.\n");
                record_transaction("UNDO last transaction");
            } else {
                printf("Nothing to undo.\n");
            }
            print_balances(&bank);
            continue;
        }

        printf("Unknown option. Please select 1-6.\n");
    }

    return 0;
}
