#2.Consider a positive number n. Determine all its decompositions as sums of prime numbers.
import timeit


def generate_primes(n: int) -> list:
    if n <= 1:
        return []

    sieve = [True] * (n + 1)

    sieve[2] = True
    d = 4
    while d <= n:
        sieve[d] = False
        d += 2

    d = 3
    while d * d <= n:
        if sieve[d]:
            p = d * d
            while p <= n:
                sieve[p] = False
                p += d
        d += 2

    primes = [2]
    for i in range(3, n + 1, 2):
        if sieve[i]:
            primes.append(i)

    return primes

def backtracking_rec(n: int, primes: list, partition: list, idx: int) -> None:
    if n == 0:
        print(partition)
    elif n != 1:
        i = idx
        while primes[i] <= n:
            partition.append(primes[i])
            backtracking_rec(n - primes[i], primes, partition,i)
            partition.pop()
            i += 1


def backtracking_iter(n: int, primes: list) -> None:
    stack = [[n, [], 0]]
    while len(stack) > 0:
        n, partition, i = stack[-1]
        stack.pop()
        if n == 0:
            print(partition)
        elif n != 1:
            if primes[i] <= n:
                stack.append([n, partition.copy(), i + 1])
                partition.append(primes[i])
                stack.append([n - primes[i], partition.copy(), i])
                partition.pop()
                i += 1

def satrt() -> bool:
    n = input("Enter the number to decompose or -1 to quit: ")
    if n == "-1":
        return True
    if n.isdigit() is False:
        return False
    n = int(n)

    if n <= 1:
        print(n + "cannot be decomposed as sum of prime numbers.")
        return True

    primes = generate_primes(n)

    primes.append(n + 1)

    print("Recursive solution:")
    strat_rec = timeit.default_timer()
    backtracking_rec(n, primes, [], 0)
    stop_rec = timeit.default_timer()
    print("Iterative solution:")
    strat_iter = timeit.default_timer()
    backtracking_iter(n, primes)
    stop_iter = timeit.default_timer()

    print("Recursive solution took:", stop_rec - strat_rec, "seconds")
    print("Iterative solution took:", stop_iter - strat_iter, "seconds")

    return True


while satrt() is False:
    pass