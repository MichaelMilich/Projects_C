import ctypes
import unittest
import os
import subprocess

c_code_name = '1_1_is_odd_checker'
file_path = os.path.realpath(__file__)
dir_path = os.path.dirname(file_path)
project_path = os.path.dirname(dir_path)
executable_path = os.path.join(project_path,"bin",f"{c_code_name}.o")
lib_path = os.path.join(dir_path,"c_lib",f"{c_code_name}.so")

try:
    lib = ctypes.CDLL(lib_path)
    print("[✓] Successfully loaded shared library.")
except OSError as e:
    print("[✗] Failed to load shared library.")
    raise e

lib.is_even.argtypes = [ctypes.c_int]
lib.is_even.restype = ctypes.c_bool  # <- critical fix
#is_even
class TestIsEvenLib(unittest.TestCase):
    def _test_lib(self,test_input, expected):
        result = lib.is_even(test_input)
        self.assertEqual(result, expected)

    def test_zero(self):
        self._test_lib(0,True)

    def test_one(self):
        self._test_lib(1,False)

    def test_two(self):
        self._test_lib(2,True)

    def test_minus_5(self):
        self._test_lib(-5,False)


class TestIsEvenExec(unittest.TestCase):
    def _test_exec(self, exec_inputs,expected):
        if not isinstance(exec_inputs, list):
            input_list = [executable_path, exec_inputs]
        else:
            input_list = [executable_path] + exec_inputs

        result = subprocess.run(input_list, capture_output=True, text=True)
        self.assertIn(expected, result.stdout)

    def test_zero(self):
        self._test_exec("0","even")

    def test_one(self):
        self._test_exec("1","odd")

    def test_two(self):
        self._test_exec("2","even")

    def test_minus_5(self):
        self._test_exec("-5", "odd")

    def test_multiple_args(self):
        result = subprocess.run([executable_path, "arg1", "arg2"], capture_output=True, text=True)
        self.assertIn("Usage:", result.stdout)

if __name__ == '__main__':
    unittest.main()
