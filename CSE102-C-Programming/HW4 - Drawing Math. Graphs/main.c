#include <stdio.h>

void write_file(int a, int b, int c);
int draw_graph(void);
int draw_graph_to_text(void);

/* Set color to yellow. */
void yellow (void){
	printf("\033[1;33m");
}

/* Set color to blue. */
void blue (void){
	printf("\033[0;34m");
}

/* Reset the printing color. */
void reset (void) {
	printf("\033[0m");
}

/* Clear buffer if input is entered false like the time when user enters a character instead of number. */
void clear_buffer(void) {
	char ch;
	while (ch = getchar() != '\n');
}

int main () {

	int choice;
	int a, b, c;
	int return_value;
	
	int exit = 0;
	int is_input_taken;
	char ch;
	
	do {
	
		printf("Select an operation...\n");
		printf("0 -> Enter the coefficients.\n");
		printf("1 -> Draw the graph.\n");
		printf("2 -> Print the graph into a .txt file.\n");
		printf("3 -> Exit\n\n");
		
		do {
			printf("Choice: ");
			
			if (! (scanf("%d%c", &choice, &ch) && ch == '\n')) {
				printf("Error : You entered an invalid input. Please try again...\n\n");
				is_input_taken = 0;
				clear_buffer();
			}
			
			else if (choice == 0 || choice == 1 || choice == 2 || choice == 3) is_input_taken = 1;
			
			else {
				printf("Error : You should enter a number between 0-3. Please try again...\n\n");
				is_input_taken = 0;
			}
			
		}while(is_input_taken == 0);
		
		
		switch(choice) {
			
			case 0 :
				printf("\nPlease enter the coefficient for the following equation: x=a*(y*y) + b*y + c\n\n");	
				
				do {
					printf("a: ");
					if (scanf("%d%c", &a, &ch) == 2 && ch == '\n') is_input_taken = 1;
					
					else {
						printf("Error : You entered an invalid input. Please try again...\n\n");
						is_input_taken = 0;
						clear_buffer();
					}
					
				}while(is_input_taken == 0);
				
				do {
					printf("b: ");
					if (scanf("%d%c", &b, &ch) == 2 && ch == '\n') is_input_taken = 1;
					
					else {
						printf("Error : You entered an invalid input. Please try again...\n\n");
						is_input_taken = 0;
						clear_buffer();
					}
					
				}while(is_input_taken == 0);
				
				do {
					printf("c: ");
					if (scanf("%d%c", &c, &ch) == 2 && ch == '\n') is_input_taken = 1;
					
					else {
						printf("Error : You entered an invalid input. Please try again...\n\n");
						is_input_taken = 0;
						clear_buffer();
					}
					
				}while(is_input_taken == 0);		
				
				write_file(a, b, c);
				printf("coefficients.txt file has been created.\n\n");
				break;
	
			case 1 :
				return_value = draw_graph();
				if (return_value == -1) printf("Warning : coefficients.txt file has not been created yet.\n\n");
				break;
		
			case 2 :
				return_value = draw_graph_to_text();
				if (return_value == -1) printf("Warning : coefficients.txt file has not been created yet.\n\n");
				break;
		
			case 3 : 
				printf("Program is closed ...\n");
				exit = 1;
		}
		
	}while(!exit);

	return 0;
}

/* Write coeffiecinets to the file. */
void write_file(int a, int b, int c) {
	FILE *file = fopen("coefficients.txt", "w");	
	fprintf(file, "%d\n", a);
	fprintf(file, "%d\n", b);
	fprintf(file, "%d\n", c);
		
	fclose(file);
}

/* Check if a point with its coordinates is on the graph with coefficients a, b, c */
int is_point_of_graph(int x, int y, int a, int b, int c) {
	int is_point_of_graph = 0;
	
	int x_calculated = a*(y*y) + b*y + c;
	if (x_calculated == x) is_point_of_graph = 1;
	else is_point_of_graph = 0;
	
	return is_point_of_graph;  
}

