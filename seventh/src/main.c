#include "stdio.h"
#include "math.h"

#define MAX_COL 40

#define INIT_CHAR 46
#define ROWS 20
#define COLS 40

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

int main(){
  char a[ROWS][COLS];
  char init_char = INIT_CHAR;

  int x, y, width, height;

  int exit;

  exit = 0;
  do {

  }  while (!exit);

  printf("Enter x0, y0, width, height:  ");
  scanf("%d %d %d %d", &x, &y, &width, &height);

  init_array(a, ROWS, COLS, init_char);
  draw_box(a, x, y, width, height, 65);
  print_array(a, ROWS, COLS);

  return 0;
}
