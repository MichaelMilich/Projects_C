import ctypes
import unittest
import os
import subprocess

c_code_name = '4_1_swap_function'
file_path = os.path.realpath(__file__)
dir_path = os.path.dirname(file_path)
project_path = os.path.dirname(dir_path)
executable_path = os.path.join(project_path, "bin", f"{c_code_name}.o")
lib_path = os.path.join(dir_path, "c_lib", f"{c_code_name}.so")

try:
    lib = ctypes.CDLL(lib_path)
    print("[✓] Successfully loaded shared library.")
except OSError as e:
    print("[✗] Failed to load shared library.")
    raise e

lib.swap.argtypes = [ctypes.POINTER(ctypes.c_int), ctypes.POINTER(ctypes.c_int)]
lib.swap.restype = None

class TestSwapFunctionLib(unittest.TestCase):
    def _test_lib(self, test_input, expected):
        input_1, input_2 = test_input
        c_input_1 = ctypes.c_int(input_1)
        c_input_2 = ctypes.c_int(input_2)
        pointer_1 = ctypes.byref(c_input_1)
        pointer_2 = ctypes.byref(c_input_2)

        lib.swap(pointer_1, pointer_2)

        # Check after swap
        self.assertEqual((c_input_1.value, c_input_2.value), expected)

    def test_swap_tuple(self):
        input_tuple = (1, 2)
        expected = (2, 1)
        self._test_lib(input_tuple, expected)

    def test_swap_negative(self):
        input_tuple = (-10, 20)
        expected = (20, -10)
        self._test_lib(input_tuple, expected)

    def test_swap_same_value(self):
        input_tuple = (7, 7)
        expected = (7, 7)
        self._test_lib(input_tuple, expected)

class TestSwapFunctionExec(unittest.TestCase):
    def _test_exec(self, exec_inputs,expected):
        if not isinstance(exec_inputs, list):
            input_list = [executable_path, exec_inputs]
        else:
            input_list = [executable_path] + exec_inputs

        result = subprocess.run(input_list, capture_output=True, text=True)
        self.assertIn(expected, result.stdout)

    def test_swap_tuple(self):
        a= 1
        b= 2
        input_list = [str(a),str(b)]
        expected_output = f"after swap: a = {b}, b = {a}"
        self._test_exec(input_list,expected_output)

    
    def test_multiple_args(self):
        result = subprocess.run([executable_path, "arg1"], capture_output=True, text=True)
        self.assertIn("Usage:", result.stdout)

if __name__ == '__main__':
    unittest.main()
