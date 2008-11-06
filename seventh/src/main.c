#include "stdio.h"
#include "math.h"
#include "malloc.h"

#define TRUE 1
#define FALSE 0

#define X_INDEX 0
#define Y_INDEX 1
#define WIDTH_INDEX 2
#define HEIGHT_INDEX 3

#define A 65

#define MAX_COL 40

#define INIT_CHAR 46
#define ROWS 20
#define COLS 40
#define MAX_INPUT_VALUES 4
#define MAX_INPUT_LENGTH 100

#define NEW_LINE_ASCII_CODE 10
#define SPACE_ASCII_CODE 32

struct box {
  int x;
  int y;
  int width;
  int height;
};

void init_array(char a[][MAX_COL], int rows, int cols, char initchar);
void print_array(char a[][MAX_COL], int rows, int cols);
void draw_box(char a[][MAX_COL], int x, int y, int width, int height, int outline_char);

void init_array(char a[][MAX_COL], int rows, int cols, char initchar){
  int i, j;
  for (i = 0; i < rows; i++){
    for (j = 0; j < cols; j++){
      a[i][j] = initchar;
    }
  }
}

char convert_int_to_char(int i){
  return (char) (i + 48);
}

int convert_char_to_int(char c){
//  return ((int) c) - 48;
  return ((int) c) - 48;
}

void print_array(char a[][MAX_COL], int rows, int cols){
  int i, j;

  // print the column header lines
  int tens;
  int ones;

  printf("  ");
  for (i = 0; i < cols; i++){
    tens = floor(i / 10);
    ones = i - tens;
    printf("%c", convert_int_to_char(tens));
  }
  printf("\n");
  printf("  ");

  for (i = 0; i < cols; i++){
    tens = floor(i / 10);
    ones = i - (tens * 10);
    printf("%c", convert_int_to_char(ones));
  }
  printf("\n");

  for (i = 0; i < rows; i++){
    tens = floor(i / 10);
    ones = i - (tens * 10);
    printf("%c%c", convert_int_to_char(tens), convert_int_to_char(ones));
    for (j = 0; j < cols; j++){
      printf("%c", a[i][j]);
    }
    printf("\n");
  }
}

void draw_box(char a[][MAX_COL], int x, int y, int width, int height, int outline_char){
  // draw the top & bottom
  int i;
  for (i = x; i < (x + width + 1); i++){
    a[y][i] = outline_char;
    a[y + height][i] = outline_char;
  }
  // draw the sides
  for (i = y; i < (y + height); i++){
    a[i][x] = a[i][x + width] = outline_char;
  }
}

int parse_input(char *input, int length, struct box *b){
  int values[MAX_INPUT_VALUES];

  // initialize the values array
  int i;
  for (i = 0; i < (sizeof(values)/sizeof(int)); i++){
    values[i] = 0;
  }

  // move backwards through the string
  // to make converting to integers easier
  int counter = MAX_INPUT_VALUES - 1;
  int multiplier = 1;
  for (i = (length - 1); i >= 0; i--){
//    printf("%d\n", input[i]);
    // exit out of function with false if any character is EOF
    if (EOF == input[i]){
      return FALSE;
    }
    if (input[i] == NEW_LINE_ASCII_CODE){  // newline
      //do nothing
    } else if (input[i] == SPACE_ASCII_CODE){
      // we found a space, so move down to the previous value
      // and reset the multiplier
      counter--;
      multiplier = 1;
    } else {
      values[counter] += convert_char_to_int(input[i]) * multiplier;
      multiplier = multiplier * 10;
    }
  }
//  for (i = 0; i < (sizeof(values)/sizeof(int)); i++){
//    printf("%d = %d\n", i, values[i]);
//  }
  b->x = values[X_INDEX];
  b->y = values[Y_INDEX];
  b->width = values[WIDTH_INDEX];
  b->height = values[HEIGHT_INDEX];

  return TRUE;
}

int get_input(char *input){
  int bytes_read;
  int nbytes = MAX_INPUT_LENGTH;

  printf("Enter x0, y0, width, height:  ");
  bytes_read = getline(&input, &nbytes, stdin);

  return bytes_read;
}

int get_input_box(struct box *b){
  char *input;
  input = (char *) malloc (MAX_INPUT_LENGTH + 1);

  // trouble allocating the memory?
  if (NULL == input){
    return FALSE;
  }

  // ask for the user input
  // exit out if there's a problem

  // this is where my console exits on EOF
  int input_length;
  input_length = get_input(input);
  if (-1 == input_length){
    printf("Goodbye.\n");
    return FALSE;
  }

  // parse the input, will return FALSE if EOF is encountered
  if (!parse_input(input, input_length, b)){
    return FALSE;
  }

  // if we got here, everything succeeded
  return TRUE;
}

int main(){
  char a[ROWS][COLS];
  char init_char = INIT_CHAR;

  init_array(a, ROWS, COLS, init_char);

  struct box b;
  char box_char = A;

  int exit;
  exit = FALSE;
  do {
    if (FALSE == get_input_box(&b)){
      exit = TRUE;
    } else {
      printf("Got: %d %d %d %d\n", b.x, b.y, b.width, b.height);
      draw_box(a, b.x, b.y, b.width, b.height, box_char);
      print_array(a, ROWS, COLS);
      box_char++;
    }
  }  while (!exit);

  return 0;
}
