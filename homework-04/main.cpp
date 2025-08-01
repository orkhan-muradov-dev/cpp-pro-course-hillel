#include <iostream>
#include <thread>
#include <vector>
#include <functional>
#include <regex>
#include <unordered_map>

class SimpleThreadPool
{
private:
	std::vector<std::thread> threads;

	void cleanup() {
		for (auto& t : threads) {
			if (t.joinable()) { t.join(); }
		}
	}

public:
	explicit SimpleThreadPool(const size_t numThreads) { threads.reserve(numThreads); }

	SimpleThreadPool(const SimpleThreadPool&) = delete;
	SimpleThreadPool& operator=(const SimpleThreadPool&) = delete;
	SimpleThreadPool(SimpleThreadPool&&) = default;
	SimpleThreadPool& operator=(SimpleThreadPool&&) = default;

	template<typename Function, typename... Args>
	void addTask(Function&& function, const std::string& taskName, Args&&... args) {
		threads.emplace_back([function = std::forward<Function>(function), taskName, args...]() mutable {
			std::cout << "Starting task: " << taskName << std::endl;
			function(args...);
			std::cout << "\nCompleted task: " << taskName << std::endl;
			});
	}

	~SimpleThreadPool() { cleanup(); }
};

class Order {
private:
	const size_t ID;
	std::vector<std::string> items;
	double totalPrice;
	std::string status;
	std::string customerEmail;

public:
	Order(const size_t ID, const std::vector<std::string>& items, const std::string& email) : ID(ID), items(items), totalPrice(0.0), status("Raw"), customerEmail(email) {}

	const size_t getID() const { return ID; }
	const std::vector<std::string>& getItems() const { return items; }
	double getTotalPrice() const { return totalPrice; }
	const std::string& getStatus() const { return status; }

	void setTotalPrice(double price) { totalPrice = price; }
	void setStatus(const std::string& newStatus) { status = newStatus; }

	const std::string& getCustomerEmail() const { return customerEmail; }

	void print() const {
		std::cout << "Order #" << ID << " - Status: " << status << ", Total: $" << totalPrice << std::endl;
	}
};

class OrderProcessor {
private:
	bool isOrderValid(const Order& order) {
		std::regex itemFormat("^[a-zA-Z ]+$");

		if (order.getID() < 1) {
			std::cerr << "Order #" << order.getID() << " failed: Invalid ID.\n";
			return false;
		}

		const auto& items = order.getItems();

		if (items.empty()) {
			std::cerr << "Order #" << order.getID() << " failed: No items.\n";
			return false;
		}

		if (items.size() > 10) {
			std::cerr << "Order #" << order.getID() << " failed: Too many items.\n";
			return false;
		}

		for (const auto& item : items) {
			if (!std::regex_match(item, itemFormat)) {
				std::cerr << "Order #" << order.getID() << " failed: Invalid item name '" << item << "'.\n";
				return false;
			}
		}

		return true;
	}

public:
	std::vector<Order> validateOrders(const std::vector<Order>& rawOrders) {
		std::vector<Order> validOrders;

		for (const auto& order : rawOrders) {
			if (isOrderValid(order)) {
				Order validated = order;
				validated.setStatus("Validated");
				validOrders.push_back(validated);
			}
		}

		return validOrders;
	}

	std::vector<Order> calculatePricing(const std::vector<Order>& validOrders) {
		std::unordered_map<std::string, double> priceList = {
			{"Bruschetta", 8.99}, {"Mozzarella Sticks", 7.99}, {"Soup of the Day", 5.99},
			{"Grilled Salmon", 18.99}, {"Chicken Alfredo", 14.99}, {"Steak Frites", 22.99}, {"Vegetarian Pasta", 12.99},
			{"Chocolate Lava Cake", 7.99}, {"Cheesecake", 6.99}, {"Fruit Tart", 7.99},
			{"Soft Drinks", 2.99}, {"Iced Tea", 2.99}, {"Juice", 3.99}, {"Coffee", 2.49}
		};

		std::vector<Order> priced;
		for (auto& order : validOrders) {
			double total = 0.0;
			for (const auto& item : order.getItems()) {
				total += priceList[item];
			}

			Order pricedOrder = order;
			pricedOrder.setTotalPrice(total);
			pricedOrder.setStatus("Priced");
			priced.push_back(pricedOrder);
		}
		return priced;
	}

