#
# Write the implementation in this file
#

REPRESENTATION = "list"# "list"/"dict"

# 
# Write below this comment 
# Functions to deal with complex numbers -- list representation
# -> There should be no print or input statements in this section 
# -> Each function should do one thing only
# -> Functions communicate using input parameters and their return values
#

def create_complex_list(real_part: float, imaginary_part: float) -> list:
    return [real_part, imaginary_part]

def get_real_part_list(z) -> float:
    """
    :param z: complex number in the list representation
    :return: real part of the complex number
    """
    return z[0]

def get_imaginary_part_list(z) -> float:
    """
    :param z: complex number in the list representation
    :return: imaginary part of the complex number
    """
    return z[1]

#
# Write below this comment 
# Functions to deal with complex numbers -- dict representation
# -> There should be no print or input statements in this section 
# -> Each function should do one thing only
# -> Functions communicate using input parameters and their return values
#

def create_complex_dictionary(real_part: float, imaginary_part: float) -> dict:
    return {"real_part": real_part, "imaginary_part": imaginary_part}

def get_real_part_dictionary(z) -> float:
    """
    :param z: complex number in the dictionary representation
    :return: real part of the complex number
    """
    return z["real_part"]

def get_imaginary_part_dictionary(z) ->  float:
    """
    :param z: complex number in the dictionary representation
    :return: imaginary part of the complex number
    """
    return z["imaginary_part"]

def create_complex(real_part: float, imaginary_part: float):
    if REPRESENTATION == "list":
        return create_complex_list(real_part, imaginary_part)
    elif REPRESENTATION == "dict":
        return create_complex_dictionary(real_part, imaginary_part)
    else:
        raise ValueError("Representation error")

def get_real_part(z) -> float:
    if REPRESENTATION == "list":
        return get_real_part_list(z)
    elif REPRESENTATION == "dict":
        return get_real_part_dictionary(z)
    else:
        raise ValueError("Representation error")

def get_imaginary_part(z) -> float:
    if REPRESENTATION == "list":
        return get_imaginary_part_list(z)
    elif REPRESENTATION == "dict":
        return get_imaginary_part_dictionary(z)
    else:
        raise ValueError("Representation error")

def to_str(z):
    re = get_real_part(z)
    if re.is_integer():
        re = int(re)
    s = str(re)

    im = get_imaginary_part(z)
    if im >= 0:
        s += "+"
    if im.is_integer():
        im = int(im)
    s += str(im)
    s += "i"
    return s

def from_str(s):
    i = 0

    signre = 1
    if s[0] == "-":
        signre = -1
        i += 1

    re = ""
    while i < len(s) and s[i] in "0123456789.":
        re += s[i]
        i += 1

    if i >= len(s) or re == "":
        raise ValueError("Invalid format")

    if s[i] not in "-+":
        raise ValueError("Invalid format")

    signim = 1
    if s[i] == "-":
        signim = -1
    im = ""

    i += 1
    while i < len(s) and s[i] in "0123456789.":
        im += s[i]
        i += 1

    if i >= len(s) or im == "":
        raise ValueError("Invalid format")

    if s[i] != "i":
        raise ValueError("Invalid format")

    re = signre * float(re)
    im = signim * float(im)

    return create_complex(re, im)

#
# Write below this comment 
# Functions that deal with subarray/subsequence properties
# -> There should be no print or input statements in this section 
# -> Each function should do one thing only
# -> Functions communicate using input parameters and their return values
#

#8.A longest subarray of numbers where both their real and imaginary parts can be written using the same base 10 digits
# (e.g. 1+3i, 31i, 33+i, 111, 11-313i)

def get_digit_list(s: str) -> list:
    """
    :param x: a real number
    :return: the sorted list of the digits appearing in x
    """
    l = []
    for d in s:
        if d.isdigit():
            l.append(int(d))

    return sorted(list(set(l)))

def included(l1: list, l2: list) -> bool:
    """
    :param l1: list
    :param l2: list
    :return: True if every element of l1 is in l2, False otherwise
    """

    for x in l1:
        is_in_l2 = False
        for y in l2:
            if x == y:
                is_in_l2 = True
        if is_in_l2 is False:
            return False
    return True


def longest_subarray(l: list) -> list:
    if len(l) == 0:
        return 0
    digit_list = []
    length = 0
    len_max = -1
    end = 0
    for i in range(0, len(l)):
        z = l[i]

        complex_digits = get_digit_list(to_str(z))
        if included(complex_digits, digit_list):
            length += 1
        else:
            if length > len_max:
                len_max = length
                end = i
            length = 1
            digit_list = complex_digits

    if length > len_max:
        len_max = length
        end = i + 1

    return l[end-len_max:end - 1]

#3.A maximum subarray sum, when considering each number's real part.

def maximum_sum_subarray(l: list) -> int:
    if len(l) == 0:
        return 0
    sum = sum_max = get_real_part(l[0])
    l_ans = l_cur = [l[0]]
    for i in range(1, len(l)):
        z = l[i]

        if sum < 0:
            sum = 0
            l_cur = []

        sum += get_real_part(z)
        l_cur.append(z)

        if sum > sum_max:
            sum_max = sum
            l_ans = l_cur.copy()

    return l_ans

#
# Write below this comment 
# UI section
# Write all functions that have input or print statements here
# Ideally, this section should not contain any calculations relevant to program functionalities
#

def print_menu() -> None:
    print("1.Read a new list of complex numbers(a+bi format)")
    print("2.Print the list")
    print("3.Print a longest subarray of numbers where both their real and imaginary parts can be written using the same"
          " base 10 digits")
    print("4.Print a maximum subarray sum, when considering each number's real part.")
    print("5.Exit")

def read_list_ui(l: list) -> None:
    n = input("Enter the number of complex numbers: ")
    if n.isdigit() is False:
        raise ValueError("The number of complex numbers must be a positive integer")
    n = int(n)
    if n <= 0:
        raise ValueError("The number of complex numbers must be a positive integer")

    user_input = input("Enter the list of complex(a+bi format) numbers separated by a comma: ")
    tokens = user_input.split(",")

    if len(tokens) != n:
        raise ValueError("You entered the wrong number of complex numbers")

    l.clear()
    for i in range(0, len(tokens)):
        tokens[i] = tokens[i].strip()
        l.append(from_str(tokens[i]))

def print_list_ui(l: list) -> None:
    s = ""
    for i in range(0, len(l)):
        s += to_str(l[i])
        if i < len(l) - 1:
            s += ", "

    print(s)

def same_digits_subarray_ui(l: list) -> None:
    print_list_ui(longest_subarray(l))

def maximum_sum_subarray_ui(l: list) -> None:
    print_list_ui(maximum_sum_subarray(l))

def start() -> None:
    exited = False
    command = {"1": read_list_ui, "2": print_list_ui, "3": same_digits_subarray_ui, "4": maximum_sum_subarray_ui}

    l = [create_complex(0, 0)]
    for re in [1, -1, 0.1]:
        for im in [1, -1, 0.1]:
            l.append(create_complex(re, im))

    while not exited:
        print_menu()
        op = input("Enter command: ")
        if op in command:
            try:
                command[op](l)
            except ValueError as ve:
                print(ve)
        elif op == "5":
            exited = True
        else:
            print("Invalid command")

start()