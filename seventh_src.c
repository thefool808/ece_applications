/*
 * Julian O'Brien
 * ECE Applications
 * Assignment #7
 * 2-Dimensional Array
 * 
 * Note:
 *  On my Linux machine, I could not send EOF to scanf without it segfaulting.
 *  Therefore, I chose to use getline and read in a string.  
 *  Then I had to parse that string and convert it into integers, 
 *  which turned out to be a a bit of a PITA.
 *  Anyways, being more flexible with input and working with strings in C is
 *  great practice for me, so I'm happy.
 */

#include "stdio.h"
#include "math.h"
#include "malloc.h"

#define TRUE 1
#define FALSE 0

#define X_INDEX 0
#define Y_INDEX 1
#define WIDTH_INDEX 2
#define HEIGHT_INDEX 3

#define MAX_COL 40

#define ROWS 20
#define COLS 40
#define MAX_INPUT_VALUES 4
#define MAX_INPUT_LENGTH 100

// ASCII stuff
#define NEW_LINE_ASCII_CODE 10
#define SPACE_ASCII_CODE 32
#define ZERO_ASCII_CODE 48
#define INIT_CHAR 46
#define A 65


struct box {
  int x;
  int y;
  int width;
  int height;
};

//
// 2 - Dimensional Array functions
//

void init_array(char a[][MAX_COL], int rows, int cols, char initchar);
void print_array(char a[][MAX_COL], int rows, int cols);
void draw_box(char a[][MAX_COL], struct box, int outline_char);

// initialize the 2-dimensional array with the initchar
void init_array(char a[][MAX_COL], int rows, int cols, char initchar){
  int i, j;
  for (i = 0; i < rows; i++){
    for (j = 0; j < cols; j++){
      a[i][j] = initchar;
    }
  }
}

// print out the 2-dimensional array
void print_array(char a[][MAX_COL], int rows, int cols){
  int i, j, ones, tens;

  // print out the top header line
  // this is the 10s place of the column number
  printf("  ");
  for (i = 0; i < cols; i++){
    tens = floor(i / 10);
    ones = i - tens;
    printf("%d", tens);
  }
  printf("\n");
  printf("  ");

  // print out the second header line
  // this is the 1s place of the column number
  for (i = 0; i < cols; i++){
    tens = floor(i / 10);
    ones = i - (tens * 10);
    printf("%d", ones);
  }
  printf("\n");

  for (i = 0; i < rows; i++){
    // print out the left two columns
    // representing the row number
    printf("%02d", i);
    for (j = 0; j < cols; j++){
      // now print the actual array element
      printf("%c", a[i][j]);
    }
    printf("\n");
  }
}

// add the user inputed box to the 2-dimensional array
void draw_box(char a[][MAX_COL], struct box b, int outline_char){
  // draw the top & bottom
  int i;
  for (i = b.x; (i < (b.x + b.width)) && (i < COLS); i++){
    a[b.y][i] = a[b.y + b.height - 1][i] = outline_char;
  }
  // draw the sides
  for (i = b.y; (i < (b.y + b.height)) && (i < ROWS); i++){
    a[i][b.x] = a[i][b.x + b.width - 1] = outline_char;
  }
}

//
// INPUT FUNCTIONS
//

// Ask the user for input and retrieve that input.
// Note that scanf will segfault on Linux when passed EOF.
// Therefore, getline has to be used instead.
int get_input(char *input){
  int bytes_read;
  int nbytes = MAX_INPUT_LENGTH;

  printf("Enter x0, y0, width, height:  ");
  bytes_read = getline(&input, &nbytes, stdin);

  return bytes_read;
}

// convert an ASCII character code (for a integer) into the corresponding int
int convert_char_to_int(char c){
  return ((int) c) - ZERO_ASCII_CODE;
}

// this function takes a string inputed by the user
// and extracts the space delineated integer values from that string
int parse_input(char *input, int length, struct box *b){
  // an array to store the inputed integers
  int values[MAX_INPUT_VALUES];

  // initialize the values array
  int i;
  for (i = 0; i < (sizeof(values)/sizeof(int)); i++){
    values[i] = 0;
  }

  // Move backwards through the string
  // to make converting to integers easier.

  //   For example, if we have a string such as "10 5 15 20",
  //   and I went through the string forwards, when I hit the 1
  //   I don't know what its value is (here it is 10).
  //   If I go backwards, then I know what the value is of
  //   each successive number I get without a space (see multiplier).

  // keeps track of which inputed value we are on
  int counter = MAX_INPUT_VALUES - 1;
  // keeps track of the value of the place
  int multiplier = 1;
  // allow for multiple spaces to delineate the values
  int previous_character_was_a_space = TRUE;

  for (i = (length - 1); i >= 0; i--){
//    printf("%d\n", input[i]);  //debugging
    // exit out of function with false if any character is EOF
    if (EOF == input[i]){
      return FALSE;
    }
    if (input[i] == NEW_LINE_ASCII_CODE){  // newline
      // do nothing
    } else if (input[i] == SPACE_ASCII_CODE){
      // we found a space, so we are done with our current value

      // move to the next value and reset the multiplier
      // only if the previous character was not a space
      if (!previous_character_was_a_space){
        counter--;
        multiplier = 1;
      }
      // also notify that we found a space
      previous_character_was_a_space = TRUE;
    } else {
      // add the current integer (with it's place-value)
      // to the current value
      values[counter] += convert_char_to_int(input[i]) * multiplier;
      multiplier = multiplier * 10;
      previous_character_was_a_space = FALSE;
    }
  }

  // debugging
//  for (i = 0; i < (sizeof(values)/sizeof(int)); i++){
//    printf("%d = %d\n", i, values[i]);
//  }

  // check the received values
  int bad_values = FALSE;
  bad_values = ((values[X_INDEX] + values[WIDTH_INDEX]) > COLS) ||
    ((values[Y_INDEX] + values[HEIGHT_INDEX]) > ROWS);
  if (bad_values){
    printf("Values entered exceed the limits of the program (%d Columns, %d Rows).\n", ROWS, COLS);
    return FALSE;
  }

  // store the values found in the string
  // into the passed box structure
  b->x = values[X_INDEX];
  b->y = values[Y_INDEX];
  b->width = values[WIDTH_INDEX];
  b->height = values[HEIGHT_INDEX];

  return TRUE;
}

// Handles getting the input string and parsing it.
int get_input_box(struct box *b){
  char *input;
  input = (char *) malloc (MAX_INPUT_LENGTH + 1);

  // trouble allocating the memory?
  if (NULL == input){
    return FALSE;
  }

  int input_length;

  // ask for the user input
  // exit out if there's a problem
  do {
    // this is where my console exits on EOF
    input_length = get_input(input);
    if (-1 == input_length){
      printf("Goodbye.\n");
      return FALSE;
    }
  } while (!parse_input(input, input_length, b));

  // if we got here, everything succeeded
  return TRUE;
}

int main(){
  char a[ROWS][COLS];
  char init_char = INIT_CHAR;

  init_array(a, ROWS, COLS, init_char);

  struct box b;

  // initial character to outline the box with
  char box_char = A;

  while(get_input_box(&b)){
    // printf("Got: %d %d %d %d\n", b.x, b.y, b.width, b.height); // debugging
    draw_box(a, b, box_char);
    print_array(a, ROWS, COLS);
    box_char++;
  }

  return 0;
}

