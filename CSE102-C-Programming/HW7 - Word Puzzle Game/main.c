#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

/* Directions to use for putting and searching words. */
typedef enum {
	left_to_right, right_to_left, up_to_bottom, bottom_to_up, diag_up_left, diag_up_right, diag_bottom_left, diag_bottom_right
}Directions;

/* Put space in all coordinates at first. */
void clear_puzzle(char puzzle[][15]) {
	int i, j;
	for(i=0; i<15; i++) {
		for(j=0; j<15; j++) {
			puzzle[i][j] = ' ';
		}
	}
}

/* Clear the hash-map of words. */
void clear_word_map(int word_map[]) {
	int i;
	for(i=0; i<50; i++) word_map[i] = 0;
}

/*
	Function : get_random_word
	To-do-List: 
		1) Get random word number between 1-50.
		2) Check if this word is used before or not by using word_map like hash map.
*/

void get_random_word(char word[], int word_map[]) {
	int is_done = 0;
	int word_number;
	int i;
	FILE *file;
	
	while(!is_done) {
		word_number = rand()%50 + 1;
		
		if(word_map[word_number-1] == 0) {
			file = fopen("wordlist.txt", "r");
			
			/* Get the word. */
			for(i=0; i<word_number; i++) {
				fscanf(file, "%s", word);
			}
			
			word_map[word_number-1] = 1;
			is_done = 1;
		}
	
	}
	
	fclose(file);
}

/* Get random starting coordinates for putting a word. */
void get_random_coordinates(char puzzle[][15], int coordinates[]) {
	int is_done = 0;
	int x;
	int y;
	
	while (!is_done) {
		x = rand()%15;
		y = rand()%15;
		if (puzzle[x][y] == ' ') {
			coordinates[0] = x;
			coordinates[1] = y;
			is_done = 1;
		}
	}
}

/*
	Function: place_word
	TO-DO-LIST: 
		1) Choose random direction to try to put the word first.
		2) Starting from this direction, try to put the word onto the puzzle for every direction.
*/

int place_word(char puzzle[][15], char word[], int coordinates[]) {
	int x = coordinates[0];
	int y = coordinates[1];
	
	int is_placed = 0;
	int try_number = 0;
	
	/* Choose random starting direction. */
	int direction = rand()%8;
	int len = strlen(word);	
	int i, is_empty;
	
	
	for(is_placed=0, try_number=0; is_placed == 0 && try_number<8; try_number++) {
		if (direction == left_to_right) {
			/* First, check if the word can be placed in this direction according to its length.*/
			if (len <= 15-y) {
				/* Check if the puzzle is empty in this direction. */
				for(i=0, is_empty = 1; i<len && is_empty; i++) {
					if (puzzle[x][y+i] != ' ') {
						is_empty = 0;
					}
				}		
				
				if (is_empty) {
					for(i=0; i<len; i++) {
						puzzle[x][y+i] = word[i];	
					}
					
					is_placed = 1;
				}
			}
		}
		
		else if (direction == right_to_left) {
			if (len <= y+1) {
				for(i=0, is_empty=1; i<len && is_empty; i++) {
					if (puzzle[x][y-i] != ' ') {
						is_empty = 0;
					}
					
				}
				
				if (is_empty) {
					for(i=0; i<len; i++) {
						puzzle[x][y-i] = word[i];
					}
					
					is_placed = 1;
				}
			}
		}
		
		else if (direction == up_to_bottom) {
			if (len <= 15-x) {
				for(i=0, is_empty=1; i<len && is_empty; i++) {
					if (puzzle[x+i][y] != ' ') {
						is_empty = 0;
					} 
				}
			
				if (is_empty) {
					for(i=0; i<len; i++) {
						puzzle[x+i][y] = word[i];
					}

					is_placed = 1;
				}
			}
		}
		
		else if (direction == bottom_to_up) {
			if (len <= x+1) {
				for(i=0, is_empty=1; i<len && is_empty; i++) {
					if (puzzle[x-i][y] != ' ') {
						is_empty = 0;
					}
				}
			
				if (is_empty) {
					for(i=0; i<len; i++) {
						puzzle[x-i][y] = word[i];
					}

					is_placed = 1;
				}
			}
		}
		
		else if (direction == diag_up_left) {
			if (len <= x+1 && len <= y+1) {
				for(i=0, is_empty = 1; i<len && is_empty; i++) {
					if (puzzle[x-i][y-i] != ' ') {
						is_empty = 0;
					}
				}
			
				if (is_empty) {
					for(i=0; i<len; i++) {
						puzzle[x-i][y-i] = word[i];
					}

					is_placed = 1;
				}
			}
		}
		
		else if (direction == diag_up_right) {
			if (len <= x+1 && len <= 15-y) {
				for(i=0, is_empty = 1; i<len && is_empty; i++) {
					if (puzzle[x-i][y+i] != ' ') {
						is_empty = 0;
					}
				}
				
				if (is_empty) {
					for(i=0; i<len; i++) {
						puzzle[x-i][y+i] = word[i];
					}

					is_placed = 1;
				}
			}
		}
		
		else if (direction == diag_bottom_left) {
			if (len <= 15-x && len <= y+1) {
				for(i=0, is_empty = 1; i<len && is_empty; i++) {
					if (puzzle[x+i][y-i] != ' ') {
						is_empty = 0;
					}
				}
				
				if (is_empty) {
					for(i=0; i<len; i++) {
						puzzle[x+i][y-i] = word[i];
					}

					is_placed = 1;
				}
			}
		}
		
		else if (direction == diag_bottom_right) {
			if (len <= 15-x && len <= 15-y) {
				for(i=0, is_empty = 1; i<len && is_empty; i++) {
					if (puzzle[x+i][y+i] != ' ') {
						is_empty = 0;
					}
				}
				
				if (is_empty) {
					for(i=0; i<len; i++) {
						puzzle[x+i][y+i] = word[i];
					}

					is_placed = 1;
				}
			}
		}
		
		/* Iterate direction. */
		if (direction==diag_bottom_right) direction = left_to_right;
		else direction++;
	}
 		
	return is_placed;
}

