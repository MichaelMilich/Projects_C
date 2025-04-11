import ctypes
import unittest
import os
import subprocess

c_code_name = '3_1_string_reversal'
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

lib.reverse_string.argtypes = [ctypes.c_char_p]
lib.reverse_string.restype = ctypes.c_void_p  # <- critical fix

lib.free_string.argtypes = [ctypes.c_void_p]
lib.free_string.restype = None

class TestStringReversalLib(unittest.TestCase):
    def _test_lib(self,test_input, expected):
        c_result = lib.reverse_string(test_input)
        result = ctypes.string_at(c_result).decode()
        self.assertEqual(result, expected)
        lib.free_string(c_result)


    def test_reverse(self):
        self._test_lib(b"hello","olleh")

    def test_racecar(self):
        self._test_lib(b"racecar","racecar")

    def test_empty_string(self):
        self._test_lib(b"","")

    def test_special_chars(self):
        self._test_lib(b"@!123abc","cba321!@")

    def test_long_string(self):
        input_str = b"a" * 1000
        expected = "a" * 1000
        self._test_lib(input_str,expected)

class TestStringReversalExec(unittest.TestCase):
    def _test_exec(self, expected, exec_inputs):
        if isinstance(exec_inputs, str):
            input_list = [executable_path, exec_inputs]
        else:
            input_list = [executable_path] + exec_inputs

        result = subprocess.run(input_list, capture_output=True, text=True)
        self.assertIn(expected, result.stdout)

    def test_reverse(self):
        self._test_exec("olleh", "hello")

    def test_racecar(self):
        self._test_exec("racecar", "racecar")

    def test_empty_string(self):
        self._test_exec("The output is: ", "")

    def test_special_chars(self):
        self._test_exec("cba321!@", "@!123abc")

    def test_multiple_args(self):
        result = subprocess.run([executable_path, "arg1", "arg2"], capture_output=True, text=True)
        self.assertIn("Usage:", result.stdout)

if __name__ == '__main__':
    unittest.main()
