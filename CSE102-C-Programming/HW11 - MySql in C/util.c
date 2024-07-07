#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "util.h"

/* Clear the stdin buffer before reading a character or string. */
void clear_buffer() {
	char ch;
	do {
		ch = getchar();
	}while (ch !='\n' && ch != EOF);
}

/* 
FUNCTION NAME : write_db_to_file
FUNCTION DOES : Writes the given database with its tables into the .txt file. 
TO-DO-LIST : 
	1) First write db name, table number, fields, types, and is key column to the file.
	2) Write records in the table if there is any into the file.
*/
void write_db_to_file(database *db) {
	
	printf("Writing database '%s' into the 'database.txt' file = \n", db->name);

	FILE *file = fopen("database.txt", "w");
	int table_num = 0;
	int record_num = 0;
	int i, j, k;
	
	record_t *cur_rlist;
	data_node *cur_rdata;
	table *t;
	tables *cur_tlist;
	
	fprintf(file, "DATABASE NAME = %s\n", db->name);
	fprintf(file, "TABLE NUMBER = %d\n", db->n);
	
	cur_tlist = db->tlist;
	for (i=0; i<db->n; i++, cur_tlist = cur_tlist->next) {
		t = cur_tlist->t;
		
		fprintf(file, "----------\n");
		fprintf(file, "TABLE NAME = %s\n", t->tableName);
		fprintf(file, "FIELD NUMBER = %d\n", t->field_num);
		
		/* Write fields and types into the .txt file.  */
		for (j=0; j<t->field_num; j++) {
			fprintf(file, "%s|%s\n", t->field[j], t->type[j]);
		}
		
		/* Write isKey column into the .txt file.  */
		fprintf(file, "ISKEY = ");
		for (j=0; j<t->field_num; j++) {
			fprintf(file, "%d,", t->isKey[j]);
		}
		fprintf(file, "\n");
		
		/* Find record number then write records into the .txt file.  */
		cur_rlist = t->records;
		record_num = 0;
		while (cur_rlist != NULL) {
			record_num++;
			cur_rlist = cur_rlist->next;
		}
		
		fprintf(file, "RECORD NUMBER = %d\n", record_num);
		
		cur_rlist = t->records;
		for (j=0; j<record_num; j++, cur_rlist = cur_rlist->next) {
			cur_rdata = cur_rlist->recordData;
			
			for (k=0; k<t->field_num; k++) {
				switch(cur_rdata[k].data_type) {
					case 1 :
						fprintf(file, "%d,", cur_rdata[k].data.i);
						break;
						
					case 2 :
						fprintf(file, "%lf,", cur_rdata[k].data.d);
						break;
						
					case 3 :
						fprintf(file, "%f,", cur_rdata[k].data.f);
						break;
						
					case 4 :
						fprintf(file, "%c,", cur_rdata[k].data.c);
						break;
						
					case 5 :
						fprintf(file, "%s,", cur_rdata[k].data.str);
						break;
				}
			}
		
			fprintf(file, "\n");
		}
		
	}
	
	printf("Database '%s' has been written into the 'database.txt' file\n", db->name);
	fclose(file);
}

