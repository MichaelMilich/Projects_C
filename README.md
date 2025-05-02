# 🧪 C Exercises Test Framework

**As you can probably tell most of this README was written with chatGPT help.**
This project is designed to practice and test C programming exercises using Python's unittest framework and ctypes to interface with compiled C code.

***Goal***
To learn the C programing language by doing some excersizes. 
Some of the excersizes become larger as I work on them.

***method***
1. Ask ChatGPT to create excersizes of implementing basic things in c for a developer that knows high-level languages like python.
2. Start doing each excersize with it's testing code (use whatever language you want to test). DO NOT use cursor while learning the new language. Google your questions and tries. Use AI only for debugging & code reviews.
3. Try to make an executable for each excersize.



## 📁 Project Structure
```
    Project/
    ├── bin/                         # Compiled C executables (.o)
    │   └── 3_1_string_reversal.o
    ├── new_c_excersizes/           # Raw C source files
    │   └── 3_1_string_reversal.c
    ├── test/
    │   ├── test_3_1_string_reversal.py  # Python test file
    │   └── c_lib/                  # Compiled shared libraries (.so)
    │       └── 3_1_string_reversal.so
    ├── utils/                      # utils c code for shared libraries & shared excersizes.
    ├── Makefile                    # Build logic
    ├── run_exercise.sh            # Runs a specific test end-to-end
    ├── run_all_exercises.sh       # Builds & runs all tests
    ├── list_exercises.sh          # Lists all available C exercises
    └── README.md                  # You're here!
```
***Note***
Somewhere after string excersizes I descided to add utils directory. to not re-write code.


## ⚙️ Prerequisites

Make sure the following tools are installed:

gcc – for compiling C code

make – for build automation

python3 – for running tests

ctypes – included with Python


## 🚀 How to Use
### ✅ 1. List All Available Exercises

    ./list_exercises.sh

### ✅ 2. Run a Single Exercise

This will:

1. Clean up any previous .so and .o files

2. Rebuild the shared library and executable

3. Run the matching Python test

```./run_exercise.sh 3_1_string_reversal.c```

💡 Only provide the .c file name (not the full path).

### ✅ 3. Run All Exercises

This will loop through every .c file in new_c_excersizes/, build its .so and .o, and run the matching Python test.

    ./run_all_exercises.sh

⚠️ If a Python test is missing for a .c file, it will print a warning and skip it.

### 🧹 Cleaning

To remove build artifacts for a specific file, just run:

    make clean

Or modify your shell script to do it per file.

### ✍️ Writing New Exercises

Create your C file in new_c_excersizes/, e.g., my_exercise.c

Write a Python test: test/test_my_exercise.py

Run it:

    ./run_exercise.sh my_exercise.c 

