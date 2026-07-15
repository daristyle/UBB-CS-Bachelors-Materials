from domain import Taxi


class Repository:
    def __init__(self):
        self._taxis = []

    def add(self, id, x, y):
        taxi = Taxi(id, x, y)
        self._taxis.append(taxi)

    def _get_closest_taxi(self, x, y):
        idx = 0
        i = 0
        min_dist = self.Manhattan_distance(x, y, self._taxis[idx].x, self._taxis[idx].y)
        for taxi in self._taxis:
            dist = self.Manhattan_distance(x, y, taxi.x, taxi.y)
            if dist < min_dist:
                min_dist = dist
                idx = i
            i += 1

        return idx

    def ride(self, xfrom, yfrom, xto, yto):
        if len(self._taxis) == 0:
            raise Exception("There are no taxis.")
        if not xfrom.is_integer() or not yfrom.is_integer() or not xto.is_integer() or not yto.is_integer():
            raise Exception("Invalid coordinates.")

        idx = self._get_closest_taxi(xfrom, yfrom)
        self._taxis[idx].x = xto
        self._taxis[idx].y = yto
        self._taxis[idx].fare += self.Manhattan_distance(xfrom, yfrom, xto, yto)

    def get_all(self):
        return self._taxis.copy()

    @staticmethod
    def Manhattan_distance(x1, y1, x2, y2):
        return abs(x1 - x2) + abs(y1 - y2)