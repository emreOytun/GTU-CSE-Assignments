#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
	char name[30];
	char author[30];
	int year;
	struct node *next;
}node;

/* Create new_node with the informations of the given input. */
node* create_new_node(node input_node) {
	node *new_node = (node*) malloc(sizeof(node));
	
	new_node->next = NULL;
	strcpy(new_node->name, input_node.name);
	strcpy(new_node->author, input_node.author);
	new_node->year = input_node.year;
	
	return new_node;
	
}


node* insert_sorted_list(node *list, node input_node) {
	node *new_node = create_new_node(input_node);

	/* Check if the list is empty. */	
	if (list == NULL) {
		list = new_node;
		printf("Sorted Insertion is successful. -- Root changed.\n");
	}
	
	/* Check if the new_node will be inserted into the head. */
	else if (input_node.year < list->year) {
		new_node->next = list;
		list = new_node;
		printf("Sorted Insertion is successful. -- Root changed.\n");
	}
	
	/* Find where the new_node will be inserted. */
	else {
		
		node *former_ptr = list;
		node *cur_ptr = list->next;
		
		int is_inserted = 0;
		
		while (is_inserted == 0 && cur_ptr != NULL) {
			if (input_node.year < cur_ptr->year) {
				former_ptr->next = new_node;
				new_node->next = cur_ptr;
				
				is_inserted = 1;
				printf("Sorted Insertion is successful.\n");
			}
			
			else {
				former_ptr = cur_ptr;
				cur_ptr = cur_ptr->next;
			}
		}
		
		if (cur_ptr == NULL) {
			former_ptr->next = new_node;
			printf("Sorted Insertion is successful. --- Inserted at end.\n");
		}
	}
	
	return list;
}

node* read_file() {
	FILE *file = fopen("data.txt", "r");
	
	
	node *book_list = NULL;
	node new_book;
	
	/* Read the file until the end, get the new_node and insert it into the list. */	
	while(!feof(file)) {
		fscanf(file, "%s %s %d", new_book.name, new_book.author, &new_book.year);
		fgetc(file);


		if (feof(file)) break;
		else {
			book_list = insert_sorted_list(book_list, new_book);
		}
	}
	
	
	fclose(file);
	return book_list;
}

/* Print the list recursively. */
void print_node(node *list) {
	if (list == NULL) return;
	else {
		printf("%s %s %d\n", list->name, list->author, list->year);
		print_node(list->next); 
	}
}

node *delete_node(node *book_list, char *input_name) {
	node *former_ptr;
	node *cur_ptr;
	
	/* Check if the list is empty. */
	if (book_list == NULL) printf("Book is not found.\n");
	
	/* Check if the root will be deleted. */
	else if ( strcmp(book_list->name, input_name) == 0 ) {
		former_ptr = book_list;
		book_list = book_list->next;
		free(former_ptr);
		printf("Book is found and deleted.\n");
	}
	
	/* Look for the given name in the rest of the list by keeping two pointers as former and cur. */
	else {
		int is_found = 0;
		former_ptr = book_list;
		cur_ptr = book_list->next;
		
		while (!is_found && cur_ptr != NULL) {
			if ( strcmp(cur_ptr->name, input_name) == 0 ) is_found = 1;
			else {
				former_ptr = cur_ptr;
				cur_ptr = cur_ptr->next;
			}
		}
	
		if (is_found) {
			former_ptr->next = cur_ptr->next;
			free(cur_ptr);
			printf("Book is found and deleted.\n");
		}
	
		else {
			printf("Book is not found.\n");
		}
	
	}

	return book_list;
}

int main() {
	node *book_list = NULL;
	book_list = read_file();
	
	printf("\nLinked List : \n");
	print_node(book_list);
		

	char input_name[30];
	printf("\nWhich book do you want to delete ? ");
	scanf("%s", input_name);
	
	book_list = delete_node(book_list, input_name);
	
	printf("\nNew List : \n");
	print_node(book_list);
	
	
	
	return 0;
}
