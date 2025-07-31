\# Homework #2: Move Semantics and Lambda Expressions



\## Task Description

This assignment focuses on implementing \*\*move semantics\*\* for a custom class `BigData` and practicing \*\*lambda expressions\*\* in C++.



\### Requirements:

\- Implement constructors and operators for `BigData`:

&nbsp; - Constructor with size

&nbsp; - Copy constructor

&nbsp; - Copy assignment operator

&nbsp; - Move constructor (with `noexcept`)

&nbsp; - Move assignment operator (with `noexcept`)

&nbsp; - Destructor

\- Add console logs inside each constructor, destructor, and operator to track when objects are copied or moved.

\- Create a function that returns a `BigData` object by value to demonstrate move semantics.

\- Write a lambda expression that captures an STL container by reference and takes a parameter. The lambda should increase every element in the container by that parameter.



\## Files

\- `main.cpp` — Implementation of `BigData` class and the demonstration code for move semantics and lambda expressions.



\## Compilation and Execution

```bash

g++ -std=c++14 -o program main.cpp

./program

