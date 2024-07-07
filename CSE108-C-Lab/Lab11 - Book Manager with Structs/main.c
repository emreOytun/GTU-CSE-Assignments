#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char title[50];
	char author[50];
	char subject[50];
	int year;	
	int id;
}book_t;

/* Copy one book to another. */
void copy_book(book_t *book1, book_t *book2) {
	strcpy(book1->title, book2->title);
	strcpy(book1->author, book2->author);
	strcpy(book1->subject, book2->subject);
	book1->year = book2->year;
}

/* Add books into the given list. */
void add_book(book_t **book_list, int *limit, int *n, book_t new_book) {
	
	/* If there is no book in the list then calloc. */
	if (*limit == 0) {
		*limit = 2;
		*book_list = (book_t*) calloc(2, sizeof(book_t));
	
		*n = 1;
		copy_book(&(*book_list)[0], &new_book);
		printf("Book is added.\n");
	}
	
	/* If arr is full, update the limit and calloc new area/list. */
	else if (*limit == *n) {
		int new_limit = *limit * 2;
		book_t *new_list = (book_t*) calloc(sizeof(book_t), new_limit);
		
		int i;
		for (i=0; i<*n; i++) {
			copy_book(&new_list[i], &(*book_list)[i]);
		}
		
		*n += 1;
		copy_book(&new_list[*n-1], &new_book);
		
		free(*book_list);
		*book_list = new_list;
		
		printf("Book is added. --- LIMIT UPDATED.\n");
	}
	
	else {
		*n += 1;
		copy_book(&(*book_list)[*n-1], &new_book);
		
		printf("Book is added.\n");	
		
	}
	
}

/* Print a given book in book_t. */
void print_book(book_t *book) {
	printf("Title : %s\n", book->title);
	printf("Author : %s\n", book->author);
	printf("Subject : %s\n", book->subject);
	printf("Year = %d\n", book->year);
}

/* Look for the book which has the given title in the given list. */
void get_by_title(book_t *book_list, int n, char title[]) {
	int i, is_found;
	for (i=0, is_found = 0; i<n && is_found == 0; i++) {
		if (strcmp(book_list[i].title, title) == 0) {
			printf("\nBook is found.\n");
			print_book(&book_list[i]);
			
			is_found = 1;
		}
	}
	
	if (!is_found) printf("\nBook is not found.\n");
}

/* Clear buffer for reading strings. */
void clear_buffer(void) {
	char ch;
	do {
		ch = getchar();
	}while(ch != '\n' && ch != EOF);
}

/* Sort structs/books by year by keeping and index_map. */
void print_sorted_list(book_t *book_list, int n) {
	int ind_map[n];
	int i, j;
	int max_i;
	
	// Fill the index_map
	for (i=0; i<n; i++) ind_map[i] = i;
	
	for (i=0; i<n; i++) {
		// Take the starting position in ind_map as the max element's index.
		max_i = i;
		
		for (j=i+1; j<n; j++) {
			int max_real_index = ind_map[max_i];
			int cur_index = ind_map[j];
			
			if (book_list[cur_index].year > book_list[max_real_index].year) max_i = j;
		}
		
		int temp = ind_map[max_i];
		ind_map[max_i] = ind_map[i];
		ind_map[i] = temp;
		
	}
	
	for(i=0; i<n; i++) {
		int cur_i = ind_map[i];
		print_book(&book_list[cur_i]);
		printf("********************\n");
	}
}

/* Look for the book which has the given author in the given list. */
void get_by_author(book_t *book_list, int n, char author[]) {
	int i, is_found;
	for (i=0, is_found=0; i<n && is_found == 0; i++) {
		if ( strcmp(book_list[i].author, author) == 0  ) {
			printf("Book is found.\n");
			is_found = 1;
			
			print_book(&book_list[i]);
		}
	}
	
	if (!is_found) {
		printf("Book is not found.\n");
	}
}

/* Look for the book which has the given subject in the given list. */
void get_by_subject(book_t *book_list, int n, char subject[]) {
	int i, is_found;
	for (i=0, is_found=0; i<n && is_found == 0; i++) {
		if ( strcmp(book_list[i].subject, subject) == 0  ) {
			printf("Book is found.\n");
			is_found = 1;
			
			print_book(&book_list[i]);
		}
	}
	
	if (!is_found) {
		printf("Book is not found.\n");
	}
}

/* Print a given list. */
void print_list(book_t *book_list, int n) {
	printf("\nList of Books \n**********************\n");
	
	int i;
	for (i=0; i<n; i++) {
		printf("%d. Book : \n", i+1);
		print_book(&book_list[i]);
		printf("********************\n");
	}
}

int main () {
	book_t *book_list = NULL;
	int limit = 0;
	int n = 0;
	
	book_t new_book;
	int choice1, choice2;
	char buff[50];
	
	do {
		printf("1.Add new book\n");
		printf("2.List books\n");
		printf("3.Exit\n");
		printf("Choice : ");
		scanf("%d", &choice1);
		printf("***********************\n");
		
		switch (choice1) {
			
			case 1 :
				printf("Enter book title = ");
				clear_buffer();
				scanf("%[^\n]s", new_book.title);
				
				printf("Enter author = ");
				clear_buffer();
				scanf("%[^\n]s", new_book.author);
				
				printf("Enter subject = ");
				clear_buffer();
				scanf("%[^\n]s", new_book.subject);
				
				printf("Enter year =");
				scanf("%d", &new_book.year);
				
				new_book.id = n;
				
				add_book(&book_list, &limit, &n, new_book);
				
				printf("*******************************\n");
				break;
				
			case 2 :
			do {
				printf("1.Get by Title\n");
				printf("2.Get by Author\n");
				printf("3.Get by Subject\n");
				printf("4.Sorted List by Year (DESC)\n");
				printf("5.List all books\n");
				printf("6.EXIT SUBMENU\n");
				printf("Choice = ");
				scanf("%d", &choice2);
				printf("*******************\n");
				
				switch (choice2) {
					
					case 1 :
						printf("Enter a title = ");
						clear_buffer();
						scanf("%[^\n]s", buff);
						
						get_by_title(book_list, n, buff);
						printf("******************\n");
						
						break;
						
					case 2 :
						printf("Enter an author = ");
						clear_buffer();
						scanf("%[^\n]s", buff);
						
						get_by_author(book_list, n, buff);
						printf("******************\n");
						break;
						
					case 3 :
						printf("Enter an subject = ");
						clear_buffer();
						scanf("%[^\n]s", buff);
						
						get_by_subject(book_list, n, buff);
						printf("******************\n");
						break;
						
					case 4 :
						print_sorted_list(book_list, n);
						break;
						
					case 5 :
						print_list(book_list, n);
						break;
						
					case 6 :
						printf("Returning to main menu\n");
						printf("************************\n");
						break;
						
					default :
						printf("TRY AGAIN ! \n");
						printf("*******************\n");
						break;
					
				}
				
			}while(choice2 != 6);
				
				break;
				
			case 3 :
				printf("Program is closing...Goodbye!\n");
				break;
			
			default :
				printf("TRY AGAIN ! \n");
			
		}
		

	}while(choice1 != 3);
	

	free(book_list);	
	return 0;
}
