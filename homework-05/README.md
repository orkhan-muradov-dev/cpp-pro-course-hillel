# Homework #5: Synchronization and Thread Safety in a Multithreaded Bank System



## Task Description

This assignment involves developing a multithreaded banking system simulation where multiple cashier threads perform concurrent transactions on bank accounts. The focus is on demonstrating the issues of race conditions in an unsafe implementation and then correcting them with proper synchronization and thread safety mechanisms.



### Requirements:

- Implement a `BankAccount` class with methods:

  * `deposit(amount)` — add funds
  * `withdraw(amount)` — remove funds with balance check
  * `get_balance()` — query current balance

- Implement a `BankStatistics` class for transaction tracking:

  * `record_transaction(amount)` — log each transaction
  * `get_total_transactions()` — count of all transactions
  * `get_total_amount()` — sum of all transaction amounts

- Simulate 5 cashier threads performing 100 random deposit or withdrawal operations each.

- Part 1: Implement an unsafe version **without synchronization** to observe race conditions and inconsistencies.

- Part 2: Implement a safe version **with synchronization** using mutexes and atomic variables to ensure thread safety and consistent results.



## Files

- `main.cpp` — Program entry, menu to select simulation version

- `unsafe_bank.h/cpp` — Unsafe bank account and statistics classes (no synchronization)

- `safe_bank.h/cpp` — Thread-safe bank account and statistics classes using mutex and atomic variables

- `bank_simulation.h` — Simulation framework running cashier threads and collecting statistics

- `banknote.h/cpp` — Functions generating random deposit/withdraw amounts

- Other headers and source files supporting the simulation logic



## Compilation and Execution

```bash

g++ -std=c++20 -pthread -o bank_sim main.cpp unsafe_bank.cpp safe_bank.cpp banknote.cpp

./bank_sim
