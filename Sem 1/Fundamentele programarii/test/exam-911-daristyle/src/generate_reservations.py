from faker import Faker
import random

days = [31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]
capacity = [0, 0, 0, 0, 0]
with open("rooms.txt", "r") as file:
    for line in file:
        tokens = line.strip().split(" ")
        if len(tokens) != 3 or tokens[2] != "room" or (tokens[1] not in ["single", "double", "family"]) or not tokens[
            0].isdigit():
            raise Exception("Invalid room file format")

        tokens[0] = int(tokens[0])
        capacity[tokens[0] - 1] = 1 if tokens[1] == "single" else 2 if tokens[1] == "double" else 4

with open("reservations.txt", "w") as file:
    faker = Faker()
    room = 0
    day = 0
    month = 0
    id = 1
    for i in range(1000):
        guests = random.randint(1, capacity[room])
        name = faker.name()
        date = str(day + 1) + "." + str(month + 1)
        file.write(str(id) + " " + str(room + 1) + " " + name + " " + str(guests) + " " + date + " " + date + "\n")

        id += 1
        room += 1
        if room >= 5:
            room = 0
            day += 1
            if day >= days[month]:
                day = 0
                month += 1