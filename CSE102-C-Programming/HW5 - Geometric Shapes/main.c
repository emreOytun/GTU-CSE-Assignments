#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14

typedef enum {
	Triangle = 1, Quadrilateral, Circle, Pyramid, Cylinder
}Shapes;

typedef enum {
	Area = 1, Perimeter, Volume
}Calculators;

int check_tail_input(void);
int is_valid_triangle(float a, float b, float c);
int calc_triangle(int calc);

int calc_quadrilateral(int calc);
int calc_circle(int calc);
int calc_pyramid(int calc);	
int calc_cylinder(int calc);

int select_shape(void);
int select_calc(void);
int calculate(int (*shape_selection)(void), int (*calc_selection)(void));

int main () {
	int exit;
	do {
		printf("Welcome to the geometric calculator!\n");
		exit = calculate(select_shape, select_calc);
	}while(!exit);

	return 0;
}

/* Check if there is a non-whitespace character after the input. */
int check_tail_input(void) {
	int is_valid = 1;
	char ch;
	
	do {
		scanf("%c", &ch);
		if (ch != ' ' && ch != '\n' && ch != '	') is_valid = 0;
		
	}while(ch != '\n');

	return is_valid;
}

int select_shape(void) {
	int shape;
	int is_valid;
	char ch;
	
	printf("\nSelect a shape to calculate:\n");
	printf("-------------------------------\n");
	printf("1. Triangle\n");
	printf("2. Quadrilateral\n");
	printf("3. Circle\n");
	printf("4. Pyramid\n");
	printf("5. Cylinder\n");
	printf("0. Exit\n");
	printf("-------------------------------\n");	
	printf("Input : ");
	
	int k;
	is_valid = 0;
	do {
		is_valid = 1;
		
		k = 0;
		k = scanf("%d", &shape);
		if (k!=1) {
			is_valid = 0;
			/* Clear the buffer as reading until '\n' character. */
			scanf("%*[^\n]");
		}
		
		if (is_valid) is_valid = check_tail_input();
		
		if (is_valid) {
			switch(shape) {
			
				case Triangle :
				case Quadrilateral :
				case Circle :
				case Pyramid :
				case Cylinder :
				case 0 :
					is_valid = 1;
					break;
					
				default :
					is_valid = 0;
			}
		}
		
		if (!is_valid) {
			printf("\nERROR ! Please enter a valid entry.\n\n");
		}
		
	}while(!is_valid);

	return shape;
}

int select_calc(void) {
	int calc;
		
	printf("\nSelect calculator:\n");
	printf("-------------------------------\n");
	printf("1. Area\n");
	printf("2. Perimeter\n");
	printf("3. Volume\n");
	printf("0. Exit\n");
	printf("-------------------------------\n");
	printf("Input : ");
	
	char ch;
	int is_valid = 0;
	int k;
	do {
		is_valid = 1;
		
		k = 0;
		k = scanf("%d", &calc);
		if (k!=1) {
			is_valid = 0;
			scanf("%*[^\n]");
		}
		
		/* If number is read successfuly, then check the tail of the input. */
		if (is_valid) is_valid = check_tail_input();
		
		if (is_valid) {
			switch(calc) {
			
				case Area :
				case Perimeter :
				case Volume :
				case 0 :
					is_valid = 1;
					break;
					
				default :
					is_valid = 0;
			}
		}
		
		if (!is_valid) {
			printf("\nERROR ! Please enter a valid entry.\n\n");
		}
		
	}while(!is_valid);

	return calc;
}

/* Return the exit value, 1 if user wants to exit; 0 if user doesn't want to exit. */
int calculate(int (*shape_selection)(void), int (*calc_selection)(void)) {
	
	int exit = 0;
	int shape;
	int calc;
	
	shape = shape_selection();
	
	if (shape != 0) {
		calc = calc_selection();
	}
		
	if (shape == 0 || calc == 0) exit = 1;
	
	else {
		switch(shape) {
			case Triangle :
				calc_triangle(calc);
				break;
			
				case Quadrilateral :
				calc_quadrilateral(calc);
				break;
			
			case Circle :
				calc_circle(calc);
				break;
			
			case Pyramid : 
				calc_pyramid(calc);
				break;
			
			case Cylinder :
				calc_cylinder(calc);
				break;		
		}
	}
	
	return exit;
}

/* Validate the triangle accoring to the sides. */
int is_valid_triangle(float a, float b, float c) {
	int is_valid_triangle;
	
	if(c<a+b && b<a+c && a<b+c) is_valid_triangle = 1;
	else is_valid_triangle = 0;

	return is_valid_triangle;
}

