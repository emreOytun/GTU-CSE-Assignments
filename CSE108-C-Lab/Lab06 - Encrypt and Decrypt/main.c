#include <stdio.h>

/* x represent each row's first letter. */
void fill_arr(char arr[][26]) {
	int i, j;
	char x = 'A';
	char y;
	
	x = 'A';
	for(i=0; i<26; i++) {
		y = x;
		
		for(j=0; j<26; j++) {
			arr[i][j] = y;
			if (y == 'Z') y = 'A';
			else y++;	
		}
		
		if (x == 'Z') x = 'A';
		else x++;
	}

}

void print_arr(char arr[][26]) {
	int i, j;
	for(i=0; i<26; i++) {
		for(j=0; j<26; j++) {
			printf("%c ", arr[i][j]);
		}
		printf("\n");
	}

}

/* Find the char according to their indexes. */
char encrypt(char arr[][26], int x, int y) {
	char ch = arr[x][y];
	return ch;
}

/* Look for the cipher char in the row of the character of the key. */
char decrypt(char arr[][26], int x, char cipher) {
	int i;
	char ch;
	int is_found = 0;
	
	for(i=0; i<26 && is_found != 1; i++) {
		if (arr[x][i] == cipher) {
			ch = arr[0][i];
			is_found = 1;
		}	
	}
	
	return ch;
}

int main () {

	char arr[26][26];
	fill_arr(arr);
	print_arr(arr);
	
	char plaintext[11];
	char key[11];
	char ciphertext[11];
	
	int i;
	char ch;
	
	/* ENCRYPTION */ 
	printf("*** ENCRYPTION ***\n\n"); 
	
	printf("Plaintext: ");
	for(i=0; i<10; i++) {
		ch = getchar();
		plaintext[i] = ch;
	}
	ch = getchar(); // space'i atla.
	plaintext[10] = '\0';

	printf("Key: ");
	for(i=0; i<3; i++) {
		ch = getchar();
		key[i] = ch;
	}
	ch = getchar(); // space'i atla.
	key[10] = '\0';
	
	/* modify the key. */	
	int j = 0;
	for(i=3; i<10; i++) {
		key[i] = key[j];
		
		if (j==2) j = 0;
		else j++;
	}
	printf("Keystream = %s\n", key);

	for(i=0; i<10; i++) {
		int x = key[i] - 'A';
		int y = plaintext[i] - 'A';
		
		ch = encrypt(arr, x, y);
		ciphertext[i] = ch;
	}
	ciphertext[10] = '\0';
	
	printf("Ciphertext = %s", ciphertext);
	
	/* DECRYPTION */
	printf("\n\n*** DECRYPTION ***\n\n");

	/* Get ciphertext. */
	printf("Ciphertext: ");
	for(i=0; i<10; i++) {
		ch = getchar();
		ciphertext[i] = ch;
	}
	ch = getchar(); // Skip the '\n' character at the end of the input. 
	/* Put EOF at the end of the string. !! */ 
	ciphertext[10] = '\0';

	/* Get key. */
	printf("Key: ");
	for(i=0; i<3; i++) {
		ch = getchar();
		key[i] = ch;
	}
	ch = getchar();
	key[10] = '\0';
	
	/* modify the key. */	
	j = 0;
	for(i=3; i<10; i++) {
		key[i] = key[j];
		
		if (j==2) j = 0;
		else j++;
	}
	printf("Keystream = %s\n", key);

	for(i=0; i<10; i++) {
		int x = key[i] - 'A';
		char cipher = ciphertext[i];
		
		ch = decrypt(arr, x, cipher);
		plaintext[i] = ch;
		
	}
	plaintext[10] = '\0';
	
	printf("Plaintext: %s\n", plaintext);
	
	

	return 0;
	
}
