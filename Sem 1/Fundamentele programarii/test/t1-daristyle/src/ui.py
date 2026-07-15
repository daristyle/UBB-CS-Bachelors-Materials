#
# User interface section
#
import functions as func

def print_lost(hidden: str) -> None:
    print("You lost! The hidden number was " + hidden + ".")

def print_won() -> None:
    print("You won!")

def print_codes_and_runners(codes: int, runners: int) -> None:
    print("In your guess there are " + str(codes) + " codes and " + str(runners) + " runners.")

def print_hidden(hidden: str) -> None:
    print("The hidden number is " + hidden + ".")

def read_input() -> str:
    return input()

def start():
    hidden = func.generate_random_number()
    exited = False

    while not exited:
        guess = read_input()
        if guess == "8086":
            print_hidden(hidden)
        elif not func.is_valid(guess):
            print_lost(hidden)
            exited = True
        elif guess == hidden:
            print_won()
            exited = True
        else:
            print_codes_and_runners(func.get_codes(guess, hidden), func.get_runners(guess, hidden))

if __name__ == "__main__":
    start()