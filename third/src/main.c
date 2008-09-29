/*
 * Julian O'Brien
 * ECE Applications
 * Assignment #3
 * Weather Baloon
 */

#include "stdio.h"
#include "math.h"

#define TWO											2.0
#define THREE										3.0
#define FOUR										4.0

#define NEG_POINT_TWELVE 				(-0.12)
#define TWELVE 									12.0
#define THREE_EIGHTY						380.0
#define FOURTY_ONE_HUNDRED 			4100.0
#define TWO_TWENTY							220.0

#define NEG_POINT_FOURTY_EIGHT	(-0.48)
#define THIRTY_SIX							36.0
#define SEVEN_SIXTY							760.0

#define MAX_INPUT_VALUE					48
#define SIXTY										60

#define CELL_PADDING						10
#define NEW_LINE								"\n"

// loops displaying the message and getting the input
// until the input is valid
void get_valid_user_input(const char *message, double *input){
  while (1){
    printf(message);
    scanf("%lf", input);
    // if the input greater than 0 and
    // less than the max, then it is valid
    if (*input >= 0 && *input <= MAX_INPUT_VALUE){
      break;
    }
  }
}

// get the user input
void get_user_input(double *initial_hour, double *increment_hour, double *final_hour){
  get_valid_user_input("Enter the initial value for the table in hours ", initial_hour);
  get_valid_user_input("Enter the increment bewteen lines in hours     ", increment_hour);
  get_valid_user_input("Enter the final value for the table in hours   ", final_hour);
}

// calculate the altitude
double calculate_altitude(const double *time_in_hours){
  return (NEG_POINT_TWELVE * pow(*time_in_hours, FOUR)) +
    (TWELVE * pow(*time_in_hours, THREE)) - (THREE_EIGHTY * pow(*time_in_hours, TWO)) +
    (FOURTY_ONE_HUNDRED * *time_in_hours) + TWO_TWENTY;
}

double convert_mph_to_mps(const double *velocity_in_mph){
  return *velocity_in_mph / (SIXTY * SIXTY);
}


// calculate the velocity
double calculate_velocity(const double *time_in_hours){
  double velocity_in_mph;
  velocity_in_mph = (NEG_POINT_FOURTY_EIGHT * pow(*time_in_hours, THREE)) +
    (THIRTY_SIX * pow(*time_in_hours, TWO)) - (SEVEN_SIXTY * *time_in_hours) +
    FOURTY_ONE_HUNDRED;
  return convert_mph_to_mps(&velocity_in_mph);
}

// print a double
void print_d(const double *d){
  printf("%*.2f", CELL_PADDING, *d);
}

// print a string
void print_s(const char *str){
  printf("   %-*s", CELL_PADDING - 3, str);
}

int main(){
  double initial_hour;
  double increment_hour;
  double final_hour;

  get_user_input(&initial_hour, &increment_hour, &final_hour);

  // space the table away from the input
  printf(NEW_LINE); printf(NEW_LINE);

  // print the table heading
  printf("Weather Balloon Information"); printf(NEW_LINE);

  print_s("Time");
  print_s("Height");
  print_s("Velocity");
   printf(NEW_LINE);

  print_s("hrs");
  print_s("meters");
  print_s("meters/s");
  printf(NEW_LINE);

  double current_hour;
  current_hour = initial_hour;

  double highest_alt, highest_alt_time;
  highest_alt = 0.0;
  highest_alt_time = 0.0;

  while(current_hour <= final_hour){
    // print the current time in hours
    print_d(&current_hour);

    // calculate and print the altitude
    double altitude;
    altitude = calculate_altitude(&current_hour);
    print_d(&altitude);

    // check for the highest altitude
    if (altitude > highest_alt){
      highest_alt = altitude;
      highest_alt_time = current_hour;
    }

    // calculate and print the velocity
    double velocity;
    velocity = calculate_velocity(&current_hour);
    print_d(&velocity);

    // print a newline
    printf(NEW_LINE);

    // move forward in time
    current_hour += increment_hour;
  }

  // space the maximum altitude display away
  // from the table
  printf(NEW_LINE); printf(NEW_LINE);

  printf("Maximum ballon height was %.2f meters", highest_alt);
  printf(NEW_LINE);
  printf("That occurred at %.2f hours", highest_alt_time);

  return 0;
}
