#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<stdbool.h>

#include "headers/aoc8.h"


                                                                                              
bool readStrFromLine(char* buffer, int length, FILE* f)
{
    char* result = fgets(buffer, length, f);
    if (result == NULL) { return false; }
    buffer[strcspn(buffer, "\n")] = 0;
    return true;
}


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
	size_t linebuf_sz, tok_len;
	char* all_codes, *end_codes, *tok;
	char** digit_codes = (char**) calloc(10, sizeof(char*));
	digit_codes[0] = (char*) calloc(6+1, sizeof(char));
	digit_codes[1] = (char*) calloc(2+1, sizeof(char));
	digit_codes[2] = (char*) calloc(5+1, sizeof(char));
	digit_codes[3] = (char*) calloc(5+1, sizeof(char));
	digit_codes[4] = (char*) calloc(4+1, sizeof(char));
	digit_codes[5] = (char*) calloc(5+1, sizeof(char));
	digit_codes[6] = (char*) calloc(6+1, sizeof(char));
	digit_codes[7] = (char*) calloc(3+1, sizeof(char));
	digit_codes[8] = (char*) calloc(7+1, sizeof(char));
	digit_codes[9] = (char*) calloc(6+1, sizeof(char));
	int sum = 0;
	for(int line_len = getline( &linebuf, &linebuf_sz, fp); line_len > 0; line_len = getline( &linebuf, &linebuf_sz, fp)){
		int letter_counts[10] = {0};
		char bar_chars[7];
		all_codes = strtok(linebuf, "|");
		end_codes = strtok(NULL, "|");
		end_codes = strtok(end_codes, "\n");
		for(tok = strtok(all_codes, " "); tok != NULL; tok = strtok(NULL, " ")){
			for(char* c=tok; *c !='\0'; ++c) letter_counts[*c-'a']++;
			tok_len = strlen(tok);
			switch(tok_len){
				case 2: strncpy(digit_codes[1], tok, tok_len);
						break;
				case 4: strncpy(digit_codes[4], tok, tok_len);
						break;
				case 3: strncpy(digit_codes[7], tok, tok_len);
						break;
				case 7: strncpy(digit_codes[8], tok, tok_len);
						break;
			}
		}

		for(int i=0; i<7; ++i){
			switch(letter_counts[i]){
				case 9: bar_chars['f'-'a'] = 'a'+i;
						break;
				case 6: bar_chars['b'-'a'] = 'a'+i; 
						break;
				case 4: bar_chars['e'-'a'] = 'a'+i;
						break;
				case 7: 
						if( strchr(digit_codes[4], 'a'+i) )
							bar_chars['d'-'a'] = 'a'+i;
						else
							bar_chars['g'-'a'] = 'a'+i;
						break;
				case 8:
						if (strchr(digit_codes[7], 'a'+i) && !strchr(digit_codes[1], 'a'+i))
							bar_chars['a'-'a'] = 'a'+i;
						else
							bar_chars['c'-'a'] = 'a'+i;
						break;
			}
		}

		digit_codes[0][0] = bar_chars['a'-'a'];
		digit_codes[0][1] = bar_chars['b'-'a'];
		digit_codes[0][2] = bar_chars['c'-'a'];
		digit_codes[0][3] = bar_chars['e'-'a'];
		digit_codes[0][4] = bar_chars['f'-'a'];
		digit_codes[0][5] = bar_chars['g'-'a'];

		digit_codes[2][0] = bar_chars['a'-'a'];
		digit_codes[2][1] = bar_chars['c'-'a'];
		digit_codes[2][2] = bar_chars['d'-'a'];
		digit_codes[2][3] = bar_chars['e'-'a'];
		digit_codes[2][4] = bar_chars['g'-'a'];

		digit_codes[3][0] = bar_chars['a'-'a'];
		digit_codes[3][1] = bar_chars['c'-'a'];
		digit_codes[3][2] = bar_chars['d'-'a'];
		digit_codes[3][3] = bar_chars['f'-'a'];
		digit_codes[3][4] = bar_chars['g'-'a'];

		digit_codes[5][0] = bar_chars['a'-'a'];
		digit_codes[5][1] = bar_chars['b'-'a'];
		digit_codes[5][2] = bar_chars['d'-'a'];
		digit_codes[5][3] = bar_chars['f'-'a'];
		digit_codes[5][4] = bar_chars['g'-'a'];

		digit_codes[6][0] = bar_chars['a'-'a'];
		digit_codes[6][1] = bar_chars['b'-'a'];
		digit_codes[6][2] = bar_chars['d'-'a'];
		digit_codes[6][3] = bar_chars['e'-'a'];
		digit_codes[6][4] = bar_chars['f'-'a'];
		digit_codes[6][5] = bar_chars['g'-'a'];

		digit_codes[9][0] = bar_chars['a'-'a'];
		digit_codes[9][1] = bar_chars['b'-'a'];
		digit_codes[9][2] = bar_chars['c'-'a'];
		digit_codes[9][3] = bar_chars['d'-'a'];
		digit_codes[9][4] = bar_chars['f'-'a'];
		digit_codes[9][5] = bar_chars['g'-'a'];

		int multiplier = 1000, value = 0;
		for(tok = strtok(end_codes, " "); tok != NULL; tok = strtok(NULL, " ")){
			int code_num = 0;
			tok_len = strlen(tok);
			switch(tok_len){
				case 2: code_num += 1; break;
				case 3: 
						code_num += 7; break;
				case 4: 
						code_num += 4; break;
				case 5: if( strchr(tok, bar_chars['a'-'a']) && strchr(tok, bar_chars['c'-'a'])
								&& strchr(tok, bar_chars['d'-'a']) && strchr(tok, bar_chars['e'-'a'])
								&& strchr(tok, bar_chars['g'-'a'])
						){
							code_num += 2;
						} else if( strchr(tok, bar_chars['a'-'a']) && strchr(tok, bar_chars['c'-'a'])
								&& strchr(tok, bar_chars['d'-'a']) && strchr(tok, bar_chars['f'-'a'])
								&& strchr(tok, bar_chars['g'-'a'])
						){
							code_num += 3;
						} else {
							code_num += 5;
						}
						break;
				case 6: if( strchr(tok, bar_chars['a'-'a']) && strchr(tok, bar_chars['b'-'a'])
								&& strchr(tok, bar_chars['c'-'a']) && strchr(tok, bar_chars['e'-'a'])
								&& strchr(tok, bar_chars['f'-'a']) && strchr(tok, bar_chars['g'-'a'])
						){
							code_num += 0;
						} else if( strchr(tok, bar_chars['a'-'a']) && strchr(tok, bar_chars['b'-'a'])
								&& strchr(tok, bar_chars['d'-'a']) && strchr(tok, bar_chars['e'-'a'])
								&& strchr(tok, bar_chars['f'-'a']) && strchr(tok, bar_chars['g'-'a'])
						){
							code_num += 6;
						}else{
							code_num += 9;
						}
						break;
				case 7: 
						code_num += 8; break;
			}
			value += code_num*multiplier;
			multiplier /= 10;
		}
		sum += value;
	}

	for(int i=0; i<10; ++i)
		free(digit_codes[i]);
	free(digit_codes);
	free(linebuf);
	fclose(fp);
	return sum;
}