int calc_triangle(int calc) {
	int return_value;
	/* Return -1 if the calculation cannot be done. */
	if (calc == Volume) {
			printf("\nERROR ! You cannot calculate the volume of a triangle. Please try again.\n\n");
			return_value = -1;
	}
	
	else {
		float a, b, c;
		int is_valid;
		int is_triangle_checked;
		int k;
		
		printf("\nPlease enter three sides of Triangle :\n");
		do {
			is_valid = 1;
			is_triangle_checked = 0;
			
			/* Read a. */
			k = 0;
			k = scanf("%f", &a);
			if (k != 1) {
				is_valid = 0; 
				scanf("%*[^\n]");
			}
				
			/* If a is read, then read b. */
			if (is_valid == 1) {
			
				k = 0;
				k = scanf("%f", &b);
				if (k != 1) {
					is_valid = 0; 
					scanf("%*[^\n]");
				}
			
				/* If b is read, then read c. */
				if (is_valid == 1) {
			
					k = 0;
					k = scanf("%f", &c);
					if (k != 1) {
						is_valid = 0; 
						scanf("%*[^\n]");				
					}
							
					/* Check if there is a character after the last input. */
					if(is_valid) is_valid = check_tail_input();
					
					if (is_valid && (a<=0 || b<=0 || c<=0)) is_valid = 0;
					
					if (is_valid && is_valid_triangle(a, b, c) == 0) {
						is_valid = 0;
						is_triangle_checked = 1;
						printf("\nERROR ! Please enter a valid triangle.\n\n");
					}
				}				
			}
		
			if (is_triangle_checked == 0 && is_valid == 0) {
				printf("\nERROR ! Please enter a valid entry.\n\n");
			}
	
		}while(!is_valid);
		
			
		float s;
		float area;
		float perimeter;
	
		switch(calc) {
		
			case Area :
				s = (a+b+c) / 2;
				area = sqrt(s*(s-a)*(s-b)*(s-c));
				printf("\nArea of TRIANGLE : %.2f\n\n", area);
				return_value = 1;
				break;
			
			case Perimeter :
				perimeter = a + b + c;
				printf("\nPerimeter of TRIANGLE : %.2f\n\n", perimeter);
				return_value = 1;
				break;
		}
	}
	
	return return_value;
}

int calc_quadrilateral(int calc) {
	int return_value;
	
	if (calc == Volume) {
		printf("\nERROR ! You cannot calculate the volume of a quadrilateral. Please try again.\n\n");
		return_value = -1;
	}
	
	else {
		float a, b, c, d;
		int is_valid;
		int k;
		
		printf("\nPlease enter four sides of Quadrilateral\n");
		do {
			is_valid = 1;
			
			/* Read a. */	
			k = 0;
			k = scanf("%f", &a);
			if (k != 1) {
				is_valid = 0; 
				scanf("%*[^\n]");
			}
				
			/* If a is read, then read b. */
			if (is_valid == 1) {
				
				k = 0;
				k = scanf("%f", &b);
				if (k != 1) {
					is_valid = 0; 
					scanf("%*[^\n]");
				}
				
				/* If b is read, then read c. */
				if (is_valid == 1) {
				
					k = 0;
					k = scanf("%f", &c);
					if (k != 1) {
						is_valid = 0; 
						scanf("%*[^\n]");	
					}
					
					/* If c is read, then read d. */				
					if (is_valid == 1) {
						
						k = 0;
						k = scanf("%f", &d);
						if (k != 1) {
							is_valid = 0;
						 	scanf("%*[^\n]");
						}
						 	
						if(is_valid) is_valid = check_tail_input();
						
						if (is_valid && (a<=0 || b<=0 || c<=0 || d<=0)) is_valid = 0;	
					
					}
				}			
			}
		
			if (is_valid == 0) {
				printf("\nERROR ! Please enter a valid entry.\n\n");
			}
			
		}while(!is_valid);		
			
		float s;
		float area;
		float brahmagupta = (s-a)*(s-b)*(s-c)*(s-d);
		float perimeter;
		
		switch(calc) {
		
			case Area :
			
				s = (a+b+c+d) / 2;
				brahmagupta = (s-a)*(s-b)*(s-c)*(s-d);
				
				if (brahmagupta <= 0) {
					printf("\nERROR ! Area can not be calculated.\n\n");
					return_value = -1;
				}
				
				else {
					area = sqrt((s-a)*(s-b)*(s-c)*(s-d));
					printf("\nArea of QUADRILATERAL : %.2f\n\n", area);
					return_value = 1;
				}
				break;
				
			case Perimeter :
			
				perimeter = a+b+c+d;
				printf("\nPerimeter of QUADRILATERAL : %.2f\n\n", perimeter);
				return_value = 1;
				break;	
		}
		
	}

	return 0;
}

int calc_circle(int calc) {
	int return_value;
	
	if (calc == Volume) {
		printf("\nERROR! You cannot calculate the volume of a Circle. Please try again.\n\n");
		return_value = -1;
	}
	
	else {
		float r;
		int is_valid = 0;
		int k;
		
		printf("\nPlease enter the radius of Circle :\n");
		do {
			is_valid = 1;
			
			/* Read r */
			k = 0;
			k = scanf("%f", &r);
			if (k != 1) {
				is_valid = 0; 
				scanf("%*[^\n]");
			}
			
			if (is_valid) is_valid = check_tail_input();
				
			if (is_valid && r<=0) is_valid = 0;	
			
			if (is_valid == 0) {
				printf("\nERROR ! Please enter a valid entry.\n\n");
			}
	
		}while(!is_valid);	

		float area;
		float perimeter;
	
		switch(calc) {
			
			case Area :
				area = PI*r*r;
				printf("\nArea of CIRCLE : %.2f\n\n", area);
				return_value = 1;
				break;
				
			case Perimeter :
				perimeter = 2*PI*r;
				printf("\nPerimeter of CIRCLE : %.2f\n\n", perimeter);
				return_value = 1;
				break;
		}
	}
	
	return return_value;
}