/* 
FUNCTION NAME : read_db_from_file
FUNCTION DOES : Read the old database from .txt file. 
TO-DO-LIST : 
	1) Check if there is a database file. The given parameter return_value is used to return if process is successful or not. 
	2) If there is the file, then get db name and table number first.
	3) Then get tables one-by-one according to the format of file.
*/
database* read_db_from_file(int *return_value) {
	FILE *file = fopen("database.txt", "r");
	database *db = NULL;
	
	int table_num;
	int record_num;
	int i, j, k;
	int char_num;
	
	char buff[300];
	char field[200];
	char type[50];
	char *token;
	
	table *t;
	
	if (file == NULL) *return_value = 0;
	
	else {
		
		fscanf(file, "DATABASE NAME = %[^\n]s", buff);
		fgetc(file);
		
		fscanf(file, "TABLE NUMBER = %d", &table_num);
		fgetc(file);
		
		db = (database*) malloc(sizeof(database));
		/* Create the database name dynamically. */
		copy_string_by_calloc(&db->name, buff);
	
		/* Set new_database to be default. */
		db->n = 0;
		db->tlist = NULL;
	
		for (i=0; i<table_num; i++) {
			t = (table*) malloc(sizeof(table));
			t->records = NULL;
			t->keys = NULL;
			
			fscanf(file, "----------");
			fgetc(file);
			
			fscanf(file, "TABLE NAME = %[^\n]s", buff);
			fgetc(file);
			
			copy_string_by_calloc(&t->tableName, buff);
			
			fscanf(file, "FIELD NUMBER = %d", &t->field_num);
			fgetc(file);
			
			
			t->field = (char**) calloc(sizeof(char*), t->field_num);
			t->type = (char**) calloc(sizeof(char*), t->field_num);
			t->isNull = (int*) calloc(sizeof(int), t->field_num);
			t->isKey = (int*) calloc(sizeof(int), t->field_num);
			
			
			for (j=0; j<t->field_num; j++) {
				t->isNull[j] = 1;
			}
			
			/* Get the fields and types of the fields. */
			for (j=0; j<t->field_num; j++) {
				fscanf(file, "%[^\n]s", buff);
				fgetc(file);
			
				token = strtok(buff, "|");
				copy_string_by_calloc(&t->field[j], token);
				
				token = strtok(NULL, "|");
				copy_string_by_calloc(&t->type[j], token);
			}
			
			
			/* Get isKey column for the table. */
			fscanf(file, "ISKEY = ");
			for (j=0; j<t->field_num; j++) {
				fscanf(file, "%d,", &t->isKey[j]);
			}
			fgetc(file); // go to the next line after reading isKey part. 
			
			/* Insert the table into the list of tables in the database. */
			tables *new_tables_node = create_new_tables_node(t);
		
			if (db->tlist == NULL) {
				db->tlist = new_tables_node;
			}
				
			else {
				tables *cur_ptr = db->tlist;
				while(cur_ptr->next != NULL) cur_ptr = cur_ptr->next;
				cur_ptr->next = new_tables_node;	
			}
			
			db->n++;
			
			
			/* Insert keys if any.  */
			for (j=0; j<t->field_num; j++) {
				if (t->isKey[j] == 1) {
					t->isKey[j] = 0;
					insert_key(db, t->tableName, t->field[j]);
				}
			}
			
			
			/* Get records of the table. */
			fscanf(file, "RECORD NUMBER = %d", &record_num);
			fgetc(file);
			
			
			for (j=0; j<record_num; j++) {

				record_t *new_record = (record_t*) malloc(sizeof(record_t));
				new_record->next = NULL;
				new_record->recordData = (data_node*) calloc(sizeof(data_node), t->field_num);
	
				for (k=0; k<t->field_num; k++) {
					
					/* isNull kisimlarini da guncelle */
					t->isNull[k] = 0;
					
					if (strcmp(t->type[k], "int") == 0) {
						fscanf(file, "%d", &new_record->recordData[k].data.i); 
						fgetc(file);
						
						new_record->recordData[k].data_type = 1;
					
					}
					
					else if (strcmp(t->type[k], "double") == 0) {
						fscanf(file, "%lf", &new_record->recordData[k].data.d); 
						fgetc(file);
						
						new_record->recordData[k].data_type = 2;
					
					}
					
					else if (strcmp(t->type[k], "float") == 0) {
						fscanf(file, "%f", &new_record->recordData[k].data.f);
						fgetc(file);
						
						new_record->recordData[k].data_type = 3;
				
					}
					
					else if (strcmp(t->type[k], "char") == 0) {
						fscanf(file, "%c", &new_record->recordData[k].data.c); 
						fgetc(file);
						
						new_record->recordData[k].data_type = 4;
				
					}
					
					else {
						int len;
						sscanf(t->type[k], "char(%d)", &len);
						
						new_record->recordData[k].data.str = (char*) calloc(sizeof(char), len);
						fscanf(file, "%[^,]s", new_record->recordData[k].data.str);
						fgetc(file);
								
						new_record->recordData[k].data_type = 5;
						new_record->recordData[k].charNum_ifStr = len;
					}
				}
				fgetc(file); // go to the next line after reading a record. 
			
				insert_record_on_table(t, new_record);
				
			}
			
		}
		
		
		*return_value = 1;
		fclose(file);
	}
		
	return db;
}

/************* INSERT KEY *************/

/* 
FUNCTION NAME : insert_keyNode_into_keyList
FUNCTION DOES : Insert a given key_node into the key. 
*/
void insert_keyNode_into_keyList(keys *key, key_node *key_ptr) {
	key_node *cur_ptr;

	key_ptr->next = NULL;
	
	if (key->keyList == NULL) {
		key->keyList = key_ptr;
	}
	
	else {
		cur_ptr = key->keyList;
		while (cur_ptr->next != NULL) cur_ptr = cur_ptr->next;
		
		cur_ptr->next = key_ptr;
	}
}

