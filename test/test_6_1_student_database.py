import ctypes
import unittest
import os
import subprocess
import tempfile
import csv
# Setup paths
script_path = os.path.abspath(__file__)
script_name = os.path.basename(script_path)
base_name = os.path.splitext(script_name)[0]  
c_code_name = base_name.removeprefix("test_")

file_path = os.path.realpath(__file__)
dir_path = os.path.dirname(file_path)
project_path = os.path.dirname(dir_path)
executable_path = os.path.join(project_path, "bin", f"{c_code_name}")
lib_path = os.path.join(dir_path, "c_lib", f"{c_code_name}.so")

# Load the shared library
try:
    lib = ctypes.CDLL(lib_path)
    print("[✓] Successfully loaded shared library.")
except OSError as e:
    print("[✗] Failed to load shared library.")
    # raise e

def call_exec(exec_inputs):
    if not isinstance(exec_inputs, list):
        input_list = [executable_path, exec_inputs]
    else:
        input_list = [executable_path] + exec_inputs

    result = subprocess.run(input_list, capture_output=True, text=True)
    return result.stdout
    

def delete_file(filepath):
    if os.path.exists(filepath):
        os.unlink(filepath)

def create_database(filepath):
    call_exec(["--func", "create_student_database", "--filepath", filepath])

def add_student(filepath, student_param):
    call_exec(["--func", "add_student", "--filepath", filepath, "--student_param", student_param])

def load_students(filepath):
    call_exec(["--func", "load_students", "--filepath", filepath])

def read_csv(filepath):
    with open(filepath, newline='') as f:
        reader = csv.DictReader(f)
        return list(reader)

