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
lib.new_empty_array.restype = ctypes.c_void_p
lib.append_value.argtypes = [ctypes.c_void_p, ctypes.c_int]
lib.append_value.restype = ctypes.c_int
lib.pop.argtypes = [ctypes.c_void_p, ctypes.POINTER(ctypes.c_int)]
lib.pop.restype = ctypes.c_bool
lib.free_array_memory.argtypes = [ctypes.c_void_p]
lib.free_array_memory.restype = ctypes.c_bool
lib.find_value_index.argtypes = [ctypes.c_void_p, ctypes.c_int]
lib.find_value_index.restype = ctypes.c_int
lib.get_value_at_index.argtypes = [ctypes.c_void_p, ctypes.c_size_t, ctypes.POINTER(ctypes.c_int)]
lib.get_value_at_index.restype = ctypes.c_int
lib.convert_string_to_dynamic_int_array.restype = ctypes.c_void_p
lib.convert_string_to_dynamic_int_array.argtypes = [ctypes.c_char_p]

class DynamicIntArray:

    @staticmethod
    def from_ptr(ptr):
        obj = DynamicIntArray.__new__(DynamicIntArray)
        obj._ptr = ptr
        return obj
    
    def __init__(self):
        self._ptr = lib.new_empty_array()
        if not self._ptr:
            raise MemoryError("Failed to allocate DynamicIntArray.")

    def append(self, value: int) -> int:
        idx = lib.append_value(self._ptr, value)
        if idx == -1:
            raise RuntimeError("Failed to append value.")
        return idx

    def pop(self) -> int:
        out_value = ctypes.c_int()
        success = lib.pop(self._ptr, ctypes.byref(out_value))
        if not success:
            raise IndexError("Pop from empty array.")
        return out_value.value

    def find_index(self, value: int) -> int:
        return lib.find_value_index(self._ptr, value)

    def __getitem__(self, index: int) -> int:
        """Support arr[index] access."""
        out_value = ctypes.c_int()
        result = lib.get_value_at_index(self._ptr, index, ctypes.byref(out_value))
        if result == -1:
            raise IndexError(f"Index {index} out of bounds.")
        return out_value.value

    def __len__(self) -> int:
        """Support len(arr)."""
        # `size_t size` is at offset 0 in the C struct
        class _Struct(ctypes.Structure):
            _fields_ = [
                ("size", ctypes.c_size_t),
                ("capacity", ctypes.c_size_t),
                ("data", ctypes.POINTER(ctypes.c_int)),
                ("is_dynamic_memory", ctypes.c_bool),
            ]

        struct = ctypes.cast(self._ptr, ctypes.POINTER(_Struct)).contents
        return struct.size

    def __str__(self) -> str:
        """Support str(arr) and print(arr)."""
        values = [self[i] for i in range(len(self))]
        return str(values)

    def __del__(self):
        if self._ptr:
            lib.free_array_memory(self._ptr)
            self._ptr = None


class TestStringArrayLib(unittest.TestCase):
    def _test_format_lib(self,test_input, expected):
        result = lib.check_format(test_input)
        self.assertEqual(result, expected)

    def _test_convert_string_to_dynamic_int_array(self, test_input, expected_values):
        raw_ptr = lib.convert_string_to_dynamic_int_array(test_input)
        self.assertTrue(raw_ptr)  # Ensure it's not NULL

        arr = DynamicIntArray.from_ptr(raw_ptr)
        self.assertEqual(len(arr), len(expected_values))

        for i, val in enumerate(expected_values):
            self.assertEqual(arr[i], val)

        del arr  # Ensures memory is freed
        
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
    
    def test_empty_list_converted(self):
        self._test_convert_string_to_dynamic_int_array(b"[]",[])
    
    def test_parsing_integer_array(self):
        self._test_convert_string_to_dynamic_int_array(
            b"[1, 2, 3, 4, 5]",
            [1, 2, 3, 4, 5]
        )

    def test_parsing_with_spaces(self):
        self._test_convert_string_to_dynamic_int_array(
            b"    [   10 ,  20 ,30   ]   ",
            [10, 20, 30]
        )

    def test_parsing_single_element(self):
        self._test_convert_string_to_dynamic_int_array(
            b"[42]",
            [42]
        )



class TestStringArrayExec(unittest.TestCase):
    def _test_exec(self, exec_inputs,expected_format_response,expected_list_response):
        if not isinstance(exec_inputs, list):
            input_list = [executable_path, exec_inputs]
        else:
            input_list = [executable_path] + exec_inputs

        result = subprocess.run(input_list, capture_output=True, text=True)
        self.assertIn(expected_format_response, result.stdout)
        self.assertIn(expected_list_response,result.stdout)

    def test_string_with_whitespace(self):
        self._test_exec(b" [a, b, c] ","✓", "Warning: could not convert token")

    def test_string_without_whitespace(self):
        self._test_exec(b"[a, b, c]","✓","Warning: could not convert token")

    def test_no_closing_brackets(self):
        self._test_exec(b"[a, b, c","[FORMAT_ERROR]", "[FORMAT_ERROR]") # we don't get to the parsing itself

    def test_no_opening_brackets(self):
        self._test_exec(b"a, b, c]","[FORMAT_ERROR]", "[FORMAT_ERROR]") # we don't get to the parsing itself

    def test_extra_wording(self):
        self._test_exec(b"[a, b] extra","[FORMAT_ERROR]", "[FORMAT_ERROR]") # we don't get to the parsing itself

    def test_trailing_white_spaces(self):
        self._test_exec(b"   [a]   ","✓","Warning: could not convert token")

    def test_empty_string(self):
        self._test_exec(b"","[FORMAT_ERROR]", "[FORMAT_ERROR]") # we don't get to the parsing itself

    def test_multiple_args(self):
        result = subprocess.run([executable_path, "arg1", "arg2"], capture_output=True, text=True)
        self.assertIn("Usage:", result.stdout)

    def test_converted_list(self):
        self._test_exec(b"   [1  ,2   ,3,7,8]","✓","[ 1, 2, 3, 7, 8 ]")
        self._test_exec(b"   [1  ,2   ,3,7,8]","✓","size = 5")

if __name__ == '__main__':
    unittest.main()
