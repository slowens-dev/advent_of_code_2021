#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<limits.h>

#include "headers/aoc14.h"
#include "headers/utils.h"

static uint load_string(const char* filepath, char* str){
	uint str_len = 0;
	FILE* fp = fopen(filepath, "r");
	for( char c = fgetc(fp); c != '\n'; c = fgetc(fp) ){
		sprintf(str, "%s%c", str, c);
		str_len++;
	}
	fclose(fp);
	return str_len;
}
static void load_translations(const char* filepath, char* translations, uint n_translations){
	FILE* fp = fopen(filepath, "r");
	char str[8];
	for( char c = fgetc(fp); c != '\n'; c = fgetc(fp) );
	for(uint i=0; i<n_translations; ++i){
		fgets(str, 8, fp);
		translations[i*3] = str[0];
		translations[(i*3)+1] = str[1];
		translations[(i*3)+2] = str[6];
	}
	fclose(fp);
}
static uint do_cycle(char* str, char* new_str, char* translations, uint str_len, uint n_translations){
	uint new_i = 0;
	new_str[new_i++] = str[0];
	for(uint s=1; s<str_len; ++s, ++new_i){
		for(uint t=0; t<n_translations; ++t){
			if(str[s-1]==translations[t*3] && str[s] == translations[(t*3)+1]){
				new_str[new_i++] = translations[(t*3)+2];
				break;
			}
		}
		new_str[new_i] = str[s];
	}
	strncpy(str, new_str, new_i);
	return new_i;
}
int aoc14(const char* filepath){
	char* str = calloc(4096, sizeof(char));
	char* swap_str = calloc(4096, sizeof(char));
	uint letters[26] = {0};
	uint str_len = load_string(filepath, str);
	uint n_translations = get_n_lines(filepath) - 1;
	char* translations = calloc(n_translations*3, sizeof(char));
	load_translations(filepath, translations, n_translations);
	uint high_count = 0, low_count = UINT_MAX;

	for(uint i=0; i<10; ++i)
		str_len = do_cycle(str,swap_str, translations, str_len, n_translations);
	for(uint i=0; i<str_len; ++i) letters[ str[i] - 65 ]++;
	for(uint i=0; i<26; i++){
		if( letters[i] > high_count ) high_count = letters[i];
		else if (letters[i] < low_count && letters[i] > 0 ) low_count = letters[i];
		printf("%c %d\n", (char)i+65, letters[i]);
	}
	free(translations);
	free(swap_str);
	free(str);
	return high_count - low_count;
}
int aoc14_2(const char* filepath ){
	FILE* fp = fopen(filepath, "r");
	fclose(fp);
	return 0;
}
