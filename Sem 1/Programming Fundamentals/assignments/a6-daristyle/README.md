[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/1KdyOoqY)
# :computer: Assignment 06 - Procedural programming

## Requirements
- Use functions to: `read a complex number` from the console, `write a complex number` to the console, implement `each required functionality`.
- Functions communicate using input parameter(s) and the return statement (**DO NOT use** global variables, nested functions, the `global` or `nonlocal` keywords)
- Have two separate representations for each complex number, one using a `list` and another using a `dictionary`. Write methods to create a new complex number, to get and set each number's real and imaginary parts as well as to transform a number into its `str` representation. The program must work with both implementations, by either commenting out one of them or changing the order in which the corresponding functions are defined.
- Separate input/output functions from those performing the calculations (see **program.py**). Any function that has a ``print`` or ``input`` statement is an input/output function. Any function that calls such a function, even transitively is also an input/output function.
- Provide the user with a menu-driven console-based user interface. Input data should be read from the console and the results printed to the console. At each step, the program must provide the user the context of the operation (never display an empty prompt).
- Deadline is **week 7** for maximum grade, week 9 is the hard deadline.

## Problem Statement
Implement a menu-driven console application that provides the following functionalities:
1. Read a list of complex numbers (in `z = a + bi` form) from the console.
2. Display the entire list of numbers on the console.
3. Display on the console the sequence, subarray or numbers required by the properties that were assigned to you. Each student will receive one property from **Set A** and another one from **Set B**.
4. Exit the application.

**The source code will include:**
- Specifications for the functions related to point 3 above. 
- 10 complex numbers already available at program startup. This is to ensure functionalities can be checked easily.

### Set A (naive implementation)
Determine the length and the elements of:
1. A longest subarray of distinct numbers.
2. A longest subarray of numbers having the same modulus.
3. A longest subarray of numbers having increasing modulus.
4. A longest subarray of numbers that contain at most 3 distinct values.
5. A longest subarray of numbers where each number's modulus is in the `[0, 10]` range.
6. A longest subarray of numbers where the difference between the modulus of consecutive numbers is a prime number.
7. A longest subarray of numbers where their real part is in the form of a mountain (first the values increase, then they decrease). (e.g. `1-i, 2+6i, 4-67i, 90+3i, 80-7i, 76+i, 43-12i, 3`)
8. A longest subarray of numbers where both their real and imaginary parts can be written using the same base 10 digits (e.g. `1+3i, 31i, 33+i, 111, 11-313i`)

## Set B (dynamic programming implementation required)
Determine the length and the elements of:
1. A longest increasing subsequence, when considering each number's modulus.
2. A longest increasing subsequence, when considering each number's real part.
3. A maximum subarray sum, when considering each number's real part.
4. A longest alternating subsequence, when considering each number's real part (e.g., given sequence [1, 3, 2, 4, 10, 6, 1], [1, 3, 2, 10] is an alternating subsequence, because 1 < 3 > 2 < 10).
5. A longest alternating subsequence, when considering each number's modulus (e.g., given sequence [1, 3, 2, 4, 10, 6, 1], [1, 3, 2, 10, 1] is an alternating subsequence, because 1 < 3 > 2 < 10 > 1).

## Observations
- Elements of a **subarray** are in consecutive order of their appearance in the array, while in a **subsequence**, this isn't necessarily true.
- The longest subarray/subsequence might not be unique, so determining a single one is sufficient.
- Understand and be able to explain the time and extra-space computational complexity of your implementation. 
