#include <stdio.h>
#include <math.h>
#include "util.h"

/* Example decision tree - see the HW2 description */
int dt0(int t, double p, double h, int s, int w) {
    int r = 0;
    if (t>35 && w!=3) r = 1;
    else if (t<=35 && s==0) r = 1;
    return r;
}

/* 's', 'c', 'g' characters indicate "Setosa", "Versicolor", "Virginica" respectively.  */
char dt1a(double pl, double pw, double sl, double sw) {
	char result;
	if (pl<2.45) result = 's';	
	else if (pw<1.75 && pl<4.95 && pw<1.65) result = 'c';
	else result = 'g';
	
	return result;
}

char dt1b(double pl, double pw, double sl, double sw) {
	char result;
	if (pl<2.55) result = 's';
	else if (pw<1.69 && pl<4.85) result = 'c';
	else result = 'g';
	
	return result;
}
	
double dt2a(double x1, double x2, double x3, int x4, int x5) {
	double result;
	if (x1<31.5) {
		if (x2>-2.5) result = 5.0;
		else if (x2-0.1<=x1 && x1<=x2+0.1) result = 2.1;
		else result = -1.1;
	}
	
	else {
		if (-1<=x3 && x3<=2) result = 1.4;
		else if (x4 && x5) result = -2.23;
		else result = 11.0; 
	}
	
	return result;
}

double dt2b(double x1, double x2, double x3, int x4, int x5) {
	double result;
	if (12<x1 && x1<22) {
		if (x3>(double)5/3) result = -2.0;
		else if (x1-0.1<=x3 && x3<=x1+0.1) result = 1.01;
		else result = -8;
	}
	
	else {
		if (x4 && x5) result = -1;
		else if (-1<=x2 && x2<=2) result = (double)-1/7;
		else result = (double)sqrt(2)/3;
	}
	
	return result;
}

/* Problem : Classifying the resistancy of a matter using breaking rate(x1), corosion rate(x2), its type-new or old one-(x3), and sensitivity, quality categories. */

int dt3a(double x1, double x2, int x3, int sensitivity, char quality) {
	int result;
	if (x1<10) {
		if (x2<7.8) {
			if (sensitivity>=3) result = 5;
			else result = 4;
		}
		else {
			if (quality=='d' || quality=='e') result = 4;
			else result = 3;
		}	
	}
	
	else {
		if (x3==1) {
			if (x2-0.1<=x1 && x1<=x2+0.1) result = 7;
			else result = 6;
		}
		else {
			if (quality=='a') {
				if (sensitivity>=3) result = 4;
				else result = 3;
			}
			else {
				if (x2<2.3) result = 2;
				else if (sensitivity == 4) result = 2;
				else result = 1;
			}
		}
	}
	
	return result;
}

int dt3b(double x1, double x2, int x3, int sensitivity, char quality) {
	int result;
	if (4<=x1 && x1<=7) {
		if (quality=='b') {
			if (x3==1) result = 7;
			else result = 6;
		}
		else {
			if (x2>=3) {
				if (sensitivity>=7) result = 6;
				else result = 4;
			}
			else result = 4;	 
		}
	}
	
	else {
		if (4<=x2 && x2<=6) {
			if (x1<=5) result = 6;
			else result = 5;
		}
		else {
			if (sensitivity>=4) {
				if (x3==0) result = 2;
				else result = 3;
			}
			else {
				if (quality=='c' || quality=='d') result = 2;
				else result = 1;
			}
		}
	}
	
	return result;
}


/* Provide your implementations for all the requested functions here */
