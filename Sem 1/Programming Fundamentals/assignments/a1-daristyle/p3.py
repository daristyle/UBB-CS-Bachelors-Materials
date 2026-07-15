# Solve the problem from the third set here
# Problem 13

def eliminate_divisor(n: int, d: int) -> int:
    while n % d == 0:
        n //= d
    return n

def nth_number(n: int) -> int:
    if n == 1:
        return 1
    n -= 1

    retval = 0
    i = 2
    while retval == 0:
        m = i
        if m % 2 == 0:
            n -= 1
            if n == 0:
                retval = 2
            m = eliminate_divisor(m, 2)
        d = 3
        while d * d <= m:
            if m % d == 0:
                n -= 1
                if n == 0:
                    retval = d
                m = eliminate_divisor(m, d)
            d += 2
        if m != 1:
            n -= 1
            if n == 0:
                retval = m
        i += 1

    return retval

x = int(input("Enter an integer: "))
print("The", x, "-th number in the sequence is: ", nth_number(x))

