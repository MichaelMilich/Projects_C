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
void process_function(const char *func_name, const char *filepath, const char *param);

bool create_student_database(const char *filepath);
bool add_student(const char *filepath, Student *student);
bool remove_student(const char *filepath, int roll_number);
bool update_student(const char *filepath, int roll_number, Student *student);
bool search_student(const char *filepath, int roll_number);
bool sort_students(const char *filepath, const char *sort_by);


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
    char *param = NULL;

    // Parse command line arguments
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--func") == 0 && i + 1 < argc) {
            func_name = argv[++i];
        } else if (strcmp(argv[i], "--filepath") == 0 && i + 1 < argc) {
            filepath = argv[++i];
        } else if (strcmp(argv[i], "--param") == 0 && i + 1 < argc) {
            param = argv[++i];
        }
    }

    // Check if required arguments are provided
    if (func_name == NULL || filepath == NULL) {
        print_usage(argv[0]);
        return 1;
    }

    // Process the function
    process_function(func_name, filepath, param);

    return 0;
}

void print_usage(const char *program_name) {
    printf("Usage: %s --func <function_name> --filepath <file_path> [--param <parameters>]\n", program_name);
    printf("Example: %s --func read --filepath data.txt --param \"param1,param2\"\n", program_name);
    printf("Functions:\n");
    printf("  load_students: Load students from a CSV file\n");
    printf("  create_student_database: Create a new student database\n");
    printf("  add_student: Add a student to the database\n");
    // printf("  remove_student: Remove a student from the database\n");
    // printf("  update_student: Update a student in the database\n");
    // printf("  search_student: Search for a student in the database\n");
}

void process_function(const char *func_name, const char *filepath, const char *param) {
    printf("Function: %s\n", func_name);
    printf("Filepath: %s\n", filepath);
    if (param != NULL) {
        printf("Parameters: %s\n", param);
    }
    size_t count;
    if (strcmp(func_name, "load_students") == 0) {
        Student** students = load_students(filepath, &count);
        print_students(students, count);
        free_students(students, count);
    } else if (strcmp(func_name, "create_student_database") == 0) {
        create_student_database(filepath);
    } else if (strcmp(func_name, "add_student") == 0) {
        Student* student = create_student_from_input_line(param);
        if (student == NULL) {
            printf("Error: Failed to create student\n");
            return;
        }
        add_student(filepath, student);
        free_student(student);
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
    fprintf(file, "%d,%s,%s,%s,%d,%d\n", student->roll_number, student->name, student->department, student->course, student->year_of_joining, student->avg_marks);
    fclose(file);
    printf("Student added successfully\n");
    return true;
}