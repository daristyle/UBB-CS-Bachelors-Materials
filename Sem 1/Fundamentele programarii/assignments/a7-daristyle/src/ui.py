#
# This is the program's UI module. The user interface and all interaction with the user (print and input statements) are found here
#

import functions

def read_input() -> list:
    input_list = input().split(' ')
    return input_list

def add_expense(l:list, tokens: list) -> None:
    if len(tokens) != 3:
        raise ValueError('Invalid number of parameters')

    apartment = tokens[0]
    type = tokens[1]
    amount = tokens[2]

    if not apartment.isdigit() or not amount.isdigit():
        raise ValueError('Invalid parameter(s)')

    apartment = int(apartment)
    amount = int(amount)

    functions.add_expense(l, functions.create_expense(apartment, amount, type))

    print('Expense added successfully!')

def remove_apartment(l:list, tokens: list) -> None:
    if len(tokens) != 1:
        raise ValueError('Invalid number of parameters')

    apartment = tokens[0]

    if not apartment.isdigit():
        raise ValueError('Invalid parameter')

    apartment = int(apartment)

    functions.remove_apartments(l, apartment, apartment)

    print('Expenses removed successfully!')

def remove_apartments(l:list, tokens: list) -> None:
    if len(tokens) != 3:
        raise ValueError('Invalid number of parameters')

    if tokens[1] != "to":
        raise ValueError('Invalid command')

    first = tokens[0]
    last = tokens[2]
    if not first.isdigit() or not last.isdigit():
        raise ValueError('Invalid parameter(s)')

    first = int(first)
    last = int(last)

    functions.remove_apartments(l, first, last)

    print('Expenses removed successfully!')

def remove_type(l:list, tokens: list) -> None:
    if len(tokens) != 1:
        raise ValueError('Invalid number of parameters')

    functions.remove_type(l, tokens[0])

    print('Expenses removed successfully!')

def replace(l:list, tokens: list) -> None:
    if len(tokens) != 4:
        raise ValueError('Invalid number of parameters')

    if tokens[2] != "with":
        raise ValueError('Invalid command')

    apartment = tokens[0]
    type = tokens[1]
    amount = tokens[3]

    if not apartment.isdigit() or not amount.isdigit():
        raise ValueError('Invalid parameter(s)')

    apartment = int(apartment)
    amount = int(amount)

    functions.replace(l, apartment, type, amount)

    print('Expenses replaced successfully!')

def list_all(l: list, tokens: list) -> None:
    if len(tokens) != 0:
        raise ValueError('Invalid number of parameters')

    print(functions.to_str(l))

def list_apartment(l: list, tokens: list) -> None:
    if len(tokens) != 1:
        raise ValueError('Invalid number of parameters')

    apartment = tokens[0]
    if not apartment.isdigit():
        raise ValueError('Invalid parameter(s)')

    apartment = int(apartment)

    list_all(functions.get_expenses_apartment(l, apartment), [])

def list_value(l: list, tokens: list) -> None:
    if len(tokens) != 2:
        raise ValueError('Invalid number of parameters')

    sign = tokens[0]
    amount = tokens[1]
    if sign not in ['<', '>', '='] or not amount.isdigit():
        raise ValueError('Invalid parameter(s)')

    amount = int(amount)

    l_new = []
    if sign == '<':
        l_new = functions.get_expenses_below(l, amount)
    elif sign == '>':
        l_new = functions.get_expenses_over(l, amount)
    else:
        l_new = functions.get_expenses_amount(l, amount)

    list_all(l_new, [])

def filter_type(l: list, tokens: list) -> None:
    if len(tokens) != 1:
        raise ValueError('Invalid number of parameters')

    type = tokens[0]

    functions.filter_type(l, type)

    list_all(l, [])

def filter_amount(l: list, tokens: list) -> None:
    if len(tokens) != 1:
        raise ValueError('Invalid number of parameters')

    amount = tokens[0]

    if not amount.isdigit():
        raise ValueError('Invalid parameter')

    functions.filter_amount(l, amount)

    list_all(l, [])

def undo(l: list, history: list, tokens: list) -> None:
    if len(tokens) != 0:
        print(tokens)
        raise ValueError('Invalid number of parameters')

    functions.undo(l, history)
    print("Undone!")
