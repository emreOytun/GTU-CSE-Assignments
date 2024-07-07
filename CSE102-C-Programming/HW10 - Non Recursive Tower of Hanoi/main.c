#include <stdio.h>
#include <stdlib.h>

#define STACK_BLOCK_SIZE 10

typedef struct {
	int n;
	int start;
	int aux;
	int end;
	int where_in_function;
}fun_variables_t;

typedef struct {
	fun_variables_t *array;
	int currentsize;
	int maxsize;
}stack;

stack *init_return();
int init(stack *s);
void copy_function_variables(fun_variables_t *fun1, fun_variables_t *fun2);
int push(stack *s, fun_variables_t fun_input);
fun_variables_t pop(stack *s);
void hanoi_solver(int n);


int main () {
	int n;
	printf("Enter Tower size:");
	scanf("%d", &n);
		
	hanoi_solver(n);
	
	return 0;		
}

stack* init_return() {
	stack *empty_stack = (stack*) malloc(sizeof(stack));
	
	empty_stack->array = calloc(STACK_BLOCK_SIZE, sizeof(fun_variables_t));
	empty_stack->currentsize = 0;
	empty_stack->maxsize = STACK_BLOCK_SIZE;

	return empty_stack; 
}

int init(stack *s) {
	int is_initialized;

	if (s->array != NULL && s->currentsize == 0 && s->maxsize == STACK_BLOCK_SIZE) is_initialized = 1;
	else is_initialized = 0;
	
	return is_initialized;
}

void copy_function_variables(fun_variables_t *fun1, fun_variables_t *fun2) {
	fun1->n = fun2->n;
	fun1->start = fun2->start;
	fun1->aux = fun2->aux;
	fun1->end = fun2->end;
	fun1->where_in_function = fun2->where_in_function;
} 

int push(stack *s, fun_variables_t fun_input) {
	int is_pushed;
	int push_index;
	int i;
	
	fun_variables_t *new_arr;
	int new_limit;
	
	/* If the given array is empty, then initialize array. */
	if (s->array == NULL) {
	
		new_limit = STACK_BLOCK_SIZE;
		s->array = (fun_variables_t*) calloc(new_limit, sizeof(fun_variables_t));
		s->maxsize = new_limit;
		
		/* Push incoming fun_input to the stack's new_node */
		copy_function_variables(&s->array[0], &fun_input);
		
		/* Increment currentsize. */
		s->currentsize = 1;
		is_pushed = 1;
		
	}
	
	else {
		
		/* Check if the stack is full; if it is, then grow the array. */
		if (s->currentsize == s->maxsize) {
			new_limit = s->maxsize + STACK_BLOCK_SIZE;
			new_arr = (fun_variables_t*) calloc(new_limit, sizeof(fun_variables_t));
			s->maxsize = new_limit;
			
			/* Copy the old array into new array. */
			for (i=0; i<s->currentsize; i++) copy_function_variables(&new_arr[i], &s->array[i]);
			free(s->array);
			
			s->array = new_arr;
		}
		
		/* Push disk. */
		push_index = s->currentsize;
		copy_function_variables(&s->array[push_index], &fun_input);
		
		/* Increment currentsize. */
		s->currentsize += 1;
		is_pushed = 1;
	}
	
	
	return is_pushed;
}

fun_variables_t pop(stack *s) {
	fun_variables_t poped_fun;
	int pop_index;
	int i;

	fun_variables_t *new_arr;
	int new_limit;

	/* If stack is empty, then there is no number to be poped. Return -1. */
	if (s->currentsize == 0) {
		poped_fun.n = -1;
		poped_fun.start = -1;
		poped_fun.aux = -1;
		poped_fun.end = -1;
	}
	
	else {
	
		/* Get the poped value and decrement the currentsize by 1. */
		pop_index = s->currentsize - 1;
		copy_function_variables(&poped_fun, &s->array[pop_index]);
		
		s->currentsize -= 1;
		
		/* If currentsize is 0 after poping process, update stack. */
		if (s->currentsize == 0) {
			free(s->array);
			
			s->array = NULL;
			s->maxsize = 0;
			
		}
		
		else if (s->currentsize % STACK_BLOCK_SIZE == 0) {
			new_limit = s->maxsize - STACK_BLOCK_SIZE;
			new_arr = (fun_variables_t*) calloc(new_limit, sizeof(fun_variables_t));
			s->maxsize = new_limit;
			
			for (i=0; i<s->currentsize; i++) copy_function_variables(&new_arr[i], &s->array[i]);	
			free(s->array);
			s->array = new_arr;
		}
			
	}
	
	return poped_fun;
}

void hanoi_solver(int n) {
	stack *fun_stack = NULL;
	
	/* Initialize the fun_stack. */
	do {	
		if (fun_stack != NULL) free(fun_stack);
		fun_stack = init_return();	
	}while(init(fun_stack) == 0);

	int temp;		
	int is_solved = 0;
	
	fun_variables_t cur_fun;
	/* Initialize the cur_fun and push it into the fun_stack. */
	cur_fun.n = n;
	cur_fun.start = 1;
	cur_fun.aux = 2;
	cur_fun.end = 3;
	
	cur_fun.where_in_function = 1;
	push(fun_stack, cur_fun);
	
	if (n <= 0) {
		printf("Tower size must be positive.\n");
		is_solved = 1;
	}
	
	while (is_solved == 0) {
	
		/* Get the current function. */
		cur_fun = pop(fun_stack);
		
		/* If there is no function anymore, then the process is done. */
		if (cur_fun.n == -1) is_solved = 1;
	
		/* Simulate the base condition. */
		else if (cur_fun.n == 1) {
			printf("Move the disk 1 from '%d' to '%d'\n", cur_fun.start, cur_fun.end);
		}
		
		else {
		
			switch(cur_fun.where_in_function) {
			
				case 1 :
					/* Before pushing the current function again, update it's position and push it. */
					cur_fun.where_in_function = 2;
					push(fun_stack, cur_fun);
					
					/* Update and Push the next function just like function call in recursive to simulate. */
					/* Change end pole and aux pole. */
					cur_fun.n -= 1;
					temp = cur_fun.end;
					cur_fun.end = cur_fun.aux;
					cur_fun.aux = temp;
					
					cur_fun.where_in_function = 1;
					push(fun_stack, cur_fun);
					
					break;
					
				case 2 :
					printf("Move the disk %d from '%d' to '%d'\n", cur_fun.n, cur_fun.start, cur_fun.end);
				
					/* It's no needed to push the current function again, because it won't do anything after returning from other functions. */
					
					/* Update and Push the next function. */
					/* Change start pole and aux pole. */
					cur_fun.n -= 1;
					temp = cur_fun.start;
					cur_fun.start = cur_fun.aux;
					cur_fun.aux = temp;	
					
					cur_fun.where_in_function = 1;
					push(fun_stack, cur_fun);
					
					break;
			}
		}
		
	}
	
	if (fun_stack != NULL) free(fun_stack);
	
}

