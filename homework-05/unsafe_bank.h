#pragma once

class UnsafeBankAccount {
private:
    double balance = 1000.0;

public:
    void deposit(double amount);

    bool withdraw(double amount);

    double get_balance() const;
};

class UnsafeBankStatistics {
private:
    size_t transaction_count = 0;
    double total_amount = 0.0;

public:
    void record_transaction(double amount);

    size_t get_total_transactions() const;

    double get_total_amount() const;
};

void runUnsafeSimulation();