#include<stdlib.h>
#include<stdio.h>

#include "headers/aoc1.h"

unsigned long long int aoc1(const char* filepath){
	FILE *fp = fopen( filepath, "r");
	char* linebuf = NULL;
	size_t linebuf_sz;
	int line_len = 0;

	int prev, next, increase_cnt = 0;
	line_len = getline( &linebuf, &linebuf_sz, fp);
	next = atoi(linebuf);
	for( line_len = getline( &linebuf, &linebuf_sz, fp); line_len >= 0; line_len = getline( &linebuf, &linebuf_sz, fp)){
		prev = next;
		next = atoi(linebuf);
		if (next > prev) increase_cnt++;
	}
	fclose( fp );
	free(linebuf);
	return increase_cnt;
}
unsigned long long int aoc1_2(const char* filepath ){
	FILE *fp = fopen( filepath , "r");
	char* linebuf = NULL;
	size_t linebuf_sz;
	int line_len = 0;

	int one,two,three, prev, next, increase_cnt = 0;
	line_len = getline( &linebuf, &linebuf_sz, fp);
	one = atoi(linebuf);
	line_len = getline( &linebuf, &linebuf_sz, fp);
	two = atoi(linebuf);
	line_len = getline( &linebuf, &linebuf_sz, fp);
	three = atoi(linebuf);
	next = one + two + three;
	for( line_len = getline( &linebuf, &linebuf_sz, fp); line_len >= 0; line_len = getline( &linebuf, &linebuf_sz, fp)){
		one = two;
		two = three;
		three = atoi(linebuf);
		prev = next;
		next = one + two + three;
		if (next > prev) increase_cnt++;
	}

	fclose( fp );
	free(linebuf);
	return increase_cnt;
}
