#include<stdbool.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<limits.h>

#include "headers/aoc11.h"
#include "headers/utils.h"


void increment_all(uint** arr, uint xy){
	for(uint r=0; r<xy; ++r)
		for(uint c=0; c<xy; ++c)
			arr[r][c]++;
}
void flash(uint** arr, bool** flashed, uint r, uint c, uint xy){
	if(!flashed[r][c]){
		flashed[r][c] = true;
		for(int rd=-1; rd<=1; ++rd){
			for(int cd=-1; cd<=1; ++cd){
				if(		r+rd >= 0 && r+rd < xy 
					 && c+cd >= 0 && c+cd < xy 
					 && !(rd == 0 &&  cd == 0)
				  ){
					arr[r+rd][c+cd]++;
					if(arr[r+rd][c+cd] > 9) flash(arr, flashed, r+rd, c+cd, xy);
				}
			}
		}
	}
}
uint reset_flashers(uint** arr, bool** flashed, uint xy){
	uint count = 0;
	for(uint r=0; r<xy; ++r)
		for(uint c=0; c<xy; ++c)
			if( flashed[r][c] ){
				arr[r][c] = 0;
				flashed[r][c] = false;
				count++;
			}
	return count;
}
uint cycle(uint** arr, bool** flashed, uint xy){
	increment_all(arr, xy);
	for(uint r=0; r<xy; ++r)
		for(uint c=0; c<xy; ++c)
			if( arr[r][c] > 9 ) 
				flash(arr, flashed, r, c, xy);
	return reset_flashers(arr, flashed, xy);
}
uint aoc11(const char* filepath){
	uint ret = 0;
	uint xy = get_uniform_line_len(filepath);
	uint** arr = calloc(xy, sizeof(uint*));
	bool** flashed = calloc(xy, sizeof(bool*));
	for(uint i=0; i<xy; ++i){
		arr[i] = calloc(xy, sizeof(uint));
		flashed[i] = calloc(xy, sizeof(bool));
	}
	load_uniform_single_digit_file_to_array_2d_by_structure(filepath, arr);


	for(int i=0; i<100; ++i)
		ret += cycle(arr, flashed, xy);


	for(uint i=0; i<xy; ++i){
		free(arr[i]);
		free(flashed[i]);
	}
	free(arr);
	free(flashed);
	return ret;
}
uint aoc11_2(const char* filepath){
	uint ret = 1;
	uint xy = get_uniform_line_len(filepath);
	uint** arr = calloc(xy, sizeof(uint*));
	bool** flashed = calloc(xy, sizeof(bool*));
	for(uint i=0; i<xy; ++i){
		arr[i] = calloc(xy, sizeof(uint));
		flashed[i] = calloc(xy, sizeof(bool));
	}
	load_uniform_single_digit_file_to_array_2d_by_structure(filepath, arr);

	while( cycle(arr, flashed, xy) != xy * xy ) ret++;

	for(uint i=0; i<xy; ++i){
		free(arr[i]);
		free(flashed[i]);
	}
	free(arr);
	free(flashed);
	return ret;
}













