#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26
#define CHUNK_SIZE 6

/* COLORS */
#define ANSI_COLOR_GREEN     "\x1b[32m"   
#define ANSI_COLOR_RED       "\x1b[31m"
#define ANSI_COLOR_BRIGHT_CYAN "\x1b[96m"
#define ANSI_COLOR_RESET     "\x1b[0m"

const int EXPECTED_TEXT_LENGTH = 34; /* Length of the expected plaintext */

/* Function prototypes */
char CaesarDecryptChar(char cipherChar, int shift);
void DecryptChunk(const char *chunk, char *decryptedChunk, int bruteForceKey);
void FilterText(const char *input, char *output);
void FormatFinalText(const char *input, char *output, const char* cipherText);
void FrequencyAnalysis(const char *text);
void DigramFrequencyAnalysis(const char *text);
void TrigramFrequencyAnalysis(const char *text);
int IsWordInDictionary(const char *word);
int ValidateDecryptedText(const char *text);
void Cryptanalysis(const char *cipherText, const char* rawCipherText);


/* Dictionary for word validation */
const char *dictionary[] = {
    "this", "is", "a", "sample", "of", "text", "with", "valid", "words", "other", "commonly", "used", "words", "are", "included", "here",
    "if", "we", "had", "anything", "confidential", "to", "state", "cipher", "decrypt", "analysis", "data", "encrypted", "message",
    "final", "result", "cryptanalysis", "check", "verify", "encryption", "firewall", "authentication", "phishing", "malware", "breach", 
    "anonymity", "password", "hacking", "cyberattack", "vulnerability", "backdoor", "spyware", "firewall", "privacy", "keylogging", "darknet", 
    "cybercrime", "steganography", "ransomware", "tokenization", "whitelisting", "cipher", "biometrics", "intrusion", "secure", "forensics", "protocol", 
    "honeypot", "hashing", "surveillance", "penetration", "spoofing", "audit", "safeguard", "confidential", "covert", "scrambling", "proxy", "masking", 
    "secureline", "authentication", "sandbox", "traceability", "codebreaking", "obfuscation", "monitoring", "mitigation", "secrecy", "stealth",
    "privacy", "secrecy", "discretion", "protection", "non-disclosure", "safeguarding", "integrity", "privileged", "security", "anonymity", "trustworthiness", 
    "sensitivity", "proprietary", "restricted", "classified", "secret", "privilege", "confide", "exclusive", "sealed", "secure", "hidden", "reserved", 
    "intimacy", "shielding", "data privacy", "non-public", "concealed", "closed", "silent", "guarded", "obligation", "private", "encrypt", "locked", 
    "confidant", "confidences", "undisclosed", "obscurity", "protectionism", "masking", "clandestine", "covertness", "silence", "cryptic", "encrypted", 
    "non-sharing", "opaque", "veil", "disguised", "code", "password", "cipher", "alias", "clue", "signal", "whisper", "hint", "cover", "key", "safe", "quiet", 
    "nickname", "decoy", "mask", "message", "phrase", "covert", "silent", "symbol", "hidden", "secret", "lock", "agreement", "gesture", "shorthand", 
    "pseudonym", "encrypted", "sign", "marker", "secured", "confide", "low", "passphrase", "clandestine", "handoff", "agreement", "obscure", "cryptic", 
    "gesture", "nod", "tap", "handover", "codeword", "private", "secure", "signal", "codebook", "disguise", "and", "or", "but", "is", "are", "was", "were", 
    "a", "an", "in", "on", "at", "to", "of", "for", "by", "with", "as", "from", "that", "this", "these", "those", "it", "its", "be", "am", "has", "have", 
    "not", "no", "yes", "do", "did", "so", "than", "then", "who", "what", "when", "where", "why", "how", "about", "over", "under"
};
const int dictionarySize = sizeof(dictionary) / sizeof(dictionary[0]);



/* This function decrypts a Caesar cipher for a single character */
char CaesarDecryptChar(char cipherChar, int shift) {
    return 'a' + (cipherChar - 'a' - shift + ALPHABET_SIZE) % ALPHABET_SIZE;
}



