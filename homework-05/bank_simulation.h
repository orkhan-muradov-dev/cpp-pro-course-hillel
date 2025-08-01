#pragma once

#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include "banknote.h"

template <typename BankAccountType, typename StatisticsType>
void cashier_work(BankAccountType& account, StatisticsType& stats) {
	for (size_t i = 0; i < 100; ++i) {
		size_t amount;

		if (rand() % 2) {
			amount = randDepositBanknote();
			account.deposit(amount);
			stats.record_transaction(amount);
		}
		else {
			amount = randWithdrawBanknote();
			if (account.withdraw(amount)) {
				stats.record_transaction(amount);
			}
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}

template <typename AccountType, typename StatisticsType>
void bankSimulation(const std::string& label) {
	AccountType account;
	StatisticsType stats;

	std::vector<std::thread> threads;

	std::cout << "\n\033[34m=== Bank Simulation Results (" << label << ") ===\033[0m";
	std::cout << "\nInitial balance : " << account.get_balance();

	for (size_t i = 0; i < 5; ++i) {
		threads.emplace_back(cashier_work<AccountType, StatisticsType>, std::ref(account), std::ref(stats));
	}

	for (auto& t : threads) {
		t.join();
	}

	std::cout << "\nFinal balance : " << account.get_balance()
		<< "\nTotal transactions : " << stats.get_total_transactions()
		<< "\nTotal transaction amount : " << stats.get_total_amount()
		<< "\nAll cashiers completed work!\n";
}