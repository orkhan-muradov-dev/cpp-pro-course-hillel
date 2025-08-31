// MathLib.h - Header file for the MathLib static library.

#ifndef MATHLIB_H
#define MATHLIB_H

#include <cstddef> // Required for size_t
#include <stdexcept>

/**
 * @brief Abstract base class for all sorting algorithms.
 *
 * This class defines the common interface for sorting strategies, allowing
 * them to be used interchangeably.
 */
class ISorter {
public:
    virtual ~ISorter() = default;
    virtual void sort(double arr[], size_t size) = 0;
};

// --- Concrete Sorting Algorithm Implementations ---

/**
 * @brief Implementation of the Bubble Sort algorithm.
 */
class BubbleSorter : public ISorter {
public:
    void sort(double arr[], size_t size) override;
};

/**
 * @brief Implementation of the Selection Sort algorithm.
 */
class SelectionSorter : public ISorter {
public:
    void sort(double arr[], size_t size) override;
};

/**
 * @brief Implementation of the Insertion Sort algorithm.
 */
class InsertionSorter : public ISorter {
public:
    void sort(double arr[], size_t size) override;
};

/**
 * @brief Implementation of the Merge Sort algorithm.
 */
class MergeSorter : public ISorter {
public:
    void sort(double arr[], size_t size) override;
private:
    void merge(double arr[], size_t left, size_t mid, size_t right);
};

// --------------------------------------------------

/**
 * @brief A static class providing a collection of mathematical utility functions.
 * All functions are implemented as static methods, meaning they can be called
 * directly using the class name without creating an object.
 */
class MathLib {
public:
    // --- Basic Arithmetic Operations ---

    /**
     * @brief Adds two numbers.
     * @param addend1 The first number.
     * @param addend2 The second number.
     * @return The sum of the two numbers.
     */
    static double add(double addend1, double addend2);

    /**
     * @brief Subtracts one number from another.
     * @param minuend The number from which to subtract.
     * @param subtrahend The number to subtract.
     * @return The difference between the two numbers.
     */
    static double subtract(double minuend, double subtrahend);

    /**
     * @brief Multiplies two numbers.
     * @param multiplier The first number.
     * @param multiplicand The second number.
     * @return The product of the two numbers.
     */
    static double multiply(double multiplier, double multiplicand);

    /**
     * @brief Divides one number by another.
     * @param numerator The number to be divided.
     * @param denominator The number to divide by.
     * @return The result of the division.
     * @throws std::runtime_error if the denominator is close to zero.
     */
    static double divide(double numerator, double denominator);

    // --- Mathematical Functions ---

    /**
     * @brief Raises a base number to an integer power.
     * @param base The base number.
     * @param exponent The integer exponent.
     * @return The result of base raised to the power of exponent.
     */
    static double power(double base, int exponent);

    /**
     * @brief Calculates the square root of a number using the Babylonian method.
     * @param value The number to calculate the square root of.
     * @return The square root of the value.
     * @throws std::runtime_error if the value is negative.
     */
    static double squareRoot(double value);

    /**
     * @brief Calculates the absolute value of a double.
     * @param value The number to get the absolute value of.
     * @return The absolute value of the number.
     */
    static double absoluteValue(double value);

    // --- Integer Functions ---

    /**
     * @brief Calculates the factorial of a number.
     * @param number The non-negative integer to calculate the factorial of.
     * @return The factorial of the number.
     * @throws std::runtime_error if the number is negative.
     */
    static long long factorial(int number);

    /**
     * @brief Checks if a number is prime.
     * @param number The integer to check.
     * @return True if the number is prime, false otherwise.
     */
    static bool isPrime(int number);

    /**
     * @brief Calculates the greatest common divisor (GCD) of two numbers.
     * @param number1 The first integer.
     * @param number2 The second integer.
     * @return The greatest common divisor of the two numbers.
     */
    static int gcd(int number1, int number2);

    // --- Array Operations ---

    /**
     * @brief Finds the maximum value in an array.
     * @param arr The array of doubles.
     * @param size The number of elements in the array.
     * @return The maximum value in the array.
     * @throws std::runtime_error if the array is empty or has a non-positive size.
     */
    static double findMax(const double arr[], size_t size);

    /**
     * @brief Finds the minimum value in an array.
     * @param arr The array of doubles.
     * @param size The number of elements in the array.
     * @return The minimum value in the array.
     * @throws std::runtime_error if the array is empty or has a non-positive size.
     */
    static double findMin(const double arr[], size_t size);

    /**
     * @brief Calculates the sum of all elements in an array.
     * @param arr The array of doubles.
     * @param size The number of elements in the array.
     * @return The sum of the array elements.
     */
    static double calculateSum(const double arr[], size_t size);

    /**
     * @brief Calculates the average of all elements in an array.
     * @param arr The array of doubles.
     * @param size The number of elements in the array.
     * @return The average of the array elements.
     * @throws std::runtime_error if the array is empty or has a non-positive size.
     */
    static double calculateAverage(const double arr[], size_t size);

    /**
     * @brief Sorts an array using the specified algorithm.
     * @param arr The array of doubles to sort.
     * @param size The number of elements in the array.
     * @param sorter A pointer to the sorting strategy to use.
     */
    static void sortArray(double arr[], size_t size, ISorter* sorter);

    // --- Utility Functions ---

    /**
     * @brief Checks if an integer is even.
     * @param number The integer to check.
     * @return True if the number is even, false otherwise.
     */
    static bool isEven(int number);

    /**
     * @brief Checks if an integer is odd.
     * @param number The integer to check.
     * @return True if the number is odd, false otherwise.
     */
    static bool isOdd(int number);

    /**
     * @brief Calculates the n-th Fibonacci number.
     * @param number The index of the Fibonacci number to calculate.
     * @return The n-th Fibonacci number.
     * @throws std::runtime_error if the number is negative.
     */
    static long long fibonacci(int number);
};

#endif // MATHLIB_H