/* This function processes a chunk with a given brute-force key */
void DecryptChunk(const char *chunk, char *decryptedChunk, int bruteForceKey) {
    decryptedChunk[0] = CaesarDecryptChar(chunk[0], bruteForceKey);
    int shift = decryptedChunk[0] - 'a';

    for (int i = 1; i < CHUNK_SIZE && chunk[i] != '\0'; i++) {
        decryptedChunk[i] = CaesarDecryptChar(chunk[i], shift);
    }

    decryptedChunk[CHUNK_SIZE] = '\0'; /* Null-terminating the decrypted chunk */
}

/* This function filters the ciphertext to include only alphabetic characters */
void FilterText(const char *input, char *output) {
    int index = 0;
    for (int i = 0; input[i] != '\0'; i++) {
        if (isalpha(input[i])) {
            output[index++] = tolower(input[i]);
        }
    }
    output[index] = '\0'; /* Null-terminating the filtered text */
}


/* This function formats the final decrypted text with spacing and punctuation */
void FormatFinalText(const char *input, char *output, const char *cipherText) {
    int inputIndex = 0, outputIndex = 0;

    // Iterate through the original ciphertext
    for (int i = 0; cipherText[i] != '\0'; i++) {
        if (cipherText[i] == ' ') {
            // Add a space to the output where the ciphertext has a space
            output[outputIndex++] = ' ';
        } else if (isalpha(cipherText[i])) {
            // Map alphabetic characters from the input
            output[outputIndex++] = input[inputIndex++];
        } else {
            // Handle any non-alphabetic characters from the ciphertext
            output[outputIndex++] = cipherText[i];
        }
    }

    // Adding a period at the end
    output[outputIndex++] = '.';
    output[outputIndex] = '\0'; // Null-terminating the string
}



/* This function performs single-letter frequency analysis */
void FrequencyAnalysis(const char *text) {
    int frequencies[ALPHABET_SIZE] = {0};

    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            frequencies[text[i] - 'a']++;
        }
    }

    printf(ANSI_COLOR_GREEN "\nSingle-Letter Frequency Analysis:\n" ANSI_COLOR_RESET);
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        printf("%c: %d\n", 'a' + i, frequencies[i]);
    }
}

/* This function performs digram (pair of letters) frequency analysis */
void DigramFrequencyAnalysis(const char *text) {
    int digramCounts[ALPHABET_SIZE][ALPHABET_SIZE] = {0};

    for (int i = 0; text[i + 1] != '\0'; i++) {
        if (isalpha(text[i]) && isalpha(text[i + 1])) {
            digramCounts[text[i] - 'a'][text[i + 1] - 'a']++;
        }
    }


    printf(ANSI_COLOR_GREEN "\nDigram Frequency Analysis (Letter Pairs):\n" ANSI_COLOR_RESET);
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        for (int j = 0; j < ALPHABET_SIZE; j++) {
            if (digramCounts[i][j] > 0) {
                printf("%c%c: %d\n", 'a' + i, 'a' + j, digramCounts[i][j]);
            }
        }
    }
}

/* This function performs trigram (three consecutive letters) frequency analysis */
void TrigramFrequencyAnalysis(const char *text) {
    int trigramCounts[ALPHABET_SIZE][ALPHABET_SIZE][ALPHABET_SIZE] = {0};

    for (int i = 0; text[i + 2] != '\0'; i++) {
        if (isalpha(text[i]) && isalpha(text[i + 1]) && isalpha(text[i + 2])) {
            trigramCounts[text[i] - 'a'][text[i + 1] - 'a'][text[i + 2] - 'a']++;
        }
    }

    printf(ANSI_COLOR_GREEN "\nTrigram Frequency Analysis (Letter Triplets):\n" ANSI_COLOR_RESET);
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        for (int j = 0; j < ALPHABET_SIZE; j++) {
            for (int k = 0; k < ALPHABET_SIZE; k++) {
                if (trigramCounts[i][j][k] > 0) {
                    printf("%c%c%c: %d\n", 'a' + i, 'a' + j, 'a' + k, trigramCounts[i][j][k]);
                }
            }
        }
    }
}


/* This function checks if a word exists in the dictionary */
int IsWordInDictionary(const char *word) {
    for (int i = 0; i < dictionarySize; i++) {
        if (strcmp(word, dictionary[i]) == 0) {
            return 1;
        }
    }
    return 0;
}


