
#include <stdio.h>

void transpose_matrix(int sizes_0, int sizes_1, int matrix[sizes_0][sizes_1], int t_mat[sizes_1][sizes_0]);
void print_matrix(int sizes_0, int sizes_1, int matrix[sizes_0][sizes_1]);

void transpose_matrix(int sizes_0, int sizes_1, int matrix[sizes_0][sizes_1], int t_mat[sizes_1][sizes_0])
{
    for (int i = 0; i < sizes_0; ++i)
    {
        for (int j = 0; j < sizes_1; ++j)
        {
            t_mat[j][i] = matrix[i][j];
        }
    }
}
void print_matrix(int sizes_0, int sizes_1, int matrix[sizes_0][sizes_1])
{
    for (int i = 0; i < sizes_0; ++i)
    {
        for (int j = 0; j < sizes_1; ++j)
        {
            printf("%d ", matrix[i][j]);
            // check
        }
        printf("\n");
    }
}

int main(void)
{
    int mat1[4][2] = {
        {1, 2},
        {3, 4},
        {5, 6},
        {7, 8}};
    int t_mat1[2][4];
    print_matrix(4, 2, mat1);
    transpose_matrix(4, 2, mat1, t_mat1);
    printf("\n");
    print_matrix(2, 4, t_mat1);
    return 0;
}