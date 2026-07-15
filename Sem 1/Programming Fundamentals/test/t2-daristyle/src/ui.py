from texttable import Texttable
from services import Service


class UI:
    def __init__(self):
        self._service = None

    def _print_menu(self):
        print("=====Main Menu=====")
        print("1. Ride")
        print("2. Simulate a ride")
        print("3. Exit")

    def _ride(self):
        inpt = input("Enter the starting position of the ride(separated by one space): ").strip()
        inpt = inpt.split()
        xfrom = int(inpt[0])
        yfrom = int(inpt[1])
        inpt = input("Enter the end position of the ride(separated by one space): ").strip()
        inpt = inpt.split()
        xto = int(inpt[0])
        yto = int(inpt[1])

        self._service.ride(xfrom, yfrom, xto, yto)

        print("Ride Completed")

    def _simulate(self):
        pos = self._service.simulate()
        xfrom = pos[0][0]
        yfrom = pos[0][1]
        xto = pos[1][0]
        yto = pos[1][1]

        print("Ride Simulated From (" + str(xfrom) + ", " + str(yfrom) + ") to (" + str(xto) + ", " + str(yto) + ")")

    def _print_all(self):
        tt = Texttable()
        tt.header(["ID", "X", "Y", "Fare"])
        l = self._service.get_taxis_decreasing()
        for taxi in l:
            tt.add_row([taxi.id, taxi.x, taxi.y, taxi.fare])

        print(tt.draw())

    def start(self):
        inpt = " "
        while not inpt.isdigit():
            inpt = input("Enter the number of taxis(an integer): ").strip()
        inpt = int(inpt)

        self._service = Service(inpt)
        exited = False
        while not exited:
            self._print_all()
            self._print_menu()

            command = input("Enter the command: ")
            if command in ["1", "2"]:
                try:
                    if command == "1":
                        self._ride()
                    elif command == "2":
                        self._simulate()
                except AssertionError as e:
                    print(e)
            elif command == "3":
                exited = True
                print("Bye bye")
            else:
                print("Invalid command")