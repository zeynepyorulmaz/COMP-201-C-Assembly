#include <stdio.h>
#include <string.h> // For strlen()
#include <ctype.h>  // For isalpha() and isupper() functions
#define MAX_LENGTH 1000
void task1(FILE *inputFile, FILE *outputFile, int shift);
void task2(FILE *inputFile, FILE *outputFile, int shift);
void task3(FILE *inputFile, FILE *outputFile);
char* findMostFrequentWord(const char* filename);
void task4(FILE *inputFile, FILE *outputFile);
int main() {
    // task1
    int shift;
    printf("Enter the shift value (N): "); //getting shift value n 
    scanf("%d", &shift);
    getchar();

    FILE *inputFile1 = fopen("message1.txt", "r");
    FILE *outputFile1 = fopen("message1_encrypted.txt", "w");

    task1(inputFile1, outputFile1, shift);
    fclose(inputFile1);
    fclose(outputFile1);

    //task2
    FILE *inputFile2 = fopen("message2_encrypted.txt", "r");
    FILE *outputFile2 = fopen("message2_decrypted.txt", "w");
    task2(inputFile2, outputFile2, 5);
    fclose(inputFile2);
    fclose(outputFile2);

    //task3
    FILE *inputFile3 = fopen("message3_encrypted.txt", "r");
    FILE *outputFile3 = fopen("message3_decrypted.txt", "w");
    task3(inputFile3, outputFile3);
    fclose(inputFile3);
    fclose(outputFile3);

    //task4
    FILE *inputFile4 = fopen("message4_encrypted.txt", "r");
    FILE *outputFile4 = fopen("message4_decrypted.txt", "w");
    task4(inputFile4, outputFile4);
    fclose(inputFile4);
    fclose(outputFile4);

    return 0;
}
void task1(FILE *inputFile, FILE *outputFile, int shift) {
    char ch;
    while ((ch = fgetc(inputFile)) != EOF) {//until it is not an end of file char
        if (isalpha(ch)) { //if it is a a-z or A-Z char. 
            if (islower(ch)) { //if it is lower we need to compare with small a
                ch = 'a' + (ch - 'a' + shift) % 26; //because chars are ascii, they are actually represented by some integer so we can subtract characters, we divide by 26 to start from the a again if the alphabet is finished. 
            } else {
                ch = 'A' + (ch - 'A' + shift) % 26; //same thing but it is capital
            }
        }
        fputc(ch, outputFile); // to write chars to theoutput file
    }
}

void task2(FILE *inputFile, FILE *outputFile, int shift) {
    task1(inputFile, outputFile, 26 - shift); //since it will be a decryption, we can just add the alphabet again then subtract the shift value, since task 1 will give the remainder of dividing after 26 
}

int maxFrequencyIndex(FILE *inputFile){ //function that returns which letter is the most frequet's index at the alphabet
    int frequency[26] = {0}; //initilizing with 0s
    char ch;
    while ((ch = fgetc(inputFile)) != EOF) {
        if (isalpha(ch)) { //if it is a letter
            ch = toupper(ch); //conver to upper case
            frequency[ch - 'A']++; //subtract from A because it is the first uppercase letter in the ascii code and also alphabet, incrementing its frequency in the array
        }
    }
    int maxFreq = 0, maxIndex = 0;
    for (int i = 0; i < 26; i++) {
        if (frequency[i] > maxFreq) {
            maxFreq = frequency[i];
            maxIndex = i; //to check array's elements to find max of it
        }
    }
    return maxIndex;
}

void task3(FILE *inputFile, FILE *outputFile) {
    int maxIndex = maxFrequencyIndex(inputFile);
    int shift = (maxIndex - ('E'- 'A')+26) % 26;//to find the shift first to find e's index we subtract a, then to find the shift we subtract it from maxindex, then we add 26 in case it is a negative number to avoid any problems, then take remainder by 26 if incase it is bigger than 26
    rewind(inputFile);    
    task2(inputFile, outputFile, shift); //after finding shift value we decrypt it
} 

char* findMostFrequentWord(const char* filename) {
    FILE *file = fopen(filename, "r");
    char buffer[MAX_LENGTH];
    char* mostFrequentWord = NULL;
    int maxFrequency = 0;

    struct WordFrequency {
        char word[MAX_LENGTH];
        int frequency;
    } wordTable[MAX_LENGTH]; //to store the words and their frequencies

    int wordCount = 0;

    for (int i = 0; i < MAX_LENGTH; ++i) {
        wordTable[i].frequency = 0; //initilizing the frequency table with 0s
    }

    while (fscanf(file, "%s", buffer) == 1) { //to take the words
        int len = strlen(buffer);

        for (int i = 0; buffer[i]; i++) { 
            buffer[i] = tolower(buffer[i]); //all lower case
        }

        int found = 0;
        for (int i = 0; i < wordCount; ++i) {
            if (strcmp(wordTable[i].word, buffer) == 0) { //checks if they are equal
                wordTable[i].frequency++; //if satisfied, increment the frequency
                found = 1;
                break;
            }
        }
        if (!found) { //if it is the first time adding it into dictionary, add it
            strcpy(wordTable[wordCount].word, buffer);
            wordTable[wordCount].frequency = 1; //initilize the frequency with 1
            wordCount++;
        }
    }

    for (int i = 0; i < wordCount; ++i) { //to find the most frequent word
        if (wordTable[i].frequency > maxFrequency) { 
            maxFrequency = wordTable[i].frequency;//if it is bigger than the previous max frequency, update it
            mostFrequentWord = wordTable[i].word;
        }
    }

    fclose(file);
    return mostFrequentWord;
}

void task4(FILE *inputFile, FILE *outputFile) {
    char* mostFrequentWord = (findMostFrequentWord("message4_encrypted.txt"));
    int shift = ((mostFrequentWord[0]) - ('t')+26) % 26; //to find the shift value, we find the first letter of the most frequent word, then subtract t's index from it, then add 26 in case it is a negative number to avoid any problems, then take remainder by 26 if incase it is bigger than 26
    rewind(inputFile);    
    task2(inputFile, outputFile, shift); 

}

//task5
/*
In the cases of brute force, anyone can just try the 25 shift values and find the secret conversation, so it is not so effective.
Its strengths are that it is easy to encrypt and decrypt and it is fast.
Its weaknesses are it is not that secure and can be brute forced
In task5 assuming some max length in an iteration is not so efficient
I remember seeing better encryption algorithms in COMP106 last year
Where we have a very large prime number and generally do operations with modulo to encrypt and decrypt
It was called RSA algorithm: 
n = p*q (p and q are large prime numbers)
C = M^e (mod n) (M is the message, C is the encrypted message, e is the public key)
 M ≡ C^d (mod n)  (d is the private key)
 */


