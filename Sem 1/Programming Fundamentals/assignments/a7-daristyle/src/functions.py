#
# The program's functions are implemented here. There is no user interaction in this file, therefore no input/print statements. Functions here
# communicate via function parameters, the return statement and raising of exceptions. 
#

from texttable import Texttable
import pdoc

########################################################################
#Expense functions
########################################################################
def create_expense(apartment: int, amount: int, type:str) -> list:
    """
    :param apartment: number of the apartment
    :param amount: the amount
    :param type: the type of the expenses
    :return: list, representing the expense
    Raises an error if:
        - the apartment number is not a positive integer
        - the amount is negative
        - the type of the expenses is not water, heating, electricity, gas or other
    """
    if apartment <= 0:
        raise ValueError("Apartment number must be positive")
    if amount < 0:
        raise ValueError("Amount must be positive")
    if type not in ["water", "heating", "electricity", "gas", "other"]:
        raise ValueError("Type must be one of water, heating, gas or other")

    return [apartment, amount, type]

def get_apartment(expense) -> int:
    return expense[0]

def get_amount(expense) -> int:
    return expense[1]

def get_type(expense) -> str:
    return expense[2]

def set_amount(expense, amount) -> None:
    expense[1] = amount


########################################################################
#List functions
########################################################################
def add_expense(l: list, expense) -> None:
    """
    :param l: list of expenses
    :param expense: a new expense that needs added to the list
    :return: None, but adds the expense to the list
    """
    l.append(expense)

def test_add_expense():
    l = []
    add_expense(l, create_expense(5, 10, "water"))
    add_expense(l, create_expense(10, 1000, "heating"))
    add_expense(l, create_expense(55354, 153540, "electricity"))
    add_expense(l, create_expense(5433234, 1450, "gas"))
    add_expense(l, create_expense(53, 1030, "other"))

    assert l == [[5, 10, "water"], [10, 1000, "heating"], [55354, 153540, "electricity"], [5433234, 1450, "gas"], [53, 1030, "other"]]

    try:
        add_expense(l, create_expense(-5, 10, "water"))
        assert False
    except ValueError:
        pass
    try:
        add_expense(l, create_expense(0, 10, "water"))
        assert False
    except ValueError:
        pass

    try :
        add_expense(l, create_expense(1, -10, "gas"))
        assert False
    except ValueError:
        pass

    try:
        add_expense(l, create_expense(1, 10, "gasf"))
        assert False
    except ValueError:
        pass

    print("add_expense passed all tests")


def to_str(l: list) -> str:
    """
    :param l: list of expenses
    :return: a string representing a table like form of the list
    """
    tt = Texttable()
    tt.add_row(["Crt. No.", "Apartment", "Amount", "Type"])

    for i in range(0, len(l)):
        tt.add_row([i + 1] + l[i])

    return tt.draw()

def remove_apartments(l: list, first: int, last: int) -> None:
    """
    :param l: list of expenses
    :param first: the number of the first apartment that needs to be removed
    :param last: the number of the last apartment that needs to be removed
    :return: None, but removes the apartments from the list
    Raises an error if:
        - first is larger than last
        - first is a negative number
    """
    if first > last:
        raise ValueError("First must be smaller or equal than last")
    if first <= 0:
        raise ValueError("First must be a positive integer")

    l_new = []
    for x in l:
        if not(first <= get_apartment(x) <= last):
            l_new.append(x)

    l[:] = l_new

def test_remove_apartments():
    l = []
    add_expense(l, create_expense(5, 10, "water"))
    add_expense(l, create_expense(10, 1000, "heating"))
    add_expense(l, create_expense(55354, 153540, "electricity"))
    add_expense(l, create_expense(5433234, 1450, "gas"))
    add_expense(l, create_expense(53, 1030, "other"))

    remove_apartments(l, 1, 4)
    assert l == [[5, 10, "water"], [10, 1000, "heating"], [55354, 153540, "electricity"], [5433234, 1450, "gas"], [53, 1030, "other"]]

    try:
        remove_apartments(l, 4, 1)
        assert False
    except ValueError:
        pass

    try:
        remove_apartments(l, -1, 4)
        assert False
    except ValueError:
        pass
    try:
        remove_apartments(l, 1, -1)
        assert False
    except ValueError:
        pass

    remove_apartments(l, 1, 100)
    assert l == [[55354, 153540, "electricity"], [5433234, 1450, "gas"]]

    print("remove_apartments passed all tests")

