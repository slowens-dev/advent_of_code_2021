#include<stdlib.h>
#include<stdio.h>
#include<stdint.h>
#include<string.h>

#include "headers/aoc6.h"

void get_starting_data6(uint64_t* fish, const char* filepath){
	FILE *fp = fopen( filepath, "r");
	char *linebuf = NULL, *tok = NULL;
	size_t linebuf_sz;
	uint64_t value;
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
void cycle(uint64_t* fish){
	uint64_t swap = fish[0];
	for(int i=1; i<9; ++i) fish[i-1] = fish[i];
	fish[6] += swap;
	fish[8] = swap;
}
uint64_t aoc6(const char* filepath){
	uint64_t fish[9] = {0};
	load_starting_data(fish, filepath);
	for(int cycles = 0; cycles < 80; ++cycles) cycle(fish);
	uint64_t retval = 0;
	for(int i=0; i<9; ++i) retval += fish[i];
	return retval;
}
uint64_t aoc6_2(const char* filepath ){
	uint64_t fish[9] = {0};
	get_starting_data6(fish, filepath);
	for(int cycles = 0; cycles < 256; ++cycles) cycle(fish);
	uint64_t retval = 0;
	for(int i=0; i<9; ++i) retval += fish[i];
	printf("%lu\n", retval);
	return retval;
}
