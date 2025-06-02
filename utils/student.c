#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

Student* new_empty_student() {
    Student* student = (Student*)malloc(sizeof(Student));
    if (student == NULL) {
        return NULL;
    }
    
    student->name = NULL;
    student->department = NULL;
    student->course = NULL;
    student->year_of_joining = 0;
    student->avg_marks = 0;
    student->roll_number = 0;
    
    return student;
}

void free_student(Student *student) {
    if (student == NULL) {
        return;
    }
    
    free(student->name);
    free(student->department);
    free(student->course);
    free(student);
}


Student* create_student_from_csv_line(const char *line, const char *delimiter, const char *header) {
    Student* student = new_empty_student();
    if (student == NULL) {
        return NULL;
    }

    char* line_copy = strdup(line);
    char* header_copy = strdup(header);
    char* line_token = strtok(line_copy, delimiter);
    char* header_token = strtok(header_copy, delimiter);

    while (line_token != NULL && header_token != NULL) {
        if (strcmp(header_token, "name") == 0) {
            student->name = strdup(line_token);
        } else if (strcmp(header_token, "department") == 0) {
            student->department = strdup(line_token);
        } else if (strcmp(header_token, "course") == 0) {
            student->course = strdup(line_token);
        } else if (strcmp(header_token, "year_of_joining") == 0) {
            student->year_of_joining = atoi(line_token);
        } else if (strcmp(header_token, "avg_marks") == 0) {
            student->avg_marks = atoi(line_token);
        } else if (strcmp(header_token, "roll_number") == 0) {
            student->roll_number = atoi(line_token);
        }

        line_token = strtok(NULL, delimiter);
        header_token = strtok(NULL, delimiter);
    }

    free(line_copy);
    free(header_copy);
    return student;
}

Student* create_student_from_input_line(const char *line) {
    Student* student = new_empty_student();
    if (student == NULL) {
        return NULL;
    }

    char name[256], department[256], course[256];
    int year, marks, roll;

    if (sscanf(line, "Student(%[^,], %[^,], %[^,], %d, %d, %d)",
               name, department, course, &year, &marks, &roll) == 6) {
        student->name = strdup(name);
        student->department = strdup(department);
        student->course = strdup(course);
        student->year_of_joining = year;
        student->avg_marks = marks;
        student->roll_number = roll;
        return student;
    }

    free_student(student);
    return NULL;
}

void print_student(Student *student) {
    if (student == NULL) {
        return;
    }

    printf(
        "Student(name: %s, department: %s, course: %s, year_of_joining: %d, avg_marks: %d, roll_number: %d)\n",
        student->name,
        student->department,
        student->course,
        student->year_of_joining, 
        student->avg_marks,
        student->roll_number
    );
}

void print_students(Student **students, size_t count) {
    if (students == NULL) {
        return;
    }

    for (size_t i = 0; i < count; i++) {
        print_student(students[i]);
    }
}

void free_students(Student **students, size_t count) {
    if (students == NULL) {
        return;
    }

    for (size_t i = 0; i < count; i++) {
        free_student(students[i]);
    }
    free(students);
}
