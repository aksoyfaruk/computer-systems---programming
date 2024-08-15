#include <stdio.h>
#include <ctype.h> 
#include <stdlib.h>
#include <string.h>

char encryptCharacter(char ch, int shift);
void encryptFile(char *inputFile, char *outputFile, int shift);
void decryptFile(char *inputFile, char *outputFile, int shift);
int findShift(const char *filename);



int main() {
    // task 1
    char *inputFile = "message1.txt";
    char *outputFile = "message1_encrypted.txt";
    int shiftValue;

    printf("Enter shift value: ");
    scanf("%d", &shiftValue);
    encryptFile(inputFile, outputFile, shiftValue);

    // task 2
    char *inputFile2 = "message2_encrypted.txt";
    char *outputFile2 = "message2_decrypted.txt";
    int decryptionShift = -5; 
    decryptFile(inputFile2, outputFile2, decryptionShift);

    //task 3 
    char *inputFile3 = "message3_encrypted.txt";
    char *outputFile3 = "message3_decrypted.txt";
    int shift = findShift(inputFile3);
    decryptFile(inputFile3, outputFile3, -shift); // we used inverse of numOfShift for decryption



    return 0;
}
// TASK 1
// read and write a file 
// we need to encrypt every single character
// separate function for file processing

char encryptCharacter(char ch, int shift) { 
    if (isalpha(ch)) { // determine base based on lower or upper case
        char base = 'A';
        if (islower(ch)) {
            base = 'a';
        }
        ch = (char)(((ch - base + shift) % 26) + base); // ch - base : normalized value, type casting!
    }
    return ch;
}

void encryptFile(char *inputFile, char *outputFile, int shift) {
    FILE *input = fopen(inputFile, "r");
    FILE *output = fopen(outputFile, "w");
    char line[1024]; // buffer


    while (fgets(line, sizeof(line), input) != NULL) { // read file till the end
        line[strcspn(line, "\n")] = '\0';
        for (int i = 0; line[i] != '\0'; i++) {
            line[i] = encryptCharacter(line[i], shift); //encryption
        }

        fputs(line, output); // write the encrypted line to a file
        fputc('\n', output); // add end sign
    }
	//close files
    fclose(input);
    fclose(output);
}
// TASK 2
// this time we know the how many times to shift and we may use similar approach as in task 1

void decryptFile(char *inputFile, char *outputFile, int shift) {
    // open files
    FILE *input = fopen(inputFile, "r");
    FILE *output = fopen(outputFile, "w");
    char line[1024]; // buffer for memory

    while (fgets(line, sizeof(line), input) != NULL) { // read the line
        line[strcspn(line, "\n")] = '\0';
        for (int i = 0; line[i] != '\0'; i++) {
             line[i] = encryptCharacter(line[i], shift); // shift to opposite direction
        }
        fputs(line, output);
        fputc('\n', output);
    }
    fclose(input);
    fclose(output);
}
// TASK 3
// now we find most frequent letter and then get the shift number from the difference between "e" and it.
//
int findShift(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    int freq[26] = {0};// array to save freq of letters

    char ch;
    while ((ch = fgetc(file)) != EOF) {
        if (isalpha(ch)) {
            ch = toupper(ch);// to compare them make it all upper
            freq[ch - 'A']++;
        }
    }
    fclose(file);

    int maxIndex = 0;// get the index by looping
    for (int i = 1; i < 26; i++) {
        if (freq[i] > freq[maxIndex]) {
            maxIndex = i;
        }
    }

    int shift = maxIndex - ('E' - 'A');
    if (shift < 0) {
        shift += 26; // shift number must be positive
    }
    return shift;
}


