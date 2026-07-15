import random
from repository import Repository

class Service:
    def __init__(self, number_of_taxis=0):
        self._repo = Repository()

        locations = [(i, j) for j in range(0, 101) for i in range(0, 101)]
        id = 1
        for _ in range(0, number_of_taxis):
            idx = random.randint(0, len(locations) - 1)
            x = locations[idx][0]
            y = locations[idx][1]

            i = 0
            while i < len(locations):
                if Repository.Manhattan_distance(x, y, locations[i][0], locations[i][1]) <= 5:
                    locations.pop(i)
                else:
                    i += 1

            self._repo.add(id, x, y)
            id += 1

    def ride(self, xfrom, yfrom, xto, yto):
        self._repo.ride(xfrom, yfrom, xto, yto)

    def simulate(self):
        locations = [(i, j) for j in range(0, 101) for i in range(0, 101)]
        idx = random.randint(0, len(locations) - 1)
        xfrom = locations[idx][0]
        yfrom = locations[idx][1]

        i = 0
        while i < len(locations):
            if Repository.Manhattan_distance(xfrom, yfrom, locations[i][0], locations[i][1]) < 10:
                locations.pop(i)
            else:
                i += 1
        idx = random.randint(0, len(locations) - 1)
        xto = locations[idx][0]
        yto = locations[idx][1]

        self._repo.ride(xfrom, yfrom, xto, yto)

        return [(xfrom, yfrom), (xto, yto)]

    def get_taxis_decreasing(self):
        l = self._repo.get_all()
        l.sort(key=lambda x: x.fare, reverse=True)

        return l.copy()