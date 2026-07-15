import random

def print_menu() -> None:
    print("\nChoose an option:")
    print("1.Generate a new list")
    print("2.Search using recrsive binary search")
    print("3.Sort using Bubble Sort")
    print("4.Sort using Shell Sort")
    print("5.Exit")

def bubble_sort(a: list, step: int) -> None:
    changes = 0
    sorted = False
    n = len(a)
    while not sorted:
        sorted = True
        for i in range(0, n - 1):
            if a[i] > a[i + 1]:
                a[i], a[i + 1] = a[i + 1], a[i]
                sorted = False

                changes += 1
                if changes >= step:
                    print(a)
                    changes = 0

def generate_gap_sequence(n: int) -> list:
    l = [1]
    k = 1
    while l[-1] <= n:
        l.append(4 ** k + 3 * 2 ** (k - 1) + 1)
        k += 1
    l.pop()

    l.reverse()

    return l

def shell_sort(a: list, step: int) -> None:
    n = len(a)
    changes = 0

    gaps = generate_gap_sequence(n)
    #print("\n\n\n\n")
    #print(gaps)
    #print("\n\n\n\n")
    for gap in gaps:
        for i in range(gap, n):
            temp = a[i]

            j = i
            while j - gap >= 0 and temp < a[j - gap]:
                a[j] = a[j - gap]
                j -= gap

            a[j] = temp

            changes += 1
            if changes >= step:
                print(a)
                changes = 0

def binary_search_recursive(a: list, x: int, begin: int, end: int) -> int:#[begin;end)
    if end - begin <= 1:
        if a[begin] == x:
            return begin
        else:
            return -1
    mid = (begin + end) // 2
    if a[mid] > x:
        return binary_search_recursive(a, x, begin, mid)
    else:
        return binary_search_recursive(a, x, mid, end)

def binary_search(a: list, x: int) -> int:
    return binary_search_recursive(a, x, 0, len(a))


def start() -> None:
    exited = False
    list_is_sorted = False
    l = []
    while not exited:
        print_menu()
        choice = input("Enter your choice: ")
        if choice == "1":
            n = input("Enter the number of elements: ")
            if(n.isdigit() is False or int(n) <= 0):
                print("Invalid input")
                continue
            n = int(n)
            l = [random.randint(0, 1000) for _ in range(n)]
            list_is_sorted = False
            print("The list generated is: ", l)
        elif choice == "2":
            if len(l) == 0:
                print("The list was not generated! Please generate it first.")
                continue
            if not list_is_sorted:
                print("The list was not sorted! Please sort it first.")
                continue

            x = input("Search for: ")
            if (x.isdigit() is False):
                print("Invalid input")
                continue
            x = int(x)

            pos = binary_search(l, x)

            if pos == -1:
                print("The number was not found in the list!")
            else:
                print("The number was found at position ", pos)

        elif choice == "3" or choice == "4":
            if len(l) == 0:
                print("The list was not generated! Please generate it first.")
                continue

            step = input("Enter the visualization step: ")
            if (step.isdigit() is False):
                print("Invalid input")
                continue
            step = int(step)

            print("The initial list is: ", l)

            if choice == "3":
                bubble_sort(l, step)
            else:
                shell_sort(l, step)

            print("The sorted list is: ", l)

            list_is_sorted = True
        elif choice == "5":
            print("Bye bye")
            exited = True
        else:
            print("Invalid input")



start()