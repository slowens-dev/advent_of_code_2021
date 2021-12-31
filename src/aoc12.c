#include<string.h>
#include<stdlib.h>
#include<stdio.h>

#include "headers/aoc12.h"
#include "headers/utils.h"

static uint load_startpoints(const char* filepath, char** routes){
	FILE *fp = fopen( filepath, "r");
	size_t line_sz;
	uint i_route = 0;
	char* line = NULL, *from, *to;
	for( int line_len = getline( &line, &line_sz, fp); line_len >= 0; line_len = getline( &line, &line_sz, fp)){
		from = strtok(line, "-");
		to = strtok( strtok(NULL, "-"), "\n");
		if( strcmp( to, "start") == 0 ){
			strcpy( routes[i_route], to);
			strcat(routes[i_route], "-");
			strcat(routes[i_route], from);
			i_route += 1;
		}
		if( strcmp( from, "start") == 0 ){
			strcpy( routes[i_route], from);
			strcat(routes[i_route], "-");
			strcat(routes[i_route], to);
			i_route += 1;
		}
		
	}
	fclose(fp);
	return i_route;
}
int aoc12(const char* filepath){
	uint n_lines = get_n_lines( filepath );
	char** routes = calloc(n_lines, sizeof(char*));
	for(uint i=0; i<n_lines; ++i) routes[i] = calloc(100, sizeof(char));



	uint n_routes = load_startpoints(filepath, routes);
	


	printf("==============\n");
	for(uint i=0; i<n_routes; ++i){
		char* last_tok;
		for(char* tok=strtok(routes[i], "-"); tok != NULL; tok=strtok(routes[i], "-")) last_tok = tok;
		printf("%s\n\t\t%s\n", routes[i], last_tok);
	}
	return 0;
}
int aoc12_2(const char* filepath ){
	return 0;
}
