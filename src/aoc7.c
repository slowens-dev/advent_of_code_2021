#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<limits.h>

#include "headers/aoc7.h"
typedef unsigned int uint;
uint get_n_crabs(const char* filepath){
	FILE *fp = fopen( filepath, "r");
	int n_crabs = 1;
	for(char c = fgetc(fp); c != EOF; c = fgetc(fp)) 
		if(c==',') n_crabs++;
	fclose(fp);
	return n_crabs;
}
void load_crabs_array(uint* crabs, uint n_crabs, const char* filepath){
	FILE *fp = fopen( filepath, "r");
	char *linebuf = NULL, *tok = NULL;
	size_t linebuf_sz;
	getline( &linebuf, &linebuf_sz, fp);
	tok = strtok(linebuf,",");	
	uint i_crab = 0;
	while( tok != NULL ){
		crabs[i_crab++] = atoi(tok);
		tok = strtok(NULL, ",");
	}
	fclose(fp);
	free(linebuf);
}
int aoc7(const char* filepath){
	uint largest = 0;
	int difference = 0;
	uint smallest = UINT_MAX;
	uint shortest_total = UINT_MAX;
	uint n_crabs = get_n_crabs(filepath);
	uint* crabs = (uint*) calloc(n_crabs, sizeof(uint));
	load_crabs_array(crabs, n_crabs, filepath);
	for(uint c=0; c<n_crabs; ++c){
		if(crabs[c] > largest) largest = crabs[c];
		else if(crabs[c] < smallest) smallest = crabs[c];
	}
	for(uint location=smallest, total_distance = 0; location<largest; ++location, total_distance=0){
		for(uint c=0; c<n_crabs; ++c){
			difference = location - crabs[c];
			total_distance += (difference>0) ? difference : difference*-1;
		}
		if(total_distance < shortest_total) shortest_total = total_distance;
	}
	free(crabs);
	return shortest_total;
}
int aoc7_2(const char* filepath ){
	uint largest = 0;
	int difference = 0;
	uint smallest = UINT_MAX;
	uint shortest_total = UINT_MAX;
	uint n_crabs = get_n_crabs(filepath);
	uint* crabs = (uint*) calloc(n_crabs, sizeof(uint));
	load_crabs_array(crabs, n_crabs, filepath);
	for(uint c=0; c<n_crabs; ++c){
		if(crabs[c] > largest) largest = crabs[c];
		else if(crabs[c] < smallest) smallest = crabs[c];
	}
	for(uint location=smallest, total_distance = 0; location<largest; ++location, total_distance=0){
		for(uint c=0; c<n_crabs; ++c){
			difference = location - crabs[c];
			difference = (difference>0) ? difference : difference*-1;
			total_distance += ( ( difference * (difference+1) ) / 2 );
		}
		if(total_distance < shortest_total) shortest_total = total_distance;
	}
	free(crabs);
	return shortest_total;
}
