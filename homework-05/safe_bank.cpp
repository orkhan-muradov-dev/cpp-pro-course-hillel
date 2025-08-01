#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <atomic>
#include "safe_bank.h"
#include "bank_simulation.h"

// SafeBankAccount class

void SafeBankAccount::deposit(double amount) {
	std::lock_guard<std::mutex> lock(balance_mutex);
	balance += amount;
}

bool SafeBankAccount::withdraw(double amount) {
	std::lock_guard<std::mutex> lock(balance_mutex);
	if (balance >= amount) {
		balance -= amount;
		return true;
	}
	return false;
}

double SafeBankAccount::get_balance() const {
	std::lock_guard<std::mutex> lock(balance_mutex);
	return balance;
}

// SafeBankStatistics class

void SafeBankStatistics::record_transaction(double amount) {
	transaction_count++;
	total_amount += amount;
}

size_t SafeBankStatistics::get_total_transactions() const { return transaction_count.load(); }

double SafeBankStatistics::get_total_amount() const { return total_amount.load(); }

void runSafeSimulation() {
	bankSimulation<SafeBankAccount, SafeBankStatistics>("Safe Version");
}