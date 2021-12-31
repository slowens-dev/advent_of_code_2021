#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#include "headers/aoc5.h"

uint get_n_lines5(const char* filepath){
	FILE* fp = fopen(filepath, "r");
	uint n_lines = 0;
	for( char c = fgetc(fp); c != EOF; c = fgetc(fp) )
		if(c == '\n') n_lines++;
	fclose(fp);
	return n_lines;
	fclose(fp);
}
void load_xy_arrays(int *x1, int *x2, int *y1, int *y2, const char* filepath){
	FILE *fp = fopen( filepath, "r");
	char *linebuf = NULL, *tok = NULL;
		size_t linebuf_sz;
		for(int i=0, line_len = getline( &linebuf, &linebuf_sz, fp); 
			line_len > 0;
			++i, line_len = getline( &linebuf, &linebuf_sz, fp))
		{
			tok = strtok(linebuf, ",");
			x1[i] = atoi(tok);
			tok = strtok(NULL, " -> ");
			y1[i] = atoi(tok);
			tok = strtok(NULL, " ");
			tok = strtok(NULL, ",");
			x2[i] = atoi(tok);
			tok = strtok(NULL, ",");
			y2[i] = atoi(tok);
		}
	fclose(fp);
	free(linebuf);
}
void load_dimension_variables(int* x1, int* x2, int *y1, int *y2, uint* x_dim, uint* y_dim, uint n_lines){
	uint x = ( x1[0] > x2[0] ) ? x1[0] : x2[0];
	*x_dim = x;
	uint y = ( y1[0] > y2[0] ) ? y1[0] : y2[0];
	*y_dim = y;
	for( uint i=1; i<n_lines; ++i){
		x = ( x1[i] > x2[i] ) ? x1[i] : x2[i];
		*x_dim = ( *x_dim > x ) ? *x_dim : x;
		y = ( y1[i] > y2[i] ) ? y1[i] : y2[i];
		*y_dim = ( *y_dim > y ) ? *y_dim : y;
	}
	*x_dim += 1;
	*y_dim += 1;
}
void calculate_field_straight_lines(int** field, int* x1, int* x2, int* y1, int* y2, uint n_lines){
	
	for( uint straight= 0,low = 0, high = 0, i=0; i<n_lines; ++i){
		if ( x1[i] == x2[i] && y1[i] != y2[i] ){
			straight = x1[i];
			if(y1[i] > y2[i]){
				high = y1[i];
				low = y2[i];
			}else{
				low = y1[i];
				high = y2[i];
			}
			for(uint iy=low; iy<=high; ++iy){
				field[iy][straight] += 1;
			}
		} 
		else if ( y1[i] == y2[i] && x1[i] != x2[i]){
			straight = y1[i];
			if(x1[i] > x2[i]){
				high = x1[i];
				low = x2[i];
			}else{
				low = x1[i];
				high = x2[i];
			}
			for(uint ix=low; ix<=high; ++ix){
				field[straight][ix] += 1;
			}
			
		}
	}

}
void calculate_field(int** field, int* x1, int* x2, int* y1, int* y2, uint n_lines){
	int straight= 0,low = 0, high = 0;
	for( uint i=0; i<n_lines; ++i){
		if ( x1[i] == x2[i] && y1[i] != y2[i] ){
			straight = x1[i];
			if(y1[i] > y2[i]){
				high = y1[i];
				low = y2[i];
			}else{
				low = y1[i];
				high = y2[i];
			}
			for(int iy=low; iy<=high; ++iy){
				field[iy][straight] += 1;
			}
		} else if ( y1[i] == y2[i] && x1[i] != x2[i]){
			straight = y1[i];
			if(x1[i] > x2[i]){
				high = x1[i];
				low = x2[i];
			}else{
				low = x1[i];
				high = x2[i];
			}
			for(int ix=low; ix<=high; ++ix){
				field[straight][ix] += 1;
			}
		} else if ( y1[i] != y2[i] && x1[i] != x2[i]){
			int rise = ( y1[i] > y2[i] ) ? y1[i] - y2[i] : y2[i] - y1[i];
			int run = ( x1[i] > x2[i] ) ? x1[i] - x2[i] : x2[i] - x1[i];
			if (rise == run){
				int iy=y1[i], ix=x1[i];
				while(iy!=y2[i] && ix!=x2[i]){
					field[iy][ix] += 1;
					if( iy > y2[i] ) iy--;
					else iy++;
					if( ix > x2[i] ) ix--;
					else ix++;
				}
				field[ y2[i] ][ x2[i] ] += 1;
			}
		}

	}
}
int aoc5(const char* filepath){
	uint x_dim, y_dim, n_lines = get_n_lines5(filepath);
	int* x1 = (int*) calloc(2*n_lines, sizeof(int));
	int* x2 = (int*) calloc(2*n_lines, sizeof(int));
	int* y1 = (int*) calloc(2*n_lines, sizeof(int));
	int* y2 = (int*) calloc(2*n_lines, sizeof(int));
	load_xy_arrays(x1, x2, y1, y2, filepath);
	load_dimension_variables(x1, x2, y1, y2, &x_dim, &y_dim, n_lines);
	int** field = (int**) calloc(y_dim,sizeof(int*));
	for(uint y=0; y<y_dim; ++y){
		field[y] = (int*) calloc(x_dim, sizeof(int));
		for(uint x=0; x<x_dim; ++x) field[y][x] = 0;
	}

	calculate_field_straight_lines(field, x1, x2, y1, y2, x_dim);

	int retval = 0;
	for(uint y=0; y<y_dim; ++y){
		for(uint x=0; x<x_dim; ++x){
			if (field[y][x] >= 2)
				retval += 1;
		}
		free(field[y]);
	}
	free(field);
	free(x1);
	free(x2);
	free(y1);
	free(y2);
	return retval;
}
int aoc5_2(const char* filepath ){
	uint x_dim, y_dim, n_lines = get_n_lines5(filepath);
	int* x1 = (int*) calloc(2*n_lines, sizeof(int));
	int* x2 = (int*) calloc(2*n_lines, sizeof(int));
	int* y1 = (int*) calloc(2*n_lines, sizeof(int));
	int* y2 = (int*) calloc(2*n_lines, sizeof(int));
	load_xy_arrays(x1, x2, y1, y2, filepath);
	load_dimension_variables(x1, x2, y1, y2, &x_dim, &y_dim, n_lines);
	int** field = (int**) calloc(y_dim,sizeof(int*));
	for(uint y=0; y<y_dim; ++y){
		field[y] = (int*) calloc(x_dim, sizeof(int));
		for(uint x=0; x<x_dim; ++x) field[y][x] = 0;
	}

	calculate_field(field, x1, x2, y1, y2, x_dim);

	int retval = 0;
	for(uint y=0; y<y_dim; ++y){
		for(uint x=0; x<x_dim; ++x)
				if (field[y][x] >= 2) retval += 1;
		free(field[y]);
	}
	free(field);
	free(x1);
	free(x2);
	free(y1);
	free(y2);
	return retval;
}