/*
FUNCTION NAME : insert_key_into_keysList 
FUNCTION DOES : Insert the given key into the key list. 
*/
void insert_key_into_keysList(table *t, keys *key) {
	keys* cur_key;
	
	key->next = NULL;
	
	if (t->keys == NULL) t->keys = key;
	
	else {
		cur_key = t->keys;
		while (cur_key->next != NULL) cur_key = cur_key->next;
		
		cur_key->next = key;
	}
}

/* 
FUNCTION NAME : insert_key
FUNCTION DOES : Insert a key into the given field of a given table by their names. 
TO-DO-LIST : 
	1) Look for the table in the database, continue if it's found.
	2) Look for the field in the table, continue if it's found.
	3) Update isKey field of the table.
	4) Get key value and record addresses into the key.
	5) Insert the key into the key list in the table.
	
*/
void insert_key(database *d, char *tableName, char *field) {
	tables *cur_tlist = d->tlist;
	table *cur_table = NULL;
	
	int is_found = 0;
	int len;
	
	/* Look for the given table name in the database. */
	while (is_found == 0 && cur_tlist != NULL) {
		cur_table = cur_tlist->t;
	
		if (strcmp(tableName, cur_table->tableName) == 0) is_found = 1;
		
		else cur_tlist = cur_tlist->next;
	}
	
	
	if (!is_found) printf("There is no table with that name.\n");
	
	
	else {
	
		int is_field_found;
		int field_index;
		
		/* If the table is found, then look for the given field in this table. */
		int i;
		for(i=0, is_field_found = 0; i<cur_table->field_num && is_field_found == 0; i++) {
		
			if (strcmp(cur_table->field[i], field) == 0) {
				is_field_found = 1;
				field_index = i;
			}
		}
		i = field_index;
		
		if (is_field_found == 0) printf("There is no field called '%s' in the table '%s'\n", field, tableName); 
		
		else if (is_field_found == 1 && cur_table->isKey[i] == 1) printf("This field already has a key.\n");
		
		else {
			/* Update isKey column of the table. */
			cur_table->isKey[i] = 1;
			
			/* Create a new key with the given field name. */
			keys *new_key = (keys*) malloc(sizeof(keys));
			new_key->keyList = NULL;
			new_key->next = NULL;
			
			copy_string_by_calloc(&new_key->field, field);
			
			/* Update new key's type variable by looking at the type of the field. */
			if (strcmp(cur_table->type[i], "int") == 0) new_key->data_type = 1;
			
			else if (strcmp(cur_table->type[i], "double") == 0) new_key->data_type = 2;
			
			else if (strcmp(cur_table->type[i], "float") == 0) new_key->data_type = 3;
			
			
			else if (strcmp(cur_table->type[i], "char") == 0) new_key->data_type = 4;
			
			
			else {
				sscanf(cur_table->type[i], "char(%d)", &len);
				
				new_key->data_type = 5;
				new_key->charNum_ifStr = len;
			}
			
			
			/* Go through the records in the table and index them. */
			record_t *cur_record = cur_table->records;
			
			key_node *new_key_node;
			
			/* Go through all records in the table, and keep the data of the key field and address of the records in the key nodes. */
			/* Key nodes in a key are linked to each other. */
			while (cur_record != NULL) {
			

				new_key_node = (key_node*) malloc(sizeof(key_node));
				
				new_key_node->next = NULL;
				new_key_node->recordAdress = NULL;
				
				new_key_node->next = NULL;
				new_key_node->recordAdress = cur_record;
				
				switch(new_key->data_type) {
					case 1 :
					
						new_key_node->keyValue.i = cur_record->recordData[i].data.i;
						break;
						
					case 2 :
			
						new_key_node->keyValue.d = cur_record->recordData[i].data.d;
						break;
						
					case 3 :
						
						new_key_node->keyValue.f = cur_record->recordData[i].data.f;		
						break;
						
					case 4 :
						
						new_key_node->keyValue.c = cur_record->recordData[i].data.c;		
						break;
						
					case 5 :
						new_key_node->keyValue.str = (char*) calloc(sizeof(char), cur_record->recordData[i].charNum_ifStr);
						strcmp(new_key_node->keyValue.str, cur_record->recordData[i].data.str);		
						break;
				}
				
				insert_keyNode_into_keyList(new_key, new_key_node);
				
				cur_record = cur_record->next;
			}
			
			insert_key_into_keysList(cur_table, new_key);
			printf("Key has been inserted into the '%s' field of '%s' table.\n", field, tableName);
		}	
	}	
}

/********** INSERT RECORD ***********/

