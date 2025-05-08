/*
Group Members: Ayush Gowda, Nikita Astionov, Syed Shayan Ali
This is a C program that demonstrates the process of encryption and decryption to a user through a console output.
The program first reads the Plain Text from the "plaintext.txt" file, encrypts it and writes the Cipher Text to the "ciphertext.txt" file.
The program then reads the Cipher Text from the "ciphertext.txt" file, decrypts it and writes the Decrypted Text to the "decrypted.txt" file.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* COLORS */
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_BRIGHT_CYAN    "\x1b[96m"
#define ANSI_COLOR_RESET   "\x1b[0m"

/* 
    This function gives the substitution key 
*/

void EncryptiontionKeyCreation(char *Encryption_Key) {
    char alphabets[] = "abcdefghijklmnopqrstuvwxyz";
    char secret_key[] = "hilwmkbdpcvazusjgrynqxofte"; /* The selected key for this project */

    for (int i = 0; i < 26; i++) {
        Encryption_Key[alphabets[i] - 'a'] = secret_key[i];
    }
}



/* 
    This function gives the reverse of the substitution key for decryption 
*/
void DecryptionKeyCreation(char *Encryption_Key, char *Reverse_Key) {
    for (int i = 0; i < 26; i++) {
        Reverse_Key[Encryption_Key[i] - 'a'] = 'a' + i;
    }
}


/* 
    This is the Caesar Cipher Shift for encryption 
*/
char CaesarShift(char letter, int shift) {
    return 'a' + (letter - 'a' + shift) % 26;
}

/* 
    This is the Caesar Cipher Shift for decryption 
*/
char DecryptingCaesarShift(char letter, int shift) {
    return 'a' + (letter - 'a' - shift + 26) % 26;
}


/* 
    This is the function for encryption along with the console output 
*/ 


void Encrypt(const char *PlainText, char *CipherText, char *Encryption_Key) {
    int index = 0;         /* This tracks the index for the Cipher Text */
    int shift = 0;          /* This is to declare the shift variable to be used in subsequent characters */
    int alphabetCount = 0;     /* This tracks the alphabetic characters for switching between the Substitution Method and Caesar Cipher */
    

    printf("\nEncryption Process: \n");
    for (int i = 0; PlainText[i] != '\0'; i++) {
        if (isalpha(PlainText[i])) {
            char LowercaseCharacter = tolower(PlainText[i]);

            /* This "if statement" applies the Substitution Method every 6th alphabetic character including the 1st one */
            if (alphabetCount == 0 || alphabetCount % 6 == 0) {

                /* This is the Mono-alphabetic Substitution Method */
                CipherText[index] = Encryption_Key[LowercaseCharacter - 'a'];
                printf(ANSI_COLOR_RED "Plaintext '%c': Mono-alphabetic Substitution '%c'\n", LowercaseCharacter, CipherText[index]); printf(ANSI_COLOR_RESET);

                /* This sets the shift value to the index of the plain Text character that is used for substitution */
                shift = LowercaseCharacter - 'a';

            } else {

                /* This is the Caesar Cipher method using the same shift value for the next 5 alphabetic characters */
                CipherText[index] = CaesarShift(LowercaseCharacter, shift);
                printf(ANSI_COLOR_BRIGHT_CYAN "Plaintext '%c': Caesar Shift Cipher (Shift by %d): '%c'\n", LowercaseCharacter, shift, CipherText[index]); printf(ANSI_COLOR_RESET);
            }

            alphabetCount++; /* This will only increment the alphabetCount for alphabetic characters */

        } else {

            /* This is used for preserving spaces or punctuation in the Text */
            CipherText[index] = PlainText[i];
        }

        index++;  /* This will increment the index value after each iteration, regardless of character type */

    }
}



