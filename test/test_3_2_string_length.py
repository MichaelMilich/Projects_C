import ctypes
import unittest
import os
import subprocess

c_code_name = '3_2_string_length'
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

lib.string_length.argtypes = [ctypes.c_char_p]
lib.string_length.restype = ctypes.c_int

class TestStringLengthLib(unittest.TestCase):
    def _test_string_length(self,input_str, expected_int):
        result = lib.string_length(input_str)
        self.assertEqual(result,expected_int)

    def test_empty_string(self):
        self._test_string_length(b"",0)
    
    def test_not_empty_string(self):
        input_str = b"-1-1-1-1-1-1-1"
        self._test_string_length(input_str, len(input_str))
    
    def test_string_with_special_cases(self):
        input_str = b"\x01\x02\x03\x04\x05''"
        self._test_string_length(input_str, len(input_str))
    
    def test_null_input(self):
        result = lib.string_length(None)
        self.assertEqual(result, -1)

class TestStringLengthExec(unittest.TestCase):
    def _test_exec(self, exec_inputs,expected):
        if not isinstance(exec_inputs, list):
            input_list = [executable_path, exec_inputs]
        else:
            input_list = [executable_path] + exec_inputs

        result = subprocess.run(input_list, capture_output=True, text=True)
        self.assertIn(expected, result.stdout)

    def test_empty_string(self):
        input_str = b""
        decoded_str = input_str.decode('utf-8')
        expected_output = f"length of string {decoded_str} is {len(decoded_str)}"
        self._test_exec(input_str,expected_output)
    
    def test_not_empty_string(self):
        input_str = b"-1-1-1-1-1-1-1"
        decoded_str = input_str.decode('utf-8')
        expected_output = f"length of string {decoded_str} is {len(decoded_str)}"
        self._test_exec(input_str,expected_output)
    
    def test_string_with_special_cases(self):
        input_str = b"\x01\x02\x03\x04\x05''"
        decoded_str = input_str.decode('utf-8')
        expected_output = f"length of string {decoded_str} is {len(decoded_str)}"
        self._test_exec(input_str,expected_output)

if __name__ == '__main__':
    unittest.main()