def remove_type(l: list, type: str) -> None:
    """
    :param l: list of expenses
    :param type: type of the expenses that should be removed
    :return: None, but removes the expenses from the list
    Raises an error if:
        - the type of the expenses is not water, heating, electricity, gas or other
    """
    if type not in ["water", "heating", "electricity", "gas", "other"]:
        raise ValueError("Type must be one of water, heating, electricity, gas or other")

    l_new = []
    for x in l:
        if get_type(x) != type:
            l_new.append(x)

    l[:] = l_new

def test_remove_type():
    l = []
    add_expense(l, create_expense(5, 10, "water"))
    add_expense(l, create_expense(10, 1000, "heating"))
    add_expense(l, create_expense(55354, 153540, "electricity"))
    add_expense(l, create_expense(5433234, 1450, "gas"))
    add_expense(l, create_expense(53, 1030, "other"))

    try:
        remove_type(l, "watehr")
        assert False
    except ValueError:
        pass

    remove_type(l, "water")
    assert l == [[10, 1000, "heating"], [55354, 153540, "electricity"], [5433234, 1450, "gas"], [53, 1030, "other"]]

    remove_type(l, "electricity")
    assert l == [[10, 1000, "heating"], [5433234, 1450, "gas"], [53, 1030, "other"]]

    remove_type(l, "other")
    assert l == [[10, 1000, "heating"], [5433234, 1450, "gas"]]

    remove_type(l, "gas")
    assert l == [[10, 1000, "heating"]]

    remove_type(l, "gas")
    assert l == [[10, 1000, "heating"]]

    remove_type(l, "heating")
    assert l == []

    remove_type(l, "gas")
    assert l == []

    try:
        remove_type(l, "gasdfd")
        assert False
    except ValueError:
        pass

    print("remove_types passed all tests")

def replace(l: list, apartment: int, type: str, amount: int) -> None:
    """
    :param l: list of expenses
    :param apartment: the number of the apartment of which the expenses should be modified
    :param type: the type of the expenses that should be modified
    :param amount: the new amount of the expenses
    :return: None, but replaces the expenses from the list
    Raises an error if:
        - the apartment number is not a positive integer
        - the amount is negative
        - the type of the expenses is not water, heating, electricity, gas or other
    """
    if apartment <= 0:
        raise ValueError("Apartment number must be positive")
    if amount < 0:
        raise ValueError("Amount must be positive")
    if type not in ["water", "heating", "electricity", "gas", "other"]:
        raise ValueError("Type must be one of water, heating, gas or other")

    for i in range(0, len(l)):
        if get_apartment(l[i]) == apartment and get_type(l[i]) == type:
            set_amount(l[i], amount)

def test_replace():
    l = []
    add_expense(l, create_expense(5, 10, "water"))
    add_expense(l, create_expense(10, 1000, "heating"))
    add_expense(l, create_expense(55354, 153540, "electricity"))
    add_expense(l, create_expense(5433234, 1450, "gas"))
    add_expense(l, create_expense(53, 1030, "other"))

    replace(l, 5, "water", 100)
    assert l == [[5, 100, "water"], [10, 1000, "heating"], [55354, 153540, "electricity"], [5433234, 1450, "gas"], [53, 1030, "other"]]

    replace(l, 10, "heating", 100)
    assert l == [[5, 100, "water"], [10, 100, "heating"], [55354, 153540, "electricity"], [5433234, 1450, "gas"], [53, 1030, "other"]]

    replace(l, 5433234, "gas", 100)
    assert l == [[5, 100, "water"], [10, 100, "heating"], [55354, 153540, "electricity"], [5433234, 100, "gas"], [53, 1030, "other"]]

    replace(l, 55354, "electricity", 100)
    assert l == [[5, 100, "water"], [10, 100, "heating"], [55354, 100, "electricity"], [5433234, 100, "gas"], [53, 1030, "other"]]

    replace(l, 53, "other", 100)
    assert l == [[5, 100, "water"], [10, 100, "heating"], [55354, 100, "electricity"], [5433234, 100, "gas"], [53, 100, "other"]]

    replace(l, 543323, "gas", 100)
    assert l == [[5, 100, "water"], [10, 100, "heating"], [55354, 100, "electricity"], [5433234, 100, "gas"], [53, 100, "other"]]

    try:
        replace(l, -543323, "gas", 100)
        assert False
    except ValueError:
        pass

    try:
        replace(l, 543323, "gas", -100)
        assert False
    except ValueError:
        pass

    try:
        replace(l, 543323, "gasdfd", 100)
        assert False
    except ValueError:
        pass

    print("replace passed all tests")