/* Put random letters to the empty places in the puzzle. */
void complete_puzzle(char puzzle[][15]) {
	int i, j;
	for(i=0; i<15; i++) {
		for(j=0; j<15; j++) {
			if (puzzle[i][j] == ' ') {
				puzzle[i][j] = 'a' + rand()%26;
			}
		}
	}
}

void print_puzzle(char puzzle[][15]) {
	int i, j;
	for(i=0; i<15; i++) {
		for(j=0; j<15; j++) {
			printf("%c ", puzzle[i][j]);
		}
		printf("\n");
	}
}


void create_puzzle(char puzzle[][15], char placed_words[][20]) {
	/* First clear puzzle(put space on everywhere) to work on it easily. */
	clear_puzzle(puzzle);
	char word[20];
	int coordinates[2];
	
	/* For 50 words in the text, keep hash-map to know which words have already been placed. */
	int word_map[50];
	clear_word_map(word_map);
	
	int is_placed;
	int placed_word_num = 0;
	
	for(placed_word_num=0; placed_word_num<7; placed_word_num++) {
		get_random_word(word, word_map);
		for(is_placed=0; is_placed==0;) {
			get_random_coordinates(puzzle, coordinates);
			is_placed = place_word(puzzle, word, coordinates);
			/* If the word is placed, print the word and coordinates for readibility. */
			if (is_placed) {
				printf("Word : %s Coordinates : %d %d\n", word, coordinates[0], coordinates[1]);
				strcpy(placed_words[placed_word_num], word);
			}
			
		}
	}
	
	complete_puzzle(puzzle);
}

/*
	Function : is_there_such_word
	TO-DO-LIST:
		1) Check if the given word in the word list.
*/

int is_there_such_word(char word[], char placed_words[][20]) {
	int i;
	int is_there = 0;
	
	for(i = 0; i<7 && is_there == 0; i++) {
		if (strcmp(word, placed_words[i]) == 0)	is_there = 1;
	}
		
	return is_there;	
}

/*
	Function : find_word
	TO-DO-LIST:
		1) Check if the given word is in the placed_words list.
		2) Look for the given word in given coordinates for every 8 directions. 
		3) If the word is found, turn it to XXXX and return 1.
		   If the word is not found, return 0.
*/

