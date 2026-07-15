from service.Services import Service

class UI:
    def __init__(self, room_file, reservation_file):
        self.__service = Service(room_file, reservation_file)

    def __print_main_menu(self):
        print("======Main Menu======")
        print("1. Reserve")
        print("2. Cancel a reservation")
        print("3. Show reservations between")
        print("4. Show all reservations by month")
        print("5. Show monthly report")
        print("0. Quit")

    def __reserve(self):
        tokens = input("Enter the dates between you want to reserve(format dd.mm-dd.mm): ").strip().split("-")
        if len(tokens) != 2:
            print("Invalid input format")
            return
        arrival = tokens[0].strip().split(".")
        departure = tokens[1].strip().split(".")
        if len(arrival) != 2 or len(departure) != 2 or not arrival[0].isdigit() or not arrival[1].isdigit() or not  departure[0].isdigit() or not departure[1].isdigit():
            print("Invalid date")
            return

        arrival_day = int(arrival[0])
        departure_day = int(departure[0])
        arrival_month = int(arrival[1])
        departure_month = int(departure[1])

        rooms = self.__service.get_available_rooms(arrival_day, arrival_month, departure_day, departure_month)
        if len(rooms) == 0:
            print("No rooms available")
            return

        for room in rooms:
            print(room)

        number = input("Enter the room number: ").strip()
        if not number.isdigit():
            print("Invalid room number")
            return
        number = int(number)
        name = input("Enter the name: ").strip()
        guests = input("Enter the number of guests: ").strip()
        if not guests.isdigit():
            print("Invalid number of guests")
            return
        guests = int(guests)

        self.__service.reserve(number, name, guests, arrival_day, arrival_month, departure_day, departure_month)

        print("Reservation completed")

    def __delete(self):
        id = input("Enter the id of the reservation: ").strip()
        if not id.isdigit():
            print("Invalid id")
            return
        id = int(id)
        self.__service.delete(id)

        print("Reservation deleted successfully")

    def __show_reservations_between(self):
        tokens = input("Enter the dates between you want to check the reservations(format dd.mm-dd.mm): ").strip().split("-")
        arrival = tokens[0].split(".")
        departure = tokens[1].split(".")
        if not arrival[0].isdigit() or not arrival[1].isdigit() or not departure[0].isdigit() or not departure[1].isdigit():
            print("Invalid date")
            return

        arrival_day = int(arrival[0])
        departure_day = int(departure[0])
        arrival_month = int(arrival[1])
        departure_month = int(departure[1])

        print(self.__service.get_reservations_between(arrival_day, arrival_month, departure_day, departure_month))

    def __show_reservations_by_month(self):
        for string in self.__service.get_reservations_by_month():
            print(string)

    def __show_monthly_report(self):
        month = input("Enter the month: ").strip()
        if not month.isdigit():
            print("Invalid month")
        month = int(month)
        if not (1 <= month <= 12):
            print("Invalid month")

        print(self.__service.get_monthly_report(month))

    def start(self):
        exited = False

        while not exited:
            self.__print_main_menu()

            try:
                command = input("Enter a command: ").strip()
                if command == "1":
                    self.__reserve()
                elif command == "2":
                    self.__delete()
                elif command == "3":
                    self.__show_reservations_between()
                elif command == "4":
                    self.__show_reservations_by_month()
                elif command == "5":
                    self.__show_monthly_report()
                elif command == "0":
                    exited = True
                else:
                    print("Invalid command")
            except Exception as e:
                print(e)