/*
FUNCTION NAME : update_keys_on_table
FUNCTION DOES : When inserting a new record into the table, update the keys in the table. 
TO-DO-LIST :
	1) Look for which field are indexed in the table.
	2) For each field in the table which has key, insert new key value and the new record address into the key.
*/
void update_keys_on_table(table *t, record_t *new_record) {
	int i;
	int is_done;
	
	keys *cur_ptr;
	key_node *new_node;
	
	/* Look for the indexed fields. */	
	for (i=0; i<t->field_num; i++) {
		if (t->isKey[i] == 1) {
			cur_ptr = t->keys;
			
			
			/* Initialize the new key_node */
			new_node = (key_node*) malloc(sizeof(key_node));
			new_node->next = NULL;
			new_node->recordAdress = new_record;
				
			is_done = 0;
			while (!is_done) {
				if (strcmp(cur_ptr->field, t->field[i]) == 0) {
					
					switch(cur_ptr->data_type) {
						case 1 :
						
							new_node->keyValue.i = new_record->recordData[i].data.i;
							break;
							
						case 2 :
				
							new_node->keyValue.d = new_record->recordData[i].data.d;
							break;
							
						case 3 :
								
							new_node->keyValue.f = new_record->recordData[i].data.f;		
							break;
							
						case 4 :
							
							new_node->keyValue.c = new_record->recordData[i].data.c;		
							break;
							
						case 5 :
							new_node->keyValue.str = (char*) calloc(sizeof(char), new_record->recordData[i].charNum_ifStr);
							strcmp(new_node->keyValue.str, new_record->recordData[i].data.str);		
							break;
					}
					
					insert_keyNode_into_keyList(cur_ptr, new_node);
					
					is_done = 1;
				}
				
				else cur_ptr = cur_ptr->next;
			}	
		}
	}
}

/*
FUNCTION NAME : insert_record_on_table 
FUNCTION DOES : Insert a given record into the table. 
*/
void insert_record_on_table(table *t, record_t *new_record) {
	if (new_record == NULL || t == NULL) return;
	
	else {
		update_keys_on_table(t, new_record);
	
		new_record->next = NULL;
		
		if (t->records == NULL) t->records = new_record;
		
		else {
			record_t *cur_record = t->records;
			while(cur_record->next != NULL) cur_record = cur_record->next;
			cur_record->next = new_record;
		}
		
	}
}

/*
FUNCTION NAME : get_table_by_name 
FUNCTION DOES :Find the table whose name is given in the database, return its address if it's found; or return NULL. 
*/
table* get_table_by_name(database *d, char *name) {
	tables *cur_tlist = d->tlist;
	table *cur_table = NULL;
	
	int is_found;
	if (cur_tlist != NULL) {
	
		is_found = 0;	
		while (is_found == 0 && cur_tlist != NULL) {
			cur_table = cur_tlist->t;
		
			if (strcmp(name, cur_table->tableName) == 0) is_found = 1;
			
			else cur_tlist = cur_tlist->next;
		}
		
		if (!is_found) cur_table = NULL;
	}
	
	return cur_table;
}

/* 
FUNCTION NAME : get_new_record_and_insert
FUNCTION DOES : Get new record informations from the user, and insert it into the records of the table. 
TO-DO-LIST :
	1) Look for the table in the database, continue if it's found.
	2) For each field, ask user to enter the values.
	3) Insert the new record into the table.
*/
void get_new_record_and_insert(database *d, char *tName) {
	
	/* Get table address. */
	table *t = get_table_by_name(d, tName);
	
	if (t == NULL) printf("There is no table with that name in the database\n");
	
	else {
		/* Create new record. */
		record_t *new_record = (record_t*) malloc(sizeof(record_t));
		new_record->next = NULL;
		new_record->recordData = (data_node*) calloc(sizeof(data_node), t->field_num);
	
		/* Get new record informations from the user. */
		int i;
		for (i=0; i<t->field_num; i++) {
		
			printf("Enter %s|%s : ", t->field[i], t->type[i]);
			
			/* Update isNull field of the table. */
			t->isNull[i] = 0;
			
			if (strcmp(t->type[i], "int") == 0) {
				scanf("%d", &new_record->recordData[i].data.i); 
				new_record->recordData[i].data_type = 1;
			}
			
			else if (strcmp(t->type[i], "double") == 0) {
				scanf("%lf", &new_record->recordData[i].data.d); 
				new_record->recordData[i].data_type = 2;
			}
			
			else if (strcmp(t->type[i], "float") == 0) {
				scanf("%f", &new_record->recordData[i].data.f);
				new_record->recordData[i].data_type = 3;
			}
			
			else if (strcmp(t->type[i], "char") == 0) {
				clear_buffer();
				scanf("%c", &new_record->recordData[i].data.c); 
				new_record->recordData[i].data_type = 4;
			}
			
			else {
				int len;
				sscanf(t->type[i], "char(%d)", &len);
				new_record->recordData[i].data.str = (char*) calloc(sizeof(char), len);
				clear_buffer();
				scanf("%[^\n]s", new_record->recordData[i].data.str);
			
				new_record->recordData[i].data_type = 5;
				new_record->recordData[i].charNum_ifStr = len;
			}
		}
	
		insert_record_on_table(t, new_record);
	}
}


