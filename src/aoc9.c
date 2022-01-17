#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<limits.h>

#include "headers/utils.h"
#include "headers/aoc9.h"


void load_heightmap(const char* filepath, int** heightmap){
	FILE* fp = fopen(filepath, "r");
	int row_i = 0, col_i = 0;
	for(char c=fgetc(fp); c!=EOF; c=fgetc(fp)){
		switch( c ){
			case '\n': row_i++;
					   col_i = 0;
					   break;
			default:
					heightmap[row_i][col_i++] = (int)( c - '0' );
		}
	}
	fclose(fp);
}
bool is_lowpoint(int** heightmap, int row, int col, int n_rows, int n_cols){
	return  !( ( (row-1) >= 0 && heightmap[row-1][col] <= heightmap[row][col] )
			|| ( (row+1) < n_rows && heightmap[row+1][col] <= heightmap[row][col] )
			|| ( (col-1) >= 0 && heightmap[row][col-1] <= heightmap[row][col] )
			|| ( (col+1) < n_cols && heightmap[row][col+1] <= heightmap[row][col] )
			);
}
int get_basin_size(int** heightmap, bool** graph, int row, int col, int n_rows, int n_cols, int refer){
	int ret = 0;
	if ( !( row < 0 || col < 0 || row >= n_rows || col >= n_cols || heightmap[row][col] == 9 || graph[row][col] ) ){
		if ( heightmap[row][col] > refer ){
			graph[row][col] = true;
			ret += get_basin_size(heightmap, graph, row-1, col, n_rows, n_cols, heightmap[row][col]);
			ret += get_basin_size(heightmap, graph, row+1, col, n_rows, n_cols, heightmap[row][col]);
			ret += get_basin_size(heightmap, graph, row, col-1, n_rows, n_cols, heightmap[row][col]);
			ret += get_basin_size(heightmap, graph, row, col+1, n_rows, n_cols, heightmap[row][col]);
			ret += 1;
			return ret;
		}
	}
	return ret;
}
lluint aoc9(const char* filepath){
	int sum = 0;
	uint n_rows = get_n_lines(filepath);
	uint n_cols = get_uniform_line_len(filepath);
	int** heightmap = (int**) calloc(n_rows, sizeof(int*));
	for(uint r=0; r<n_rows; ++r) heightmap[r] = (int*) calloc(n_cols, sizeof(int));
	load_heightmap(filepath, heightmap);
	for(uint r=0; r<n_rows; ++r){
		for(uint c=0; c<n_cols; ++c){
			if( is_lowpoint(heightmap, r, c, n_rows, n_cols ) ){
				sum += heightmap[r][c] + 1;
			}
		}
	}

	for(uint r=0; r<n_rows; ++r)
		free(heightmap[r]);
	free(heightmap);
	return sum;
}
lluint aoc9_2(const char* filepath){
	uint n_rows = get_n_lines(filepath);
	uint n_cols = get_uniform_line_len(filepath);
	int** heightmap = (int**) calloc(n_rows, sizeof(int*));
	bool** graph = (bool**) calloc(n_rows, sizeof(bool*));
	for(uint r=0; r<n_rows; ++r){
		heightmap[r] = (int*) calloc(n_cols, sizeof(int));
		graph[r] = (bool*) calloc(n_cols, sizeof(bool));
		memset(graph[r], false, n_cols);
	}
	load_heightmap(filepath, heightmap);
	int big3[3] = {0};
	for(uint r=0; r<n_rows; ++r){
		for(uint c=0; c<n_cols; ++c){
			if (is_lowpoint(heightmap, r, c, n_rows, n_cols)){
				int basin_size = get_basin_size(heightmap, graph, r, c, n_rows, n_cols, -1);
				if(basin_size > big3[0]){
					big3[2] = big3[1];
					big3[1] = big3[0];
					big3[0] = basin_size;
				}else if(basin_size > big3[1]){
					big3[2] = big3[1];
					big3[1] = basin_size;
				}else if(basin_size > big3[2]){
					big3[2] = basin_size;
				}
			}
		}
	}
	for(uint r=0; r<n_rows; ++r){
		free(heightmap[r]);
		free(graph[r]);
	}
	free(heightmap);
	free(graph);
	return big3[0] * big3[1] * big3[2];
}
