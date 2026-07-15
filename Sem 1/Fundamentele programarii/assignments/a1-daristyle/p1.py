# Solve the problem from the first set here
# Problem 4

def maximum_anagram(n: int) -> int:
    frequency = {}
    for i in range(0, 10):
        frequency[i] = 0
    while n != 0:
        frequency[n % 10] += 1
        n //= 10
    m = 0
    for digit in range(9, -1, -1):
        for _ in range(0, frequency[digit]):
            m = m * 10 + digit
    return m

x = int(input("Enter an integer: "))
print("The maximum anagram of that number is: ", maximum_anagram(x))