/************* SELECT FROM TABLE *************/

/*
FUNCTION NAME : select_from_table
FUNCTION DOES : Print all records of the table whose name is given by parameter, if there are any records. 
TO-DO-LIST: 
	1) Look for the table in the database, continue if it's found.
	2) If there is no records, print this information; continue other way.
	3) Print each record.
*/
void select_from_table(database *d, char *tableName) {
	table *t;
	
	t = get_table_by_name(d, tableName);
	
	if (t == NULL) printf("There is no table in the database with that name.\n");
	
	else if (t->records == NULL) printf("There is no records in the table.\n");
	
	else {
	
		record_t *cur_record = t->records;
		int i;
		
		/* Print fields and types in the 1st row of the table. */
		for (i=0; i<t->field_num; i++) {
			int len1 = strlen(t->field[i]);
			int len2 = strlen(t->type[i]);
			int rest_of_space = 64 - (len1 + len2 + 1);
			
			printf("%s|%s", t->field[i], t->type[i]);	
		
			int j;
			for (j=0; j<rest_of_space; j++) printf(" ");
		}
		printf("\n");
		
		/* Print records. */
		while (cur_record != NULL) {
			
			for (i=0; i<t->field_num; i++) {
				
				switch (cur_record->recordData[i].data_type) {
				
					case 1 :
						printf("%-64d", cur_record->recordData[i].data.i);
						break;
						
					case 2 :
						printf("%-64lf", cur_record->recordData[i].data.d);
						break;
						
					case 3 :
						printf("%-64f", cur_record->recordData[i].data.f);
						break;
						
					case 4 :
						printf("%-64c", cur_record->recordData[i].data.c);
						break;
						
					case 5 :
						printf("%-64s", cur_record->recordData[i].data.str);
						break;
				}	
			}	
			printf("\n");
			cur_record = cur_record->next;
		}
	}
}


/******************* SELECT A SPECIFIC RECORD FROM TABLE *******************/

