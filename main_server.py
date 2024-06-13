import ctypes

lib = ctypes.CDLL('./libdart_interface.so')


if __name__ == '__main__':
    my_function = lib.are_equal
    my_function.argtypes = [ctypes.c_char_p, ctypes.c_char_p]
    my_function.restype = ctypes.c_int

    b_string1 = "./data/named/eminem_1.png".encode('utf-8')
    b_string2 = "./data/named/eminem_2.png".encode('utf-8')
    result = my_function(b_string1, b_string2)
    print(result)
