
#include <stdio.h>
#include <math.h>

#define MAX_STRING 256
#define LEN(arr) (sizeof(arr) / sizeof(arr[0]))

typedef struct ComplexNumber ComplexNumber;

void add(ComplexNumber *self, ComplexNumber *n_2);
void multiply(ComplexNumber *self, ComplexNumber *z_2);
void subtract(ComplexNumber *self, ComplexNumber *n_2);
int divide(ComplexNumber *self, ComplexNumber *z_2);
float get_R(ComplexNumber *self);

struct ComplexNumber
{
    float real;
    float imaginary;
    float (*get_R_func)(ComplexNumber *);
    void (*add_func)(ComplexNumber *, ComplexNumber *);
    void (*subtract_func)(ComplexNumber *, ComplexNumber *);
    void (*multiply_func)(ComplexNumber *, ComplexNumber *);
    int (*divide_func)(ComplexNumber *, ComplexNumber *);
};

void add(ComplexNumber *self, ComplexNumber *n_2)
{
    self->imaginary += n_2->imaginary;
    self->real += n_2->real;
}

void subtract(ComplexNumber *self, ComplexNumber *n_2)
{
    self->imaginary -= n_2->imaginary;
    self->real -= n_2->real;
}

void multiply(ComplexNumber *self, ComplexNumber *z_2)
{
    float imagin_temp = self->imaginary * z_2->real + z_2->imaginary * self->real;
    float real_temp = self->real * z_2->real - self->imaginary * z_2->imaginary;
    self->imaginary = imagin_temp;
    self->real = real_temp;
}

float get_R(ComplexNumber *self)
{
    double imagein_2 = (double)(self->imaginary);
    double real_2 = (double)(self->real);
    return (float)(pow(imagein_2, 2.0) + pow(real_2, 2.0));
}

int divide(ComplexNumber *self, ComplexNumber *z_2)
{
    if (get_R(z_2) == 0.0)
    {
        return -1;
    }
    float imagin_temp = (self->real * z_2->imaginary - self->imaginary * z_2->real) / get_R(z_2);
    float real_temp = (self->real * z_2->real + self->imaginary * z_2->imaginary) / get_R(z_2);
    self->real = real_temp;
    self->imaginary = imagin_temp;
    return 0;
}

void print_number(ComplexNumber *self)
{
    printf("[(%f) +(%f)*i] \n", self->real, self->imaginary);
}

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

    ComplexNumber numbers[] = {{1, 1}, {2, 2}};
    length = 2;
    for (int i = 0; i < length; ++i)
    {
        numbers[i].add_func = add;
        numbers[i].subtract_func = subtract;
        numbers[i].multiply_func = multiply;
        numbers[i].get_R_func = get_R;
        numbers[i].divide_func = divide;
        print_number(&numbers[i]);
    }
    numbers[0].add_func(&numbers[0], &numbers[1]);
    printf(" added 2+2i \n ");
    print_number(&numbers[0]);
    numbers[0].subtract_func(&numbers[0], &numbers[1]);
    printf(" subtracted 2+2i \n ");
    print_number(&numbers[0]);
    numbers[0].multiply_func(&numbers[0], &numbers[1]);
    printf(" multiplied 2+2i \n ");
    print_number(&numbers[0]);
    numbers[0].divide_func(&numbers[0], &numbers[1]);
    printf(" diveded by  2+2i \n ");
    print_number(&numbers[0]);
    numbers[0].divide_func(&numbers[0], &numbers[1]);
    printf(" diveded again by  2+2i \n ");
    print_number(&numbers[0]);
    float r = numbers[0].get_R_func(&numbers[0]);
    printf(" R^2 of result = %f \n ", r);

    return 0;
}