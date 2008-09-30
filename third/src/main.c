/*
 * Julian O'Brien
 * ECE Applications
 * Assignment #3
 * Weather Baloon
 */

#include "stdio.h"
#include "math.h"

//
// These are the two polynomial equations used
//

// This equation returns the altitude in meters of the balloon
// at the given hour t.
// a(t) = -0.12t^4 + 12t^3 - 380t^2 + 4100t + 220
#define calculate_altitude(t) (\
          ((-0.12) * pow(t, 4.0)) + \
          (12.0 * pow(t, 3.0)) - \
          (380.0 * pow(t, 2.0)) + \
          (4100.0 * t) + 220.0 \
        )

// This equation returns the velocity in meters/hour of the balloon
// at a given hour t.
// v(t) = -0.48t^3 + 36t^2 - 760t + 4100
#define calculate_velocity(t) (\
          ((-0.48) * pow(t, 3.0)) + \
          (36.0 * pow(t, 2.0)) - \
          (760.0 * t) + 4100.0 \
        )

// used in the conversion
#define MINUTES_IN_HOUR     60.0
#define SECONDS_IN_MINUTE   60.0

// the maxmimum input allowable for any of the inputs
#define MAX_INPUT_VALUE     48.0

// the maximum amount of time steps allowed
#define MAX_NUMBER_OF_ITERATIONS 100

// helper
#define PRINT_NEW_LINE     printf("\n");

// table layout
#define CELL_PADDING        10
#define COL_1_PADDING       8
#define COL_2_PADDING       12
#define COL_3_PADDING       14

// readability
#define TRUE                1
#define FALSE               1

// loops displaying the message and getting the input
// until the input is valid
void get_valid_user_input(const char *message, double *input){
  while (TRUE){
    printf(message);
    scanf("%lf", input);
    // if the input greater than 0 and
    // less than the max, then it is valid
    if (*input >= 0.0 && *input <= MAX_INPUT_VALUE){
      break;
    }
  }
}

// get the user input
void get_user_input(double *initial_hour, double *increment_hour, double *final_hour){
  while(TRUE){
    get_valid_user_input("Enter the initial value for the table in hours ", initial_hour);
    get_valid_user_input("Enter the increment bewteen lines in hours     ", increment_hour);
    get_valid_user_input("Enter the final value for the table in hours   ", final_hour);

    // make sure the number of results to be calculated is
    // less than the maximum allowed and more than 0
    unsigned int number_of_iterations = 0;
    number_of_iterations = floor( (*final_hour - *initial_hour) / *increment_hour );
    if (number_of_iterations > MAX_NUMBER_OF_ITERATIONS){
      printf("Please enter numbers that would cause less than %d iterations.\n",
        MAX_NUMBER_OF_ITERATIONS);
    } else if (0 == number_of_iterations) {
      printf("Please enter numbers that would cause more than 0 iterations.\n");
    } else {
      break;
    }
  }
}

// convert meters/hr to meters/s
double convert_mph_to_mps(const double velocity_in_mph){
  return velocity_in_mph / (MINUTES_IN_HOUR * SECONDS_IN_MINUTE);
}

//
// printing functions
//

// print a double
void print_d(const double d, const int padding){
  printf("%*.2f", padding, d);
}

void print_hour(const double d){
  print_d(d, COL_1_PADDING);
}

void print_altitude(const double d){
  print_d(d, COL_2_PADDING);
}

void print_velocity(const double d){
  print_d(d, COL_3_PADDING);
}

void print_col_1_heading(const char *str){
  printf("    %-*s", COL_1_PADDING, str);
}

void print_col_2_heading(const char *str){
  printf("  %-*s", COL_2_PADDING, str);
}

void print_col_3_heading(const char *str){
  printf("  %-*s", COL_3_PADDING, str);
}

// main
int main(){
  double initial_hour;
  double increment_hour;
  double final_hour;

  get_user_input(&initial_hour, &increment_hour, &final_hour);

  // space the table away from the input
  PRINT_NEW_LINE; PRINT_NEW_LINE;

  // print the table heading
  printf("Weather Balloon Information"); PRINT_NEW_LINE;

  // print the table headings
  print_col_1_heading("Time");
  print_col_2_heading("Height");
  print_col_3_heading("Velocity");
  PRINT_NEW_LINE;

  print_col_1_heading("hrs");
  print_col_2_heading("meters");
  print_col_3_heading("meters/s");
  PRINT_NEW_LINE;

  // used to keep track of what time we are at
  double current_hour;
  current_hour = initial_hour;

  // used for recording the highest altitude
  // and at what time that occurred
  double highest_alt, highest_alt_time;
  highest_alt = 0.0;
  highest_alt_time = 0.0;

  // loop from the initial time to the
  // final time, while doing the calculations
  while(current_hour <= final_hour){
    // print the current time in hours
    print_hour(current_hour);

    // calculate and print the altitude
    double altitude;
    altitude = calculate_altitude(current_hour);
    print_altitude(altitude);

    // check for the highest altitude
    if (altitude > highest_alt){
      highest_alt = altitude;
      highest_alt_time = current_hour;
    }

    // calculate and print the velocity
    double velocity;
    velocity = convert_mph_to_mps( calculate_velocity(current_hour) );
    print_velocity(velocity);

    // print a newline at the end of each row
    PRINT_NEW_LINE;

    // move forward in time
    current_hour += increment_hour;
  }

  // space the maximum altitude display away
  // from the table
  PRINT_NEW_LINE; PRINT_NEW_LINE;

  // print the maximum height
  printf("Maximum ballon height was %.2f meters", highest_alt); PRINT_NEW_LINE;
  printf("That occurred at %.2f hours", highest_alt_time); PRINT_NEW_LINE;

  return 0;
}
