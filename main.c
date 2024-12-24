#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// Function para e convert ang single roman numeral to iyang decimal value
int romanToDecimal(char c) {
    switch (toupper(c)) {
        case 'I': return 1;
        case 'V': return 5;
        case 'X': return 10;
        case 'L': return 50;
        case 'C': return 100;
        case 'D': return 500;
        case 'M': return 1000;
        default: return -1; // Invalid character
    }
}

// Function para convert ang roman numeral string to iyang decimal equivalent
int convertRomanToDecimal(const char *roman) {
    int total = 0;
    int prevValue = 0;

    for (int i = strlen(roman) - 1; i >= 0; i--) {
        int currentValue = romanToDecimal(roman[i]);
        if (currentValue == -1) {
            printf("Invalid Roman numeral: %c\n", roman[i]);
            return -1; // Return -1 for invalid input
        }
        if (currentValue < prevValue) {
            total -= currentValue;
        } else {
            total += currentValue;
        }
        prevValue = currentValue;
    }
    return total;
}

// Function para mo ug perform arithmetic operations sa decimal values
int performArithmetic(int num1, int num2, char operation) {
    switch (operation) {
        case '+': return num1 + num2;
        case '-': return num1 - num2;
        case '*': return num1 * num2;
        case '/': return num2 != 0 ? num1 / num2 : 0; // e prevent niya ang division by zero
        default: return 0;
    }
}

// Function para e  convert ang number sa iyang word equivalent up to 9999
void numberToWords(int num, char *result) {
    char *ones[] = {"", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine"};
    char *teens[] = {"Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};
    char *tens[] = {"", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
    char *thousands[] = {"", "Thousand"};

    if (num == 0) {
        strcpy(result, "Zero");
        return;
    }

    char temp[100] = "";
    if (num / 1000 > 0) {
        strcat(temp, ones[num / 1000]);
        strcat(temp, " Thousand ");
        num %= 1000;
    }
    if (num / 100 > 0) {
        strcat(temp, ones[num / 100]);
        strcat(temp, " Hundred ");
        num %= 100;
    }
    if (num >= 10 && num <= 19) {
        strcat(temp, teens[num - 10]);
    } else {
        strcat(temp, tens[num / 10]);
        num %= 10;
        if (num > 0) {
            strcat(temp, " ");
            strcat(temp, ones[num]);
        }
    }
    strcpy(result, temp);
}

int main() {
    FILE *inputFile = fopen("Input.txt", "r");
    FILE *outputFile = fopen("Output.txt", "w");

    if (!inputFile || !outputFile) {
        printf("Error opening file!\n");
        return 1;
    }

    char line[100];
    while (fgets(line, sizeof(line), inputFile)) {
        char roman1[50], roman2[50];
        char operation;
        if (sscanf(line, "%s %c %s", roman1, &operation, roman2) != 3) {
            fprintf(outputFile, "Invalid input format\n");
            continue;
        }

        int num1 = convertRomanToDecimal(roman1);
        int num2 = convertRomanToDecimal(roman2);

        if (num1 == -1 || num2 == -1) {
            fprintf(outputFile, "Invalid Roman numeral(s)\n");
            continue;
        }

        int result = performArithmetic(num1, num2, operation);
        char resultInWords[100];
        numberToWords(result, resultInWords);

        fprintf(outputFile, "%s\n", resultInWords);
    }

    fclose(inputFile);
    fclose(outputFile);

    // Ilhanan if na successfully converted na ba

    printf("\nConvert completed!.\nCheck Output.txt in your File!\n");
    return 0;
}
