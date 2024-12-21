#include <stdio.h> // Include the standard I/O library for file handling and console outputclear

// Function prototypes
int romanToDecimal(char *roman); // Prototype for converting Roman numerals to decimal
int isValidRoman(char *roman); // Prototype for validating a Roman numeral
void numberToWords(int number, char *words); // Prototype for converting a number to its word representation
int getValue(char roman); // Prototype for getting the decimal value of a Roman numeral character
void performOperation(char *roman1, char *operator, char *roman2, char *output); // Prototype for performing operations on two Roman numerals
int custom_strcmp(const char *str1, const char *str2); // Prototype for a custom string comparison function

// Arrays for word representations of numbers
const char *units[] = {"", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"}; // Units
const char *teens[] = {"", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"}; // Teens
const char *tens[] = {"", "ten", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"}; // Tens
const char *hundreds[] = {"", "one hundred", "two hundred", "three hundred", "four hundred", "five hundred", "six hundred", "seven hundred", "eight hundred", "nine hundred"}; // Hundreds
const char *thousands[] = {"", "one thousand", "two thousand", "three thousand", "four thousand", "five thousand", "six thousand", "seven thousand", "eight thousand", "nine thousand"}; // Thousands

// Custom function to calculate the length of a string
int custom_strlen(char *str) {
    int length = 0; // Initialize length counter
    while (str[length] != '\0') { // Loop until null character is encountered
        length++; // Increment length counter
    }
    return length; // Return the calculated length
}

// Custom function to copy a string
void custom_strcpy(char *dest, char *src) {
    while (*src) { // Loop through source string
        *dest++ = *src++; // Copy each character to destination
    }
    *dest = '\0'; // Add null terminator to destination string
}

// Custom function to concatenate two strings
void custom_strcat(char *dest, const char *src) {
    while (*dest) dest++; // Move to the end of the destination string
    while (*src) *dest++ = *src++; // Append source string to destination
    *dest = '\0'; // Add null terminator to the concatenated string
}

// Function to get the decimal value of a Roman numeral character
int getValue(char roman) {
    switch (roman) { // Use a switch statement for each Roman numeral character
        case 'I': return 1; // Return 1 for 'I'
        case 'V': return 5; // Return 5 for 'V'
        case 'X': return 10; // Return 10 for 'X'
        case 'L': return 50; // Return 50 for 'L'
        case 'C': return 100; // Return 100 for 'C'
        case 'D': return 500; // Return 500 for 'D'
        case 'M': return 1000; // Return 1000 for 'M'
        default: return 0; // Return 0 for invalid characters
    }
}

// Function to convert Roman numerals to decimal
int romanToDecimal(char *roman) {
    int total = 0, current, next, i; // Initialize variables

    for (i = 0; i < custom_strlen(roman); i++) { // Loop through each character in the Roman numeral
        current = getValue(roman[i]); // Get the decimal value of the current character
        next = (i + 1 < custom_strlen(roman)) ? getValue(roman[i + 1]) : 0; // Get the value of the next character

        if (current >= next) { // If the current value is greater than or equal to the next
            total += current; // Add the current value to the total
        } else { // If the next value is greater
            total += (next - current); // Subtract the current value from the next and add to the total
            i++; // Skip the next character
        }
    }
    return total; // Return the total decimal value
}

// Function to convert a number to its word representation
void numberToWords(int number, char *words) {
    words[0] = '\0'; // Initialize the words string
    if (number == 0) { // If the number is 0
        custom_strcpy(words, "zero"); // Copy "zero" to words
        return; // Exit the function
    }

    if (number / 1000 > 0) { // If the number has thousands
        custom_strcat(words, thousands[number / 1000]); // Add the corresponding thousands word
        custom_strcat(words, " "); // Add a space
    }

    number %= 1000; // Reduce the number to exclude thousands

    if (number / 100 > 0) { // If the number has hundreds
        custom_strcat(words, hundreds[number / 100]); // Add the corresponding hundreds word
        custom_strcat(words, " "); // Add a space
    }

    number %= 100; // Reduce the number to exclude hundreds

    if (number > 10 && number < 20) { // If the number is a teen
        custom_strcat(words, teens[number % 10]); // Add the corresponding teen word
    } else { // If the number is not a teen
        if (number / 10 > 0) { // If the number has tens
            custom_strcat(words, tens[number / 10]); // Add the corresponding tens word
            custom_strcat(words, " "); // Add a space
        }
        if (number % 10 > 0) { // If the number has units
            custom_strcat(words, units[number % 10]); // Add the corresponding units word
        }
    }
}

// Function to perform an arithmetic operation on two Roman numerals
void performOperation(char *roman1, char *operator, char *roman2, char *output) {
    int num1 = romanToDecimal(roman1); // Convert the first Roman numeral to decimal
    int num2 = romanToDecimal(roman2); // Convert the second Roman numeral to decimal
    int result = 0; // Initialize the result

    if (custom_strcmp(operator, "+") == 0) { // If the operator is addition
        result = num1 + num2; // Add the two numbers
    } else if (custom_strcmp(operator, "-") == 0) { // If the operator is subtraction
        result = num1 - num2; // Subtract the second number from the first
    } else if (custom_strcmp(operator, "*") == 0 || custom_strcmp(operator, "x") == 0) { // If the operator is multiplication
        result = num1 * num2; // Multiply the two numbers
    } else if (custom_strcmp(operator, "/") == 0 || custom_strcmp(operator, "\u00F7") == 0) { // If the operator is division
        if (num2 == 0) { // If the second number is 0
            printf("Error: Division by zero is not allowed.\n"); // Print an error message
            custom_strcpy(output, "Error: Division by zero"); // Set the output to an error message
            return; // Exit the function
        }
        result = num1 / num2; // Divide the first number by the second
    } else { // If the operator is invalid
        printf("Error: Invalid operator '%s'.\n", operator); // Print an error message
        custom_strcpy(output, "Error: Invalid operator"); // Set the output to an error message
        return; // Exit the function
    }

    char words[1000]; // Buffer for the result in words
    numberToWords(result, words); // Convert the result to words
    custom_strcpy(output, words); // Copy the words to the output

    printf("Process: %d %s %d = %d\n", num1, operator, num2, result); // Print the operation process
}

// Custom string comparison function
int custom_strcmp(const char *str1, const char *str2) {
    while (*str1 && (*str1 == *str2)) { // Loop while characters are equal
        str1++; // Move to the next character in the first string
        str2++; // Move to the next character in the second string
    }
    return *(unsigned char *)str1 - *(unsigned char *)str2; // Return the difference
}

// Function to read input file and write to output file
void readFile(char *inputFile, char *outputFile) {
    FILE *inFile = fopen(inputFile, "r"); // Open the input file for reading
    FILE *outFile = fopen(outputFile, "w"); // Open the output file for writing

    if (inFile == NULL || outFile == NULL) { // Check if either file couldn't be opened
        printf("Error: Cannot open input or output file.\n"); // Print an error message
        return; // Exit the function
    }

    char line[100]; // Buffer for a line of input
    while (fgets(line, sizeof(line), inFile) != NULL) { // Read each line from the input file
        if (line[0] == '\n' || line[0] == '\0') continue; // Skip empty lines

        char roman1[100], operator[10], roman2[100]; // Buffers for the input components
        int result = sscanf(line, "%s %s %s", roman1, operator, roman2); // Parse the line into components

        if (result != 3) { // If the line doesn't have exactly three components
            printf("Warning: Invalid input line skipped.\n"); // Print a warning
            continue; // Skip the line
        }

        if (!isValidRoman(roman1) || !isValidRoman(roman2)) { // If either Roman numeral is invalid
            printf("Error: Invalid Roman numeral '%s' or '%s' skipped.\n", roman1, roman2); // Print an error
            fprintf(outFile, "%s %s %s = Invalid Roman numeral\n", roman1, operator, roman2); // Write the error to the output file
            continue; // Skip the line
        }

        char words[1000]; // Buffer for the result in words
        performOperation(roman1, operator, roman2, words); // Perform the operation

        fprintf(outFile, "%s\n", words); // Write the result to the output file
    }

    fclose(inFile); // Close the input file
    fclose(outFile); // Close the output file
}

// Function to validate a Roman numeral
int isValidRoman(char *roman) {
    int i = 0; // Initialize index

    while (roman[i] != '\0') { // Loop through each character in the Roman numeral
        if (roman[i] == 'M' || roman[i] == 'D' || roman[i] == 'C' || roman[i] == 'L' || roman[i] == 'X' || roman[i] == 'V' || roman[i] == 'I') { // Check if the character is valid
            i++; // Move to the next character
        } else { // If the character is invalid
            return 0; // Return 0 (invalid)
        }
    }
    return 1; // Return 1 (valid)
}

// Main function
int main() {
    char inputFile[] = "input.txt"; // Input file name
    char outputFile[] = "output.txt"; // Output file name

    readFile(inputFile, outputFile); // Call the readFile function to process the files

    return 0; // Return 0 to indicate successful execution
}
