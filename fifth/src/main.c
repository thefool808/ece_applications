/*
 * Julian O'Brien
 * ECE Applications
 * Assignment #5
 * Text Processing
 *
 * Note: EOF on Linux is ctrl-D
 */

#include "stdio.h"

// include limits.h for UINT_MAX
#include "limits.h"

#define TRUE 1
#define FALSE 0

#define LOCASE_ASCII_LOWER_LIMIT 65
#define LOCASE_ASCII_UPPER_LIMIT 90
#define UPCASE_ASCII_LOWER_LIMIT 97
#define UPCASE_ASCII_UPPER_LIMIT 122

#define NEW_LINE_CODE 10

#define PADDING 36

// check whether the character ch is an upper or lower case letter
int is_letter(const char ch){
  // check if the ch is within the limits of lower & upper case ascii letter codes
  if ( ((LOCASE_ASCII_LOWER_LIMIT <= ch) && (ch <= LOCASE_ASCII_UPPER_LIMIT)) ||
       ((UPCASE_ASCII_LOWER_LIMIT <= ch) && (ch <= UPCASE_ASCII_UPPER_LIMIT)) ){
    return TRUE;
  }
  return FALSE;
}

int main(){

  char ch;
  unsigned int word_count, new_line_count, short_word_char_count, long_word_char_count,
    total_char_in_words, current_char_count;

  // intialize the counters
  word_count = 0;
  current_char_count = 0;
  total_char_in_words = 0;
  long_word_char_count = 0;
  // set this to the largest uint on the system (limits.h)
  short_word_char_count = UINT_MAX;
  new_line_count = 0;

  // a line for formatting
  char * line = "-------------------------------------------------------------------------\n";

  // request input from the user
  printf("ENTER A BLOCK OF TEXT TERMINATED BY END-OF-FILE (ctrl-D)\n");
  printf(line);

  // loop until EOF character received
  do {
    ch = getchar();

    if (is_letter(ch)){

      word_count += 1;
      current_char_count = 0;

      // get the whole word
      while(is_letter(ch)){
        current_char_count += 1;
        ch = getchar();
      }

      // update the running total of letters in all words
      total_char_in_words += current_char_count;

      // update short_word_char_count as needed
      if (current_char_count < short_word_char_count){
        short_word_char_count = current_char_count;
      }

      // update long_word_char_count as needed
      if (current_char_count > long_word_char_count){
        long_word_char_count = current_char_count;
      }
    }

    // check for NEWLINE
    if (NEW_LINE_CODE == ch){
      new_line_count += 1;
    }

  } while(EOF != ch);

  // calculate the avg numbers of char in a word
  int avg_chars = (int) ((total_char_in_words / word_count) + 0.5);

  // output the results
  printf(line);
  printf("                            STATISTICS\n");
  printf("\n");

  printf("%*s", PADDING, "Word Count = ");
  printf("%d\n", word_count);

  printf("%*s", PADDING, "Letters in Shortest Word = ");
  printf("%d\n", short_word_char_count);

  printf("%*s", PADDING, "Letters in Longest Word = ");
  printf("%d\n", long_word_char_count);

  printf("%*s", PADDING, "Average Word size = ");
  printf("%d\n", avg_chars);

  printf("%*s", PADDING, "Number of NEWLINE characters = ");
  printf("%d\n", new_line_count);

  return 0;
}
