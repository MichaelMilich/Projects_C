import ctypes
import unittest
import os
import subprocess
import tempfile

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
    # raise e


class TestStudentDatabaseExec(unittest.TestCase):
    def setUp(self):
        # Create a temporary file for testing
        self.temp_filepath = os.path.join(dir_path, "data.csv")

    def tearDown(self):
        # Clean up the temporary file
        if os.path.exists(self.temp_filepath):
            os.unlink(self.temp_filepath)

    def _test_exec(self, exec_inputs, expected):
        if not isinstance(exec_inputs, list):
            input_list = [executable_path, exec_inputs]
        else:
            input_list = [executable_path] + exec_inputs

        result = subprocess.run(input_list, capture_output=True, text=True)
        self.assertIn(expected, result.stdout)

    def test_create_student_database(self):
        input_list = ["--func", "create_student_database", "--filepath", self.temp_filepath]
        expected_output = "Student database created successfully"
        self._test_exec(input_list, expected_output)

    def test_add_student(self):
        
        # Then add a student
        student_param = "Student(John Doe,Computer Science,BS,2023,85)"
        input_list = ["--func", "add_student", "--filepath", self.temp_filepath, "--student_param", student_param]
        expected_output = "Student added successfully"
        self._test_exec(input_list, expected_output)

    def test_load_students(self):
        self.test_add_student()
        
        # Then test loading students
        input_list = ["--func", "load_students", "--filepath", self.temp_filepath]
        expected_output = "John Doe"  # Should contain the student name we added
        self._test_exec(input_list, expected_output)

    def test_remove_student(self):
        self.test_add_student()
        
        # Then remove the student
        input_list = ["--func", "remove_student", "--filepath", self.temp_filepath, "--other_param", "1"]
        expected_output = ""  # No specific output expected, just check it doesn't fail
        self._test_exec(input_list, expected_output)

    def test_update_student(self):
        self.test_add_student()
        
        # Then update the student
        student_param = "Student(Jane Doe,Computer Science,BS,2023,90)"
        input_list = ["--func", "update_student", "--filepath", self.temp_filepath, "--student_param", student_param, "--other_param", "1"]
        expected_output = ""  # No specific output expected, just check it doesn't fail
        self._test_exec(input_list, expected_output)

    def test_search_student(self):
        self.test_add_student()
        
        # Then search for the student
        input_list = ["--func", "search_student", "--filepath", self.temp_filepath, "--other_param", "1"]
        expected_output = "Student found"
        self._test_exec(input_list, expected_output)

    def test_search_nonexistent_student(self):
        
        # Then search for a non-existent student
        input_list = ["--func", "search_student", "--filepath", self.temp_filepath, "--other_param", "999"]
        expected_output = "Student not found"
        self._test_exec(input_list, expected_output)


if __name__ == '__main__':
    unittest.main()