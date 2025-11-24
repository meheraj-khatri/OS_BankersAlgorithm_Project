# Banker's Algorithm Implementation

## Overview
This project implements the Banker's Algorithm for deadlock avoidance in operating systems. The algorithm determines whether a system is in a safe state and finds a safe sequence of process execution if one exists.

## Algorithm Explanation
The Banker's Algorithm works as follows:

1. **Input**: 
   - Number of processes and resource types
   - Allocation matrix (resources currently allocated to each process)
   - Max matrix (maximum resources each process may need)
   - Available resources (resources currently available)

2. **Need Calculation**: Need = Max - Allocation

3. **Safety Check**:
   - Find a process whose Need ≤ Available
   - If found, assume the process finishes and returns all its resources
   - Repeat until all processes are finished (safe state) or no such process exists (unsafe state)

## Problem Solution
For the given system snapshot with 5 processes (P0-P4) and 3 resource types (A, B, C):

- **Total Resources**: A=10, B=5, C=7
- **Allocation Matrix**:
  - P0: [0, 1, 0]
  - P1: [2, 0, 0]
  - P2: [3, 0, 2]
  - P3: [2, 2, 1]
  - P4: [0, 0, 2]
- **Max Matrix**:
  - P0: [7, 5, 3]
  - P1: [3, 3, 2]
  - P2: [9, 0, 2]
  - P3: [2, 2, 2]
  - P4: [4, 3, 3]
- **Available**: [3, 2, 2]

**Result**: The system is in a **SAFE** state with safe sequence: **P3 → P1 → P0 → P2 → P4**

## Project Structure

OS_BankersAlgorithm_Project

- banker.cpp          # Main implementation
- input.txt           # Input data file
- README.md           # This file
- Makefile            # Build configuration
- output_example.txt  # Example output


## Compilation and Execution

### Prerequisites
- GCC compiler
- Linux/Unix environment

### Steps to Run
1. Clone the repository:
   ```bash
   git clone <repository-url>
   cd OS_BankersAlgorithm_Project

2. Compile the program:
   ```bash
   make

3. Run the program:
    ```bash
    make run
    
or
        ```bash
        ./banker

## Input File Format

The input file input/system_state.txt follows this format:

- Line 1: Number of processes, Number of resource types

- Line 2: Total instances of each resource type

- Next n lines: For each process: Allocation values + Max values

- Last line: Currently available resources


## Features

1. Reads system state from input file

2. Calculates Need matrix automatically

3. Implements complete Banker's Algorithm safety check

4. Outputs detailed system state information

5. Provides clear safe sequence or unsafe state warning

6. Robust error handling for file operations

