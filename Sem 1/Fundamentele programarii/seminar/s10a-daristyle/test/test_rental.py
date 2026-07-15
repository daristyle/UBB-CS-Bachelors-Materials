from unittest import TestCase
from domain.car import Car, CarColors
from domain.rental import Rental
from datetime import date

class RentalTest(TestCase):
    def test_rental_1(self):
        car = Car(100, "SJ 33 ABC", "Golf 6",CarColors.MAGENTA)
        rental = Rental(12, car, date(2025, 12, 4), date(2025, 12, 10))

        self.assertEqual(12, rental.id)
        self.assertEqual(car, rental.car)
        self.assertEqual(date(2025, 12, 4), rental.start)
        self.assertEqual(date(2025, 12, 10), rental.end)

    def test_rental_2(self):
        car = Car(120, "SB 28 BIS", "Skoda Octavia", CarColors.RED)
        rental = Rental(17, car, date(2025, 4, 3), date(2026, 2, 10))

        self.assertEqual(17, rental.id)
        self.assertEqual(car, rental.car)
        self.assertEqual(date(2025, 4, 3), rental.start)
        self.assertEqual(date(2026, 2, 10), rental.end)
