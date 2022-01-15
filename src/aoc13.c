#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

#include "headers/aoc13.h"
#include "headers/utils.h"

static void get_dimensions (const char* filepath, uint* x_dim, uint* y_dim){
	FILE* fp = fopen(filepath, "r");
	char *linebuf = NULL;
	size_t linebuf_sz;
	int line_len = 0;
	uint swap = 0;
	*x_dim = 0, *y_dim = 0;
	for( line_len = getline( &linebuf, &linebuf_sz, fp); line_len >= 2; line_len = getline( &linebuf, &linebuf_sz, fp)){
		swap = atoi( strtok(linebuf, ",") );
		if (swap > *x_dim) *x_dim = swap;
		swap = atoi( strtok(NULL, ",") );
		if (swap > *y_dim) *y_dim = swap;
	}
	*x_dim += 1;
	*y_dim += 1;
	fclose(fp);
}
static void init_points (const char* filepath, bool** arr,  uint* x_dim, uint* y_dim){
	FILE* fp = fopen(filepath, "r");
	char *linebuf = NULL;
	size_t linebuf_sz;
	int line_len = 0;
	int x,y;
	for( line_len = getline( &linebuf, &linebuf_sz, fp); line_len >= 2; line_len = getline( &linebuf, &linebuf_sz, fp)){
		x = atoi( strtok(linebuf, ",") );
		y = atoi( strtok(NULL, ",") );
		arr[y][x] = true;
	}
	fclose(fp);
}
static void foldx(bool** arr, uint fold, uint* x_dim, uint* y_dim){
	printf("X %d\n", fold);
	for(uint y=0; y<*y_dim; ++y){
		for(uint x=fold+1, fold_x; x<*x_dim; ++x){
			fold_x = fold - (x-fold);
			if( arr[y][x] )
				arr[y][fold_x] = true;
		}
	}
	*x_dim = fold;
}
static void foldy(bool** arr, uint fold, uint* x_dim, uint* y_dim){
	printf("Y %d\n", fold);
	for(uint y=fold+1, fold_y; y<*y_dim; ++y){
		fold_y = fold - (y - fold);
		for(uint x=0; x<*x_dim; ++x){
			if ( arr[y][x] )
				arr[fold_y][x] = true;
		}
	}
	*y_dim = fold;
}
static void do_n_folds (const char* filepath, uint n, bool** arr,  uint x_dim, uint y_dim){
	FILE* fp = fopen(filepath, "r");
	char *linebuf = NULL;
	size_t linebuf_sz;
	int line_len = 0;
	for( line_len = getline( &linebuf, &linebuf_sz, fp); line_len >= 2; line_len = getline( &linebuf, &linebuf_sz, fp));
	for( line_len = getline( &linebuf, &linebuf_sz, fp); line_len >= 0 && n-- > 0; line_len = getline( &linebuf, &linebuf_sz, fp)){
		switch( linebuf[11] ){
			case 'y':
				foldy(arr, atoi(linebuf+13), &x_dim, &y_dim);
				break;
			case 'x':
				foldx(arr, atoi(linebuf+13), &x_dim, &y_dim);
				break;
		}
	}
	fclose(fp);
}
static void do_folds (const char* filepath, bool** arr,  uint* x_dim, uint* y_dim){
	FILE* fp = fopen(filepath, "r");
	char *linebuf = NULL;
	size_t linebuf_sz;
	int line_len = 0;
	for( line_len = getline( &linebuf, &linebuf_sz, fp); line_len >= 2; line_len = getline( &linebuf, &linebuf_sz, fp));
	for( line_len = getline( &linebuf, &linebuf_sz, fp); line_len >= 0; line_len = getline( &linebuf, &linebuf_sz, fp)){
		switch( linebuf[11] ){
			case 'y':
				foldy(arr, atoi(linebuf+13), x_dim, y_dim);
				break;
			case 'x':
				foldx(arr, atoi(linebuf+13), x_dim, y_dim);
				break;
		}
	}
	fclose(fp);
}
int aoc13(const char* filepath){
	uint x_dim, y_dim, ret = 0;
	get_dimensions(filepath, &x_dim, &y_dim);
	bool** arr = calloc(y_dim, sizeof(bool*));
	for(uint i=0; i<y_dim; i++) arr[i] = calloc(x_dim, sizeof(bool));
	init_points(filepath, arr, &x_dim, &y_dim);
	do_n_folds(filepath, 1, arr, x_dim, y_dim);
	for(uint y=0; y<y_dim; ++y){
		for(uint x=0; x<x_dim; ++x){
			if(arr[y][x]) ret++;
		}
	}
	return ret;
}
int aoc13_2(const char* filepath ){
	uint x_dim, y_dim;
	get_dimensions(filepath, &x_dim, &y_dim);
	bool** arr = calloc(y_dim, sizeof(bool*));
	for(uint i=0; i<y_dim; i++) arr[i] = calloc(x_dim, sizeof(bool));
	init_points(filepath, arr, &x_dim, &y_dim);
	do_folds(filepath, arr, &x_dim, &y_dim);
	for(uint y=0; y<y_dim; ++y){
		for(uint x=0; x<x_dim; ++x){
			printf("%c ", (arr[y][x])?'#':'.');
		}
		printf("\n");
	}
	return 0;
}