int find_word(char puzzle[][15], char word[], int x, int y, char placed_words[][20]) {
	int is_found;
	int is_same;
	int direction = left_to_right;
	int len = strlen(word);
	int is_word_in_list = is_there_such_word(word, placed_words);

	
	
	int i;
	
	if (is_word_in_list) {
		for(i=0, direction = left_to_right, is_found = 0; i<8 && is_found == 0; i++, direction++) {
			if (direction == left_to_right) {
				if (len <= 15-y) {
					for(i=0, is_same = 1; i<len && is_same; i++) {
						if (puzzle[x][y+i] != word[i]) {
							is_same = 0;
						}
					}		
					
					if (is_same) {
						for(i=0; i<len; i++) {
								puzzle[x][y+i] = 'X';	
						}
						is_found = 1;
					}
				}
			}
			
			else if (direction == right_to_left) {
				if (len <= y+1) {
					for(i=0, is_same = 1; i<len && is_same; i++) {
						if (puzzle[x][y-i] != word[i]) {
							is_same = 0;
						}
					}		
					
					if (is_same) {
						for(i=0; i<len; i++) {
							puzzle[x][y-i] = 'X';	
						}
						is_found = 1;
					}
					
				}
			}
		
			else if (direction == up_to_bottom) {
				if (len <= 15-x) {
					for(i=0, is_same = 1; i<len && is_same; i++) {
						if (puzzle[x+i][y] != word[i]) {
							is_same = 0;
						}
					}		
				
					if (is_same) {
						for(i=0; i<len; i++) {
							puzzle[x+i][y] = 'X';	
						}
						is_found = 1;
					}
	
				}
			}
			
			else if (direction == bottom_to_up) {
				if (len <= x+1) {
					for(i=0, is_same = 1; i<len && is_same; i++) {
						if (puzzle[x-i][y] != word[i]) {
							is_same = 0;
						}
					}		
					
					if (is_same) {
						for(i=0; i<len; i++) {
							puzzle[x-i][y] = 'X';
						}
						is_found = 1;
					}
				}
			}
			
			else if (direction == diag_up_left) {
				if (len <= x+1 && len <= y+1) {
					for(i=0, is_same = 1; i<len && is_same; i++) {
						if (puzzle[x-i][y-i] != word[i]) {
							is_same = 0;
						}
					}		
					
					if (is_same) {
						for(i=0; i<len; i++) {
							puzzle[x-i][y-i] = 'X';	
						}
						is_found = 1;
					}
				}
			}
			
			else if (direction == diag_up_right) {
				if (len <= x+1 && len <= 15-y) {
					for(i=0, is_same = 1; i<len && is_same; i++) {
						if (puzzle[x-i][y+i] != word[i]) {
							is_same = 0;
						}
					}		
					
					if (is_same) {
						for(i=0; i<len; i++) {
							puzzle[x-i][y+i] = 'X';	
						}
						is_found = 1;
					}
					
				}
			}
			
			else if (direction == diag_bottom_left) {
				if (len <= 15-x && len <= y+1) {
					for(i=0, is_same = 1; i<len && is_same; i++) {
						if (puzzle[x+i][y-i] != word[i]) {
							is_same = 0;
						}
					}		
					
					if (is_same) {
						for(i=0; i<len; i++) {
							puzzle[x+i][y-i] = 'X';	
						}
						is_found = 1;
					}
				
				}
			}
			
			else if (direction == diag_bottom_right) {
				if (len <= 15-x && len <= 15-y) {
					for(i=0, is_same = 1; i<len && is_same; i++) {
						if (puzzle[x+i][y+i] != word[i]) {
							is_same = 0;
						}
					}		
					
					if (is_same) {
						for(i=0; i<len; i++) {
							puzzle[x+i][y+i] = 'X';	
						}
						is_found = 1;
					}
					
				}
			}
				
		}
		
	}
	
	else is_found = 0;
	
	return is_found;	
}


int main () {
	srand(time(NULL));
	char puzzle[15][15];
	char placed_words[7][20];
	
	printf("***********************\n");
	printf("WORDS PLACED ON THE PUZZLE AND ITS COORDINATES : \n\n");
	create_puzzle(puzzle, placed_words);
	printf("***********************\n");
	
	
	int remained_mistakes = 3;
	int points = 0;
	int founded_word_num = 0;
	
	int exit = 0;
	int is_word_found;
	int x, y;
	char word[20];
	char buff[100];
	char ch;
	
	
	print_puzzle(puzzle);
	
	while (remained_mistakes != 0 && founded_word_num < 7 && exit == 0) {
		printf("Enter coordinates and word:");
		/* Read the input till the end of line to the buffer. */
		scanf("%[^\n]s", buff);
		
		/* Validate the input. */
		if (buff[0] == ':' && buff[1] == 'q') {
			exit = 1;
			printf("Your total points: %d\n", points);
			printf("Game is closing...Goodbye!\n");
		}
		
		else {
			/* If user doesn't want to exit, then read the input from buffer with sscanf. */
			sscanf(buff, "%d %d %s", &x, &y, word);
			is_word_found = find_word(puzzle, word, x, y, placed_words);
			
			if (is_word_found) {
				printf("\n");
				print_puzzle(puzzle);
				
				points += 2;
				founded_word_num++;
				printf("Founded! You got 2 points.Your total points : %d\n", points);
			}
			
			else {
				print_puzzle(puzzle);
				remained_mistakes--;
				printf("Wrong choice! You have only %d lefts.\n", remained_mistakes);
			}
	
		}
	
		/* flush the buffer before reading string/character again. */
		do {
			ch = getchar();
		}while(ch!='\n');
	}
	
	if (remained_mistakes == 0) printf("GAME OVER. You have no left. Your total points : %d\n", points);
	if (founded_word_num == 7) printf("You have founded all words !! Congrats.. \n");
	
	return 0;
}