/* 
FUNCTION NAME : select_specific_record_from_table
FUNCTION DOES : Find and print the record by looking at the specific record from given field of given table. 
TO-DO-LIST : 
	1) Look for the table in the database, continue if it's found.
	2) Look for the specified field in the database, continue if it's found.
	3) Check if specified field has key, use key when searching the record.
	4) Look for the record in the key or in all records.
*/
void select_specific_record_from_table(database *d, char *tableName, char *field, char *queryInput) {
	
	table *cur_table;
	
	keys *cur_key_ptr;
	key_node *cur_node_ptr;
	
	record_t *cur_record;
	var_data_t queryData;

	int i;
	int is_found;
	
	cur_table = get_table_by_name(d, tableName);
		
	if (cur_table == NULL) printf("There is no table in the database with that name.\n");
	
	else {
		/* Check if the table has the given field. */
		for (i=0, is_found = 0; i<cur_table->field_num && is_found == 0;) {
			if (strcmp(field, cur_table->field[i]) == 0) is_found = 1; 
			else i++;
		}
	
		if (!is_found) printf("There is no field '%s' in the table '%s'\n", field, tableName);
	
		else {
			/* Convert the queryData which is given as string into the convenient variable by looking at the type of the field. */
			if (strcmp(cur_table->type[i], "int") == 0) {
				queryData.i = atoi(queryInput);
			}
			
			else if (strcmp(cur_table->type[i], "double") == 0) {
				queryData.d = atof(queryInput);
			}
			
			else if (strcmp(cur_table->type[i], "float") == 0) {
				queryData.f = (double) atof(queryInput);
			}
			
			else if (strcmp(cur_table->type[i], "char") == 0) {
				queryData.c = queryInput[0];
			}
			
			else {
				copy_string_by_calloc(&queryData.str, queryInput);
			}
		
			/* If this field has a key, then look for the record in the key. */
			if (cur_table->isKey[i] == 1) {
				printf("KEY HAS BEEN FOUND. LOOKING FOR THE RECORD IN INDEXES...\n");
				
				cur_key_ptr = cur_table->keys;
				is_found = 0;
				
				while(!is_found) {
					if (strcmp(cur_key_ptr->field, field) == 0) is_found = 1;
					else cur_key_ptr = cur_key_ptr->next;
				}
				
				cur_node_ptr = cur_key_ptr->keyList;
				is_found = 0;
				
				/* Look for the specific record from the key. */
				while (!is_found && cur_node_ptr != NULL) {
					switch(cur_key_ptr->data_type) {
						case 1 :
							if (cur_node_ptr->keyValue.i == queryData.i) is_found = 1;
							break;
							
						case 2 :
							if (cur_node_ptr->keyValue.d == queryData.d) is_found = 1;
							
							break;
							
						case 3 :
							if (cur_node_ptr->keyValue.f == queryData.f) is_found = 1;
							break;
							
						case 4 :
							if (cur_node_ptr->keyValue.c == queryData.c) is_found = 1;
							break;
							
						case 5 :
							if (strcmp(cur_node_ptr->keyValue.str, queryData.str) == 0) is_found = 1;		
							break;
					}		
				
					if (!is_found) cur_node_ptr = cur_node_ptr->next;
					else cur_record = cur_node_ptr->recordAdress;
				}
				
			}
				
			/* If there is no key related with that field, then look for all records in the table. */
			else {
				cur_record = cur_table->records;
				
				is_found = 0;
				while (cur_record != NULL && is_found == 0) {
				
					switch (cur_record->recordData[i].data_type) {
				
					case 1 :
						if (cur_record->recordData[i].data.i == queryData.i) is_found = 1;
						break;
						
					case 2 :
						if (cur_record->recordData[i].data.d == queryData.d) is_found = 1;
						break;
						
					case 3 :
						if (cur_record->recordData[i].data.f == queryData.f) is_found = 1;
						break;
						
					case 4 :
						if (cur_record->recordData[i].data.c == queryData.c) is_found = 1;	
						break;
						
					case 5 :
						if (strcmp(cur_record->recordData[i].data.str, queryData.str) == 0) is_found = 1;
						break;
					
					}
				
					if (!is_found) cur_record = cur_record->next;
				
				}
			
				
			}
			
			if (!is_found) printf("There is no record like that in the table.\n");
			
			/* If the record is found, then print the record. */
			else {
			
				for (i=0; i<cur_table->field_num; i++) {
					int len1 = strlen(cur_table->field[i]);
					int len2 = strlen(cur_table->type[i]);
					int rest_of_space = 64 - (len1 + len2 + 1);
					
					printf("%s|%s", cur_table->field[i], cur_table->type[i]);	
			
					int j;
					for (j=0; j<rest_of_space; j++) printf(" ");
				}
				printf("\n");
			
				for (i=0; i<cur_table->field_num; i++) {
				
					switch (cur_record->recordData[i].data_type) {
					
						case 1 :
							printf("%-64d", cur_record->recordData[i].data.i);
							break;
							
						case 2 :
							printf("%-64lf", cur_record->recordData[i].data.d);
							break;
							
						case 3 :
							printf("%-64f", cur_record->recordData[i].data.f);
							break;
							
						case 4 :
							printf("%-64c", cur_record->recordData[i].data.c);
							break;
							
						case 5 :
							printf("%-64s", cur_record->recordData[i].data.str);
							break;
					}	
				}
				
				printf("\n");	
			}		
		}
	}
}


/************** CREATE DATABASE ***************/

/* 
FUNCTION NAME : create_database
FUNCTION DOES : Create a database whose name is given in the parameter. 
TO-DO-LIST :
	1) Allocate memory for new database.
	2) Set memory name.
	3) Set table number to 0, and tlist pointer to NULL as default.
*/
database *create_database(char *name) {
	database *new_database = (database*) malloc(sizeof(database));
	
	/* Create the database name dynamically. */
	copy_string_by_calloc(&new_database->name, name);

	/* Set new_database to be default. */
	new_database->n = 0;
	new_database->tlist = NULL;
	
	return new_database;
}

/***************** INSERT TABLE **************/

/* 
FUNCTION NAME : create_new_tables_node
FUNCTION DOES : Create and return a new tables node. 
*/
tables* create_new_tables_node(table *new_t) {
	tables *new_tables_node = (tables*) malloc(sizeof(tables));
	
	new_tables_node->next = NULL;
	new_tables_node->t = new_t;
	
	return new_tables_node;
}

/* 
FUNCTION NAME : create_new_table_node
FUNCTION DOES : Create and return a new table node by setting it default. 
TO-DO-LIST : 
	1) Allocate memory for new table.
	2) Set numbers to 0, pointers to NULL as default.
*/
table *create_new_table_node() {
	table *new_table = (table*) malloc(sizeof(table));
	new_table->isNull = NULL;
	new_table->isKey = NULL;
	new_table->tableName = NULL;
	new_table->records = NULL;
	new_table->type = NULL;
	new_table->field = NULL;
	new_table->keys = NULL;

	return new_table;
}

