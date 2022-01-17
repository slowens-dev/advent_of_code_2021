#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<stdbool.h>

#include "headers/aoc4.h"
#include "headers/utils.h"

void get_file_stats(const char* filepath, uint* n_lines, uint* n_rounds, uint* n_boards){
	FILE* fp = fopen(filepath, "r");
	*n_rounds = 1;
	*n_lines = 2;
	for( char c = fgetc(fp); c != '\n'; c = fgetc(fp) )
		if(c == ',') *n_rounds += 1;
	for( char c = fgetc(fp); c != EOF; c = fgetc(fp) )
		if(c == '\n') *n_lines += 1;
	*n_boards = (*n_lines - 1) / 6;
	fclose(fp);
}
void load_arrays(const char* filepath, int* rounds, int** boards, uint n_boards){
	FILE *fp = fopen( filepath, "r");
	char* linebuf = NULL;
	size_t linebuf_sz;
	getline( &linebuf, &linebuf_sz, fp);
	char* round_tok = strtok(linebuf, ",");
	for(uint i=0; round_tok != NULL; ++i){
		rounds[i] = atoi(round_tok);
		round_tok = strtok(NULL, ",");
	}
	rewind(fp);
	for( char c = fgetc(fp); c != '\n'; c = fgetc(fp) );
	fgetc(fp);
	for(uint i=0; i<n_boards; ++i){
		for(uint j=0, k=0; j<5; ++j, k=0){
			getline( &linebuf, &linebuf_sz, fp);
			for(char* tok = strtok(linebuf, " "); tok != NULL; tok = strtok(NULL, " "))
				boards[i][(j*5)+(k++)] = atoi(tok);
		}
		fgetc(fp);
	}
	fclose(fp);
	free(linebuf);
}
void print_board(int* board){
	for(uint i=0; i<5; ++i){
		for(uint j=0; j<5; ++j){
			printf("%3d ", board[(i*5)+j]);
		}
		printf("\n");
	}
	printf("\n");
}
void print_boards(int** boards, uint n_boards){
	for(uint b=0; b<n_boards; b++){
		print_board(boards[b]);
	}
}
void execute_round(int** boards, uint n_boards, int round){
	for(uint b=0; b<n_boards; b++){
		for(int i=0; i<5; ++i){
			for(int j=0; j<5; ++j){
				if( boards[b][(i*5)+j] == round){
					boards[b][(i*5)+j] = -1;
				}
			}
		}
	}
}
bool check_board(int* board){
	for(int i=0, row=0, col=0; i<5; ++i, row=0, col=0){
		for(int j=0; j<5; ++j){
			if(board[(i*5)+j] == -1) row++;
			if(board[i+(j*5)] == -1) col++;
		}
		if (row==5 || col==5) return true;
	}
	return false;
}
uint find_first_winner(int** boards, uint n_boards){
	for(uint b=0; b<n_boards; b++){
		if (check_board(boards[b])) return b;
	}
	return n_boards;
}
int sum_board(int* board){
	int sum=0;
	for(int i=0; i<25 ; ++i)
		if(board[i] != -1)
			sum += board[i];
	return sum;			
}
lluint aoc4(const char* filepath){
	uint n_lines, n_rounds, n_boards;
	get_file_stats(filepath, &n_lines, &n_rounds, &n_boards);

	int* rounds = (int*) calloc(n_rounds, sizeof(int));
	int** boards = (int**) calloc(n_boards, sizeof(int*));
	for (uint i=0; i<n_boards; ++i){
		boards[i] = (int*) calloc(25, sizeof(int));
	}
	load_arrays(filepath, rounds, boards, n_boards);
	uint winner= n_boards, i_round = 0;
	while(i_round<n_rounds && winner==n_boards){
		execute_round(boards, n_boards, rounds[i_round]);
		winner = find_first_winner(boards, n_boards); ++i_round; }
	int retval = sum_board(boards[winner]);
	retval *= rounds[i_round-1];

	for (uint i=0; i<n_boards; ++i)
		free(boards[i]);
	free(boards);
	free(rounds);
	return retval;
}
lluint aoc4_2(const char* filepath){
	uint n_lines, n_rounds, n_boards;
	get_file_stats(filepath, &n_lines, &n_rounds, &n_boards);
	int* rounds = (int*) calloc(n_rounds, sizeof(int));
	int** boards = (int**) calloc(n_boards, sizeof(int*));
	bool* winners = (bool*) calloc(n_boards, sizeof(bool));
	for (uint i=0; i<n_boards; ++i){
		boards[i] = (int*) calloc(25, sizeof(int));
	}
	load_arrays(filepath, rounds, boards, n_boards);
	uint n_winners = 0, i_round = 0, last_winner = 0;
	
	while(i_round<n_rounds && n_winners<n_boards){
		execute_round(boards, n_boards, rounds[i_round]);
		for(uint b=0; b<n_boards; ++b){
			if(check_board(boards[b]) && !winners[b]){
				last_winner = b;
				winners[b] = true;
				n_winners++;
			}
		}
		i_round++;
	}


	int retval = sum_board(boards[last_winner]);
	retval *= rounds[i_round-1];

	for (uint i=0; i<n_boards; ++i)
		free(boards[i]);
	free(boards);
	free(rounds);
	free(winners);
	return retval;
}
