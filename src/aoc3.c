
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdint.h>

#include "headers/aoc3.h"
typedef unsigned int uint;

uint convert_binary_to_decimal(const char* binary, uint n_bits){
	uint ret = 0;
	for(uint b=0; b<n_bits; ++b)
		if(binary[b] == '1') ret += 1 << (n_bits - b - 1);
	return ret;
}
uint get_n_lines(const char* filepath){
	FILE* fp = fopen(filepath, "r");
	uint n_lines = 0;
	for( char c = fgetc(fp); c != EOF; c = fgetc(fp) )
		if(c == '\n') n_lines++;
	fclose(fp);
	return n_lines;
}
uint get_n_bits(const char* filepath){
	FILE* fp = fopen(filepath, "r");
	uint n_bits = 0;
	while( fgetc(fp) != '\n' ) n_bits++;
	fclose(fp);
	return n_bits;
}
void load_array_from_file(const char* filepath, char** arr){
	FILE *fp = fopen( filepath, "r");
	char* linebuf = NULL;
	size_t linebuf_sz;
	for(int l = 0,  line_len = getline( &linebuf, &linebuf_sz, fp); line_len > 0; l++, line_len = getline( &linebuf, &linebuf_sz, fp)){
			strncpy( arr[l], linebuf, line_len);
	}
	fclose(fp);
	free(linebuf);
}
int aoc3(const char* filepath){
	uint n_lines = get_n_lines(filepath);
	uint n_bits = get_n_bits(filepath);
	char** line_arr = (char**) malloc(n_lines * sizeof(char*));
	for(uint l=0; l<n_lines; ++l) line_arr[l] = (char*) malloc((n_bits+1) * sizeof(char));
	uint G = 0, E = 0;

	load_array_from_file(filepath, line_arr);

	for(uint b=0; b<n_bits; ++b){
		int cnt = 0;
		for(uint l=0; l<n_lines; ++l){
			switch( line_arr[l][b] ){
				case '1': cnt++; break;
				case '0': cnt--; break;
			}
		}
		G += (cnt>0) ? 1 << (n_bits-b-1) : 0 << (n_bits-b-1);
		E += (cnt>0) ? 0 << (n_bits-b-1) : 1 << (n_bits-b-1);
	}
	for(uint l=0; l<n_lines; ++l) free( line_arr[l] );
	free(line_arr);
	return G*E;
}
int aoc3_2(const char* filepath){
	uint n_lines = get_n_lines(filepath);
	uint n_bits = get_n_bits(filepath);
	char** line_arr = (char**) malloc(n_lines * sizeof(char*));
	for(uint l=0; l<n_lines; ++l) line_arr[l] = (char*) malloc((n_bits+1) * sizeof(char));
	load_array_from_file(filepath, line_arr);
	char * o2_bits = (char*) malloc((n_bits+1) * sizeof(char));
	char * co2_bits = (char*) malloc((n_bits+1) * sizeof(char));
	int cnt = 0;
	uint o2 = 0, co2 = 0;

	//first bit count
	for(uint l=0; l<n_lines; ++l){
		switch( line_arr[l][0] ){
			case '1': cnt++; break;
			case '0': cnt--; break;
		}
	}//first bit check 
	if( cnt >= 0){
		o2_bits[0] = '1';
		co2_bits[0] = '0';
	}else{
		o2_bits[0] = '0';
		co2_bits[0] = '1';
	}

	//remaining bits for o2
	for(uint b=1, row = 0; b<n_bits; ++b, row = 0){
		char* bit_string;
		cnt = 0;
		for(uint l=0; l<n_lines; ++l){
			if( strncmp(o2_bits, line_arr[l], b) ==0 ){
				switch( line_arr[l][b] ){
					case '1': cnt++; break;
					case '0': cnt--; break;
				}
				row++;
				bit_string = line_arr[l];
			}
		}
		if( cnt >= 0){
			o2_bits[b] = '1';
		}else{
			o2_bits[b] = '0';
		}
		if(row == 1){
			strncpy(o2_bits, bit_string, n_bits); break;
		}
	}
	o2_bits[n_bits] = '\0';
	//remaining bits for co2
	for(uint b=1, row=0; b<n_bits; ++b, row=0){
		char* bit_string;
		cnt = 0;
		for(uint l=0; l<n_lines; ++l){
			if( strncmp(co2_bits, line_arr[l], b) ==0 ){
				switch( line_arr[l][b] ){
					case '1': cnt++; break;
					case '0': cnt--; break;
				}
				row++;
				bit_string = line_arr[l];
			}
		}
		if( cnt >= 0){
			co2_bits[b] = '0';
		}else{
			co2_bits[b] = '1';
		}
		if(row == 1){
			strncpy(co2_bits, bit_string, n_bits);
			break;
		}
	}
	//co2_bits[n_bits] = '\0';
	o2 = convert_binary_to_decimal( o2_bits, n_bits );
	co2 = convert_binary_to_decimal( co2_bits, n_bits);
	for(uint l=0; l<n_lines; ++l) free( line_arr[l] );
	free(line_arr);
	free(o2_bits);
	free(co2_bits);
	return o2 * co2;
}
