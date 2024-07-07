#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* IMPORTANT : x represents vertical axis, y represent horizantal axis for convenience. */

typedef enum {
	right = 1, down = 2, left = 3, up = 4
}directions;

void createMap(char map[15][30]) {
	int i, j;
	for (i=0; i<15; i++) {
		for (j=0; j<30; j++) {
			/* Draw the most outer border. */
			if (i==0 || i==14) map[i][j] = '.';
			else if (j==0 || j==29) map[i][j] = ':';
		
			/* Draw middle border. */
			else if ( (i==2 || i==12) && (2<=j && j<=27) ) map[i][j] = '.';
			else if ( (j==2 || j==27) && (2<=i && i<=12) ) map[i][j] = ':';
			
			/* Draw inner border. */
			else if ( (i==4 || i==10) && (4<=j && j<=25) ) map[i][j] = '.';
			else if ( (j==4 || j==25) && (4<=i && i<=10) ) map[i][j] = ':';
			
			/* If point is not on a border, than put a space at that point. */
			else map[i][j] = ' ';
		}
	}
	
	/* Put penalty points of player 1. */
	map[1][14] = 'X';
	map[7][28] = 'X';
	map[13][14] = 'X';
	
	/* Put penalty points of player 2. */
	map[3][10] = 'X';
	map[3][18] = 'X';
	map[5][26] = 'X';
	map[10][26] = 'X';
	map[11][10] = 'X';
	map[11][18] = 'X';
	
	/* Put beginning positions. */
	map[1][1] = '1';
	map[3][3] = '2';
	
	/* Put finish lines. */
	map[2][1] = '_';
	map[4][3] = '_';
}

void red () {
  printf("\033[1;31m");
}
void yellow () {
  printf("\033[1;33m");
}

void blue () {
  printf("\033[0;34m");
}

void green()  {
  printf("\033[0;32m");
}

void reset () {
  printf("\033[0m");
}

void printMap(char map[15][30]) {
	int i, j;
	for (i=0; i<15; i++) {
		for (j=0; j<30; j++) {
		
			if (map[i][j] == '1') {
				yellow();
				printf("1");
				reset();
			}
			
			else if (map[i][j] == '2') {
				blue();
				printf("2");
				reset();
			}
			
			else if (map[i][j] == 'X') {
				red();
				printf("X");
				reset();
			}
			
			else if (map[i][j] == '_') {
				green();
				printf("_");
				reset();
			}
			
			else printf("%c", map[i][j]);
		
		}
		
		printf("\n");
	}

}

int dice(void) {
	int dice = rand() % 6 + 1;
	return dice;
}

int startGame(void) {
	int start_player;
	int dice1, dice2;
	int is_started = 0;
	char ch;
	
	do {
		yellow();
		printf("PLAYER 1... press ENTER to dice... ");
		scanf("%c", &ch);
		
		dice1 = dice();
		printf("DICE: %d\n", dice1);
		reset();
		
		blue();
		printf("PLAYER 2... press ENTER to dice... ");
		scanf("%c", &ch);
		
		dice2 = dice();
		printf("DICE: %d\n", dice2);
		reset();
		
		if (dice1 > dice2) {	
			start_player = 1;
			is_started = 1;
		}
		
		else if (dice2 > dice1) {
	 		start_player = 2;
			is_started = 1;
		}
		
		else printf("Same dice value... Please try again.\n");
		
	}while(!is_started);
	
	return start_player;
}

void check_penalty1(int player1[]);
void check_penalty2(int player2[]);
int move_player1(char map[15][30], int player1[3], int dice);
int move_player2(char map[15][30], int player2[3], int dice);

int main () {
	srand(time(NULL));
	
	char map[15][30];
	createMap(map);
	printMap(map);
	
	/* Keeps the players' informations. -> {X, Y, DIRECTION} */
	int player1[3] = {1, 1, 1};
	int player2[3] = {3, 3, 1};
	
	printf("To start the game, players should dice and decide who is going to start according to it...\n");
	int start_player = startGame();
	
	int dice1, dice2;
	int is_finished = 0;
	
	char ch;
	/* Order of players are determined according to the return value of startGame function.*/
	if (start_player == 1) {
		printf(" *** PLAYER 1 will start the game... ***\n");
		
		do {
			yellow();
			printf("PLAYER 1... press ENTER to dice... ");
			scanf("%c", &ch);
			
			dice1 = dice();
			printf("DICE: %d\n", dice1);
			reset();
			
			is_finished = move_player1(map, player1, dice1);
			
			
			if (is_finished) {
				yellow();
				printf(" *** PLAYER 1 WON THE GAME ***\n");
				reset();
				
				is_finished = 1;
			}
		
			else {
			
				blue();
				printf("PLAYER 2... press ENTER to dice... ");
				scanf("%c", &ch);
				
				dice2 = dice();
				printf("DICE: %d\n", dice2);
				
				is_finished = move_player2(map, player2, dice2);
				
				if (is_finished) {
					printf(" *** PLAYER 2 WON THE GAME ***\n");
					is_finished = 1;
				}
				reset();
			}
			
			printMap(map);
			
		}while(!is_finished);
			
	}
	
	else if (start_player == 2) {
	
		printf(" *** PLAYER 2 will start the game... ***\n");
		
		do {
			blue();
			printf("PLAYER 2... press ENTER to dice... ");
			scanf("%c", &ch);
			
			dice2 = dice();
			printf("DICE: %d\n", dice2);
			reset();
			
			is_finished = move_player2(map, player2, dice2);
			
			if (is_finished) {
				blue();
				printf(" *** PLAYER 2 WON THE GAME ***\n");
				reset();
				
				is_finished = 1;
			}
		
			else {
				yellow();
				printf("PLAYER 1... press ENTER to dice... ");
				scanf("%c", &ch);
				
				dice1 = dice();
				printf("DICE: %d\n", dice1);
				
				is_finished = move_player1(map, player1, dice1);
				
				if (is_finished) {
					printf(" *** PLAYER 1 WON THE GAME ***\n");
					is_finished = 1;
				}
				reset();
			}
			
			printMap(map);
			
		}while(!is_finished);
	}

	return 0;
}

