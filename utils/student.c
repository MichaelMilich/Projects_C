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
    
    char *line_saveptr = NULL;
    char *header_saveptr = NULL;
    char* line_token = strtok_r(line_copy, delimiter, &line_saveptr);
    char* header_token = strtok_r(header_copy, delimiter, &header_saveptr);

    while (line_token != NULL && header_token != NULL) {
        if (strcmp(header_token, "Name") == 0) {
            student->name = strdup(line_token);
        } else if (strcmp(header_token, "Department") == 0) {
            student->department = strdup(line_token);
        } else if (strcmp(header_token, "Course") == 0) {
            student->course = strdup(line_token);
        } else if (strcmp(header_token, "Year of Joining") == 0) {
            student->year_of_joining = atoi(line_token);
        } else if (strcmp(header_token, "Average Marks") == 0) {
            student->avg_marks = atoi(line_token);
        } else if (strcmp(header_token, "Roll Number") == 0) {
            student->roll_number = atoi(line_token);
        }

        line_token = strtok_r(NULL, delimiter, &line_saveptr);
        header_token = strtok_r(NULL, delimiter, &header_saveptr);
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
    int year, marks;

    if (sscanf(line, "Student(%[^,], %[^,], %[^,], %d, %d)",
               name, department, course, &year, &marks) == 5) {
        student->name = strdup(name);
        student->department = strdup(department);
        student->course = strdup(course);
        student->year_of_joining = year;
        student->avg_marks = marks;
        student->roll_number = -1;
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
