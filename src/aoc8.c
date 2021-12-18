#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<limits.h>

#include "headers/aoc8.h"


int aoc8(const char* filepath){
	FILE* fp = fopen(filepath, "r");
	int word_len, n_lines = 0, count = 0;
	for(char c=fgetc(fp); c!=EOF; c=fgetc(fp))
		n_lines += (c == '\n') ? 1 : 0;

	rewind(fp);

	for(int l=0; l<n_lines; ++l){
		while( fgetc(fp) != '|' );
		fgetc(fp);
		word_len = 0;
		for( char c=fgetc(fp); c != '\n'; c=fgetc(fp) )
			switch(c){
				case ' ': 
					switch(word_len){
						case 2: 
						case 4: 
						case 3: 
						case 7: count+=1;
								break;
					}
					word_len = 0;
					break;
				case '\n':
					switch(word_len){
						case 2: 
						case 4: 
						case 3: 
						case 7: count+=1;
								break;
					}
					word_len = 0;
					break;
				default:
					word_len++;
					break;
			}
		switch(word_len){
			case 2: 
			case 4: 
			case 3: 
			case 7: count+=1;
					break;
		}
	}

	fclose(fp);
	return count;
}
int aoc8_2(const char* filepath ){
	FILE *fp = fopen( filepath, "r");
	char* linebuf = NULL;
	size_t linebuf_sz;
	int line_len = 0;
	char* all_codes, *end_codes, *tok;
	char* digit_codes[10];
	digit_codes[0] = (char*) calloc(6, sizeof(char));
	digit_codes[1] = (char*) calloc(2, sizeof(char));
	digit_codes[2] = (char*) calloc(5, sizeof(char));
	digit_codes[3] = (char*) calloc(5, sizeof(char));
	digit_codes[4] = (char*) calloc(4, sizeof(char));
	digit_codes[5] = (char*) calloc(5, sizeof(char));
	digit_codes[6] = (char*) calloc(6, sizeof(char));
	digit_codes[7] = (char*) calloc(3, sizeof(char));
	digit_codes[8] = (char*) calloc(7, sizeof(char));
	digit_codes[9] = (char*) calloc(6, sizeof(char));

	for(int line_len = getline( &linebuf, &linebuf_sz, fp); line_len > 0; line_len = getline( &linebuf, &linebuf_sz, fp)){
		all_codes = strtok(linebuf, "|");
		end_codes = strtok(NULL, "|");
		for(tok = strtok(all_codes, " "); tok != NULL; tok = strtok(NULL, " "))
			printf("%s ", tok);
		printf("\n");
	}
	return 80085;
}
