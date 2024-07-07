#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"

int main () {

	/********* Create database function test : ********/
	
	printf("************** CREATE DATABASE FUNCTION TEST **************\n\n");
	
	database *db1 = create_database("db1");
	printf("Part case 1 Database Name : %s, The Database Name should be : %s\n", db1->name, "db1");
	
	database *db2 = create_database("db2");
	printf("Part case 2 Database Name : %s, The Database Name should be : %s\n", db2->name, "db2");
	
	database *db3 = create_database("db3");
	printf("Part case 3 Database Name : %s, The Database Name should be : %s\n", db3->name, "db3");
	
	
	/************ Show table function test : *******/
	
	printf("\n************** SHOW TABLE FUNCTION TEST **************\n\n");
	
	/* Put new tables into the database 1 manually. */
	table *table1 = create_new_table_node();
	
	table1->tableName = (char*) calloc(sizeof(char), 7);
	strcpy(table1->tableName, "table1");
	
	
	tables *tablesNode1 = create_new_tables_node(table1);
	
	db1->tlist = tablesNode1;
	db1->n = 1;
	
	
	printf("\nCase 1 Show table function result : \n\n");
	show_table(db1);
	printf("\nCase 1 Tables should be : \n%s \n", "table1");
	
	table *table2 = create_new_table_node();
	
	table2->tableName = (char*) calloc(sizeof(char), 7);
	strcpy(table2->tableName, "table2");
	
	tables *tablesNode2 = create_new_tables_node(table2);
	
	tablesNode1->next = tablesNode2;
	db1->n = 2;
	
	printf("\nCase 2 Show table function result : \n\n");
	show_table(db1);
	printf("\nCase 2 Tables should be : \n%s \n%s \n\n", "table1", "table2");
	
	printf("\nCase 3 Show table function result : \n\n");
	show_table(db2);
	printf("\nCase 3 Tables Should be : Empty Set.\n\n");
	
	/********** Insert table function test : ********/
	
	printf("\n************** INSERT TABLE FUNCTION TEST **************\n\n");
	
	/* Function will add the table given by command into the given database db2. */
	char table_command1[70] = "workers,4,id|int,name|char(40),level|char,salary|double";
	
	printf("Case 1 Insert Table --- Show table result : \n\n");
	insert_table(db3, table_command1);
	show_table(db3);
	printf("\nCase 1 Expected Tables should be : \n%s \n\n", "workers");

	char table_command2[70] = "houses,4,address|char(40),room_number|int,year|int,price|double"; 
	
	printf("Case 2 Insert Table --- Show table result : \n\n");
	insert_table(db3, table_command2);
	show_table(db3);
	printf("\nCase 2 Expected Tables should be : \n%s \n%s \n\n", "workers", "houses");
	
	char table_command3[70] = "students,3,no|inttt,name|char(50),grade|double";
	
	printf("Case 3 Insert Table --- Insert Table Function Result = \n");
	insert_table(db3, table_command2);
	printf("\nCase 3 Insert Table --- Insert Table Function Result Should Be = \n");
	printf("There is a problem with the command. Be sure you enter valid command and try again...\n");
	
	
	printf("\nCase 3 Insert Table --- Show table result : \n\n");
	show_table(db3);
	printf("\nCase 3 Expected Tables should be : \n%s \n%s \n\n", "workers", "houses");

	
	/************ Describe table function test : *******/
	
	printf("\n************** DESCRIBE TABLE FUNCTION TEST **************\n\n");
	
	printf("Case 1 Describe Table '%s' result : \n\n", "workers");
	desc_table(db3, "workers");
	printf("\nCase 1 Expected Result : \n");
	printf("id		int			YES		\n");
	printf("name		char(40)		YES		\n");
	printf("level		char			YES		\n");
	printf("salary		double			YES		\n");
	
	printf("\nCase 2 Describe Table '%s' result : \n\n", "houses");
	desc_table(db3, "houses");
	printf("\nCase 1 Expected Result : \n");
	printf("address			char(40)		YES		\n");
	printf("room_number		int			YES		\n");
	printf("year			int			YES		\n");
	printf("price			double			YES		\n");
	
	printf("\nCase 3 Describe Table '%s' result : \n\n", "students");
	desc_table(db3, "students");
	printf("\nCase 3 Expected Result : \n");
	printf("There is no table with that name.\n");
	
	
	/********** Insert record / Select from table Functions Test : *********/
	
	printf("\n************** INSERT RECORD/SELECT FROM TABLE FUNCTIONS TEST **************\n\n");
	
	printf("Case 1 Insert New Record Below Into the Table 'workers' and Show All Records with Select From Function : \n");
	printf("New Record : id = 1, name = Emre Oytun, level = J, salary = 10000\n\n");
	
	get_new_record_and_insert(db3, "workers");
	printf("\nSelect from table 'workers' result after insertion of new record : \n\n");
	select_from_table(db3, "workers");
	
	printf("\nCase 2 Insert New Record Below Into the Table 'workers' and Show All Records with Select From Function : \n");
	printf("New Record : id = 2, name = Mehmet Yapici, level = S, salary = 15000\n\n");
	
	get_new_record_and_insert(db3, "workers");
	printf("\nSelect from table 'workers' result after insertion of new record : \n\n");
	select_from_table(db3, "workers");
	
	
	/******** Select specific record from table function test : *********/
	
	printf("\n************** SELECT SPECIFIC RECORD FROM TABLE FUNCTION TEST **************\n\n");
	
	printf("Case 1 Select the record from table 'workers' whose id = 1\n"); 
	printf("Expected Result = 1	Emre Oytun	J	10000\n\n");
	
	printf("Result from function = \n");
	select_specific_record_from_table(db3, "workers", "id", "1");
	
	
	printf("\nCase 2 Select the record from table 'workers' whose name = Mehmet Yapici\n"); 
	printf("Expected Result = 2	Mehmet Yapici	S	15000\n\n");
	
	printf("Result from function = \n");
	select_specific_record_from_table(db3, "workers", "name", "Mehmet Yapici");
	
	printf("\nCase 3 Select the record from table '%s' whose grade = %lf\n", "students", 86.12);
	printf("Expected Result = There is no table in the database with that name.\n\n");
	
	printf("Result from function = \n");
	select_specific_record_from_table(db3, "students", "grade", "86.12");
	
	/********* Insert Key Function Test : ***********/
	
	printf("\n************** INSERT KEY FUNCTION TEST **************\n\n");
	
	printf("Case 1 Insert Key into 'workers' table in 'id' field : \n");
	insert_key(db3, "workers", "id");
	
	printf("\nDescribe table after insertion of key : \n");
	desc_table(db3, "workers");
	
	printf("\nSelect a specific record from table (Key should be used) :\n");
	printf("Select the record from table 'workers' whose id = 1\n");
	printf("Result = \n\n");
	select_specific_record_from_table(db3, "workers", "id", "1");
	
	printf("\nCase 2 Insert Key into 'workers' table in 'old' field : \n");
	
	printf("Result = \n");
	insert_key(db3, "workers", "old");
	
	printf("\nExpected Result = There is no field called 'old' in the table 'workers'\n");
	
	/******** WRITE/READ FROM FILE TEST : **********/
	
	printf("\n************** WRITE/READ FUNCTIONS TEST **************\n\n");
		
	int r;
	write_db_to_file(db3);
	database *file_db = read_db_from_file(&r);
		
	printf("\nShow table function result should be = \n");
	printf("-workers\n");
	printf("-houses\n");
	
	printf("\nShow table result = \n");
	show_table(file_db);
	
	printf("\nSelect from table 'workers' result should be = \n");
	printf("1	Emre Oytun	J	10000\n");
	printf("2	Mehmet Yapici	S	15000\n");
	
	printf("\nSelect from table result = \n");
	select_from_table(file_db, "workers");
	
	/********* Remove Table Function Test : *********/
	
	printf("\n************** REMOVE TABLE FUNCTION TEST **************\n\n");
	
	printf("Before Removing Table : \n");
	show_table(db3);
	
	printf("\n----- Remove table 'workers' from database 'db3' ---- \n\n");
	remove_table(db3, "workers");
	
	printf("After Removing Table : \n");
	show_table(db3);
	
	printf("\n----- Remove table 'houses' from database 'db3' ----- \n\n");
	remove_table(db3, "houses");
	
	printf("After Removing Table : \n");
	show_table(db3);
	

	free(db1);
	free(db2);
	free(db3);
	free(file_db);
	return 0;
}
