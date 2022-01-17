#include <bits/types.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<limits.h>

#include "headers/aoc14.h"
#include "headers/utils.h"

static void load_translations(const char* filepath, char* translations, uint n_translations){
	FILE* fp = fopen(filepath, "r");
	char str[8];
	for( char c = fgetc(fp); c != '\n'; c = fgetc(fp) );
	for(uint i=0; i<n_translations; ++i){
		fgets(str, 8, fp);
		translations[i*3] = str[0];
		translations[(i*3)+1] = str[1];
		translations[(i*3)+2] = str[6];
		fgetc(fp);
	}
	fclose(fp);
}
//PART 1 
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
//PART 2
static void get_starting_stats(const char* filepath,
		lluint** pair_counts, lluint*letter_counts){
	size_t linebuf_sz;
	uint i, j;
	char *c, *linebuf = NULL;
	FILE* fp = fopen(filepath, "r");
	getline( &linebuf, &linebuf_sz, fp);
	for( c=linebuf+1; *c!='\n'; ++c){
		i = *(c-1) - 'A';
		j = *c - 'A';
		pair_counts[i][j]++;
		letter_counts[*c-'A']++;
	}
	letter_counts[linebuf[0]-'A']++;
	free(linebuf);
	fclose(fp);
}
static void do_n_cycles(uint n_cycles, uint n_translations,
		char* translations, lluint* letter_counts, lluint** pair_counts){
	char c1, c2, newc;
	uint i1, i2, newi;
	lluint swap[26][26];
	for(uint i_cycle=0; i_cycle<n_cycles; ++i_cycle){
		for(uint i=0; i<26; ++i) memcpy(swap[i], pair_counts[i], 26*sizeof(lluint));
		for(uint i_t=0; i_t<n_translations*3; i_t+=3){
			c1=translations[i_t];
			i1 = c1 - 'A';
			c2=translations[i_t+1];
			i2 = c2 - 'A';
			newc=translations[i_t+2];
			newi = newc - 'A';

			swap[i1][i2] -= pair_counts[i1][i2];
			swap[i1][newi] += pair_counts[i1][i2];
			swap[newi][i2] += pair_counts[i1][i2];
			letter_counts[newi] += pair_counts[i1][i2];
		}
		for(uint i=0; i<26; ++i) memcpy(pair_counts[i], swap[i], 26*sizeof(lluint));
	}
}
//////////////////
lluint aoc14(const char* filepath ){
	char* str = calloc(102400, sizeof(char));
	char* swap_str = calloc(102400, sizeof(char));
	uint letters[26] = {0};
	uint str_len = load_string(filepath, str);
	uint n_translations = get_n_lines(filepath) - 1;
	char* translations = calloc(n_translations*3, sizeof(char));
	load_translations(filepath, translations, n_translations);
	uint high_count = 0, low_count = UINT_MAX;

	for(uint i=0; i<10; ++i){
		str_len = do_cycle(str,swap_str, translations, str_len, n_translations);
	}
	for(uint i=0; i<str_len; ++i) letters[ str[i] - 65 ]++;
	for(uint i=0; i<26; i++){
		if( letters[i] > high_count ) high_count = letters[i];
		else if (letters[i] < low_count && letters[i] > 0 ) low_count = letters[i];
	}
	free(translations);
	free(swap_str);
	free(str);
	return high_count - low_count;
}
lluint aoc14_2(const char* filepath){
	uint n_translations = get_n_lines(filepath) - 1;
	lluint** pair_counts = calloc(26, sizeof(lluint*));
	for(uint i=0; i<26; ++i) pair_counts[i] = calloc(26, sizeof(lluint));
	lluint* letter_counts = calloc(26, sizeof(lluint));
	char* translations = calloc(n_translations*3, sizeof(char));

	load_translations(filepath, translations, n_translations);
	get_starting_stats(filepath, pair_counts, letter_counts);
	do_n_cycles(40, n_translations, translations, letter_counts, pair_counts);

	lluint high_count = 0, low_count = ULLONG_MAX;
	for(uint i=0; i<26; ++i){
		if(letter_counts[i] > high_count) 
			high_count = letter_counts[i];
		else if (letter_counts[i] < low_count && letter_counts[i] > 0)
			low_count = letter_counts[i];
	}
	for(uint i=0; i<26; ++i) free(pair_counts[i]);
	free(letter_counts);
	free(pair_counts);
	free(translations);
	return high_count - low_count;
}
