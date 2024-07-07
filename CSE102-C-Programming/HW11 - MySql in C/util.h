#ifndef _UTIL_H_
#define _UTIL_H_

typedef union var_data_t {
	int i;
	double d;
	float f;
	char c;
	char *str;
} var_data_t;

/* Int -> 1 Double -> 2 Float -> 3 Char->4 Str->5 */
typedef struct data_node {
	int data_type;
	int charNum_ifStr;
	var_data_t data;
} data_node;

/* Records are kept in a linked list inside a table, and each record has its data inside. */
typedef struct record_t {
	struct record_t *next;
	data_node *recordData;
} record_t;


typedef struct key_node {
	struct key_node *next;
	var_data_t keyValue;
	record_t *recordAdress;
}key_node;

typedef struct keys {
	struct keys *next;
	
	char *field;
	int data_type;
	int charNum_ifStr;
	
	key_node *keyList; 
} keys;

/* tableName, records and keys has been added as addition. */
typedef struct table {
	char *tableName;
	int field_num;
	
	char **field;
	char **type;
	int *isNull;
	int *isKey;
	
	/* Keeps the records linked list. */
	record_t *records;
	keys *keys;
} table;

typedef struct tables {
	struct tables *next;
	table *t;
} tables;


typedef struct database {
	tables *tlist;
	int n;	/* number of tables */
	char *name; /* name of database */
} database;

void write_db_to_file(database *db);
database* read_db_from_file();

void clear_buffer();
void insert_keyNode_into_keyList(keys *key, key_node *key_ptr);
void insert_key_into_keysList(table *t, keys *key);
void insert_key(database *d, char *tableName, char *field);


void update_keys_on_table(table *t, record_t *new_record);
void insert_record_on_table(table *t, record_t *new_record);
void get_new_record_and_insert(database *d, char *tName);

void select_from_table(database *d, char *tableName);
void select_specific_record_from_table(database *d, char *tableName, char *field, char *queryInput);

database *create_database(char *name);

tables* create_new_tables_node(table *new_t);
void copy_string_by_calloc(char **dest, char *source);
table *create_new_table_node();
void insert_table (database *d, char *command);

void show_table(database *d);
void desc_table(database *d, char *tableName);

void free_record(record_t *r);
void free_key_node(key_node *kn);
void free_table(table *t);

void remove_table(database *d, char *name);

#endif /* _UTIL_H_ */
