#include <iostream>
#include <thread>
#include <vector>
#include "unsafe_bank.h"
#include "bank_simulation.h"

// UnsafeBankAccount class

void UnsafeBankAccount::deposit(double amount) {
	balance += amount;
}

bool UnsafeBankAccount::withdraw(double amount) {
	if (balance >= amount) {
		balance -= amount;
		return true;
	}
	return false;
}

double UnsafeBankAccount::get_balance() const {
	return balance;
}

// UnsafeBankStatistics class

void UnsafeBankStatistics::record_transaction(double amount) {
	transaction_count++;
	total_amount += amount;
}

size_t UnsafeBankStatistics::get_total_transactions() const { return transaction_count; }
double UnsafeBankStatistics::get_total_amount() const { return total_amount; }

void runUnsafeSimulation() {
	bankSimulation<UnsafeBankAccount, UnsafeBankStatistics>("Unsafe Version");
}