/* Calculate how many character required to print a number on the graph. */
int calculate_character_num(int num) {
	int character_num = 0;
	
	/* For '-' sign. */
	if (num < 0) character_num++;
	
	do {
		num = num / 10;
		character_num++;
	}while(num != 0);

	return character_num;
}

/* Draw y=-1 part of the graph, write the x-axis numbers. */
void draw_under_x_axis(int x, int y, int a, int b, int c) {

	if (x % 10 == 0) {
							
		int character_num = calculate_character_num(x);
		
		/* For writing 0 at origin */			
		if (x == 0) {	
			int x1 = x;
			int x2 = x - 1;
					
			int is_x2_on_graph = is_point_of_graph(x2, y, a, b, c);
					
			if (is_x2_on_graph == 1) {
				yellow();
				printf("\b\b0");
				
				blue();
				printf("#");
				reset();
					
				printf("|");	
			}
					
			else {
				int is_x1_on_graph = is_point_of_graph(x1, y, a, b, c);
			
				yellow();	
				printf("\b0");
				reset();
						
				if (is_x1_on_graph == 1) {
					blue();
					printf("#");
					reset();
				}
				else printf("|");
			}
		}
		
		/* If number has 2 characters like number 10, occupy 3 blocks/points and check them whether they're on the graph or not. */					
		if (character_num == 2) {
			int x1 = x;
			int x2 = x - 1;
			int x3 = x - 2;
								
			int is_x1_on_graph = is_point_of_graph(x1, y, a, b, c);
			int is_x2_on_graph = is_point_of_graph(x2, y, a, b, c);
			int is_x3_on_graph = is_point_of_graph(x3, y, a, b, c);
					
			if (is_x2_on_graph == 1) {
				yellow();
				printf("\b\b\b%d", x);	
				reset();
						
				blue();
				printf("#");
				printf(" ");
				reset();
			}
								
			else if (is_x3_on_graph == 1) {
				yellow();
				printf("\b%d", x);	
					reset();
			}
								
			else {
				yellow();
				printf("\b\b%d", x);
				reset();
							
				if (is_x1_on_graph == 1) {
					blue();
					printf("#");
					reset();
				}
				else printf(" ");
			}
		}
		
		/* If number has 3 characters like number -10, occupy 4 blocks/points and check them whether they're on the graph or not. */
		if (character_num == 3) {
			int x1 = x;
			int x2 = x - 1;
			int x3 = x - 2;
			int x4 = x - 3;
					
			int is_x1_on_graph = is_point_of_graph(x1, y, a, b, c);
			int is_x2_on_graph = is_point_of_graph(x2, y, a, b, c);
			int is_x3_on_graph = is_point_of_graph(x3, y, a, b, c);
			int is_x4_on_graph = is_point_of_graph(x4, y, a, b, c);
					
			if (is_x2_on_graph == 1) {
				yellow();	
				printf("\b\b\b\b%d", x);
						
				blue();
				printf("#");
				printf(" ");
				reset();
			}
						
			else if (is_x3_on_graph == 1) {
				yellow();	
				printf("\b\b\b\b\b%d", x);
						
				blue();
				printf("#");
				printf(" ");
				printf(" ");
				reset();
			}
						
			else if (is_x4_on_graph == 1) {	
				yellow();
				printf("\b\b%d", x);
				reset();
			}
						
			else {	
				yellow();
				printf("\b\b\b%d", x);
				reset();
							
				if (is_x1_on_graph == 1) {
					blue();
					printf("#");	
					reset();
				}
				
				else printf(" ");
			}			
		}				
	}
	
	/* If axis-number will not be written, then just check if the point is on the graph or not. */
	else {
		int is_on_graph = is_point_of_graph(x, y, a, b, c);
		if (is_on_graph == 1) {
			blue();
			printf("#");
			reset();	
		}
		
		else printf(" ");
	}
	
}

