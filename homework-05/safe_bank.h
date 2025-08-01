#pragma once
#include <mutex>

class SafeBankAccount {
private:
    double balance = 1000.0;
    mutable std::mutex balance_mutex;

public:
    void deposit(double amount);

    bool withdraw(double amount);

    double get_balance() const;
};

class SafeBankStatistics {
private:
    std::atomic<size_t> transaction_count{ 0 };
    std::atomic<double> total_amount{ 0.0 };

public:
    void record_transaction(double amount);

    size_t get_total_transactions() const;

    double get_total_amount() const;
};

void runSafeSimulation();