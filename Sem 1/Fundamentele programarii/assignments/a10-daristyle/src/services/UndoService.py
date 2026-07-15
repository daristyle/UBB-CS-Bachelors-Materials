class FunctionCall:
    def __init__(self, func, *args):
        self.__func = func
        self.__args = args

    def call(self):
        return self.__func(*self.__args)

    def __call__(self, *args, **kwargs):
        return self.call()

class Operation:
    def __init__(self, undo, redo):
        self.__undo = undo
        self.__redo = redo

    def undo(self):
        self.__undo()

    def redo(self):
        self.__redo()

class UndoError(Exception):
    pass

class UndoService:
    def __init__(self):
        self._history = []
        self._index = 0

    def record(self, operations: list[Operation]):
        self._history = self._history[:self._index]
        self._history.append(operations)
        self._index += 1

    def undo(self):
        if self._index <= 0:
            raise UndoError("Nothing to undo")

        self._index -= 1
        l = self._history[self._index]
        for op in l:
            op.undo()

    def redo(self):
        if self._index == len(self._history):
            raise UndoError("Nothing to redo")

        l = self._history[self._index]
        self._index += 1
        for op in l:
            op.redo()