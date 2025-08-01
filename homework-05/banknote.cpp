#include <random>
#include "banknote.h"

size_t randDepositBanknote() {
	size_t roll = rand() % 5;

	switch (roll) {
	case 0: return 50;
	case 1: return 100;
	case 2: return 200;
	case 3: return 500;
	}
}

size_t randWithdrawBanknote() {
	size_t roll = rand() % 5;
	
	switch (roll) {
	case 0: return 10;
	case 1: return 20;
	case 2: return 50;
	case 3: return 100;
	case 4: return 200;
	}
}