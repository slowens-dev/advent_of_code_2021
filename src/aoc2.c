#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#include "headers/aoc2.h"
#include "headers/utils.h"
//o(n)
lluint aoc2(const char* filepath){
	FILE *fp = fopen( filepath, "r");
	char* linebuf = NULL;
	size_t linebuf_sz;
	int line_len;

	char* str;
	int val = 0, depth = 0, distance = 0;

	for( line_len = getline( &linebuf, &linebuf_sz, fp); line_len >= 0; line_len = getline( &linebuf, &linebuf_sz, fp)){
		str = strtok(linebuf, " ");
		val = atoi(strtok(NULL, " "));
		if  ( strcmp(str, "forward") == 0 )
			distance += val;
		else if (strcmp(str, "up") == 0)
			depth -= val;
		else if (strcmp(str, "down") == 0)
			depth += val;
	}
	fclose( fp );
	free(linebuf);
	return (depth * distance);
}
lluint aoc2_2(const char* filepath){
	FILE *fp = fopen( filepath, "r");
	char* linebuf = NULL;
	size_t linebuf_sz;
	int line_len;

	char* str = NULL;
	int aim = 0, val = 0, depth = 0, distance = 0;

	for( line_len = getline( &linebuf, &linebuf_sz, fp); line_len >= 0; line_len = getline( &linebuf, &linebuf_sz, fp)){
		str = strtok(linebuf, " ");
		val = atoi(strtok(NULL, " "));
		if  ( strcmp(str, "forward") == 0 ){
			distance += val;
			depth += ( val * aim );
		}
		else if (strcmp(str, "up") == 0)
			aim -= val;
		else if (strcmp(str, "down") == 0)
			aim += val;
	}
	fclose( fp );
	free(linebuf);
	return (depth * distance);
}
