/*
Student Database:
Create a structure to specify data on students given as: Roll number, Name, Department, Course, Year of joining. 
Write a program to print these.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "file_utils.h"
#include "student.h"


// Function declarations
void print_usage(const char *program_name);
void process_function(const char *func_name, const char *filepath, const char *student_param, const char *other_param);

bool create_student_database(const char *filepath);
bool add_student(const char *filepath, Student *student);
bool remove_student(const char *filepath, int roll_number);
bool update_student(const char *filepath, int roll_number, Student *student);
bool search_student(const char *filepath, int roll_number);


/**
 * Loads students from a CSV file. uses the header to determine the order of the columns,
 * uses the function to create a Student struct from a line in the CSV file.
 * @param filepath: The path to the CSV file
 * @return: An array of Student pointers
 */
Student** load_students(const char *filepath, size_t *out_count);

int main(int argc, char *argv[]) {
    char *func_name = NULL;
    char *filepath = NULL;
    char *student_param = NULL;
    char *other_param = NULL;

    // Parse command line arguments
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--func") == 0 && i + 1 < argc) {
            func_name = argv[++i];
        } else if (strcmp(argv[i], "--filepath") == 0 && i + 1 < argc) {
            filepath = argv[++i];
        } else if (strcmp(argv[i], "--student_param") == 0 && i + 1 < argc) {
            student_param = argv[++i];
        } else if (strcmp(argv[i], "--other_param") == 0 && i + 1 < argc) {
            other_param = argv[++i];
        }
    }

    // Check if required arguments are provided
    if (func_name == NULL || filepath == NULL) {
        print_usage(argv[0]);
        return 1;
    }

    // Process the function
    process_function(func_name, filepath, student_param, other_param);

    return 0;
}

void print_usage(const char *program_name) {
    printf("Usage: %s --func <function_name> --filepath <file_path> [--student_param <student_parameters>] [--other_param <other_parameters>]\n", program_name);
    printf("Example: %s --func read --filepath data.txt --student_param \"Student(...)\" --other_param \"param3\"\n", program_name);
    printf("Functions:\n");
    printf("  load_students: Load students from a CSV file\n");
    printf("  create_student_database: Create a new student database\n");
    printf("  add_student: Add a student to the database\n");
    printf("  remove_student: Remove a student from the database\n");
    printf("  update_student: Update a student in the database\n");
    printf("  search_student: Search for a student in the database\n");
}

void process_function(const char *func_name, const char *filepath, const char *student_param, const char *other_param) {
    printf("Function: %s\n", func_name);
    printf("Filepath: %s\n", filepath);
    if (student_param != NULL) {
        printf("Student Parameters: %s\n", student_param);
    }
    if (other_param != NULL) {
        printf("Other Parameters: %s\n", other_param);
    }
    size_t count;
    if (strcmp(func_name, "load_students") == 0) {
        Student** students = load_students(filepath, &count);
        print_students(students, count);
        free_students(students, count);
    } else if (strcmp(func_name, "create_student_database") == 0) {
        create_student_database(filepath);
    } else if (strcmp(func_name, "add_student") == 0) {
        Student* student = create_student_from_input_line(student_param);
        if (student == NULL) {
            printf("Error: Failed to create student\n");
            return;
        }
        add_student(filepath, student);
        free_student(student);
    } else if (strcmp(func_name, "remove_student") == 0) {
        remove_student(filepath, atoi(other_param));
    } else if (strcmp(func_name, "update_student") == 0) {
        Student* student = create_student_from_input_line(student_param);
        if (student == NULL) {
            printf("Error: Failed to create student\n");
            return;
        }
        update_student(filepath, atoi(other_param), student);
        free_student(student);
    } else if (strcmp(func_name, "search_student") == 0) {
        search_student(filepath, atoi(other_param));
    }
}

Student** load_students(const char *filepath, size_t *out_count) {
    FILE* file = fopen(filepath, "r");
    if (file == NULL) {
        return NULL;
    }

    // Read header
    char* header = read_full_line(file);
    if (header == NULL) {
        fclose(file);
        return NULL;
    }

    // Remove newline if present
    header[strcspn(header, "\n")] = 0;

    Student** students = NULL;
    size_t count = 0;
    char* line;

    // Read each line and create student
    while ((line = read_full_line(file)) != NULL) {
        // Remove newline if present
        line[strcspn(line, "\n")] = 0;
        
        Student* student = create_student_from_csv_line(line, ",", header);
        if (student != NULL) {
            students = realloc(students, (count + 1) * sizeof(Student*));
            students[count++] = student;
        }
        free(line);  // Free the line after we're done with it
    }

    free(header);    // Free the header
    fclose(file);
    *out_count = count;
    return students;
}

