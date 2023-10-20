#ifndef FILE_H
#define FILE_H

#include <stdint.h>
#include <stdio.h>

FILE* open_file(char* path);
uint32_t read_coordinates_file_header(FILE* file);
uint32_t read_distances_file_header(FILE* file);

#endif
