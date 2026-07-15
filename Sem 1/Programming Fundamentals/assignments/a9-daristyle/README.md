[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/RgJQvWyJ)
# 💻 Assignment 09 - Layered Architecture I
## Requirements common to all problem statements
1. Implement layered architecture using classes. Provide a menu-driven console-based user interface. Implementation details are up to you
2. Have at least 20 procedurally generated items **for each domain class** in your application at startup (e.g., at least 20 students, 20 disciplines and 20 grades). Hint - the **[faker](https://faker.readthedocs.io/en/master/#)** library can generate many of the required class fields.
3. Provide specifications and **[PyUnit test cases](https://realpython.com/python-testing/)** for all non-UI classes and methods for the first functionality. You may skip simple getter/setter functions or properties.
4. Implement and use your own exception classes.
5. Implement in-memory, as well as file-based repositories for all entities. For each entity, implement a text-file repository and a binary-file repository (using [Pickle](https://docs.python.org/3/library/pickle.html)). The program must work the same way using in-memory repositories, text-file repositories and binary file repositories. You may use inheritance to reuse repository source code.
6. Allow configuring the application using a `settings.properties` file. The decision of which repositories are employed, as well as the location of the repository input files will be made in the program’s `settings.properties` file. An example is below:

    a. `settings.properties` for working with repositories that store entities in memory (in this case there are no input files):
    ```
    repository = inmemory
    cars = “”
    clients = “”
    rentals = “”
    ```
    b. `settings.properties` for working with repositories that store entities to binary files:
    ```
    repository = binaryfiles
    cars = “cars.pickle”
    clients = “clients.pickle”
    rentals = “rentals.pickle”
    ```

## Problem Statements
### 1. Students Register Management
A faculty stores information about:
- **Student**: `student_id`, `name`
- **Discipline**: `discipline_id`, `name`
- **Grade**: `discipline_id`, `student_id`, `grade_value`

Create an application to:
1. Manage students and disciplines. The user can add, remove, update, and list both students and disciplines.
2. Grade students at a given discipline. Any student may receive one or several grades at any discipline. Deleting a student also removes their grades. Deleting a discipline deletes all grades at that discipline for all students.
3. Search for disciplines/students based on ID or name/title. The search must work using case-insensitive, partial string matching, and must return all matching disciplines/students.

### 2. Student Lab Assignment
Write an application that manages student lab assignments for a discipline. The application will store:
- **Student**: `student_id`, `name`, `group`
- **Assignment**: `assignment_id`, `description`, `deadline`
- **Grade**: `assignment_id`, `student_id`, `grade_value`

Create an application that allows to:
1. Manage students and assignments. The user can add, remove, update, and list both students and assignments.
2. Give assignments to a student or a group of students. In case an assignment is given to a group of students, every student in the group will receive it. In case there are students who were previously given that assignment, it will not be assigned again.
3. Grade student for a given assignment. When grading, the program must allow the user to select the assignment that is graded, from the student’s list of ungraded assignments. A student’s grade for a given assignment cannot be changed. Deleting a student removes their assignments. Deleting an assignment also removes all grades at that assignment.

### 3. Movie Rental
Write an application for movie rentals. The application will store:
- **Movie**: `movie_id`, `title`, `description`, `genre`
- **Client**: `client_id`, `name`
- **Rental**: `rental_id`, `movie_id`, `client_id`, `rented_date`, `due_date`, `returned_date`

Create an application which allows to:
1. Manage clients and movies. The user can add, remove, update, and list both clients and movies.
2. Rent or return a movie. A client can rent a movie until a given date, as long as they have no rented movies that passed their due date for return. A client can return a rented movie at any time.
3. Search for clients or movies using any one of their fields (e.g. movies can be searched for using id, title, description or genre). The search must work using case-insensitive, partial string matching, and must return all matching items.

### 4. Library
Write an application for a book library. The application will store:
- **Book**: `book_id`, `title`, `author`
- **Client**: `client_id`, `name`
- **Rental**: `rental_id`, `book_id`, `client_id`, `rented_date`, `returned_date`

Create an application to:
1. Manage clients and books. The user can add, remove, update, and list both clients and books.
2. Rent or return a book. A client can rent an available book. A client can return a rented book at any time. Only available books (those which are not currently rented) can be rented.
3. Search for clients or books using any one of their fields (e.g. books can be searched for using id, title or author). The search must work using case-insensitive, partial string matching, and must return all matching items.

### 5. Activity Planner
The following information is stored in a personal activity planner:
- **Person**: `person_id`, `name`, `phone_number`
- **Activity**: `activity_id`, `person_id` - list, `date`, `time`, `description`

Create an application to:
1. Manage persons and activities. The user can add, remove, update, and list both persons and activities.
2. Add/remove activities. Each activity can be performed together with one or several other persons, who are already in the user’s planner. Activities must not overlap (user cannot have more than one activity at a given time).
3. Search for persons or activities. Persons can be searched for using name or phone number. Activities can be searched for using date/time or description. The search must work using case-insensitive, partial string matching, and must return all matching items.

Deadline for maximum grade is **week 11**

## Bonus possibility (0.1p, deadline week 12)
- 95% unit test code coverage for all modules except the UI (use *PyCharm Professional*, the *[coverage](https://coverage.readthedocs.io/en/coverage-5.3/)* or other modules)

## Bonus possibility (0.2p, deadline week 12)
- Implement a graphical user interface, in addition to the required menu-driven UI
- The program can be started with either UI
