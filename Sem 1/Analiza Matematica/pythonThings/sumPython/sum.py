import math

def compute_sum(n:int, p: int, q: int, step: int) -> None:
    m = n // (p + q)
    k = n % (p + q)
    cnt = 0
    sum = 0
    pos = 1
    neg = 2
    for i in range(0, m):
        for j in range(0, p):
            sum += 1/pos
            pos += 2
            cnt += 1
            if cnt % step == 0:
               print("The sum after the first ", cnt, " terms is ", sum)
        for j in range(0, q):
            sum -= 1/neg
            neg += 2
            cnt += 1
            if cnt % step == 0:
                print("The sum after the first ", cnt, " terms is ", sum)

    for j in range(0, min(k, p)):
        sum += 1 / pos
        pos += 2
        cnt += 1
        if cnt % step == 0:
            print("The sum after the first ", cnt, " terms is ", sum)

    k -= p

    for j in range(0, k):
        sum -= 1 / neg
        neg += 2
        cnt += 1
        if cnt % step == 0:
            print("The sum after the first ", cnt, " terms is ", sum)

    if n % step != 0:
        print("The sum after the first ", n, " terms is ", sum)



print("The value of natural logarithm of 2 is ", math.log(2))
compute_sum(10000000, 1, 1, 1000000)
print("Adding 2 positives and 1 negative")
compute_sum(10000000, 2, 1, 1000000)
print("Adding 1 positive and 2 negatives")
compute_sum(10000000, 1, 2, 1000000)
print("Adding 2 positives and 2 negatives")
compute_sum(10000000, 2, 2, 1000000)
print("Adding only positives")
compute_sum(10000000, 1, 0, 1000000)
print("Adding only negatives")
compute_sum(10000000, 0, 1, 1000000)
