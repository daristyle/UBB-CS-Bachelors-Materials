class FunctionCall:
    def __init__(self, func_name, *func_parameters):
        self._func_name = func_name
        self._func_parameters = func_parameters

    def call(self):
        self._func_name(*self._func_parameters)

    # def __call__(self, *args, **kwargs):
    #     self.call()


class Operation:
    def __init__(self, undo_function: FunctionCall, redo_function: FunctionCall):
        self.__undo = undo_function
        self.__redo = redo_function

    def undo(self):
        self.__undo.call()

    def redo(self):
        self.__redo.call()


class UndoService:
    """
    For each operation the user makes that changes a repository, there has to be an undo and a redo

    We will keep a list of the user undoable operations
    Each element of the list will have an undo() and a redo()
    """

    def __init__(self):
        # the list of all operations made in the program that have undo/redo support
        self.__history = []
        # the current index in the undo/redo list
        # index == 0 => no more undos
        # index == len(self.__history) => no more redos
        self.__index = 0

    def add_operation(self, operation: Operation):
        # After several undos, a new operation invalidates all existing
        # redos
        self.__history = self.__history[:self.__index]
        self.__history.append(operation)
        self.__index = len(self.__history)

    def undo(self):
        if self.__index == 0:
            # TODO Raise an exception that is caught in the UI
            return

        self.__index -= 1
        oper = self.__history[self.__index]
        oper.undo()

    def redo(self):
        if self.__index == len(self.__history):
            # TODO Raise an exception that is caught in the UI
            return

        oper = self.__history[self.__index]
        oper.redo()
        self.__index += 1


def fun_fun_fun(a, b, c):
    print("yay!")
    print(a + b + c)


if __name__ == "__main__":
    # x is a command according to the Command design pattern
    x = FunctionCall(fun_fun_fun, 100, 9, 8)
    x.call()  # undo or redo

    # x()
