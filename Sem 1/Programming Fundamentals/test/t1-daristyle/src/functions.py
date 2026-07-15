#
# Functions section
#
import random

def generate_random_number() -> str:
    l = [i for i in range(10)]
    s = ""

    pos = random.randint(1, len(l) - 1)
    s += str(l[pos])
    l.pop(pos)
    for i in range(3):
        pos = random.randint(0, len(l) - 1)
        s += str(l[pos])
        l.pop(pos)

    return s

def is_valid(s: str) -> bool:
    if len(s) != 4:
        return False
    if not s.isdigit():
        return False

    if s[0] == '0':
        return False

    return sorted(list(set(s))) == sorted(list(s))

def get_codes(guess: str, ans: str) -> int:
    """
    :param guess: the number guessed by the human represented as a string
    :param ans: the answer represented as a string
    :return: the number of codes(digits in the correct position)
    """
    cnt = 0
    for i in range(4):
        if guess[i] == ans[i]:
            cnt += 1

    return cnt

def get_runners(guess: str, ans: str) -> int:
    """
        :param guess: the number guessed by the human represented as a string
        :param ans: the answer represented as a string
        :return: the number of runners(correct digits in wrong positions)
        """
    cnt = 0
    for i in range(4):
        for j in range(4):
            if i != j and guess[i] == ans[j]:
                cnt += 1

    return cnt

if __name__ == '__main__':
    is_valid("1243")
