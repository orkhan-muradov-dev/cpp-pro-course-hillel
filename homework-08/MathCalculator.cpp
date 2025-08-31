// MathCalculator.cpp - A console application to test the MathLib static library.

#include <iostream>
#include <string>
#include <limits>
#include <memory>
#include "MathLib.h"

// Helper function to create a border for section titles to improve readability.
void titleBorder(const std::string& TITLE) {
    for (size_t i = 0; i < TITLE.size(); ++i) {
        std::cout << "-";
    }
    std::cout << std::endl << std::endl;
}

// Helper function to get a valid integer from user input
int getIntInput(const std::string& prompt) {
    int value;

    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            return value;
        }
        else {
            std::cout << "Invalid input. Please enter an integer.\n\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

// Helper function to get a valid double from user input
double getDoubleInput(const std::string& prompt) {
    double value;

    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            return value;
        }
        else {
            std::cout << "Invalid input. Please enter a number.\n\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

// Function to print a double array
void printArray(const double arr[], size_t size) {
    std::cout << "[ ";
    for (size_t i = 0; i < size; ++i) {
        std::cout << arr[i] << (i < size - 1 ? ", " : "");
    }
    std::cout << " ]" << std::endl;
}

// Demonstrates a sorting algorithm on a demo array.
void demonstrateSorting(ISorter& sorter, const std::string& sorterName) {
    double arr[] = { 10.5, 2.3, 50.1, -5.0, 18.2 };
    size_t size = sizeof(arr) / sizeof(arr[0]);

    MathLib::sortArray(arr, size, &sorter);

    std::cout << "Sorted with " << sorterName << ": ";
    printArray(arr, size);
}

// Function to handle basic arithmetic operations
void basicOperations() {
    const std::string G_TITLE = "--- Basic Operations ---";
    std::cout << G_TITLE << std::endl;

    double num1 = getDoubleInput("Enter first number: ");
    double num2 = getDoubleInput("Enter second number: ");

    std::cout << "\nAddition: " << MathLib::add(num1, num2) << std::endl;
    std::cout << "Subtraction: " << MathLib::subtract(num1, num2) << std::endl;
    std::cout << "Multiplication: " << MathLib::multiply(num1, num2) << std::endl;
    try {
        std::cout << "Division: " << MathLib::divide(num1, num2) << std::endl;
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    titleBorder(G_TITLE);
}

// Function to handle mathematical functions
void mathFunctions() {
    const std::string G_TITLE = "--- Mathematical Functions ---";
    std::cout << G_TITLE << std::endl;

    double base = getDoubleInput("Enter base for power function: ");
    int exponent = getIntInput("Enter integer exponent: ");
    std::cout << "Power(" << base << ", " << exponent << "): " << MathLib::power(base, exponent) << std::endl;

    double value = getDoubleInput("\nEnter a value for square root: ");
    try {
        std::cout << "Square Root of " << value << ": " << MathLib::squareRoot(value) << std::endl;
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    double absVal = getDoubleInput("\nEnter a value for absolute value: ");
    std::cout << "Absolute value of " << absVal << ": " << MathLib::absoluteValue(absVal) << std::endl;
    titleBorder(G_TITLE);
}

// Function to handle array operations
void arrayOperations() {
    const std::string G_TITLE = "--- Array Operations ---";
    std::cout << G_TITLE << std::endl;

    int arraySizeInt = getIntInput("Enter the number of elements in the array: ");
    if (arraySizeInt <= 0) {
        std::cout << "Array size must be positive." << std::endl;
        return;
    }
    size_t arraySize = static_cast<size_t>(arraySizeInt);

    std::unique_ptr<double[]> arr(new double[arraySize]);
    std::cout << "\nEnter " << arraySize << " numbers:" << std::endl;
    for (size_t i = 0; i < arraySize; ++i) {
        arr[i] = getDoubleInput("Element " + std::to_string(i + 1) + ": ");
    }

    std::cout << "\nOriginal array: ";
    printArray(arr.get(), arraySize);

    try {
        std::cout << "\nMax value: " << MathLib::findMax(arr.get(), arraySize) << std::endl;
        std::cout << "Min value: " << MathLib::findMin(arr.get(), arraySize) << std::endl;
        std::cout << "Sum: " << MathLib::calculateSum(arr.get(), arraySize) << std::endl;
        std::cout << "Average: " << MathLib::calculateAverage(arr.get(), arraySize) << std::endl;

        std::cout << "\nChoose sorting algorithm:" << std::endl;
        std::cout << "1. Bubble Sort" << std::endl;
        std::cout << "2. Selection Sort" << std::endl;
        std::cout << "3. Insertion Sort" << std::endl;
        std::cout << "4. Merge Sort" << std::endl;

        int sortChoice = getIntInput("Your choice: ");
        std::unique_ptr<ISorter> sorter;
        switch (sortChoice) {
        case 1: sorter = std::make_unique<BubbleSorter>(); break;
        case 2: sorter = std::make_unique<SelectionSorter>(); break;
        case 3: sorter = std::make_unique<InsertionSorter>(); break;
        case 4: sorter = std::make_unique<MergeSorter>(); break;
        default:
            std::cout << "Invalid choice. Skipping sort." << std::endl;
            return;
        }

        MathLib::sortArray(arr.get(), arraySize, sorter.get());
        std::cout << "\nSorted array: ";
        printArray(arr.get(), arraySize);
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    titleBorder(G_TITLE);
}

// Function to handle integer functions
void integerFunctions() {
    const std::string G_TITLE = "--- Integer Functions ---";
    std::cout << G_TITLE << std::endl;
    
    int factNum = getIntInput("Enter a non-negative integer for factorial: ");
    try {
        std::cout << "Factorial of " << factNum << ": " << MathLib::factorial(factNum) << std::endl;
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    int primeNum = getIntInput("\nEnter an integer to check if it's prime: ");
    std::cout << primeNum << (MathLib::isPrime(primeNum) ? " is prime." : " is not prime.") << std::endl;

    int gcdNum1 = getIntInput("\nEnter first integer for GCD: ");
    int gcdNum2 = getIntInput("Enter second integer for GCD: ");
    std::cout << "GCD of " << gcdNum1 << " and " << gcdNum2 << ": " << MathLib::gcd(gcdNum1, gcdNum2) << std::endl;

    int fibNum = getIntInput("\nEnter index for Fibonacci number: ");
    try {
        std::cout << "Fibonacci number at index " << fibNum << ": " << MathLib::fibonacci(fibNum) << std::endl;
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    titleBorder(G_TITLE);
}

// Function to demonstrate all functions with predefined examples
void demonstrateAllFunctions() {
    const std::string G_TITLE = "--- Demonstrating All Functions ---";
    std::cout << G_TITLE << std::endl;

    // Basic Operations
    {
        const std::string TITLE = "--- Basic Operations ---";
        std::cout << TITLE << std::endl;

		std::cout << "add(10.5, 5.2): " << MathLib::add(10.5, 5.2) << std::endl;
		std::cout << "subtract(20, 7.5): " << MathLib::subtract(20, 7.5) << std::endl;
		std::cout << "multiply(3.4, 6.1): " << MathLib::multiply(3.4, 6.1) << std::endl;
		try {
			std::cout << "divide(15.0, 3.0): " << MathLib::divide(15.0, 3.0) << std::endl;
			std::cout << "divide(10.0, 0.0): ";
			MathLib::divide(10.0, 0.0);
		}
		catch (const std::runtime_error& e) {
			std::cerr << "Error: " << e.what() << std::endl;
		}
        titleBorder(TITLE);
    }

    // Mathematical Functions
    {
        const std::string TITLE = "--- Mathematical Functions ---";
        std::cout << TITLE << std::endl;

        std::cout << "power(2.0, 5): " << MathLib::power(2.0, 5) << std::endl;
        std::cout << "power(2.0, -2): " << MathLib::power(2.0, -2) << std::endl;
        try {
            std::cout << "squareRoot(16.0): " << MathLib::squareRoot(16.0) << std::endl;
            std::cout << "squareRoot(-4.0): ";
            MathLib::squareRoot(-4.0);
        }
        catch (const std::runtime_error& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
        std::cout << "absoluteValue(-100.5): " << MathLib::absoluteValue(-100.5) << std::endl;
        std::cout << "absoluteValue(-50): " << MathLib::absoluteValue(-50) << std::endl;
        titleBorder(TITLE);
    }

    // Integer Functions
    {
        const std::string TITLE = "--- Integer Functions ---";
        std::cout << TITLE << std::endl;

        try {
            std::cout << "factorial(5): " << MathLib::factorial(5) << std::endl;
            std::cout << "factorial(-1): ";
            MathLib::factorial(-1);
        }
        catch (const std::runtime_error& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
        std::cout << "isPrime(7): " << (MathLib::isPrime(7) ? "true" : "false") << std::endl;
        std::cout << "isPrime(10): " << (MathLib::isPrime(10) ? "true" : "false") << std::endl;
        std::cout << "gcd(48, 18): " << MathLib::gcd(48, 18) << std::endl;
        std::cout << "fibonacci(10): " << MathLib::fibonacci(10) << std::endl;
        titleBorder(TITLE);
    }

    // Array Operations
    {
        const std::string TITLE = "--- Array Operations ---";
        std::cout << TITLE << std::endl;

        double demoArr[] = { 10.5, 2.3, 50.1, -5.0, 18.2 };
        size_t demoSize = sizeof(demoArr) / sizeof(demoArr[0]);

        std::cout << "Original array: ";
        printArray(demoArr, demoSize);

        std::cout << "Max value: " << MathLib::findMax(demoArr, demoSize) << std::endl;
        std::cout << "Min value: " << MathLib::findMin(demoArr, demoSize) << std::endl;
        std::cout << "Sum: " << MathLib::calculateSum(demoArr, demoSize) << std::endl;
        std::cout << "Average: " << MathLib::calculateAverage(demoArr, demoSize) << std::endl;
        titleBorder(TITLE);

        // Demonstrating the Strategy Pattern with different sorters

        std::string SUB_TITLE = "--- Sorting with different strategies ---";
        std::cout << SUB_TITLE << std::endl;

        BubbleSorter bubbleSorter;
        demonstrateSorting(bubbleSorter, "Bubble Sort");

        SelectionSorter selectionSorter;
        demonstrateSorting(selectionSorter, "Selection Sort");

        InsertionSorter insertionSorter;
        demonstrateSorting(insertionSorter, "Insertion Sort");

        MergeSorter mergeSorter;
        demonstrateSorting(mergeSorter, "Merge Sort");

        titleBorder(SUB_TITLE);
    }
    titleBorder(G_TITLE);
}

int main() {
    const std::string G_TITLE = "--- Math Calculator Menu ---";
    int choice;
    do {
        std::cout << G_TITLE << std::endl;
        std::cout << "1. Basic Operations" << std::endl;
        std::cout << "2. Mathematical Functions" << std::endl;
        std::cout << "3. Array Operations" << std::endl;
        std::cout << "4. Integer Functions" << std::endl;
        std::cout << "5. Demonstrate All Functions" << std::endl;
        std::cout << "6. Exit" << std::endl;
        choice = getIntInput("Enter your choice: ");
        titleBorder(G_TITLE);

        switch (choice) {
        case 1: basicOperations(); break;
        case 2: mathFunctions(); break;
        case 3: arrayOperations(); break;
        case 4: integerFunctions(); break;
        case 5: demonstrateAllFunctions(); break;
        case 6: std::cout << "Exiting program. Goodbye!" << std::endl; break;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
            break;
        }
    } while (choice != 6);

    return 0;
}