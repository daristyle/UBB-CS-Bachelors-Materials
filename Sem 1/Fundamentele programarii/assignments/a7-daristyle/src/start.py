#
# This module is used to invoke the program's UI and start it. It should not contain a lot of code.
#

import functions
import ui
from faker import Faker

from src.functions import create_expense


def add(*args) -> None:
    ui.add_expense(args[0], args[1])

def remove(*args) -> None:
    tokens = args[1]
    if len(tokens) == 3:
        ui.remove_apartments(args[0], tokens)
    elif tokens[0].isdigit():
        ui.remove_apartment(args[0], tokens)
    else:
        ui.remove_type(args[0], tokens)

def replace(*args) -> None:
    ui.replace(args[0], args[1])

def list_command(*args) -> None:
    tokens = args[1]
    if len(tokens) == 2:
        ui.list_value(args[0], tokens)
    elif len(tokens) == 1:
        ui.list_apartment(args[0], tokens)
    else:
        ui.list_all(args[0], tokens)

def filter(*args) -> None:
    if len(args[1]) == 0:
        raise ValueError("Invalid command")
    if args[1][0].isdigit():
        ui.filter_amount(args[0], args[1])
    else:
        ui.filter_type(args[0], args[1])

def undo(*args) -> None:
    ui.undo(args[0], args[2], args[1])

def update(l: list, history: list) -> None:
    functions.update_history(l, history)

def start():
    exited = False
    command = {"add": add, "remove": remove, "replace": replace, "list": list_command, "filter": filter, "undo": undo}
    l = []
    history = []

    fake = Faker()
    for _ in range(10):
        functions.add_expense(l, create_expense(fake.random_int(1, 100), fake.random_int(0, 1000),
                                fake.random_element(elements=["water", "heating", "electricity","gas", "other"])))

    while not exited:
        tokens = ui.read_input()
        op = tokens[0]
        tokens = tokens[1:]
        if op in command:
            try:
                if op not in ["list", "undo"]:
                    update(l, history)
                command[op](l, tokens, history)
            except ValueError as ve:
                print(ve)
        elif op == "exit":
            exited = True
        else:
            print("Invalid command")


start()