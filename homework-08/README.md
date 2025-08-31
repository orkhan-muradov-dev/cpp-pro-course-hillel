# Homework #8: Static Libraries

## Project Overview
This project demonstrates the creation and use of a static library, `MathLib`, which provides a collection of mathematical and utility functions. A separate console application, `MathCalculator`, was developed to test and showcase the library's functionality.

### Key Features:
- **Static Library:** `MathLib` includes functions for a variety of tasks, from basic arithmetic to advanced array and integer operations.
- **Algorithm Implementation:** The library demonstrates the use of a **Strategy design pattern** to provide multiple sorting algorithms.

## Files
- `MathLib.h`: Public header for the static library.
- `MathLib.cpp`: Implementation of the library's functions.
- `MathLib.lib`: Pre-compiled static library for Windows.
- `MathCalculator.cpp`: Source code for the test program.

## Compilation and Execution
The `MathLib` source code is provided for cross-platform compilation. A pre-compiled `MathLib.lib` file is included for Windows users.

### Visual Studio (Recommended for Windows)

**1. Create Solution and Projects:**
    - Create a new **Static Library** project and name it MathLib. Add `MathLib.h` and `MathLib.cpp` to it.
    - Add a new **Console App** project to the same solution and name it `MathCalculator`. Add `MathCalculator.cpp` to it.

**2. Set Project Dependencies:**
- In the **Solution Explorer**, right-click on the **solution** and select **Project Dependencies**.
- Check the box for `MathLib` to make it a dependency of `MathCalculator`. This ensures `MathLib` is always built before the main program.

**3. Configure and Build:**
- Right-click on the `MathCalculator` project and go to **Properties**.
- Under `C/C++ -> General`, find **Additional Include Directories** and add: `$(SolutionDir)MathLib\`.
- Under `Linker -> General`, find **Additional Library Directories** and add: `$(OutDir)`.
- Under `Linker -> Input`, find **Additional Dependencies** and add: `MathLib.lib`.
- Build the solution. Visual Studio will now automatically link the two projects.

### Command-Line Compilation (Windows, macOS & Linux)
To compile the library and the test program from the command line, follow these steps.

**- Compile the Library**

| Platform    | Command                                                          |
|-------------|------------------------------------------------------------------|
| Windows     | cl.exe /EHsc /c MathLib.cpp                                      |
| macOS/Linux | g++ -std=c++20 -c MathLib.cpp <br> ar rcs libMathLib.a MathLib.o |

**- Link and Run the Program**

| Platform    | Command                                                                                 |
|-------------|-----------------------------------------------------------------------------------------|
| Windows     | cl.exe /EHsc MathCalculator.cpp MathLib.lib                                             |
| macOS/Linux | g++ -std=c++20 -o MathCalculator MathCalculator.cpp -L. -lMathLib <br> ./MathCalculator |