\# Homework #4: Multithreading Basics



\## Task Description

This program demonstrates basic multithreading by performing several mathematical computations in parallel using a thread pool and implements an order processing system where multiple threads process orders in sequence with synchronization.



\## Features



\### Task 1: Parallel Mathematical Computations

\- Thread 1: Calculates factorial of 15

\- Thread 2: Computes the sum of squares from 1 to 1000

\- Thread 3: Generates Fibonacci sequence up to the 30th element

\- Thread 4: Finds all prime numbers up to 100  

All tasks run in a thread pool and print their results independently.



\### Task 2: Order Processing System

\- Thread 1: Validates initial orders (checks format and correctness)

\- Thread 2: Waits for Thread 1, then calculates prices for valid orders

\- Thread 3: Waits for Thread 2, checks inventory availability for priced orders

\- Thread 4: Waits for Thread 3, generates invoices and sends them to customers



\## Files

\- `main.cpp` — Contains the full implementation of the tasks and test code.



\## Compilation and Running

```bash

g++ -std=c++14 -pthread -o program main.cpp

./program

