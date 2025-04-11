import ctypes
import unittest
import os

file_path = os.path.realpath(__file__)
dir_path = os.path.dirname(file_path)

try:
    lib = ctypes.CDLL(f'{dir_path}/c_lib/3_1_string_reversal.so')
    print("[✓] Successfully loaded shared library.")
except OSError as e:
    print("[✗] Failed to load shared library.")
    raise e

lib.reverse_string.argtypes = [ctypes.c_char_p]
lib.reverse_string.restype = ctypes.c_void_p  # <- critical fix

lib.free_string.argtypes = [ctypes.c_void_p]
lib.free_string.restype = None

class TestStringReversal(unittest.TestCase):
    def test_reverse(self):
        c_result = lib.reverse_string(b"hello")
        result = ctypes.string_at(c_result).decode()
        self.assertEqual(result, "olleh")
        lib.free_string(c_result)

    def test_racecar(self):
        c_result = lib.reverse_string(b"racecar")
        result = ctypes.string_at(c_result).decode()
        self.assertEqual(result, "racecar")
        lib.free_string(c_result)

if __name__ == '__main__':
    unittest.main()
