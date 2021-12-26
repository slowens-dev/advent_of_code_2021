#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#include "headers/aoc6.h"
#include "headers/defined_types.h"

void get_starting_data6(llui* fish, const char* filepath){
	FILE *fp = fopen( filepath, "r");
	char *linebuf = NULL, *tok = NULL;
	size_t linebuf_sz;
	llui value;
	getline( &linebuf, &linebuf_sz, fp);
	tok = strtok(linebuf,",");	
	while( tok != NULL ){
		value = atoi(tok);
		fish[value]++;
		tok = strtok(NULL, ",");
	}
	fclose(fp);
	free(linebuf);
}
void cycle(llui* fish){
	llui swap = fish[0];
	for(int i=1; i<9; ++i) fish[i-1] = fish[i];
	fish[6] += swap;
	fish[8] = swap;
}
llui aoc6(const char* filepath){
	llui fish[9] = {0};
	get_starting_data6(fish, filepath);
	for(int cycles = 0; cycles < 80; ++cycles) cycle(fish);
	llui retval = 0;
	for(int i=0; i<9; ++i) retval += fish[i];
	return retval;
}
llui aoc6_2(const char* filepath ){
	llui fish[9] = {0};
	get_starting_data6(fish, filepath);
	for(int cycles = 0; cycles < 256; ++cycles) cycle(fish);
	llui retval = 0;
	for(int i=0; i<9; ++i) retval += fish[i];
	return retval;
}
