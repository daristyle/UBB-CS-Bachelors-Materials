from unittest import TestCase

from poetry.console.commands import self

from domain.car import Car, CarColors

class CarTest(TestCase):
    def test_car_1(self):
        car = Car(100, "SJ 33 ABC", "Golf 6",CarColors.MAGENTA)

        self.assertEqual(100, car.id)
        self.assertEqual("SJ 33 ABC", car.license_plate)
        self.assertEqual("Golf 6", car.model)
        self.assertEqual(CarColors.MAGENTA, car.color)

    def test_car_2(self):
        car = Car(120, "SB 28 BIS", "Skoda Octavia", CarColors.RED)

        self.assertEqual(120, car.id)
        self.assertEqual("SB 28 BIS", car.license_plate)
        self.assertEqual("Skoda Octavia", car.model)
        self.assertEqual(CarColors.RED, car.color)
