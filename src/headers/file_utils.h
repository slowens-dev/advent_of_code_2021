#ifndef __FILE_UTILS_H
#define __FILE_UTILS_H

void load_uniform_single_digit_file_to_array_2d_by_structure
	(const char* filepath, unsigned int** arr);
void load_uniform_single_digit_file_to_array_2d_by_index
	(const char* filepath, unsigned int* arr, unsigned int n_cols);

unsigned int get_n_lines(const char* filepath);
long unsigned int get_n_lines_long(const char* filepath);
long long unsigned int get_n_lines_long_long(const char* filepath);

unsigned int get_uniform_line_len(const char* filepath);
long unsigned int get_uniform_line_len_long(const char* filepath);
long long unsigned int get_uniform_line_len_long_long(const char* filepath);

#endif