/* 
 1) Check if player1 is on a penalty point. 
 2) If it's, then take 2 steps backward and print this information.
*/
void check_penalty1(int player1[]) {
	int x = player1[0];
	int y = player1[1];
	int is_penalty = 0;
	
	if (x==1 && y==14) {
		y = 12;
		is_penalty = 1;
	}	
	else if (x==7 && y==28) {
		x = 5;
		is_penalty = 1;
	}
	else if (x==13 && y==14) {
		y = 16;
		is_penalty = 1;
	}
	
	if (is_penalty) {
		yellow();
		printf("Penalty for player 1...\n");
		reset();
	}
	
	player1[0] = x;
	player1[1] = y;
}

/*
	1) Move the player 1 as much as dice.
	2) Then call the function 'check_penalty1' to check penalty position.
*/
int move_player1(char map[15][30], int player1[3], int dice) {
	int is_finished = 0;
	int x = player1[0];
	int y = player1[1];
	int direction = player1[2];
	
	map[x][y] = ' ';
	
	/* Iterate untill all steps are done. */
	while (dice != 0) {
		
		if (direction == right) {
			while(dice!=0 && y<28) {
				y++;
				dice--;
			}
			
			if (dice!=0) direction = down;
		}
		
		else if (direction == down) {
			while(dice!=0 && x<13) {
				x++;
				dice--;
			}
			
			if (dice!=0) direction = left;
		}
	
		else if (direction == left) {
			while(dice!=0 && y>1) {
				y--;
				dice--;
			}
			
			if (dice!=0) direction = up;
		}
	
		else if (direction == up) {
			while(dice!=0 && x>1) {
				x--;
				dice--;
			}
			
			if (x<=2) is_finished = 1;
			if (dice!=0) direction = right;
		}
	
	}
	
	player1[0] = x;
	player1[1] = y;
	player1[2] = direction;	
	check_penalty1(player1);
	
	int xfinal = player1[0];
	int yfinal = player1[1];
	map[xfinal][yfinal] = '1';
	
	
	return is_finished;
}

/* 
 1) Check if player2 is on a penalty point. 
 2) If it's, then take 2 steps backward and print this information.
*/
void check_penalty2(int player2[]) {
	int x = player2[0];
	int y = player2[1];
	int is_penalty = 0;
	
	if (x==3 && y==10) {
		y = 8;
		is_penalty = 1;
	}
	else if (x==3 && y==18) {
		y = 16;
		is_penalty = 1;
	}
	else	if (x==5 && y==26) {
		x = 3;
		is_penalty = 1;
	}
	else if (x==10 && y==26) {
		x = 8;
		is_penalty = 1;
	}
	else if (x==11 && y==10) {
		y = 12;
		is_penalty = 1;	
	}
	else if (x==11 && y==18) {
		y = 20;
		is_penalty = 1;
	}
	
	if (is_penalty) {
		blue();
		printf("Penalty for player 2...\n");
		reset();
	}
	
	player2[0] = x;
	player2[1] = y;
}

int move_player2(char map[15][30], int player2[3], int dice) {
	int is_finished = 0;
	int x = player2[0];
	int y = player2[1];
	int direction = player2[2];
	
	map[x][y] = ' ';
	
	while (dice != 0) {
		
		if (direction == right) {
			while(dice!=0 && y<26) {
				y++;
				dice--;
			}
			
			if (dice!=0) direction = down;
		}
		
		else if (direction == down) {
			while(dice!=0 && x<11) {
				x++;
				dice--;
			}
			
			if (dice!=0) direction = left;
		}
	
		else if (direction == left) {
			while(dice!=0 && y>3) {
				y--;
				dice--;
			}
			
			if (dice!=0) direction = up;
		}
	
		else if (direction == up) {
			while(dice!=0 && x>3) {
				x--;
				dice--;
			}
			
			if (x<=4) is_finished = 1;
			if (dice!=0) direction = right;
		}
	
	}
	
	player2[0] = x;
	player2[1] = y;
	player2[2] = direction;	
	check_penalty2(player2);
	
	int xfinal = player2[0];
	int yfinal = player2[1];
	map[xfinal][yfinal] = '2';
	
	return is_finished;
}

