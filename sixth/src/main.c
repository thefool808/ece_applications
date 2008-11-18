#include "main.h"

int convert_char_to_int(const char c){
  return (c - ASCII_ZERO);
}

int convert_digit_to_char(const int i){
  return (i + ASCII_ZERO);
}

int is_binary(const char ch){
  return (ASCII_ONE == ch || ASCII_ZERO == ch);
}

int is_exit_code(const char ch){
  return (ASCII_LC_Q == ch || ASCII_UC_Q == ch);
}

int get_input(int *sum){
  printf("Enter a binary number:  ");

  int tmp_sum = 0;
  char ch;

  while ( (ch = getchar()) != ASCII_NEWLINE ){
    if (is_binary(ch)){
      tmp_sum <<= 1;
      tmp_sum += convert_char_to_int(ch);
    } else if (is_exit_code(ch)){
      // exit_code found so return EXIT
      return EXIT;
    } else { // bad input
      // discard the rest of the line
      while ( (ch = getchar()) != ASCII_NEWLINE );
      // return false
      return FALSE;
    }
  }

  *sum += tmp_sum;

  // keep the sum 8 bits
  while (*sum >= HIGHEST_SUM){
    *sum = *sum - HIGHEST_SUM;
  }

  // everything worked
  return TRUE;
}

void output_binary(const int sum){
  int i, bit_value, current_digit, tmp_sum;
  tmp_sum = sum;
  for (i = 7; i >= 0; i--){
    bit_value = pow(BINARY_BASE, i);
    current_digit = floor(tmp_sum/bit_value);
    tmp_sum = tmp_sum - (current_digit * bit_value);
    printf("%c", convert_digit_to_char(current_digit));
  }
}

void output_sum(const int sum){
  printf("sum = %3d decimal %2x hex and ", sum, sum);
  output_binary(sum);
  printf(" binary\n");
}

int main(){
  int sum = 0;
  int status;

  // loop until exit character received
  while (TRUE){
    status = get_input(&sum);
    if (TRUE == status){
      output_sum(sum);
    } else if (EXIT == status) {
      printf("Goodbye.\n");
      return 0;
    } else {
      // else FALSE, so keep looping
      printf("Bad input supplied.\n");
    }
  }
}