void draw_y_axis_and_numbers(int x, int y, int a, int b, int c) {
	/* Print the numbers on y-axis in this block of code. When y=0, 0 can not be written at the left-side of origin.*/
	if (y != 0 && y % 5 == 0) {
		int character_num = calculate_character_num(y);
						
		if (character_num == 1) {
		/* Occuppy 2 points from the left-side of y-axis. (1 for space 1 for number). */
			int x2 = x - 2;
			int x1 = x - 1;
				
			int is_x1_on_graph = is_point_of_graph(x1, y, a, b, c);
			int is_x2_on_graph = is_point_of_graph(x2, y, a, b, c);
						
			/* If the point of character of the number(x) is on graph, then write the number at 1 right of the point where it should be. */
			if (is_x2_on_graph == 1) {
				yellow();
				printf("\b%d", y);
				reset();
			}
					
		/* If the point of character of the number is not on the graph, then write the number; and check if the point at just left of the y-axis is on the graph. */
			else {
				yellow();
				printf("\b\b%d", y);
				reset();
				
				if (is_x1_on_graph == 1) {
					blue();
					printf("#");	
					reset();
				}
				else printf(" ");
			}
		}
			
		if (character_num == 2) {
			/* Occuppy 3 points from the left-side of y-axis. (1 for space 2 for number). */
			int x3 = x - 3;
			int x2 = x - 2;
			int x1 = x - 1;
			
			int is_x1_on_graph = is_point_of_graph(x1, y, a, b, c);
			int is_x2_on_graph = is_point_of_graph(x2, y, a, b, c);
			int is_x3_on_graph = is_point_of_graph(x3, y, a, b, c);
				
			if (is_x3_on_graph == 1) {
				yellow();
				printf("\b\b%d", y);
				reset();
			}
					
			else if (is_x2_on_graph == 1) {
				yellow();
				printf("\b\b\b\b%d", y);
			
				blue();
				printf("#");
				printf(" ");
				reset();
			}
						
			else {
				yellow();
				printf("\b\b\b%d", y);
				reset();
					
				if (is_x1_on_graph == 1) {
					blue();
					printf("#");
					reset();
				}
				else printf(" ");
			}
							
		}
					
		if (character_num == 3) {
			/* Occuppy 4 points from the left-side of y-axis. (1 for space, 3 for number) */
			int x4 = x - 4;	
			int x3 = x - 3;
			int x2 = x - 2;
			int x1 = x - 1;
							
			int is_x1_on_graph = is_point_of_graph(x1, y, a, b, c);
			int is_x2_on_graph = is_point_of_graph(x2, y, a, b, c);
			int is_x3_on_graph = is_point_of_graph(x3, y, a, b, c);
			int is_x4_on_graph = is_point_of_graph(x4, y, a, b, c);
						
			if (is_x4_on_graph == 1) {
				yellow();
				printf("\b\b\b%d", y);
				reset();
			}
				
			else if (is_x3_on_graph == 1) {
				yellow();
				printf("\b\b\b\b\b\b%d" , y);
					
				blue();
				printf("#");
				printf("  ");
				reset();
			}
			
			else if (is_x2_on_graph == 1) {
				yellow();
				printf("\b\b\b\b\b%d", y);
						
				blue();
				printf("#");
				printf(" ");
				reset();
			}
				
			else {
				yellow();
				printf("\b\b\b\b%d", y);
				reset();
				
				if(is_x1_on_graph == 1) {
					blue();
					printf("#");	
					reset();
				}
				else printf(" ");
			}		
		}				
	}
					
	/* Draw the y-axis here. Put '|' or '#'. */	
	int is_on_graph = is_point_of_graph(x, y, a, b, c);				
	if (!is_on_graph) printf("|");
	else {
		blue();
		printf("#");
		reset();
		
	}

}

/* Draw x-axis in this function. Put '-' or '#' according to the graph. */
void draw_x_axis(int x, int y, int a, int b, int c) {

	int is_on_graph = is_point_of_graph(x, y, a, b, c);	
	if(!is_on_graph) printf("-");
	else {
		blue();
		printf("#");
		reset();
	}
}

