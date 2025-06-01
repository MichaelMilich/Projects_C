#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fp = fopen("created_file.txt", "w");  // Will create or overwrite
    if (fp == NULL) {
        perror("Error creating file");
        return 1;
    }

    fprintf(fp, "This file has been created and written by C!\n");
    fprintf(fp, "Another line here.\n");

    fclose(fp);
    printf("File created successfully!\n");

    return 0;
}