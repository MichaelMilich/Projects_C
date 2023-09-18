
#include <stdio.h>
#define MAX_STRING 256
#define LEN(arr) (sizeof(arr) / sizeof(arr[0]))

typedef struct
{
    char name[MAX_STRING];
    int roll_number;
    char department[MAX_STRING];
    char course[MAX_STRING];
    int year;

} Student;

void print_student(Student student)
{
    printf("[name = %s, rool number = %d, department =%s, course = %s, year =%d] \n",
           student.name, student.roll_number, student.department, student.course, student.year);
}

int main(void)
{
    Student students[] = {
        {"Michael", 1, "programing", "high-tech", 1994},
        {"Miki", 2, "material engenerring", "academy", 1995},
        {"Yulia", 3, "programing", "high-tech", 2001}};

    int length = LEN(students);
    printf("length of students = %d \n", length);
    for (int i = 0; i < length; ++i)
    {
        print_student(students[i]);
    }
    return 0;
}