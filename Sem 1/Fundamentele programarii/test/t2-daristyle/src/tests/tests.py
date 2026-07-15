from unittest import TestCase

from repository import Repository
from services import Service

class tests(TestCase):
    def setUp(self):
        self.service = None

    def test_exceptions(self):
        self.service = Service(0)
        try:
            self.service.ride(0, 0, 100, 100)
            self.assertTrue(False)
        except Exception:
            pass

        self.service = Service(10)
        try:
            self.service.ride(0.1, 0, 100, 100)
            self.assertTrue(False)
        except Exception:
            pass

        try:
            self.service.ride(0, "6", 100, 100)
            self.assertTrue(False)
        except Exception:
            pass

        try:
            self.service.ride(0, 0, 100.1, 100)
            self.assertTrue(False)
        except Exception:
            pass

        try:
            self.service.ride(0, 0, 100, None)
            self.assertTrue(False)
        except Exception:
            pass

    def test_functionality(self):
        self.service = Service(10)
        l = self.service.get_taxis_decreasing()
        taxi = l[0]
        xfrom = taxi.x - 1 if taxi.x > 0 else taxi.x + 1
        yfrom = taxi.y - 1 if taxi.y > 0 else taxi.y + 1
        xto = 100
        yto = 100
        if xfrom == xto and yfrom == yto:
            xto = yto = 0
        self.service.ride(xfrom, yfrom, xto, yto)

        l = self.service.get_taxis_decreasing()
        taxi = l[0]
        self.assertTrue(taxi.x == xto and taxi.y == yto and taxi.fare == Repository.Manhattan_distance(xfrom, yfrom, xto, yto))