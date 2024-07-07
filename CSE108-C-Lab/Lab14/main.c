#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUMOFITEMS 2
#define FILENAME "Lab11_data.bin"
typedef struct {
	char phone[50];
	char mail[50];
}contactInfo_t;

typedef struct {
	int id;
	double price;
	char name[50];
}item_t;

typedef struct {
	int id;
	double price;
	char name[50];
	contactInfo_t contactInfo;
}itemWithContact_t;

void clear_buffer() {
	char ch;
	do {
		ch = getchar();
	}while(ch != '\n');
}

item_t *getItems(int size, int *n) {
	int i;
	item_t *items = (item_t*) calloc(sizeof(item_t), size);
	
	for (i=0; i<size; i++) {
		printf("\nPress a key to continue adding item...\n");
		scanf("%*c");
		
		(*n)++;
		printf("Id = %d\n", *n);
		items[i].id = *n;
		
		printf("Name = ");
		//clear_buffer();
		scanf("%[^\n]s", items[i].name);
	
		printf("Price = ");
		scanf("%lf", &items[i].price);
	}
	
	return items;
}

void printItem(item_t item) {
	printf("Id = %d\n", item.id);
	printf("Name = %s\n", item.name); 
	printf("Price = %lf\n", item.price);
}

void printItemWithContactInfo(itemWithContact_t item) {
	printf("Id = %d\n", item.id);
	printf("Name = %s\n", item.name); 
	printf("Price = %lf\n", item.price);
	printf("Phone = %s\n", item.contactInfo.phone);
	printf("Mail = %s\n", item.contactInfo.mail);
}

int writeItems(char *filename, item_t *items, int size) {
	FILE *file = fopen(filename, "ab");
	if (file == NULL) return 0;
	
	printf("\nPrinting...\n");
	
	int i;
	for (i=0; i<size; i++) {
		printItem(items[i]);
		fwrite(&items[i], sizeof(item_t), 1, file);
	}
	
	
	printf("Successfully wrote data to file.\n");
	fclose(file);
	return 1;
}

item_t* readAnItem(char *filename) {
	FILE *file = fopen(filename, "rb");

	item_t *items = (item_t*) calloc(sizeof(item_t), 2 * NUMOFITEMS);
	
	printf("\nReading from file :\n");
	
	int i;
	for (i=0; i<2*NUMOFITEMS; i++) {
		fread(&items[i], sizeof(item_t), 1, file);
		printItem(items[i]);
	}
	
	return items;
}

void copyItemtoContact(item_t item, itemWithContact_t *itemWcontact) {
	strcpy((*itemWcontact).name, item.name);
	itemWcontact->id = item.id;
	itemWcontact->price = item.price; 
}

void contactInfoAdder(item_t *items, int size, itemWithContact_t contacts[]) {
	int i;
	for (i=0; i<size; i++) {
		copyItemtoContact(items[i], &contacts[i]);
	
		printf("Enter the phone for %s = ", items[i].name);
		clear_buffer();
		scanf("%s", contacts[i].contactInfo.phone);
	
		printf("Enter the mail for %s = ", items[i].name);
		clear_buffer();
		scanf("%s", contacts[i].contactInfo.mail);
	}
}

int main () {
	item_t *items;
	itemWithContact_t contacts[4];
	remove(FILENAME);
	
	int i, j;
	int n = 0;	

	for (i=0; i<NUMOFITEMS; i++) {
		items = getItems(NUMOFITEMS, &n);
		writeItems(FILENAME, items, NUMOFITEMS);
		free(items);
	}
	
	items = readAnItem(FILENAME);
	contactInfoAdder(items, 4, contacts);
	
	for (i=0; i<4; i++) {
		printItemWithContactInfo(contacts[i]);
	}
	
	
	



	return 0;
}
