#include "file_utils.h"
#include <stdlib.h>
#include <string.h>

bool file_exists(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        return false;
    }
    fclose(fp);
    return true;
}

FILE *open_append_or_create(const char *filename) {
    return fopen(filename, "a+");
}

char *read_full_line(FILE *fp) {
    size_t capacity = 1024;
    size_t len = 0;
    char buffer[1024];
    char *line = malloc(capacity);
    if (!line) return NULL;

    while (fgets(buffer, sizeof(buffer), fp)) {
        size_t chunk_len = strlen(buffer);
        int ends_with_newline = (chunk_len > 0 && buffer[chunk_len - 1] == '\n');

        // Grow line buffer if needed
        if (len + chunk_len + 1 > capacity) {
            capacity = (len + chunk_len + 1) * 2;
            char *new_line = realloc(line, capacity);
            if (!new_line) {
                free(line);
                return NULL;
            }
            line = new_line;
        }

        memcpy(line + len, buffer, chunk_len);
        len += chunk_len;
        line[len] = '\0';  // Ensure null termination

        if (ends_with_newline)
            break;
    }

    if (len == 0 && feof(fp)) {
        free(line);
        return NULL;
    }

    return line;
}


char **load_lines(const char *filename, size_t *out_count) {
    *out_count = 0;
    size_t lines_capacity = 1024;
    char **lines = malloc(lines_capacity * sizeof(char *));
    if (!lines) return NULL;

    FILE *fp = fopen(filename, "r");
    if (!fp) {
        free(lines);
        return NULL;
    }

    char *line;
    while ((line = read_full_line(fp))) {
        if (*out_count >= lines_capacity) {
            lines_capacity *= 2;
            char **new_lines = realloc(lines, lines_capacity * sizeof(char *));
            if (!new_lines) {
                // Cleanup
                for (size_t i = 0; i < *out_count; ++i) free(lines[i]);
                free(lines);
                free(line);
                fclose(fp);
                return NULL;
            }
            lines = new_lines;
        }
        lines[(*out_count)++] = line;
    }

    fclose(fp);
    return lines;
}

/**
 * Frees the memory allocated for the lines array
 * @param lines: The array of lines to free
 * @param count: The number of lines in the array
 */
void free_lines(char **lines, size_t count) {
    for (size_t i = 0; i < count; i++) {
        free(lines[i]);
    }
    free(lines);
}