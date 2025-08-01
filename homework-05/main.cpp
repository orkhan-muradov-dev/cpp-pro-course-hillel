#include <iostream>
#include "unsafe_bank.h"
#include "safe_bank.h"

int main() {
	srand(time(NULL));

	bool retry = true;

	std::cout << "\t\t\tC++ Multithreading Demonstrations with and without Synchronization\n";

	do
	{
		retry = false;

		std::cout << "\n=== MULTITHREADING DEMONSTRATIONS MENU ===\n"
			   	  << "1. Unsafe Version (without Synchronization)\n"
				  << "2. Safe Version (with Synchronization)\n"
				  << "0. Exit\n"
				  << "Choose option: ";

		size_t choice;
		std::cin >> choice;

		switch (choice) {
		case 0: break;
		case 1: runUnsafeSimulation(); break;
		case 2: runSafeSimulation(); break;
		default: retry = true;  std::cout << "Invalid choice! Please try again.\n"; break;
		}
	} while (retry);

	return 0;
}