# test_dynamic_int_array.py
import ctypes
import unittest
import os

# Load the shared library
c_code_name = 'dynamic_int_array'
file_path = os.path.realpath(__file__)
dir_path = os.path.dirname(file_path)
project_path = os.path.dirname(dir_path)
executable_path = os.path.join(project_path,"bin",f"{c_code_name}.o")
lib_path = os.path.join(dir_path,"c_lib",f"{c_code_name}.so")
lib = ctypes.CDLL(os.path.abspath(lib_path))

# Define argument types and return types
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

class DynamicIntArray:
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


class TestDynamicIntArray(unittest.TestCase):

    def test_append_and_len(self):
        arr = DynamicIntArray()

        self.assertEqual(len(arr), 0)

        idx0 = arr.append(10)
        self.assertEqual(idx0, 0)
        self.assertEqual(len(arr), 1)
        self.assertEqual(arr[0], 10)

        idx1 = arr.append(20)
        self.assertEqual(idx1, 1)
        self.assertEqual(len(arr), 2)
        self.assertEqual(arr[1], 20)

    def test_pop(self):
        arr = DynamicIntArray()

        arr.append(5)
        arr.append(15)
        arr.append(25)

        self.assertEqual(len(arr), 3)

        val = arr.pop()
        self.assertEqual(val, 25)
        self.assertEqual(len(arr), 2)

        val = arr.pop()
        self.assertEqual(val, 15)
        self.assertEqual(len(arr), 1)

        val = arr.pop()
        self.assertEqual(val, 5)
        self.assertEqual(len(arr), 0)

        with self.assertRaises(IndexError):
            arr.pop()  # Popping empty array should raise IndexError

    def test_find_index(self):
        arr = DynamicIntArray()

        arr.append(100)
        arr.append(200)
        arr.append(300)

        idx = arr.find_index(200)
        self.assertEqual(idx, 1)

        idx = arr.find_index(500)
        self.assertEqual(idx, -1)

    def test_str_representation(self):
        arr = DynamicIntArray()

        self.assertEqual(str(arr), "[]")

        arr.append(7)
        arr.append(14)
        arr.append(21)

        self.assertEqual(str(arr), "[7, 14, 21]")

if __name__ == "__main__":
    unittest.main()
