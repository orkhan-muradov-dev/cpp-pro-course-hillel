// MathLib.cpp - Implementation of the MathLib static library functions.

#include "MathLib.h"
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <vector>

// A constant used for floating-point comparisons to zero.
const double EPSILON = 1e-15;

// --- Basic Arithmetic Operations ---

double MathLib::add(double addend1, double addend2) { return addend1 + addend2; }

double MathLib::subtract(double minuend, double subtrahend) { return minuend - subtrahend; }

double MathLib::multiply(double multiplier, double multiplicand) { return multiplier * multiplicand; }

double MathLib::divide(double numerator, double denominator) {
    if (MathLib::absoluteValue(denominator) < EPSILON) {
        throw std::runtime_error("Division by zero is not allowed.");
    }
    return numerator / denominator;
}

// --- Mathematical Functions ---

double MathLib::power(double base, int exponent) {
    if (exponent == 0) { return 1.0; }

    double result = 1.0;
    size_t absExponent = absoluteValue(exponent);
    for (size_t i = 0; i < absExponent; ++i) {
        result *= base;
    }
    
    if (exponent < 0) { return 1.0 / result; }

    return result;
}

double MathLib::squareRoot(double value) {
    if (value < 0) { throw std::runtime_error("Cannot take the square root of a negative number."); }
    if (value == 0) { return 0; }

    double guess = value / 2.0;
    double newGuess = 0.0;

    // Implements the Babylonian method for calculating the square root.
    while (true) {
        newGuess = 0.5 * (guess + value / guess);
        if (MathLib::absoluteValue(newGuess - guess) < EPSILON) {
            return newGuess;
        }
        guess = newGuess;
    }
}

double MathLib::absoluteValue(double value) { return (value < 0 ? -value : value); }

// --- Integer Functions ---

long long MathLib::factorial(int number) {
    if (number < 0) { throw std::runtime_error("Factorial is defined only for non-negative numbers."); }
    if (number == 0) { return 1; }

    long long result = 1;    
    for (size_t i = 1; i <= number; ++i) {
        result *= i;
    }
    
    return result;
}

bool MathLib::isPrime(int number) {
    if (number <= 1) { return false; }

    for (size_t i = 2; i * i <= number; ++i) {
        if (number % i == 0) { return false; }
    }
    
    return true;
}

int MathLib::gcd(int number1, int number2) {
    // Implements the Euclidean algorithm to find the greatest common divisor.
    while (number2 != 0) {
        int temp = number2;
        number2 = number1 % number2;
        number1 = temp;
    }

    return MathLib::absoluteValue(number1);
}

// --- Array Operations ---

double MathLib::findMax(const double arr[], size_t size) {
    if (size == 0) { throw std::runtime_error("The array is empty."); }

    double maxVal = arr[0];
    for (size_t i = 1; i < size; ++i) {
        if (arr[i] > maxVal) { maxVal = arr[i]; }
    }
    
    return maxVal;
}

double MathLib::findMin(const double arr[], size_t size) {
    if (size == 0) { throw std::runtime_error("The array is empty."); }
    
    double minVal = arr[0];
    for (size_t i = 1; i < size; ++i) {
        if (arr[i] < minVal) { minVal = arr[i]; }
    }
    
    return minVal;
}

double MathLib::calculateSum(const double arr[], size_t size) {
    double sum = 0.0;
    for (size_t i = 0; i < size; ++i) {
        sum += arr[i];
    }
    
    return sum;
}

double MathLib::calculateAverage(const double arr[], size_t size) {
    if (size == 0) { throw std::runtime_error("The array is empty."); }
    
    return MathLib::calculateSum(arr, size) / size;
}

// --- Sorting Strategy Implementations ---

void BubbleSorter::sort(double arr[], size_t size) {
    // Compares adjacent elements and swaps them if they are in the wrong order.
    // Repeats passes until no more swaps are needed.
    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                double temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void SelectionSorter::sort(double arr[], size_t size) {
    // Finds the minimum element from the unsorted part and places it at the beginning.
    for (size_t i = 0; i < size - 1; ++i) {
        size_t min_idx = i;
        for (size_t j = i + 1; j < size; ++j) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        double temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
    }
}

void InsertionSorter::sort(double arr[], size_t size) {
    // Builds the final sorted array one item at a time.
    for (size_t i = 1; i < size; ++i) {
        double key = arr[i];
        size_t j = i - 1;
        while (j < size && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void MergeSorter::sort(double arr[], size_t size) {
    if (size <= 1) { return; }

    size_t left = 0;
    size_t right = size - 1;

    // Iterative approach to avoid potential stack overflow with large arrays.
    for (size_t currentSize = 1; currentSize <= right; currentSize = 2 * currentSize) {
        for (size_t leftStart = 0; leftStart < right; leftStart += 2 * currentSize) {
            size_t mid = std::min(leftStart + currentSize - 1, right);
            size_t rightEnd = std::min(leftStart + 2 * currentSize - 1, right);
            merge(arr, leftStart, mid, rightEnd);
        }
    }
}

void MergeSorter::merge(double arr[], size_t left, size_t mid, size_t right) {
    // Implements the merge step of the merge sort algorithm.
    size_t subArrayOne = mid - left + 1;
    size_t subArrayTwo = right - mid;

    double* leftArray = new double[subArrayOne];
    double* rightArray = new double[subArrayTwo];

    for (size_t i = 0; i < subArrayOne; i++) { leftArray[i] = arr[left + i]; }
    for (size_t j = 0; j < subArrayTwo; j++) { rightArray[j] = arr[mid + 1 + j]; }

    size_t indexOfSubArrayOne = 0, indexOfSubArrayTwo = 0;
    size_t indexOfMergedArray = left;

    while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo) {
        if (leftArray[indexOfSubArrayOne] <= rightArray[indexOfSubArrayTwo]) {
            arr[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
            indexOfSubArrayOne++;
        }
        else {
            arr[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
            indexOfSubArrayTwo++;
        }
        indexOfMergedArray++;
    }

    while (indexOfSubArrayOne < subArrayOne) {
        arr[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
        indexOfSubArrayOne++;
        indexOfMergedArray++;
    }

    while (indexOfSubArrayTwo < subArrayTwo) {
        arr[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
        indexOfSubArrayTwo++;
        indexOfMergedArray++;
    }

    delete[] leftArray;
    delete[] rightArray;
}

void MathLib::sortArray(double arr[], size_t size, ISorter* sorter) {
    if (size <= 1 || !sorter) { return; }
    
    sorter->sort(arr, size);
}

// --- Utility Functions ---

bool MathLib::isEven(int number) { return number % 2 == 0; }

bool MathLib::isOdd(int number) { return number % 2 != 0; }

long long MathLib::fibonacci(int number) {
    if (number < 0) { throw std::runtime_error("Fibonacci number is defined only for non-negative numbers."); }
    if (number <= 1) { return number; }

    long long a = 0, b = 1, c;
    for (size_t i = 2; i <= number; ++i) {
        c = a + b;
        a = b;
        b = c;
    }

    return b;
}