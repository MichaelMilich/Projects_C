# test_4_2_sum_of_array_elements.py

import ctypes
import unittest
import os
import subprocess

# Setup paths
c_code_name = '4_2_sum_of_array_elements'
file_path = os.path.realpath(__file__)
dir_path = os.path.dirname(file_path)
project_path = os.path.dirname(dir_path)
executable_path = os.path.join(project_path, "bin", f"{c_code_name}.o")
lib_path = os.path.join(dir_path, "c_lib", f"{c_code_name}.so")

# Load the shared library
try:
    lib = ctypes.CDLL(lib_path)
    print("[✓] Successfully loaded shared library.")
except OSError as e:
    print("[✗] Failed to load shared library.")
    raise e

lib.sum.argtypes = [ctypes.POINTER(ctypes.c_int), ctypes.c_int]
lib.sum.restype = ctypes.c_int

class TestArraySumLib(unittest.TestCase):
    def _test_sum_lib(self, test_input, expected):
        arr = (ctypes.c_int * len(test_input))(*test_input)  # Create C array
        result = lib.sum(arr, len(test_input))
        self.assertEqual(result, expected)

    def test_empty_array(self):
        test_input = []
        expected = 0
        self._test_sum_lib(test_input, expected)

    def test_single_element_array(self):
        test_input = [1]
        expected = sum(test_input)
        self._test_sum_lib(test_input, expected)

    def test_many_elements_array(self):
        test_input = [1, 7, 4, 8, 3]
        expected = sum(test_input)
        self._test_sum_lib(test_input, expected)

class TestArraySumExec(unittest.TestCase):
    def _test_exec(self, exec_input, expected):
        input_list = [executable_path, exec_input]
        result = subprocess.run(input_list, capture_output=True, text=True)
        self.assertIn(expected, result.stdout)

    def test_empty_array_exec(self):
        test_input = "[ 0]"
        expected = f"sum = 0"
        self._test_exec(test_input, expected)

    def test_single_element_array_exec(self):
        test_input = "[1]"
        expected = f"sum = 1"
        self._test_exec(test_input, expected)

    def test_many_elements_array_exec(self):
        test_input = "[1,7,4,8,3]"
        expected = f"sum = 23"
        self._test_exec(test_input, expected)

if __name__ == '__main__':
    unittest.main()