	std::vector<Order> checkInventory(const std::vector<Order>& pricedOrders) {
		std::unordered_map<std::string, int> inventory = {
			{"Bruschetta", 8}, {"Mozzarella Sticks", 7}, {"Soup of the Day", 5},
			{"Grilled Salmon", 8}, {"Chicken Alfredo", 4}, {"Steak Frites", 4}, {"Vegetarian Pasta", 3},
			{"Chocolate Lava Cake", 7}, {"Cheesecake", 6}, {"Fruit Tart", 7},
			{"Soft Drinks", 24}, {"Iced Tea", 21}, {"Juice", 30}, {"Coffee", 18}
		};

		std::vector<Order> inStockOrders;
		for (auto& order : pricedOrders) {
			bool inStock = true;

			for (const auto& item : order.getItems()) {
				if (inventory[item] <= 0) {
					inStock = false;
					std::cerr << "Order #" << order.getID() << " failed - item out of stock: " << item << std::endl;
					break;
				}
			}
			
			if (inStock) {
				Order updated = order;
				updated.setStatus("InStock");
				inStockOrders.push_back(updated);
			}
		}
		return inStockOrders;
	}

	void generateInvoices(const std::vector<Order>& finalOrders) {
		for (const auto& order : finalOrders) {
			std::cout << "\nGenerating invoice for Order #" << order.getID() << ", Total: $" << order.getTotalPrice() << std::endl
				      << "Sending invoice for Order #" << order.getID() << " to " << order.getCustomerEmail() << std::endl;
		}
		std::cout << std::endl;
	}
};

void factorial(const size_t n = 15) {
	size_t result = 1;

	for (size_t i = 1; i <= n; ++i) { result *= i; }

	std::cout << "Factorial of " << n << " is " << result << std::endl;
}

void squaresSum(const int start = 1, const int end = 1000) {
	size_t sum = 0;

	for (size_t i = start; i <= end; ++i) { sum += i * i; }

	std::cout << "Sum of squares from numbers " << start << " to " << end << " is " << sum << std::endl;
}

void fibonacci(const size_t end = 30) {
	size_t t1 = 0, t2 = 1;

	std::cout << "Fibonacci sequence up to " << end << " terms: ";
	for (size_t i = 1; i <= end; ++i) {
		std::cout << t1;
		if (i < end) { std::cout << ", "; }

		size_t nextTerm = t1 + t2;
		t1 = t2;
		t2 = nextTerm;
	}
	std::cout << std::endl;
}

void simpleNum(const size_t till = 100) {
	std::cout << "List of prime numbers till " << till << ": ";

	for (size_t i = 2; i <= till; ++i) {
		bool prime = true;

		for (size_t j = 2; j * j <= i; ++j){
			if (i % j == 0) { prime = false; break; }
		}

		if (prime) { std::cout << i << (i < till ? ", " : ""); }
	}
}

int main()
{
	std::cout << "--- Task 1: Parallel calculation of mathematical functions ---\n" << std::endl;
	
	{
		SimpleThreadPool pool(std::thread::hardware_concurrency());
		pool.addTask(factorial, "Task 1", 15);
		pool.addTask(squaresSum, "Task 2", 1, 1000);
		pool.addTask(fibonacci, "Task 3", 30);
		pool.addTask(simpleNum, "Task 4", 100);
	}

	std::cout << "\n--- Task 2: Order processing system ---\n" << std::endl;

	std::vector<Order> rawOrders = {
		Order(1, {"Bruschetta", "Iced Tea"}, "alice@example.com"),
		Order(2, {"Cheesecake"}, "bob@example.org"),
		Order(3, {"Steak Frites", "Vegetarian Pasta", "Soft Drinks"}, "carol@example.net")
	};

	OrderProcessor processor;

	std::vector<Order> validatedOrders;
	std::vector<Order> pricedOrders;
	std::vector<Order> inStockOrders;

	std::thread t1([&processor, &rawOrders, &validatedOrders]() {
		std::cout << "[Flow 1] Validating orders...\n";
		validatedOrders = processor.validateOrders(rawOrders);
		std::cout << "[Flow 1] Completed.\n" << std::endl;
		});

	std::thread t2([&processor, &validatedOrders, &pricedOrders, &t1]() {
		t1.join();
		std::cout << "[Flow 2] Calculating prices...\n";
		pricedOrders = processor.calculatePricing(validatedOrders);
		std::cout << "[Flow 2] Completed.\n" << std::endl;
		});

	std::thread t3([&processor, &pricedOrders, &inStockOrders, &t2]() {
		t2.join();
		std::cout << "[Flow 3] Checking inventory...\n";
		inStockOrders = processor.checkInventory(pricedOrders);
		std::cout << "[Flow 3] Completed.\n" << std::endl;
		});

	std::thread t4([&processor, &inStockOrders, &t3]() {
		t3.join();
		std::cout << "[Flow 4] Generating invoices and sending to customers...\n";
		processor.generateInvoices(inStockOrders);
		std::cout << "[Flow 4] Completed.\n" << std::endl;
		});

	t4.join();

	return 0;
}