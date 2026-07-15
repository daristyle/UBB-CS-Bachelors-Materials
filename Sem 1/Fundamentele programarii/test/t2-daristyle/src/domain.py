class Taxi:
    def __init__(self, id, x, y):
        if not x.is_integer() or not y.is_integer():
            raise ValueError("Taxi must be at an integer position")
        if not id.is_integer():
            raise ValueError("Taxi must have an integer id")

        self._id = id
        self._x = x
        self._y = y
        self._fare = 0

    @property
    def id(self):
        return self._id

    @property
    def x(self):
        return self._x

    @property
    def y(self):
        return self._y

    @property
    def fare(self):
        return self._fare

    @x.setter
    def x(self, x):
        if not x.is_integer():
            raise ValueError("Taxi must be at an integer position")

        self._x = x

    @y.setter
    def y(self, y):
        if not y.is_integer():
            raise ValueError("Taxi must be at an integer position")

        self._y = y

    @fare.setter
    def fare(self, fare):
        if not fare.is_integer():
            raise ValueError("Taxi must be at an integer position")

        self._fare = fare