/*
    This is the function for decryption along with the console output
*/
void Decrypt(const char *CipherText, char *DecryptedText, char *Decryption_Key) {
    int index = 0;          /* This tracks the index for the decrypted text */
    int alphabetCount = 0;    /* This tracks the alphabetic characters for switching between the decryption for Mono-alphabetic cipher and decryption for Caesar Cipher */
    int shift = 0;          /* This is to declare the shift variable to be used in subsequent characters */


    printf("\nDecryption Process:\n");
    for (int i = 0; CipherText[i] != '\0'; i++) {
        if (isalpha(CipherText[i])) {
            char LowercaseCharacter = tolower(CipherText[i]);
            /* This "if statement" applies the Reverse Substitution Method every 6th alphabetic character including the 1st one */
            if (alphabetCount == 0 || alphabetCount % 6 == 0) {

                /* This is the Reverse Mono-alphabetic Substitution Method */
                DecryptedText[index] = Decryption_Key[LowercaseCharacter - 'a'];
                printf(ANSI_COLOR_RED "Ciphertext '%c': Reverse Mono-Alphabetic Substitution: '%c'\n", LowercaseCharacter, DecryptedText[index]); printf(ANSI_COLOR_RESET);


                /* This sets the shift value to the index of the plain Text character decrypted that is used for substitution */
                shift = DecryptedText[index] - 'a';

            } else {

                /* This is the Decrypting Caesar Cipher method using the same shift value for the next 5 alphabetic characters */
                DecryptedText[index] = DecryptingCaesarShift(LowercaseCharacter, shift);
                printf(ANSI_COLOR_BRIGHT_CYAN "Ciphertext '%c': Decrypting Caesar Shift Cipher (Shift by %d): '%c'\n", LowercaseCharacter, shift, DecryptedText[index]); printf(ANSI_COLOR_RESET);
            }

            alphabetCount++; /* This will only increment the alphabetCount for alphabetic characters */


        } else {

            /* This is used for preserving spaces or punctuation in the Text */
            DecryptedText[index] = CipherText[i];
        }

        index++;  /* This will increment the index value after each iteration, regardless of character type */
    }
    DecryptedText[index] = '\0';  /* This will null-terminate the string */
}



/* 
    This function is used to read Text from a File 
*/
char *readFromFile(const char *FileName) {
    FILE *File = fopen(FileName, "r");
    if (File == NULL) {
        printf("FILE COULD NOT BE OPENED %s\n", FileName);
        exit(0);
    }

    /* This Gets the File size */
    fseek(File, 0, SEEK_END);
    long Size_of_File = ftell(File);
    rewind(File);

    /* This allocates memory for the file contents */
    char *FileContent = (char *)malloc((Size_of_File + 1) * sizeof(char));
    if (FileContent == NULL) {
        printf("Error in allocating memory for File Contents\n");
        exit(0); 
    }

    /* This reads the File into the FileContent */
    fread(FileContent, sizeof(char), Size_of_File, File);
    FileContent[Size_of_File] = '\0'; /* This will Null-terminate the string */
    fclose(File);
    return FileContent;
}


/* 
    This functions Writes into a File
*/
void FileWriter(const char *FileName, const char *Text) {
    FILE *File = fopen(FileName, "w");
    if (File == NULL) {
        printf("THE FILE COULD NOT BE OPENED %s\n", FileName);
        exit(1);
    }
    fprintf(File, "%s", Text);
    fclose(File);
}


/*
    This is the Main Function
*/
int main() {
    /* Here the Substitution key is created */
    char Encryption_Key[26];
    EncryptiontionKeyCreation(Encryption_Key);

    /* Here the Decryption Key is created */
    char Decryption_Key[26];
    DecryptionKeyCreation(Encryption_Key, Decryption_Key); 

    /* This reads the Plain Text from the input File */
    char *PlainText = readFromFile("plaintext.txt");
    printf("Plain Text: %s\n", PlainText);

    /* This allocates memory for the Cipher Text and Decrypted Text with error checking */
    char *CipherText = (char *)malloc((strlen(PlainText) + 1) * sizeof(char));
    if (CipherText == NULL) {
        printf("Error in Allocating Memory for File Contents\n");
        exit(0);
    }

    char *DecryptedText = (char *)malloc((strlen(PlainText) + 1) * sizeof(char));
    if (DecryptedText == NULL) {
        printf("Error in Allocating Memory for File Contents\n");
        free(CipherText);
        exit(0);
    }

    /* This encrypts the Plain Text and displays the detailed console output */
    Encrypt(PlainText, CipherText, Encryption_Key);
    printf("\nFinal Cipher Text: %s\n", CipherText);

    /* This writes the cipher text into the output file */
    FileWriter("ciphertext.txt", CipherText);

    /* This Decrypts the Cipher Text and displays the detailed console output */
    Decrypt(CipherText, DecryptedText, Decryption_Key);
    printf("\nFinal Decrypted Text: %s\n", DecryptedText);

    /* This writes the Decrypted Text into the Output File */
    FileWriter("decrypted.txt", DecryptedText);
    return 0;
}