int draw_graph(void) {
	
	FILE *file = fopen("coefficients.txt", "r");
	int return_value;
	int a, b, c;
	
	/* Return -1 if the file has not been created yet. */
	if (file == NULL) return_value = -1;
	
	else {
		fscanf(file, "%d\n", &a);
		fscanf(file, "%d\n", &b);
		fscanf(file, "%d\n", &c);	
		printf("Coefficients has been read from the coefficient.txt file.\n");
		printf("Printing the graph of x=%d*(y*y) + %d*y + %d\n\n", a, b, c);
		int x, y;
		
		for (y=16; y>=-15; y--) {
			for (x=-56; x<=56; x++) {
				/* Determine the borders of the graph. */
				if (x == -56 && y == 0) printf("<");
				else if (x == 56 && y == 0) printf(">");
				else if (y == 16 && x == 0) printf("^"); 
								
				else if (y == -1) draw_under_x_axis(x, y, a, b, c);
					
				/* Draw y-axis (x=0) in this block of code. The x=0 and y=-1 case will be handled by another block of code that prints numbers on x-axis. */
				else if (x == 0) draw_y_axis_and_numbers(x, y, a, b, c);				
					
				/* Draw the x-axis here, put '-' or '#'. */
				else if (y == 0) draw_x_axis(x, y, a, b, c);
				
				/* If the point is not on the special places like x=0, y=0 and y=-1; then put '#' or ' ' according to the result. */
				else {
					int is_on_graph = is_point_of_graph(x, y, a, b, c);
					if (is_on_graph == 1) {
						blue();
						printf("#");
						reset();
					}
					else printf(" ");
				
				}
			}
			printf("\n");
		}	
		fclose(file);	
		return_value = 1;
	}
	
	return return_value;
}


int draw_graph_to_text(void) {
	
	FILE *file = fopen("coefficients.txt", "r");
	int return_value;
	int a, b, c;
	
	/* Return -1 if the file has not been created yet. */
	if (file == NULL) return_value = -1;
	
	else {
		FILE *text = fopen("graph.txt", "w");
		fscanf(file, "%d\n", &a);
		fscanf(file, "%d\n", &b);
		fscanf(file, "%d\n", &c);
		printf("Coefficients has been read from the coefficient file.\n");
		printf("The graph of x=%d*(y*y) + %d*y + %d has been written to graph.txt file.\n\n", a, b, c);
		int x, y;
		
		for (y=16; y>=-15; y--) {
			for (x=-56; x<=56; x++) {
			
				/* Determine the borders of the graph. */
				if (x == -56 && y == 0) fprintf(text, "<");
				else if (x == 56 && y == 0) fprintf(text, ">");
				else if (y == 16 && x == 0) fprintf(text, "^"); 
				
				/* Draw y-axis (x=0) in this block of code. The x=0 and y=-1 case will be handled by another block of code that prints numbers on x-axis. */
				else if (x == 0) {			
					/* Draw the y-axis here. Put '|' or '#'. */
					int is_on_graph = is_point_of_graph(x, y, a, b, c);				
					if (!is_on_graph) fprintf(text, "|");
					else fprintf(text, "#");
				}
				
				/* Draw the x-axis here, put '-' or '#'. */
				else if (y == 0) {		
					int is_on_graph = is_point_of_graph(x, y, a, b, c);
					if(!is_on_graph) fprintf(text, "-");
					else fprintf(text, "#");	
				}
				
				/* If the point is not on the special places like x=0, y=0 and y=-1; then put '#' or ' ' according to the result. */
				else {
					int is_on_graph = is_point_of_graph(x, y, a, b, c);
					if (is_on_graph == 1) fprintf(text, "#");
					else fprintf(text, " ");
				}
			}
			
			fprintf(text, "\n");
		}	
		
		fclose(file);
		fclose(text);		
		return_value = 1;	
	}
	
	return return_value;
}

