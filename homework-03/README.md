\# Homework #3: RAII and Smart Pointers



\## Task Description

This homework focuses on applying \*\*RAII (Resource Acquisition Is Initialization)\*\* principles and \*\*smart pointers\*\* in modern C++. The task consists of two parts:



\### Part 1: FileManager Class

Create a class `FileManager` that:

\- Opens a file in its constructor using `std::fopen`

\- Closes the file in its destructor using `std::fclose`

\- Has a method `write(const std::string\&)` for writing text to the file



\#### Requirements:

\- Throw an exception if the file cannot be opened

\- Ensure the file is always closed, even if an exception occurs



\### Part 2: Sensor Class with Shared Data

Create a class `Sensor` that:

\- Holds readings in a `std::shared\_ptr<std::vector<int>>`

\- Provides methods to add and print readings

\- Supports shared ownership of the readings between multiple `Sensor` instances



Demonstrate shared ownership by:

\- Creating two `Sensor` objects that share the same vector

\- Adding and printing readings from both objects



\## Files

\- `main.cpp` – Contains both class implementations and a test program



\## Compilation and Execution

```bash

g++ -std=c++14 -o program main.cpp

./program



