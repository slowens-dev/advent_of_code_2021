#include<stdlib.h>
#include<stdio.h>
#include<limits.h>

#include "headers/aoc10.h"
#include "headers/utils.h"

lluint aoc10(const char* filepath){
	C_STACK* closer_stack = (C_STACK*) malloc(sizeof(C_STACK));
	*closer_stack = (C_STACK){.value = '\0', .below = NULL};
	FILE* fp = fopen(filepath, "r");
	unsigned int sum = 0;
	for(char c=fgetc(fp); c!=EOF; c=fgetc(fp)){
		switch(c){
			case '(': 
				C_STACK_push(closer_stack, ')');
				break;
			case '[': 
				C_STACK_push(closer_stack, ']');
				break;
			case '{': 
				C_STACK_push(closer_stack, '}');
				break;
			case '<': 
				C_STACK_push(closer_stack, '>');
				break;
			case ')': 
				if(closer_stack->value != c){
					sum += 3;
					C_STACK_pull(closer_stack);
					while( c!='\n' ) c = fgetc(fp);
					while(C_STACK_pull(closer_stack) == EXIT_SUCCESS);
				}else{
					C_STACK_pull(closer_stack);
				}
				break;
			case ']': 
				if(closer_stack->value != c){
					sum += 57;
					while( c!='\n' ) c = fgetc(fp);
					while(C_STACK_pull(closer_stack) == EXIT_SUCCESS);
				}else{
					C_STACK_pull(closer_stack);
				}
				break;
			case '}': 
				if(closer_stack->value != c){
					sum += 1197;
					C_STACK_pull(closer_stack);
					while( c!='\n' ) c = fgetc(fp);
					while(C_STACK_pull(closer_stack) == EXIT_SUCCESS);
				}else{
					C_STACK_pull(closer_stack);
				}
				break;
			case '>': 
				if(closer_stack->value != c){
					sum += 25137;
					C_STACK_pull(closer_stack);
					while( c!='\n' ) c = fgetc(fp);
					while(C_STACK_pull(closer_stack) == EXIT_SUCCESS);
				}else{
					C_STACK_pull(closer_stack);
				}
				break;
			case '\n':
				while(C_STACK_pull(closer_stack) == EXIT_SUCCESS);
				break;
		}
	}
	while(C_STACK_pull(closer_stack) == EXIT_SUCCESS);
	free(closer_stack);
	fclose(fp);
	return sum;
}
lluint aoc10_2(const char* filepath){
	C_STACK* closer_stack = (C_STACK*) malloc(sizeof(C_STACK));
	*closer_stack = (C_STACK){.value = '\0', .below = NULL};
	FILE* fp = fopen(filepath, "r");
	lluint ret, n_lines = 0, i_line = 0;
	for(char c=fgetc(fp); c!=EOF; c=fgetc(fp))
		if( c == '\n' ) n_lines++;
	rewind(fp);
	lluint* scores = ( lluint*) calloc(n_lines, sizeof( lluint));
	for(char c=fgetc(fp); c!=EOF; c=fgetc(fp)){
		switch(c){
			case '(': 
				C_STACK_push(closer_stack, ')');
				break;
			case '[': 
				C_STACK_push(closer_stack, ']');
				break;
			case '{': 
				C_STACK_push(closer_stack, '}');
				break;
			case '<': 
				C_STACK_push(closer_stack, '>');
				break;
			case ')': 
				if(closer_stack->value != c){
					C_STACK_pull(closer_stack);
					while( c!='\n' ) c = fgetc(fp);
					while(C_STACK_pull(closer_stack) == EXIT_SUCCESS);
				}else{
					C_STACK_pull(closer_stack);
				}
				break;
			case ']': 
				if(closer_stack->value != c){
					while( c!='\n' ) c = fgetc(fp);
					while(C_STACK_pull(closer_stack) == EXIT_SUCCESS);
				}else{
					C_STACK_pull(closer_stack);
				}
				break;
			case '}': 
				if(closer_stack->value != c){
					C_STACK_pull(closer_stack);
					while( c!='\n' ) c = fgetc(fp);
					while(C_STACK_pull(closer_stack) == EXIT_SUCCESS);
				}else{
					C_STACK_pull(closer_stack);
				}
				break;
			case '>': 
				if(closer_stack->value != c){
					C_STACK_pull(closer_stack);
					while( c!='\n' ) c = fgetc(fp);
					while(C_STACK_pull(closer_stack) == EXIT_SUCCESS);
				}else{
					C_STACK_pull(closer_stack);
				}
				break;
			case '\n':
				scores[i_line] = 0;
				do{
					scores[i_line] *= 5;
					switch(closer_stack->value){
						case '>': 
							scores[i_line]++;
						case '}':
							scores[i_line]++;
						case ']':
							scores[i_line]++;
						case ')':
							scores[i_line]++;
							break;
					}
				}while(C_STACK_pull(closer_stack) == EXIT_SUCCESS);
				i_line ++;
				break;
		}
	}

	llui_bubble_sort(scores, i_line);
	ret =  scores[i_line/2];
	free(scores);
	free(closer_stack);
	fclose(fp);
	return ret;
}