int calc_pyramid(int calc) {

	float a, h;
	float slant_height;
	int is_valid;
	int k;
	
	switch (calc) {
	
		case Area :
		case Perimeter :
			
			printf("\nPlease enter the base side and the slant height of a Pyramid :\n");
			do {
				is_valid = 1;
				
				/* Read a. */
				k = 0;
				k = scanf("%f", &a);
				if (k != 1) {
					is_valid = 0; 
					scanf("%*[^\n]");
				}
			
				/* If a is read, then read h. */
				if (is_valid == 1) {
					
					k = 0;
					k = scanf("%f", &slant_height);
					if (k != 1) {
						is_valid = 0; 
						scanf("%*[^\n]");
					}
						
					if (is_valid) is_valid = check_tail_input();
					
					if (is_valid && (a<=0 || h<=0)) is_valid = 0;	
				}
				
				if (is_valid == 0) {
					printf("\nERROR ! Please enter a valid entry.\n\n");
				}
			
			}while(!is_valid);
			break;
	
		case Volume :
			
			printf("\nPlease enter the base side and height of a Pyramid :\n");
			do {
				is_valid = 1;
				
				k = 0;
				k = scanf("%f", &a);
				if (k != 1) {
					is_valid = 0; 
					scanf("%*[^\n]");
				}
			
				/* If a is read, then read h. */
				if (is_valid == 1) {
				
					k = 0;
					k = scanf("%f", &h);	
					if (k != 1) {
						is_valid = 0; 
						scanf("%*[^\n]");
					}
						
					if (is_valid) is_valid = check_tail_input();
					
					if (is_valid && (a<=0 || h<=0)) is_valid = 0;	
				}
				
				if (is_valid == 0) {
					printf("\nERROR ! Please enter a valid entry.\n\n");
				}
			
			}while(!is_valid);
	
	}

	float base_surface_area;
	float lateral_surface_area;
	float surface_area;
	
	float perimeter;
	float diagonal_length;
	float lateral_edge_length;
	
	float volume;
	
	switch(calc) {
			
		case Area :
			base_surface_area = a*a;
			lateral_surface_area = 2*a*slant_height;
			surface_area = base_surface_area + lateral_surface_area;
			
			printf("\nBase Surface Area of PYRAMID : %.2f\n\n", base_surface_area);
			printf("\nLateral Surface Area of PYRAMID : %.2f\n\n", lateral_surface_area);
			printf("\nSurface Area of PYRAMID : %.2f\n\n", surface_area);
			break;
			
		case Perimeter :
			
			perimeter = 4*a;
			printf("\nBase Surface Perimeter of PYRAMID : %.2f\n\n", perimeter);
			break;
	
		case Volume :
			volume = a*a*h/3;
			printf("\nVolume of PYRAMID : %.2f\n\n", volume);
			break;
	}
	
	return 0;
}

int calc_cylinder(int calc) {

	float r, h;
	int is_valid = 0;
	int k;
	
	printf("\nPlease enter the radius and height of a Cylinder :\n");
	do {
		is_valid = 1;
		
		/* Read r */
		k = 0;
		k = scanf("%f", &r);
		if (k != 1) {
			is_valid = 0; 
			scanf("%*[^\n]");
		}
		
		/* If r is read, then read h. */
		if (is_valid == 1) {
			
			k = 0;
			k = scanf("%f", &h);
			if (k != 1) {
				is_valid = 0; 
				scanf("%*[^\n]");
			}
			
			if (is_valid) is_valid = check_tail_input();	
			
			if (is_valid && (r<=0 || h<=0)) is_valid = 0;
		}
		
		if (is_valid == 0) {
			printf("\nERROR ! Please enter a valid entry.\n\n");
		}
	
	}while(!is_valid);	

	float base_area;
	float lateral_area;
	float surface_area;
	
	float perimeter;
	float volume;

	switch(calc) {
	
		case Area :
			base_area = PI*r*r;
			lateral_area = 2*PI*r*h;
			surface_area = 2*base_area + lateral_area;
			
			printf("\nBase Surface Area of CYLINDER : %.2f\n\n", base_area);
			printf("\nLateral Surface Area of CYLINDER : %.2f\n\n", lateral_area);
			printf("\nSurface Area of CYLINDER : %.2f\n\n", surface_area);
			break;
			
		case Perimeter :
			perimeter = 2*PI*r;
			printf("\nBase Surface Perimeter of CYLINDER : %.2f\n\n", perimeter);
			break;
			
		case Volume :
			volume = PI*r*r*h;
			printf("\nVolume of CYLINDER : %.2f\n\n", volume);
			break;
	}

	return 0;
}
