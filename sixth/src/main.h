/*
 * Julian O'Brien
 * ECE Applications
 * Assignment #6
 * Bit Manipulation
 */

#ifndef MAIN_H_
#define MAIN_H_

#include "stdio.h"
#include "math.h"

#define FALSE 0
#define TRUE  1
#define EXIT  2

#define ASCII_ZERO                        48
#define ASCII_ONE                         49
#define ASCII_LC_Q                        113
#define ASCII_UC_Q                        81
#define ASCII_SPACE                       32
#define ASCII_NEWLINE                     10
#define ASCII_NINE                        57
#define ASCII_SKIP_TO_LOWER_CASE_LETTERS  39

#define BINARY_BASE	2

#define HIGHEST_SUM 256

// Convert an ASCII character code (for a digit) into
//   the corresponding integer value.
int convert_char_to_int(const char c);

// Convert a single digit to ASCII character code.
int convert_digit_to_char(const int i);

// Check if the character is a 0 or 1.
int is_binary(const char ch);

// Check if the character is the exit_code.
int is_exit_code(const char ch);

// Asks for input and checks the input.
// If the input contains anything other than 0, 1, and the exit_code,
// then the entire line of input will be discarded and the function will
// return false.
// If the exit_code is anywhere in the input, return EXIT.
int get_input(int *sum);

// Output the sum in binary with leading zeros.
void output_binary(const int sum);

// Output the sum in various formats.
void output_sum(const int sum);

#endif /* MAIN_H_ */
