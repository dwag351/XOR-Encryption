#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
/* This file was tested using the GNU compiler "gcc", using different compilers may give varying results. */

/* This function appends original_name to the end of new_name. */
void make_new_name(char *new_name, char *original_name) {
	strcat (new_name, original_name);
}

/* This function returns the length of the password. */
int length_of_password(char *password) {
	return strlen (password);
}

/* This function returns the integers 1 or 0 if the given character is apart of the alphabet. */
int is_alpha(char c) {
	int result;
	if (c >= 65 && c <= 90) {
		result = 1;
	} else if (c >= 97 && c <= 122) {
		result = 1;
	} else {
		result = 0;
	}
	return result;
}

/* This function returns the integers 1 or 0 if the given character is a numerical digit or not. */
int is_digit(char c) {
	int result;
	if (c >= 48 && c <= 57) {
		result = 1;
	} else {
		result = 0;
	}
	return result;
}

/* This function returns the integers 1 or 0 if the given password is of a valid length and has valid characters. */
int is_valid_password(char *password) {
	int result = 0;
	if (length_of_password (password) < 8) {
		printf ("The password needs to have at least 8 characters.\n");
		result = 1;
	}
	int alpha = 0;
	int number = 0;
	for (int i = 0; i < length_of_password (password); i++) {
		if (is_alpha (password[i])) {
			alpha++;
		}
		if (is_digit (password[i])) {
			number++;
		}
	}
	if (alpha == 0) {
		printf ("The password needs to contain at least 1 alphabetical character.\n");
		result = 1;
	}
	if (number == 0) {
		printf ("The password needs to contain at least 1 digit.\n");
		result = 1;
	}
	return result;
}

/* This function performs the encryption of the given file by taking blocks of binary data from said file and */
/* encrypting them with the valid password through the use of the XOR function. */
void perform_XOR(char *input_filename, char *output_filename, char *password) {
	FILE *file, *newFile;
	file = fopen(input_filename, "rb");
	newFile = fopen(output_filename, "wb");
	int length = length_of_password(password);
	char check_password[15];
	strcpy(check_password, password);
	char block[15];
	int i, numBytes;
	int count = 5;
	do {
		numBytes = fread(block, 1, length, file);
		for (i = 0; i < numBytes; i++) {
			block[i] = block[i] ^ check_password[i];
			if (count > 0) {
				printf("%02x\n", (unsigned int)(block[i] & 0xFF));
				count--;
			}
		}
		fwrite(block, 1, numBytes, newFile);
	} while (numBytes == length);
	fclose (newFile);
	fclose (file);
}

void print_first_five(char *filename);

/* This is the main function which takes the input of the filename and the password. */
int main(int argc, char *argv[]) {
	if (argc == 3) {
		char* filename = argv[1];
		char* password = argv[2];
		char new_filename[18] = "new-";
		make_new_name (new_filename, filename);
		printf ("New filename = %s\n", new_filename);
		printf ("Password Length = %d\n", length_of_password (password));
		if (is_valid_password (password) == 0) {
			perform_XOR (filename, new_filename, password);
		}
	} else {
		printf ("Usage: ./A2 filename password");
	}
	return 0;
}