class TestStudentDatabaseExec(unittest.TestCase):
    def setUp(self):
        self.temp_filepath = os.path.join(tempfile.gettempdir(), "test_student_db.csv")
        if os.path.exists(self.temp_filepath):
            os.unlink(self.temp_filepath)

    def tearDown(self):
        if os.path.exists(self.temp_filepath):
            os.unlink(self.temp_filepath)

    def read_csv(self):
        with open(self.temp_filepath, newline='') as f:
            reader = csv.DictReader(f)
            return list(reader)

    def test_add_student_with_missing_fields(self):
        call_exec(["--func", "create_student_database", "--filepath", self.temp_filepath])
        result = call_exec([
            "--func", "add_student",
            "--filepath", self.temp_filepath,
            "--student_param", "Student(John Doe,Computer Science,BS,2023)"  # missing avg_marks
        ])
        self.assertIn("Error", result)

    def test_add_and_check_csv_contents(self):
        call_exec(["--func", "create_student_database", "--filepath", self.temp_filepath])
        call_exec(["--func", "add_student", "--filepath", self.temp_filepath, "--student_param", "Student(John Doe,CS,BS,2023,85)"])
        records = self.read_csv()
        self.assertEqual(len(records), 1)
        self.assertEqual(records[0]['Name'], "John Doe")

    def test_remove_student_and_check_csv(self):
        call_exec(["--func", "create_student_database", "--filepath", self.temp_filepath])
        call_exec(["--func", "add_student", "--filepath", self.temp_filepath, "--student_param", "Student(John Doe,CS,BS,2023,85)"])
        call_exec(["--func", "remove_student", "--filepath", self.temp_filepath, "--other_param", "1"])
        records = self.read_csv()
        self.assertEqual(len(records), 0)

    def test_update_student_and_check_csv(self):
        call_exec(["--func", "create_student_database", "--filepath", self.temp_filepath])
        call_exec(["--func", "add_student", "--filepath", self.temp_filepath, "--student_param", "Student(John Doe,CS,BS,2023,85)"])
        call_exec(["--func", "update_student", "--filepath", self.temp_filepath, "--student_param", "Student(Jane Doe,EE,MS,2022,90)", "--other_param", "1"])
        records = self.read_csv()
        self.assertEqual(records[0]['Name'], "Jane Doe")
        self.assertEqual(records[0]['Department'], "EE")
        self.assertEqual(records[0]['Course'], "MS")
        self.assertEqual(records[0]['Year of Joining'], "2022")
        self.assertEqual(records[0]['Average Marks'], "90")

    def test_search_student_invalid_roll(self):
        call_exec(["--func", "create_student_database", "--filepath", self.temp_filepath])
        result = call_exec(["--func", "search_student", "--filepath", self.temp_filepath, "--other_param", "-1"])
        self.assertIn("Student not found", result)


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
        create_database(self.temp_filepath)
        # Then add a student
        student_param = "Student(John Doe,Computer Science,BS,2023,85)"
        input_list = ["--func", "add_student", "--filepath", self.temp_filepath, "--student_param", student_param]
        expected_output = "Student added successfully"
        self._test_exec(input_list, expected_output)

    def test_load_students(self):
        create_database(self.temp_filepath)
        self.test_add_student()
        
        # Then test loading students
        input_list = ["--func", "load_students", "--filepath", self.temp_filepath]
        expected_output = "John Doe"  # Should contain the student name we added
        self._test_exec(input_list, expected_output)

    def test_remove_student(self):
        create_database(self.temp_filepath)
        self.test_add_student()
        
        # Then remove the student
        input_list = ["--func", "remove_student", "--filepath", self.temp_filepath, "--other_param", "1"]
        expected_output = ""  # No specific output expected, just check it doesn't fail
        self._test_exec(input_list, expected_output)

    def test_update_student(self):
        create_database(self.temp_filepath)
        self.test_add_student()
        
        # Then update the student
        student_param = "Student(Jane Doe,Computer Science,BS,2023,90)"
        input_list = ["--func", "update_student", "--filepath", self.temp_filepath, "--student_param", student_param, "--other_param", "1"]
        expected_output = ""  # No specific output expected, just check it doesn't fail
        self._test_exec(input_list, expected_output)

    def test_search_student(self):
        create_database(self.temp_filepath)
        self.test_add_student()
        
        # Then search for the student
        input_list = ["--func", "search_student", "--filepath", self.temp_filepath, "--other_param", "1"]
        expected_output = "Student found"
        self._test_exec(input_list, expected_output)

    def test_search_nonexistent_student(self):
        create_database(self.temp_filepath)
        # Then search for a non-existent student
        input_list = ["--func", "search_student", "--filepath", self.temp_filepath, "--other_param", "999"]
        expected_output = "Student not found"
        self._test_exec(input_list, expected_output)

            # ----------- CREATE -------------
    def test_create_database_success(self):
        out = call_exec(["--func", "create_student_database", "--filepath", self.temp_filepath])
        self.assertTrue(os.path.exists(self.temp_filepath))
        with open(self.temp_filepath, "r") as f:
            header = f.readline().strip()
        self.assertEqual(header, "Roll Number,Name,Department,Course,Year of Joining,Average Marks")

    def test_create_existing_file(self):
        self.test_create_database_success()
        out = call_exec(["--func", "create_student_database", "--filepath", self.temp_filepath])
        self.assertIn("Error", out)

    # ----------- ADD -------------
    def test_add_valid_student(self):
        self.test_create_database_success()
        out = call_exec(["--func", "add_student", "--filepath", self.temp_filepath,
                         "--student_param", "Student(John Doe,CS,BS,2023,85)"])
        self.assertIn("Student added successfully", out)
        rows = read_csv(self.temp_filepath)
        self.assertEqual(len(rows), 1)

    def test_add_invalid_student_format(self):
        self.test_create_database_success()
        out = call_exec(["--func", "add_student", "--filepath", self.temp_filepath,
                         "--student_param", "Student(OnlyName)"])
        self.assertIn("Error", out)

    def test_add_student_auto_roll(self):
        self.test_add_valid_student()
        out = call_exec(["--func", "add_student", "--filepath", self.temp_filepath,
                         "--student_param", "Student(Jane Smith,CS,BS,2023,92)"])
        rows = read_csv(self.temp_filepath)
        self.assertEqual(rows[-1]["Roll Number"], "2")

    # ----------- SEARCH -------------
    def test_search_existing_student(self):
        self.test_add_valid_student()
        out = call_exec(["--func", "search_student", "--filepath", self.temp_filepath, "--other_param", "1"])
        self.assertIn("Student found", out)

    def test_search_non_existing_student(self):
        self.test_add_valid_student()
        out = call_exec(["--func", "search_student", "--filepath", self.temp_filepath, "--other_param", "999"])
        self.assertIn("Student not found", out)

    def test_search_invalid_roll(self):
        self.test_add_valid_student()
        out = call_exec(["--func", "search_student", "--filepath", self.temp_filepath, "--other_param", "-1"])
        self.assertIn("Student not found", out)

    # ----------- UPDATE -------------
    def test_update_existing_student(self):
        self.test_add_valid_student()
        out = call_exec(["--func", "update_student", "--filepath", self.temp_filepath,
                         "--student_param", "Student(Jane Updated,EE,MS,2022,90)", "--other_param", "1"])
        rows = read_csv(self.temp_filepath)
        self.assertEqual(rows[0]["Name"], "Jane Updated")

    def test_update_non_existing_student(self):
        self.test_add_valid_student()
        out = call_exec(["--func", "update_student", "--filepath", self.temp_filepath,
                         "--student_param", "Student(Jane Updated,EE,MS,2022,90)", "--other_param", "999"])
        rows = read_csv(self.temp_filepath)
        self.assertEqual(rows[0]["Name"], "John Doe")  # Should remain unchanged

    # ----------- REMOVE -------------
    def test_remove_existing_student(self):
        self.test_add_valid_student()
        out = call_exec(["--func", "remove_student", "--filepath", self.temp_filepath, "--other_param", "1"])
        rows = read_csv(self.temp_filepath)
        self.assertEqual(len(rows), 0)

    def test_remove_non_existing_student(self):
        self.test_add_valid_student()
        out = call_exec(["--func", "remove_student", "--filepath", self.temp_filepath, "--other_param", "999"])
        rows = read_csv(self.temp_filepath)
        self.assertEqual(len(rows), 1)  # Should remain

    # ----------- INTEGRATION FLOW -------------
    def test_full_flow(self):
        call_exec(["--func", "create_student_database", "--filepath", self.temp_filepath])
        call_exec(["--func", "add_student", "--filepath", self.temp_filepath,
                   "--student_param", "Student(Flow User,Data,BA,2020,77)"])
        out1 = call_exec(["--func", "search_student", "--filepath", self.temp_filepath, "--other_param", "1"])
        self.assertIn("Student found", out1)

        call_exec(["--func", "update_student", "--filepath", self.temp_filepath,
                   "--student_param", "Student(Flow Updated,Science,MA,2021,88)", "--other_param", "1"])
        rows = read_csv(self.temp_filepath)
        self.assertEqual(rows[0]["Name"], "Flow Updated")

        call_exec(["--func", "remove_student", "--filepath", self.temp_filepath, "--other_param", "1"])
        out2 = call_exec(["--func", "search_student", "--filepath", self.temp_filepath, "--other_param", "1"])
        self.assertIn("Student not found", out2)



if __name__ == '__main__':
    unittest.main()