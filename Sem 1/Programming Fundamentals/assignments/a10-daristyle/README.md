[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/P8itmi0j)
# 💻 Assignment 10 - Layered Architecture II
## Requirements
There are some new requirements for the program you've implemented for the previous assignment. The undo/redo requirement is common across all problem statements. Additionally, for each problem statement you will have to create the statistics detailed in the text below.

### Common requirement for all problem statements
Implement unlimited undo/redo functionality using the [Command design pattern](https://refactoring.guru/design-patterns/command), which ensures a memory-efficient implementation of undo/redo operations. Each step will undo/redo the previous operation performed by the user. Undo/redo operations must cascade (e.g., deleting a student must also delete their grades; undoing the deletion must restore all deleted objects).

### 1. Students Register Management
4. Create statistics:
    - All students failing at one or more disciplines (students having an average <5 for a discipline are failing it)
    - Students with the best school situation, sorted in descending order of their aggregated average (the average between their average grades per discipline)
    - All disciplines at which there is at least one grade, sorted in descending order of the average grade(s) received by all students

### 2. Student Lab Assignment
4. Create statistics:
    - All students who received a given assignment, ordered descending by grade.
    - All students who are late in handing in at least one assignment. These are all the students who have an ungraded assignment for which the deadline has passed.
    - Students with the best school situation, sorted in descending order of the average grade received for all graded assignments.
  
### 3. Movie Rental
4. Create statistics:
    - Most rented movies. This will provide the list of movies, sorted in descending order of the number of days they were rented.
    - Most active clients. This will provide the list of clients, sorted in descending order of the number of movie rental days they have (e.g. having 2 rented movies for 3 days each counts as 2 x 3 = 6 days).
    - Late rentals. All the movies that are currently rented, for which the due date for return has passed, sorted in descending order of the number of days of delay.

### 4. Library
4. Create statistics:
    - Most rented books. This will provide the list of books, sorted in descending order of the number of times they were rented.
    - Most active clients. This will provide the list of clients, sorted in descending order of the number of book rental days they have (e.g. having 2 rented books for 3 days each counts as 2 x 3 = 6 days).
    - Most rented author. This provides the list of book authors, sorted in descending order of the number of rentals their books have.
  
### 5. Activity Planner
4. Create statistics:
    - Activities for a given date. List the activities for a given date, in the order of their start time.
    - Busiest days. This will provide the list of upcoming dates with activities, sorted in ascending order of the free time in that day (all intervals with no activities).
    - Activities with a given person. List all upcoming activities to which a given person will participate.

deadline for maximum grade is **week 12**.