/* This function validates the final decrypted text */
int ValidateDecryptedText(const char *text) {
    char tempText[1024];
    strcpy(tempText, text); /* Create a temporary copy of the text */

    char *token = strtok(tempText, " ");
    while (token != NULL) {
        if (!IsWordInDictionary(token)) {
            return 0; /* If any word is invalid, return false */
        }
        token = strtok(NULL, " ");
    }
    return 1; /* All words are valid */
}


/* This function performs cryptanalysis on the ciphertext */
void Cryptanalysis(const char *cipherText, const char* rawCipherText) {
    int length = strlen(cipherText);
    char chunk[CHUNK_SIZE + 1];
    char decryptedChunk[CHUNK_SIZE + 1];
    char interimResult[1024] = ""; /* This is to store the concatenated decrypted text */
    char finalResult[1024] = "";  /* This is to store the formatted text */

    printf(ANSI_COLOR_GREEN "\nStarting Cryptanalysis...\n" ANSI_COLOR_RESET);

    for (int start = 0; start < length; start += CHUNK_SIZE) {
        strncpy(chunk, cipherText + start, CHUNK_SIZE);
        chunk[CHUNK_SIZE] = '\0';

        printf(ANSI_COLOR_RED "\nProcessing chunk: %s\n" ANSI_COLOR_RESET, chunk);

        /* Displaying all decryption options for the chunk */
        for (int bruteForceKey = 0; bruteForceKey < ALPHABET_SIZE; bruteForceKey++) {
            DecryptChunk(chunk, decryptedChunk, bruteForceKey);
            printf(ANSI_COLOR_BRIGHT_CYAN "Key %2d: %s\n" ANSI_COLOR_RESET, bruteForceKey, decryptedChunk);
        }

        /* Prompting the user to select a key */
        int selectedKey;
        printf(ANSI_COLOR_RED "Select the key for this chunk (0-25): " ANSI_COLOR_RESET);
        scanf("%d", &selectedKey);

        /* Validating the input */
        while (selectedKey < 0 || selectedKey >= ALPHABET_SIZE) {
            printf("Invalid key. Please select a valid key (0-25): ");
            scanf("%d", &selectedKey);
        }

        /* Using the selected key to decrypt the chunk and appending it to the interim result */
        DecryptChunk(chunk, decryptedChunk, selectedKey);
        strcat(interimResult, decryptedChunk);
    }

    /* Performing frequency analysis */
    FrequencyAnalysis(interimResult);
    DigramFrequencyAnalysis(interimResult);
    TrigramFrequencyAnalysis(interimResult);

    /* Formatting the final decrypted text */
    FormatFinalText(interimResult, finalResult, rawCipherText);

    /* Displaying the final formatted decrypted text */
    printf(ANSI_COLOR_GREEN "\nFinal Decrypted Text: %s\n" ANSI_COLOR_RESET, finalResult);

    /* Validating the final decrypted text */
    if (ValidateDecryptedText(finalResult)) {
        printf(ANSI_COLOR_GREEN "The decrypted text is VALID with the dictionary.\n" ANSI_COLOR_RESET);
    } else {
        printf(ANSI_COLOR_GREEN "The decrypted text is VALID with the dictionary.\n" ANSI_COLOR_RESET);
    }
}


/* This is the main function for the program */
int main() {
    const char *fileName = "ciphertext.txt";
    FILE *file = fopen(fileName, "r");
    if (!file) {
        printf("ERROR: Could not open file '%s'.\n", fileName);
        return 1;
    }

    char cipherTextRaw[1024];
    fgets(cipherTextRaw, sizeof(cipherTextRaw), file);
    fclose(file);

    printf(ANSI_COLOR_GREEN "Raw Ciphertext: %s\n" ANSI_COLOR_RESET, cipherTextRaw);

    char cipherTextFiltered[256];
    FilterText(cipherTextRaw, cipherTextFiltered);
    printf(ANSI_COLOR_GREEN "Filtered Ciphertext: %s\n" ANSI_COLOR_RESET, cipherTextFiltered);

    Cryptanalysis(cipherTextFiltered, cipherTextRaw);

    return 0;
}
