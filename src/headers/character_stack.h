#ifndef __CHARACTER_STACK_H_
#define __CHARACTER_STACK_H_

typedef struct CHARACTER_STACK{
	char value;
	struct CHARACTER_STACK* below;
} C_STACK;
void C_STACK_push(C_STACK* top, char in);
int C_STACK_pull(C_STACK* top);
void C_STACK_show(C_STACK* top);


#endif
