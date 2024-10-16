assessment-cplus-24-25-heavydragon99 created by GitHub Classroom

## Building the Project

### Prerequisites
- CMake 3.10 or higher
- A C++ compiler that supports C++17
- GoogleTest library installed on your system

### Building the Main Program

1. Navigate to the build directory:
    ```sh
    cd code/build
    ```

2. Run CMake to configure the project:
    ```sh
    cmake ..
    ```

3. Build the project:
    ```sh
    make -j 64
    ```

4. The executable will be located in `code/build/bin/`. Run the main program:
    ```sh
    ./bin/dungeon_crawler
    ```

5. Alternatively, you can build and run the main program using:
    ```sh
    cmake --build . --target run -- -j 64
    ```

### Running Valgrind to Check for Memory Leaks

1. Navigate to the build directory (if not already there):
    ```sh
    cd code/build
    ```

2. Run Valgrind with the main program:
    ```sh
    cmake --build . --target run_valgrind -- -j 64
    ```

### Building and Running the Tests

1. Navigate to the build directory (if not already there):
    ```sh
    cd code/build
    ```

2. Run CMake to configure the tests:
    ```sh
    cmake ..
    ```

3. Build the tests:
    ```sh
    make dungeon_crawler_tests -j 64
    ```

4. Run the tests:
    ```sh
    ./bin/runTests
    ```

5. Alternatively, you can build and run the tests using:
    ```sh
    cmake --build . --target run_tests -- -j 64
    ```

The tests will be executed, and the results will be displayed in the terminal.