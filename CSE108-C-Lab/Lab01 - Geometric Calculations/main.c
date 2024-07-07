#include <stdio.h>
#define PI 3.14

void midPoint(double x1, double y1, double x2, double y2) {
	double midX = (x1+x2) / 2;
	double midY = (y1+y2) / 2; 
	printf("Mid point M(x,y) = (%.1lf,%.1lf)\n", midX, midY);
}

void slope(double x1, double y1, double x2, double y2) {
	double slope = (y2-y1) / (x2-x1);
	printf("Slope : m = (%.1lf)\n", slope);
}

void area(int x1, int y1, int x2, int y2) {
	double	diameter_sqr = (x2-x1)*(x2-x1) + (y2-y1)*(y2-y1); /* Since we don't use sqr funct, it's enough to find squre of diameter.((2r)^2 = 4r2 ) */
	double radius_sqr = diameter_sqr / 4; /* r^2 = 4r^2 / 4*/
	double area = PI * radius_sqr;
	printf("Area: A = %.1lf\n", area);
}


int main() {
	int x1,y1;
	int x2,y2;
	
	printf("x1 : ");
	scanf("%d", &x1);
	
	printf("y1 : ");
	scanf("%d", &y1);
	
	printf("x2 : ");
	scanf("%d", &x2);
	
	printf("y2 : ");
	scanf("%d", &y2);
	
	midPoint(x1, y1, x2, y2);
	slope(x1, y1, x2, y2);	
	area(x1, y1, x2, y2);
	
	return 0;
} 