bool create_student_database(const char *filepath) {
    if (file_exists(filepath)) {
        printf("Error: File already exists\n");
        return false;
    }
    FILE* file = open_append_or_create(filepath);
    if (file == NULL) {
        return false;
    }
    fprintf(file, "Roll Number,Name,Department,Course,Year of Joining,Average Marks\n");
    fclose(file);
    printf("Student database created successfully\n");
    return true;
}

bool add_student(const char *filepath, Student *student) {
    FILE* file = open_append_or_create(filepath);
    if (file == NULL) {
        return false;
    }
    if (student->roll_number == -1) {
        size_t count;
        Student** students = load_students(filepath, &count);
        if (students == NULL) {
            return false;
        }
        student->roll_number = count + 1;
        free_students(students, count);
    }
    fprintf(file, "%d,%s,%s,%s,%d,%d\n", student->roll_number, student->name, student->department, student->course, student->year_of_joining, student->avg_marks);
    fclose(file);
    printf("Student added successfully\n");
    return true;
}
/**
 * Removes a student from the database.
 * The student is removed by the roll number.
 * To remove a student, we need to read the database line by line, and remove the line if the roll number matches.
 * we need to open the file in write mode to overwrite the file with the new content.
 * @param filepath: The path to the database file
 * @param roll_number: The roll number of the student to remove
 * @return: True if the student was removed successfully, false otherwise
 */
bool remove_student(const char *filepath, int roll_number) {
    FILE* file = open_append_or_create(filepath);
    if (file == NULL) {
        return false;
    }
    size_t count;
    Student** students = load_students(filepath, &count);
    if (students == NULL) {
        return false;
    }
    fclose(file);

    for (size_t i = 0; i < count; i++) {
        if (students[i]->roll_number == roll_number) {
            free_student(students[i]);
            students[i] = NULL;
        }
    }
    
    FILE* new_file = fopen(filepath, "w");
    if (new_file == NULL) {
        return false;
    }
    fprintf(new_file, "Roll Number,Name,Department,Course,Year of Joining,Average Marks\n");
    for (size_t i = 0; i < count; i++) {
        if (students[i] != NULL) {
            fprintf(new_file, "%d,%s,%s,%s,%d,%d\n", students[i]->roll_number, students[i]->name, students[i]->department, students[i]->course, students[i]->year_of_joining, students[i]->avg_marks);
        }
    }
    fclose(new_file);
    return true;
}

bool update_student(const char *filepath, int roll_number, Student *student){
    FILE* file = open_append_or_create(filepath);
    if (file == NULL) {
        return false;
    }
    size_t count;
    Student** students = load_students(filepath, &count);
    if (students == NULL) {
        return false;
    }
    fclose(file);

    for (size_t i = 0; i < count; i++) {
        if (students[i]->roll_number == roll_number) {
            free_student(students[i]);
            student->roll_number = roll_number;
            students[i] = student;
        }
    }
    
    FILE* new_file = fopen(filepath, "w");
    if (new_file == NULL) {
        return false;
    }
    fprintf(new_file, "Roll Number,Name,Department,Course,Year of Joining,Average Marks\n");
    for (size_t i = 0; i < count; i++) {
        if (students[i] != NULL) {
            fprintf(new_file, "%d,%s,%s,%s,%d,%d\n", students[i]->roll_number, students[i]->name, students[i]->department, students[i]->course, students[i]->year_of_joining, students[i]->avg_marks);
        }
    }
    fclose(new_file);
    return true;
}

bool search_student(const char *filepath, int roll_number){
    FILE* file = open_append_or_create(filepath);
    if (file == NULL) {
        return false;
    }
    size_t count;
    Student** students = load_students(filepath, &count);
    if (students == NULL) {
        return false;
    }
    fclose(file);
    for (size_t i = 0; i < count; i++) {
        if (students[i]->roll_number == roll_number) {
            printf("Student found:\n");
            print_student(students[i]);
            free_students(students, count);
            return true;
        }
    }
    free_students(students, count);
    printf("Student not found\n");
    return false;
}
