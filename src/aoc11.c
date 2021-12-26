#include<stdbool.h>
#include<stdlib.h>
#include<stdio.h>
#include<limits.h>

#include "headers/aoc11.h"
#include "headers/file_utils.h"


uint aoc11(const char* filepath){
	uint size = get_uniform_line_len(filepath);
	uint n_rows = get_n_lines(filepath);
	uint n_cols = get_uniform_line_len(filepath);
	uint* arr = calloc(n_rows*n_cols, sizeof(uint));
	bool* flashed = calloc(n_rows * n_cols, sizeof(bool));
	load_uniform_single_digit_file_to_array_2d_by_index(filepath, arr, n_cols);

	for(uint r=0; r<n_rows; ++r){
		for(uint c=0; c<n_cols; ++c)
			printf("%u ", arr[r*n_cols+c]);
		printf("\n");
	}
	printf("\n================\n");

	free(arr); 
	free(flashed);
	return 0;
}
uint aoc11_2(const char* filepath){
	return 0;
}