def get_expenses_apartment(l: list, apartment: int) -> list:
    """
    :param l: list of expenses
    :param apartment: apartment number
    :return: the list of the expenses for the apartment
    Raises an error if:
        - the apartment number is not a positive integer
    """
    if apartment <= 0:
        raise ValueError("Apartment number must be positive")

    l_new = []
    for i in range(0, len(l)):
        if get_apartment(l[i]) == apartment:
            l_new.append(l[i])

    return l_new

def get_expenses_over(l: list, amount: int) -> list:
    """
    :param l: list of all expenses
    :param amount:
    :return: list of expenses over the amount
    """
    l_new = []
    for i in range(0, len(l)):
        if get_amount(l[i]) > amount:
            l_new.append(l[i])

    return l_new

def get_expenses_below(l: list, amount: int) -> list:
    """
    :param l: list of all expenses
    :param amount:
    :return: list of expenses below the amount
    """
    l_new = []
    for i in range(0, len(l)):
        if get_amount(l[i]) < amount:
            l_new.append(l[i])

    return l_new

def get_expenses_amount(l: list, amount:int) -> list:
    """
    :param l: list of all expenses
    :param amount:
    :return: list of expenses equal to the amount
    """

    l_new = []
    for i in range(0, len(l)):
        if get_amount(l[i]) == amount:
            l_new.append(l[i])

    return l_new

def filter_type(l: list, type: str) -> None:
    """
    :param l: list of all expenses
    :param type: the type of the expenses that should be filtered
    :return: None, but the list will be filtered
    Raises an error if:
        - the type of the expenses is not water, heating, electricity, gas or other
    """
    if type not in ["water", "heating", "electricity", "gas", "other"]:
        raise ValueError("Type must be one of water, heating, gas or other")

    l_new = []
    for i in range(0, len(l)):
        if get_type(l[i]) == type:
            l_new.append(l[i])

    l[:] = l_new

def filter_amount(l: list, amount: int) -> None:
    """
    :param l: list of all expenses
    :param amount: the value of the amount of the expenses that should be filtered
    :return: None, but the list will be filtered
    Raises an error if:
        - the amount is negative
    """
    if amount < 0:
        raise ValueError("Amount must be positive")

    l_new = []
    for i in range(0, len(l)):
        if get_amount(l[i]) == amount:
            l_new.append(l[i])

    l[:] = l_new

def update_history(l: list, history: list) -> None:
    """
    :param history: list of previous lists of expenses
    :param l: list of expenses
    :return: None, but adds list at the end of history
    """
    history.append(l.copy())

def undo(l: list, history: list) -> None:
    """
    :param history: list of previous lists of expenses
    :param l: list of expenses
    :return: None, but changes l to the last element of history and deletes it
    Raises an error if:
        - the history list is empty
    """
    if len(history) == 0:
        raise ValueError("There is no operation to undo")

    l[:] = history.pop()


if __name__ == "__main__":
    html = pdoc.pdoc("functions.py")
    with open("functions.html", "w") as file:
        file.write(html)

    test_add_expense()

    l = []
    add_expense(l, create_expense(5, 10, "water"))
    add_expense(l, create_expense(10, 1000, "heating"))
    add_expense(l, create_expense(55354, 153540, "electricity"))
    add_expense(l, create_expense(5433234, 1450, "gas"))
    add_expense(l, create_expense(53, 1030, "other"))
    print(to_str(l))

    test_remove_apartments()
    test_remove_type()
    test_replace()