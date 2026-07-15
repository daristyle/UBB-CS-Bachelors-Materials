[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/EkJiZBBD)
# 💻 Assignment 02 - Searching. Sorting

## Requirements
Implement a menu-driven console application to help visualize the way searching and sorting algorithms work. You will be given one search algorithm and two sorting algorithms from the list below to implement (one from each of the three sets). When started, the program will print a menu with the following options:
- Generate a list of `n` random natural numbers. Generated numbers must be between `0` and `1000`.
- Search for an item in the list using the algorithm you implemented. (see **NB!** below)
- Sort the list using the first sorting algorithm you implemented. (see **NB!** below)
- Sort the list using the second sorting algorithm you implemented. (see **NB!** below)
- Exit the program

## NB!
- The search algorithms require a sorted list as input. In this case, make sure the user first sorted the list before being able to call the search algorithm.
- Before starting each sort, the program will ask for the value of parameter `step`. During sorting, the program will display the partially sorted list on the console each time it makes `step` operations or passes, depending on the algorithm (e.g., if `step=2`, display the partially sorted list after each 2 element swaps in bubble sort, after each 2 element insertions in insert sort, after every 2nd generation of a permutation in permutation sort etc.).
- [List of sorting algorithms](https://en.wikipedia.org/wiki/Sorting_algorithm)

## Implementation requirements
- Write a separate function for each of the searching and sorting algorithms you implement; each function must take as parameter the list to be searched/sorted, the value of the element we are searching for (only in the case of search algorithms) and the value of parameter `step` that was read from the console (only in the case of sort algorithms).
- Functions communicate using input parameter(s) and return values (**DO NOT use global, or module-level variables**)
- Provide the user with a menu-driven console-based user interface. Program output must be printed to the console. At each step, the program must provide the user the context of the operation (display the main menu, or what data you expect the user to provide). Never display an empty prompt.
- You may use Internet resources to research the searching and sorting algorithm, but you must be able to explain **how** and **why** they work in detail.

## Searching algorithms
- Binary search (iterative implementation)
- Binary search (recursive implementation)
- Jump search (also known as block search)
- Exponential search
- Interpolation search (using linear interpolation)

## Sorting algorithms 
### Basic set
- Bogosort
- Bubble Sort
- Cocktail Sort
- Exchange Sort
- Insert Sort
- Permutation Sort
- Selection Sort

### Advanced set
- Comb Sort
- Gnome Sort
- Heap Sort
- Shell Sort
- Strand Sort
- Stooge Sort
