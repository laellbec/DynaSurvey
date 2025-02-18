# Survey System Refactoring and Improvement

This repository contains the refactored and improved version of a survey system developed as part of the SENG 265 course at the University of Victoria. The project focuses on enhancing the efficiency, modularity, and maintainability of a survey system initially developed in Assignment 1.

## Key Features:
- **Dynamic Memory Allocation**: The system uses dynamic memory allocation to handle survey data, ensuring efficient memory usage and scalability.
- **Modular Design**: The codebase is split into multiple source files (`input_handling.c`, `processing.c`, `output.c`) and header files (`dyn_survey.h`) to promote modularity and separation of concerns.
- **Struct Usage**: The project leverages C structs to organize survey responses and demographic data, improving data handling and readability.
- **Filtering Capabilities**: The system supports filtering survey responses based on demographic criteria such as undergraduate program, country of birth, and age group.
- **Automated Build Process**: The project uses a `Makefile` to automate the build process, ensuring easy compilation and dependency management.

## Repository Structure:
- **`dyn_survey.c`**: Main program file containing the entry point.
- **`input_handling.c`**: Handles reading and parsing input data.
- **`processing.c`**: Implements data processing and filtering logic.
- **`output.c`**: Manages the output of survey results.
- **`Makefile`**: Automates the build process.
- **`tests/`**: Contains input and output test files used for validation.

## Learning Outcomes:
- Gained experience in refactoring legacy code to improve design and efficiency.
- Developed skills in dynamic memory management and modular programming in C.
- Learned to implement and test filtering algorithms for data processing.
- Practiced version control practices using Git.
