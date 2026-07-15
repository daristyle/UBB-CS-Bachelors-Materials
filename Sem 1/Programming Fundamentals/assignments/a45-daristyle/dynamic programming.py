#5. Maximize the profit when selling a rod of length n. The rod can be cut into pieces of integer lengths and pieces can
# be sold individually. The prices are known for each possible length. For example, if rod length n = 7, and the price
# array is price = [1, 5, 8, 9, 10, 17, 17] (the price of a piece of length 3 is 8), the maximum profit is 18, and is
# obtained by cutting the rod into 3 pieces, two of length two and one of length 3. Display the profit and the length of
# rod sections sold to obtain it.
import timeit


def dp_naive(prices: list, w:int) -> list:
    if w < 0:
        return [-(1 << 31)]
    if w == 0 or len(prices) <= 0:
        return [0]

    taken = dp_naive(prices, w-len(prices))
    taken[0] += prices[-1]
    taken.append(len(prices))

    aux = prices.copy()
    aux.pop()
    untaken = dp_naive(aux, w)

    ans = taken if taken[0] > untaken[0] else untaken

    return ans

def dp_optimized(prices: list, w: int, printing: bool) -> list:
    n = len(prices)
    dp = [[0 for _ in range(w + 1)] for _ in range(n)]

    for j in range(w + 1):
        if prices[0] <= j:
            dp[0][j] = prices[0] + dp[0][j - prices[0]]

    for i in range(1, n):
        for j in range(w + 1):
            dp[i][j] = dp[i - 1][j]
            for k in range(min(i + 1, j)):
                    dp[i][j] = max(dp[i][j], prices[k] + dp[i][j - k - 1])

    if printing:
        for i in range(n):
            print(dp[i])

    ans = [dp[n - 1][w]]
    sum = dp[n - 1][w]
    i = n - 1
    j = w
    while sum > 0:
        for k in range(min(i + 1, sum)):
            if sum == prices[k] + dp[i][j - k - 1]:
                ans.append(k + 1)
                j -= k + 1
                sum = dp[i][j]
                break
        i = i - 1


    return ans

def print_answer(ans: list) -> None:
    x = ans[0]
    ans.pop(0)
    print("The maximum value is " + str(x) + " and it can be achieved by selling pieces of lengths: " + str(ans))

def start() -> bool:

    n = input("Enter the length of the rod or -1 to quit: ")
    if n == "-1":
        return True
    if n.isdigit() is False:
        print("Enter a positive number")
        return False
    n = int(n)
    if n <= 0:
        print("Enter a positive number")
        return False
    price = []
    for i in range(1, n + 1):
        x = input("Enter the price of the piece of length " + str(i) + ": ")
        if x.isdigit() is False:
            print("Enter a positive number")
            return False
        x = int(x)
        if x <= 0:
            print("Enter a positive number")
            return False
        price.append(x)

    start_naive = timeit.default_timer()
    ans_naive = dp_naive(price, n)
    stop_naive = timeit.default_timer()

    start_optimized = timeit.default_timer()
    ans_optimized = dp_optimized(price, n, False)
    stop_optimized = timeit.default_timer()

    print("Naive dynamic programming took " + str(stop_naive - start_naive) + " seconds and outputed:")
    print_answer(ans_naive)
    print("Optimized dynamic programming took " + str(stop_optimized - start_optimized) + " seconds and outputed:")
    print_answer(ans_optimized)
    print("The data structure used is a matrix/list of lists")
    dp_optimized(price, len(price), True)

while start() is False:
    pass