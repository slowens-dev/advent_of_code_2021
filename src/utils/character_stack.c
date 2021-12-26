#include<stdlib.h>
#include<stdio.h>

#include "../headers/character_stack.h"

void C_STACK_push(C_STACK* top, char in){
	if( top->value == '\0' && top->below == NULL){
		top->value = in;
	}
	else{
		C_STACK* replacer = (C_STACK*) malloc(sizeof(C_STACK));
		replacer->value = top->value;
		replacer->below = top->below;
		top->value = in;
		top->below = replacer;
	}
}
int C_STACK_pull(C_STACK* top){
	if (top->below != NULL){
		C_STACK* old_below = top->below;
		top->value = top->below->value;
		top->below = top->below->below;
		free(old_below);
		return EXIT_SUCCESS;
	}else{
		top->value = '\0';
		top->below = NULL;
		return EXIT_FAILURE;
	}
}
void C_STACK_show(C_STACK* top){
	while(top != NULL && top->value != '\0'){
		printf("%c", top->value);
		top = top->below;
	}
	printf("\n");
}
