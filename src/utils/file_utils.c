#include<stdlib.h>
#include<stdio.h>

#include "../headers/file_utils.h"
#include "../headers/defined_types.h"

void load_uniform_single_digit_file_to_array_2d_by_structure(const char* filepath, uint** arr){
	FILE* fp = fopen(filepath, "r");
	int row=0, col=0;
	for(char c = fgetc(fp); c != EOF; c = fgetc(fp)){
		if( c == '\n' ){
			row++;
			col = 0;
		}
		else
			arr[row][col++] = c - '0';
	}
	fclose(fp);
}
void load_uniform_single_digit_file_to_array_2d_by_index(const char* filepath, uint* arr){
	FILE* fp = fopen(filepath, "r");
	uint i = 0;
	for(char c=fgetc(fp); c != EOF; c=fgetc(fp)){
		if( c != '\n' )
			arr[i++] = c - '0';
	}
	fclose(fp);
}
uint get_n_lines(const char* filepath){
	uint ret = 0;
	FILE* fp = fopen(filepath, "r");
	for(char c = fgetc(fp); c != EOF; c = fgetc(fp))
		if ( c == '\n' ) ret++;
	fclose(fp);
	return ret;
}
luint get_n_lines_long(const char* filepath){
	luint ret = 0;
	FILE* fp = fopen(filepath, "r");
	for(char c = fgetc(fp); c != EOF; c = fgetc(fp))
		if ( c == '\n' ) ret++;
	fclose(fp);
	return ret;
}
lluint get_n_lines_long_long(const char* filepath){
	lluint ret = 0;
	FILE* fp = fopen(filepath, "r");
	for(char c = fgetc(fp); c != EOF; c = fgetc(fp))
		if ( c == '\n' ) ret++;
	fclose(fp);
	return ret;
}

uint get_uniform_line_len(const char* filepath){
	uint ret = 0;
	FILE* fp = fopen(filepath, "r");
	for(char c = fgetc(fp); c != '\n'; c = fgetc(fp))
		ret++;
	fclose(fp);
	return ret;
}
luint get_uniform_line_len_long(const char* filepath){
	luint ret = 0;
	FILE* fp = fopen(filepath, "r");
	for(char c = fgetc(fp); c != '\n'; c = fgetc(fp))
		ret++;
	fclose(fp);
	return ret;
}
lluint get_uniform_line_len_long_long(const char* filepath){
	lluint ret = 0;
	FILE* fp = fopen(filepath, "r");
	for(char c = fgetc(fp); c != '\n'; c = fgetc(fp))
		ret++;
	fclose(fp);
	return ret;
}
