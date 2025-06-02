#ifndef STUDENT_H
#define STUDENT_H

#include <stdbool.h>

typedef struct {
    char* name;
    char* department;
    char* course;
    int year_of_joining;
    int avg_marks;
    int roll_number;
} Student;

/**
 * Creates a new empty Student struct
 * @return: A pointer to a Student struct
 */
Student* new_empty_student();
/**
 * Frees the memory allocated for a Student struct
 * @param student: The Student struct to free
 */
void free_student(Student *student);


/**
 * Creates a Student struct from a line in the CSV file.
 * @param line: The line to create the Student struct from
 * @param delimiter: The delimiter used in the CSV file
 * @param header: The header of the CSV file, used to determine the order of the columns
 * @return: A pointer to a Student struct
 */
Student* create_student_from_csv_line(const char *line, const char *delimiter, const char *header);

/**
 * Creates a Student struct from a line of input from the user
 * @param line: The line to create the Student struct from. 
 * The line must have the format of Student(name, department, course, year_of_joining, avg_marks, roll_number)
 * @return: A pointer to a Student struct
 */
Student* create_student_from_input_line(const char *line);

/**
 * Prints a Student struct
 * @param student: The Student struct to print
 */
void print_student(Student *student);
/**
 * Prints an array of Student structs
 * @param students: The array of Student structs to print
 * @param count: The number of Student structs in the array
 */
void print_students(Student *students, size_t count);
/**
 * Frees the memory allocated for an array of Student structs
 * @param students: The array of Student structs to free
 * @param count: The number of Student structs in the array
 */
void free_students(Student *students, size_t count);


#endif