/* 
FUNCTION NAME : copy_string_by_calloc
FUNCTION DOES : Copy a source string into a target string created dynamically by using the length of the source string. 
TO-DO-LIST :
	1) Get the length of the source.
	2) Allocate memory to be the address of the target string according to the length of the source.
	3) Copy source into the new string.
	4) Append EOF('\0') into the new string.
*/
void copy_string_by_calloc(char **dest, char *source) {
	int len = strlen(source);
	
	/* Allocate the necessary memory. */
	*dest = (char*) calloc(len+1, sizeof(char));

	int i;
	for (i=0; i<len; i++) (*dest)[i] = source[i];

	(*dest)[len] = '\0';
	
}

/* 
FUNCTION NAME : insert_table
FUNCTION DOES : Insert a new table into the database. 
TO-DO LIST : 
	1) Get a command as parameter whose format is specified in the program.
	2) Parse the command to get the table name, fields and types.
	3) Create new table, and fill it.
	4) Insert the new table into the database.

*/
void insert_table (database *d, char *command) {
	
	int is_read = 1, is_end;
	int i;
	int count_read_field;
	int str_len, k;
	char field[50];
	char type[20];
	
	table *new_table = create_new_table_node();
	
	/* Get table name by parsing till ',' .*/
	char *token = strtok(command, ",");
	
	if(token == NULL) is_read = 0;
	else {
		copy_string_by_calloc(&new_table->tableName, token);
		
		/* Get field num. */
		token = strtok(NULL, ",");
		
		if (token == NULL) is_read = 0;
		
		else {
			
			for(i=0; token[i] != '\0' && is_read; i++) {
				if (isdigit(token[i]) == 0) {
					printf("Field number must only contain digits.\n");
					is_read = 0;	
				}
			} 
		
			if (is_read) {
				new_table->field_num = atoi(token);
				
				new_table->field = (char**) calloc(sizeof(char*), new_table->field_num);
				new_table->type = (char**) calloc(sizeof(char*), new_table->field_num);
				new_table->isNull = (int*) calloc(sizeof(int), new_table->field_num);
				new_table->isKey = (int*) calloc(sizeof(int), new_table->field_num);
	
				for (i=0; i<new_table->field_num; i++) {
					new_table->isNull[i] = 1;
				}
				
				/* First get field by parsing until '|' character; then get type by reading until ',' character. */
				token = strtok(NULL, "|");
				i = 0;
				is_end = 0;
				while (!is_end && token != NULL && is_read) {
					
					copy_string_by_calloc(&new_table->field[i], token);
					
					token = strtok(NULL, ",");
					copy_string_by_calloc(&new_table->type[i], token);
		
					if (strcmp(new_table->type[i], "int") == 0 || strcmp(new_table->type[i], "double") == 0 || strcmp(new_table->type[i], "float") == 0 || strcmp(new_table->type[i], "char") == 0) is_read = 1;
					else {
						k = sscanf(new_table->type[i], "char(%d)", &str_len);
						if (k != 1) is_read = 0;
					}
										
					token = strtok(NULL, "|");
					i++;
				}

				if (is_read && i != new_table->field_num) is_read = 0;
						
			}
		}
		
	}
	
	if (is_read) {	
		
		tables *new_tables_node = create_new_tables_node(new_table);
		
		if (d->tlist == NULL) {
			d->tlist = new_tables_node;
		}
			
		else {
			tables *cur_ptr = d->tlist;
			while(cur_ptr->next != NULL) cur_ptr = cur_ptr->next;
			cur_ptr->next = new_tables_node;	
		}
		
		d->n++;
		printf("New table '%s' has been inserted into the database '%s'.\n", new_table->tableName, d->name);

	}
	
	else printf("There is a problem with the command. Be sure you enter valid command and try again...\n");
}

/*************** SHOW TABLES *******************/

/* 
FUNCTION NAME : show_table
FUNCTION DOES : Get the database, and show all tables.
*/
void show_table(database *d) {
	int i;
	tables *cur_ptr;
	
	printf("------ TABLES IN %s DATABASE -------\n", d->name);	
	if (d->n == 0) printf("Empty set.\n");
	
	else {
		for(cur_ptr = d->tlist; cur_ptr != NULL; cur_ptr = cur_ptr->next) printf("%s\n", cur_ptr->t->tableName); 
	} 
}

/********************* DESCRIBE TABLE *********************/

