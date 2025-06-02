#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <stdio.h>
#include <stdbool.h>

bool file_exists(const char *filename);
FILE *open_append_or_create(const char *filename);
char *read_full_line(FILE *fp);
char **load_lines(const char *filename, size_t *out_count);
/**
 * Frees the memory allocated for the lines array
 * @param lines: The array of lines to free
 * @param count: The number of lines in the array
 */
void free_lines(char **lines, size_t count);

#endif
