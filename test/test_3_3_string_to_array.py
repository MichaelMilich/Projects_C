import ctypes
import unittest
import os
import subprocess

c_code_name = '3_3_string_to_array'
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

lib.check_format.argtypes = [ctypes.c_char_p]
lib.check_format.restype = ctypes.c_bool 


class TestStringArrayLib(unittest.TestCase):
    def _test_format_lib(self,test_input, expected):
        result = lib.check_format(test_input)
        self.assertEqual(result, expected)
        
    def test_string_with_whitespace(self):
        self._test_format_lib(b" [a, b, c] ",True)

    def test_string_without_whitespace(self):
        self._test_format_lib(b"[a, b, c]",True)

    def test_no_closing_brackets(self):
        self._test_format_lib(b"[a, b, c",False)

    def test_no_opening_brackets(self):
        self._test_format_lib(b"a, b, c]",False)

    def test_extra_wording(self):
        self._test_format_lib(b"[a, b] extra",False)

    def test_trailing_white_spaces(self):
        self._test_format_lib(b"   [a]   ",True)
    
    def test_empty_string(self):
        self._test_format_lib(b"",False)

class TestStringArrayExec(unittest.TestCase):
    def _test_exec(self, exec_inputs,expected):
        if not isinstance(exec_inputs, list):
            input_list = [executable_path, exec_inputs]
        else:
            input_list = [executable_path] + exec_inputs

        result = subprocess.run(input_list, capture_output=True, text=True)
        self.assertIn(expected, result.stdout)

    def test_string_with_whitespace(self):
        self._test_exec(b" [a, b, c] ","✓")

    def test_string_without_whitespace(self):
        self._test_exec(b"[a, b, c]","✓")

    def test_no_closing_brackets(self):
        self._test_exec(b"[a, b, c","[FORMAT_ERROR]")

    def test_no_opening_brackets(self):
        self._test_exec(b"a, b, c]","[FORMAT_ERROR]")

    def test_extra_wording(self):
        self._test_exec(b"[a, b] extra","[FORMAT_ERROR]")

    def test_trailing_white_spaces(self):
        self._test_exec(b"   [a]   ","✓")
    
    def test_empty_string(self):
        self._test_exec(b"","[FORMAT_ERROR]")

    def test_multiple_args(self):
        result = subprocess.run([executable_path, "arg1", "arg2"], capture_output=True, text=True)
        self.assertIn("Usage:", result.stdout)

if __name__ == '__main__':
    unittest.main()