/*
FUNCTION NAME : desc_table 
FUNCTION DOES : Describe in a table whose name is given as paramater in the given database. 
*/
void desc_table(database *d, char *tableName) {
	
	int is_found = 0;
	
	table *table = get_table_by_name(d, tableName);
	
	if (table == NULL) printf("There is no table in the database with that name.\n");
	
	else {
		printf("TABLE NAME FOUND = %s\n", table->tableName); 

		int i;

		printf("-------------------------------------------\n");	
		printf("%-64s", "FIELD");
		printf("%-64s", "TYPE");
		printf("%-64s", "NULL");
		printf("%-64s\n", "KEY");
		
		for (i=0; i<table->field_num; i++) {
			printf("%-64s%-64s", table->field[i], table->type[i]);
			
			switch(table->isNull[i]) {
				case 1 :
					printf("%-64s", "YES");
					break;
					
				case 0 :
					printf("%-64s", "NO");
					break;
			}
			
			switch(table->isKey[i]) {
				case 1 :
					printf("YES\n");
					break;
					
				case 0 :
					printf("   \n");
					break;
			}
		}
	}
}

/********************* REMOVE TABLE ********************/

/*
FUNCTION NAME : free_record 
FUNCTION DOES : Free all dynamic things from a given record. 
*/
void free_record(record_t *r) {
	if (r->recordData != NULL) {
		if (r->recordData->data_type == 5) free(r->recordData->data.str);
		free(r->recordData);
	}
	
	free(r);
}

/*
FUNCTION NAME : free_key_node 
FUNCTION DOES :Free the given key_node. 
*/
void free_key_node(key_node *kn) {
	if (kn->recordAdress != NULL) free(kn->recordAdress);
	free(kn);
}

/*
FUNCTION NAME : free_table 
FUNCTION DOES : Free the given table. 
*/
void free_table(table *table) {
	record_t *cur_record, *next_record;
	key_node *cur_key, *next_key;
	keys *cur_keys, *next_keys;
	
	int i, is_done, flag;


	if (table->tableName != NULL) free(table->tableName);
	if (table->isNull != NULL) free(table->isNull);
	if (table->isKey != NULL) free(table->isKey);
	
	for (i=0; i<table->field_num; i++) {
		if (table->field[i] != NULL) free(table->field[i]);
		if (table->type[i] != NULL) free(table->type[i]);			
	}
	
	if (table->field != NULL) free(table->field);
	if (table->type != NULL) free(table->type);
	
	if (table->keys != NULL) {
		cur_keys = table->keys;
		next_keys = table->keys->next;
	
		is_done = 0;
		while(!is_done) {
			
			if (cur_keys->keyList != NULL) {
				cur_key = cur_keys->keyList;
				next_key = cur_key->next;
				
				flag = 0;
				while (!flag) {
					free_key_node(cur_key);
					if (next_key == NULL) flag = 1;
					else {
						cur_key = next_key;
						next_key = next_key->next;
					}
				}
			}
		
			free(cur_keys);
			if (next_keys == NULL) is_done = 1;
			else {
				cur_keys = next_keys;
				next_keys = next_keys->next;
			}
		}
	}
				
}

/*
FUNCTION NAME : remove_table 
FUNCTION DOES : Remove table whose name is given as paramater from the given database. 
TO-DO-LIST : 
	1) Look for the table in the database.
	2) Check if the table is root or not.
	3) Remove table if it's found.
*/
void remove_table(database *d, char *name) {
	tables *cur_ptr;
	tables *former_ptr;
	int is_found;
	
	if (d->tlist == NULL) printf("There is no table in the database with that name.\n");
	
	/* Check if the given table is the root of the tables linked list. */
	else if (strcmp(name, d->tlist->t->tableName) == 0) {
		cur_ptr = d->tlist;
		d->tlist = d->tlist->next;
		
		table *table = cur_ptr->t;
		free_table(table);
		free(cur_ptr);
		
		d->n--;
	}
	
	/* If it's not the root, then look for the table in the table list and remove it. */
	else {
		former_ptr = d->tlist;
		cur_ptr = d->tlist->next;
		int is_found = 0;
		
		while (!is_found && cur_ptr != NULL) {
			if (strcmp(name, cur_ptr->t->tableName) == 0) is_found = 1;
			else {
				former_ptr = cur_ptr;
				cur_ptr = cur_ptr->next;
			}
		}
	
		if (!is_found) printf("There is no table in the database with that name.\n");
		
		else {
			former_ptr->next = cur_ptr->next;
			
			table *table = cur_ptr->t;
			free_table(table);
			
			d->n--;
			free(cur_ptr->t);
			free(cur_ptr);
		}
	}
}

