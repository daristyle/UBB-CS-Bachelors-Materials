import random
import timeit

from texttable import *
from datetime import *

def print_main_menu() -> None:
    print("\n---MAIN MENU---")
    print("1.Bubble sort")
    print("2.Shell sort")
    print("3.Recursive binary search")
    print("4.Exit")

def print_secondary_menu(name: str) -> None:
    print("\n---" + name + "---")
    print("1.Best case")
    print("2.Average case")
    print("3.Worst case")
    print("4.Complexity")
    print("5.Exit")


def bubble_sort(a: list) -> None:
    sorted = False
    n = len(a)
    while not sorted:
        sorted = True
        for i in range(0, n - 1):
            if a[i] > a[i + 1]:
                a[i], a[i + 1] = a[i + 1], a[i]
                sorted = False

def generate_gap_sequence(n: int) -> list:
    l = [1]
    k = 1
    while l[-1] <= n:
        l.append(4 ** k + 3 * 2 ** (k - 1) + 1)
        k += 1
    l.pop()

    l.reverse()

    return l

def shell_sort(a: list) -> None:
    n = len(a)

    gaps = generate_gap_sequence(n)
    for gap in gaps:
        for i in range(gap, n):
            temp = a[i]

            j = i
            while j - gap >= 0 and temp < a[j - gap]:
                a[j] = a[j - gap]
                j -= gap

            a[j] = temp

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

def binary_search(a: list) -> int:
    x = a[-1]
    a.pop()
    return binary_search_recursive(a, x, 0, len(a))

def build_table(lists: list, function) -> None:
    table = Texttable()
    table.add_row(["Length", "Time"])
    for l in lists:
        start = timeit.default_timer()
        function(l)
        end = timeit.default_timer()

        table.add_row([len(l), end - start])

    return table
def start() -> None:
    initial_size = 1000
    functions = {
        "Bubble sort": bubble_sort,
        "Shell sort": shell_sort,
        "Recursive binary search": binary_search,
    }
    explanation = {
        "Bubble sort": "\nBest case: All the elements are sorted in ascending order and the algorithm goes through them"
                       " and sees that they are sorted and stops. This is O(N)."
                       "\nWorst case: All the elements are sorted in descending order and the algorithm goes through them"
                       " and swaps neighbouring elements. The first element will be swapped n - 1 times, and for every swap"
                       " of a number the algorithm traverses all n elements of the list. This is O((N - 1) * N) = O(N²)."
                       "\nAverage case: There are N * (N - 1) / 2 pairs of elements, having a 50% chance of being inverted"
                       " so there will be N * (N - 1) / 4 inversions, which will require at least N * (N - 1) / 2 swaps."
                       " Therefore, the complexity is O(N²).",
        "Shell sort": "\nBest case: All elements are sorted in ascending order, and the algorithm goes through every"
                      " element at most once per gap. Let GAPS be the number of gaps, then 4 ^ (GAPS - 1) + 3 * 2 ^ (GAPS"
                      " - 2) + 1 <= N, which means that O(GAPS) ∈ O(log(N)).We will also use the fact that gap[i] > 4 ^ i."
                      " The complexity is O(sum(N - gap[i]) = O(N * GAPS - sum(gap[i])) ∈ O(N * log(N) - sum(4^i)) = O(N"
                      " * log(N) - (4^GAPS - 1)/3) ∈ O(N * log(N) - (4 ^ log(N) - 1)/3) = O(N * log(N) - (N - 1)/3) ="
                      " O(N * log(N))."
                      "\nWorst case: Let H be a fixed number greater than 1. Let C(H) be the cost of large gaps(>H)."
                      " Since the gaps grow almost geometrically with a factor of 4, so the gaps coold be approximated as"
                      " 4^i * H. There are less than O(log(N / H)) large gaps and for every gap the algorithm does"
                      " O(gap * (N / gap)²) = O(N² / gap) steps. So, C(H) = O(sum(N²/gap)) ∈ O(N² * 1 / H *"
                      " sum(1 / 4 ^ i)) = O(N² / H). Let c(H) be the cost of small gaps(<=H). Sedgewick proved with maths"
                      " behind my understanding that c(H) = O(N * sqrt(H)). Let T(H) be the cost for a fixed H. T(H) ="
                      " = C(H) + c(h) = O(N² / H + N * sqrt(H)). To minimize T(H) we need to choose H such that N² / H"
                      " = N * sqrt(H) => H * sqrt(H) = N => H = N ^ (2/3). Therefore the complexity of the algorithm is"
                      " O(N^(4/3))."
                      "\nAverage case: Since on the avergae case the array has a lot of inversions, the complexity is"
                      "the same as in the worst case, O(N^(4/3))",
        "Recursive binary search": "\nThis implementation of recursive binary search does not check if it has found an"
                                   " element unless it arrived to an interval of length 1. We start with an interval of"
                                   " length n and divide it by 2, so we will go through O(log₂(N)) intervals in all cases"
                                   " even if a[mid] is the target number, so the complexity of the algorithm is the same"
                                   " in the best case, worst case and in the average case; O(log(N))."
    }
    exited = False
    while not exited:
        print_main_menu()
        choice = input("Enter your choice: ")
        if choice == "1" or choice == "2" or choice == "3":
            name =  "Bubble sort" if choice == "1" else "Shell sort" if choice == "2" else "Recursive binary search"
            print_secondary_menu(name)
            secondary_choice = input("Enter your choice: ")

            if secondary_choice not in ["1", "2", "3", "4", "5"]:
                print("Invalid input")
                continue

            if secondary_choice == "5":
                continue
            elif secondary_choice == "4":
                print(explanation[name])
                continue

            lists = []
            if secondary_choice == "1" or choice == "3":
                for i in range(0, 5):
                    lists.append([j for j in range(0, initial_size * (2 ** i))])
            elif secondary_choice == "2" or (secondary_choice == "3" and choice == "2"):
                for i in range(0, 5):
                    lists.append([random.randint(0, initial_size * (2 ** i)) for _ in range(0, initial_size * (2 ** i))])
            elif secondary_choice == "3":
                for i in range(0, 5):
                    l = [j for j in range(0, initial_size * (2 ** i))]
                    l.reverse()
                    lists.append(l)


            if choice == "3":
                for l in lists:
                    l.append(random.randint(0, len(l) - 1))

            table = build_table(lists, functions[name])

            print(table.draw())

        elif choice == "4":
            print("Bye bye")
            exited = True
        else:
            print("Invalid input")



start()