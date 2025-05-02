import ctypes
import unittest
import os
import subprocess

# Setup paths
script_path = os.path.abspath(__file__)
script_name = os.path.basename(script_path)
base_name = os.path.splitext(script_name)[0]  
c_code_name = base_name.removeprefix("test_")

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


class TestSortFunctionExec(unittest.TestCase):
    def _test_exec(self, exec_inputs, expected):
        if not isinstance(exec_inputs, list):
            input_list = [executable_path, exec_inputs]
        else:
            input_list = [executable_path] + exec_inputs

        result = subprocess.run(input_list, capture_output=True, text=True)
        self.assertIn(expected, result.stdout)

    def test_empty_array_quick_sort_exec(self):
        sort_function = "quick_sort"
        array = "[ ]"
        input_list = [sort_function, array]
        expected_output = f"[ ]"
        self._test_exec(input_list, expected_output)

    def test_single_element_quick_sort_exec(self):
        sort_function = "quick_sort"
        array = "[42]"
        input_list = [sort_function, array]
        expected_output = f"[ 42 ]"
        self._test_exec(input_list, expected_output)

    def test_basic_array_quick_sort_exec(self):
        sort_function = "quick_sort"
        array = "[1,3,2,4,5]"
        input_list = [sort_function, array]
        expected_output = f"[ 1, 2, 3, 4, 5 ]"
        self._test_exec(input_list, expected_output)

    def test_reverse_array_quick_sort_exec(self):
        sort_function = "quick_sort"
        array = "[5,4,3,2,1]"
        input_list = [sort_function, array]
        expected_output = f"[ 1, 2, 3, 4, 5 ]"
        self._test_exec(input_list, expected_output)

    def test_duplicate_elements_quick_sort_exec(self):
        sort_function = "quick_sort"
        array = "[3,1,4,1,5,9,2,6,5,3,5]"
        input_list = [sort_function, array]
        expected_output = f"[ 1, 1, 2, 3, 3, 4, 5, 5, 5, 6, 9 ]"
        self._test_exec(input_list, expected_output)

    def test_empty_array_merge_sort_exec(self):
        sort_function = "merge_sort"
        array = "[ ]"
        input_list = [sort_function, array]
        expected_output = f"[ ]"
        self._test_exec(input_list, expected_output)

    def test_single_element_merge_sort_exec(self):
        sort_function = "merge_sort"
        array = "[42]"
        input_list = [sort_function, array]
        expected_output = f"[ 42 ]"
        self._test_exec(input_list, expected_output)

    def test_basic_array_merge_sort_exec(self):
        sort_function = "merge_sort"
        array = "[1,3,2,4,5]"
        input_list = [sort_function, array]
        expected_output = f"[ 1, 2, 3, 4, 5 ]"
        self._test_exec(input_list, expected_output)

    def test_reverse_array_merge_sort_exec(self):
        sort_function = "merge_sort"
        array = "[5,4,3,2,1]"
        input_list = [sort_function, array]
        expected_output = f"[ 1, 2, 3, 4, 5 ]"
        self._test_exec(input_list, expected_output)

    def test_duplicate_elements_merge_sort_exec(self):
        sort_function = "merge_sort"
        array = "[3,1,4,1,5,9,2,6,5,3,5]"
        input_list = [sort_function, array]
        expected_output = f"[ 1, 1, 2, 3, 3, 4, 5, 5, 5, 6, 9 ]"
        self._test_exec(input_list, expected_output)

    def test_empty_array_naive_sort_exec(self):
        sort_function = "naive_sort"
        array = "[ ]"
        input_list = [sort_function, array]
        expected_output = f"[ ]"
        self._test_exec(input_list, expected_output)

    def test_single_element_naive_sort_exec(self):
        sort_function = "naive_sort"
        array = "[42]"
        input_list = [sort_function, array]
        expected_output = f"[ 42 ]"
        self._test_exec(input_list, expected_output)

    def test_basic_array_naive_sort_exec(self):
        sort_function = "naive_sort"
        array = "[1,3,2,4,5]"
        input_list = [sort_function, array]
        expected_output = f"[ 1, 2, 3, 4, 5 ]"
        self._test_exec(input_list, expected_output)

    def test_reverse_array_naive_sort_exec(self):
        sort_function = "naive_sort"
        array = "[5,4,3,2,1]"
        input_list = [sort_function, array]
        expected_output = f"[ 1, 2, 3, 4, 5 ]"
        self._test_exec(input_list, expected_output)

    def test_duplicate_elements_naive_sort_exec(self):
        sort_function = "naive_sort"
        array = "[3,1,4,1,5,9,2,6,5,3,5]"
        input_list = [sort_function, array]
        expected_output = f"[ 1, 1, 2, 3, 3, 4, 5, 5, 5, 6, 9 ]"
        self._test_exec(input_list, expected_output)

if __name__ == '__main__':
    unittest.main()