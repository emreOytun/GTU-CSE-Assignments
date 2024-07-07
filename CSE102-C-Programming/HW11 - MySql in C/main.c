#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"

int main () {


	database *db;

	int choice;
	char buff[200];
	char fieldName[65];
	char queryInput[65];
	int k;
	
	int is_done = 0;
	int r;
	do {
	
		printf("Welcome to the Database Application : \n");
		printf("Select the database : \n");
		printf("1. Use Old Database\n");
		printf("2. Create New Database\n");
		printf("Choice = ");
		scanf("%d", &choice);
		
		switch(choice) {
			case 1 :
				db = read_db_from_file(&r);
				if (r == 1) is_done = 1;
				else printf("There is no old database file in the system.\n");		
				
				break;
				
			case 2 :
				printf("Enter database name  = ");
				clear_buffer();
				scanf("%[^\n]s", buff); 
				
				db = create_database(buff);
							
				is_done = 1;
				break;
		}
		
	
	}while(!is_done);
	
	
	do {
		printf("\n*****************************\n");
		printf("Welcome to the Database Application Menu \n");
		printf("1. Add table to database\n");
		printf("2. Remove table\n");
		printf("3. Show tables\n");
		printf("4. Describe a table\n");
		printf("5. Insert a key to a table\n");
		printf("6. Enter a record on a table\n");
		printf("7. Select from table\n");
		printf("8. Select a specific record from table by using field\n");
		printf("0. Exit\n");

		printf("Choice = ");
		k = scanf("%d", &choice);
		if (k != 1) clear_buffer();
		
	if (k == 1) {	
	
		switch(choice) {
		
			case 1 :
				printf("Enter table insert command in the format : \n");
				printf("TABLE_NAME,FIELD_NUM,FIELD_NAME|FIELD_TYPE,...");
				printf("FIELD TYPE FORMATS : \n");
				printf("int / double / float / char / char(max_size)\n");	
				
				printf("COMMAND = \n");
				clear_buffer();
				scanf("%[^\n]s", buff); 
				insert_table(db, buff);
					
				break;
			
			case 2 :
				printf("Enter table name = ");
				clear_buffer();
				scanf("%[^\n]s", buff);
				
				remove_table(db, buff);
				break;	
			
			case 3 :
				show_table(db);
				break;
				
			case 4 :
				printf("Enter table name = ");
				clear_buffer();
				scanf("%[^\n]s", buff); 
				
				desc_table(db, buff);
				break;
				
			
			case 5 :
				printf("Enter table name = ");
				clear_buffer();
				scanf("%[^\n]s", buff); 
				
				printf("Enter field name = ");
				clear_buffer();
				scanf("%[^\n]s", fieldName); 
				
				insert_key(db, buff, fieldName);	
				break;
			
			case 6 :
				
				printf("Enter table name you want to insert a record = ");
				clear_buffer();
				scanf("%[^\n]s", buff);
				
				get_new_record_and_insert(db, buff);
				break;
				
			case 7 :
				printf("Enter table name = ");
				clear_buffer();
				scanf("%[^\n]s", buff); 
				
				select_from_table(db, buff);
				break;
				
		
			case 8 :
				printf("Enter table name = ");
				clear_buffer();
				scanf("%[^\n]s", buff); 
				
				printf("Enter field name = ");
				clear_buffer();
				scanf("%[^\n]s", fieldName); 
				
				printf("Enter record value belongs to this field = ");
				clear_buffer();
				scanf("%[^\n]s", queryInput); 
				
				select_specific_record_from_table(db, buff, fieldName, queryInput);
				break;
				
			/* When user wants to exit, then write the database to the file. */
			case 0 :
				write_db_to_file(db);
				break;
		}
	
	}
	
	}while(choice != 0);
		
	return 0;
}
