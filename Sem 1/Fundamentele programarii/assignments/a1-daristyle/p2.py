# Solve the problem from the second set here
# Problem 8

def next_fibonacci(n: int) -> int:
    f0 = f1 = 1
    f2 = 0
    while f2 <= n:
        f2 = f0 + f1
        f0 = f1
        f1 = f2
    return f2
x = int(input("Enter an integer: "))
print("The next Fibonacci number after that is: ", next_fibonacci(x))

