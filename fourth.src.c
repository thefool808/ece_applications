/*
 * Julian O'Brien
 * ECE Applications
 * Assignment #4
 * Calendar
 */

#include "stdio.h"

// readability
#define TRUE 1
#define FALSE 0
#define PRINT_NEWLINE printf("\n");

// number of months in a year
#define MONTHS_IN_A_YEAR 12

// number of days in each month
#define JANUARY_DAYS                31
#define FEBRUARY_DAYS               28
#define FEBRUARY_LEAP_YEAR_DAYS     29
#define MARCH_DAYS                  31
#define APRIL_DAYS                  30
#define MAY_DAYS                    31
#define JUNE_DAYS                   30
#define JULY_DAYS                   31
#define AUGUST_DAYS                 31
#define SEPTEMBER_DAYS              30
#define OCTOBER_DAYS                31
#define NOVEMBER_DAYS               30
#define DECEMBER_DAYS               31

#define DAYS_IN_YEAR      365
#define DAYS_IN_LEAP_YEAR 366

#define LEAP_YR_TEST_1    1600
#define LEAP_YR_TEST_2    400
#define LEAP_YR_TEST_3    100
#define LEAP_YR_TEST_4    4

// the months of the year
enum months {
  january     = 1,
  february    = 2,
  march       = 3,
  april       = 4,
  may         = 5,
  june        = 6,
  july        = 7,
  august      = 8,
  september   = 9,
  october     = 10,
  november    = 11,
  december    = 12
};

// determine if the given year is a leap year
int is_leap_year(year){
  if (0 == (year % LEAP_YR_TEST_1)) return FALSE;
  if (0 == (year % LEAP_YR_TEST_2)) return TRUE;
  if (0 == (year % LEAP_YR_TEST_3)) return FALSE;
  if (0 == (year % LEAP_YR_TEST_4)) return TRUE;
  return FALSE;
}

// calculate the number of days in a month in a given year
int days_in_month(const int month, const int leap_year){
  switch(month){
    case january   : return JANUARY_DAYS;
    case february  : return (leap_year ? FEBRUARY_LEAP_YEAR_DAYS : FEBRUARY_DAYS);
    case march     : return MARCH_DAYS;
    case april     : return APRIL_DAYS;
    case may       : return MAY_DAYS;
    case june      : return JUNE_DAYS;
    case july      : return JULY_DAYS;
    case august    : return AUGUST_DAYS;
    case september : return SEPTEMBER_DAYS;
    case november  : return NOVEMBER_DAYS;
    case december  : return DECEMBER_DAYS;
    default        : return 0;
  }
}

// calculate the day of the year
int day_in_year(day, month, leap_year){
  int total_day_number = 0;
  int i;
  for(i = 1; i <= month - 1; i++){
    total_day_number += days_in_month(i, leap_year);
  }
  total_day_number += day;
  return total_day_number;
}

// scanf the user data
void get_user_input(int *month, int *day, int *year){
  printf("Enter Date (mm dd yyyy): ");
  scanf("%d %d %d", month, day, year);
  PRINT_NEWLINE;
}

// Make sure the date is valid
int validate_date(const int month, const int day, const int year){
  // is the month valid?
  if (month < 1 || month > MONTHS_IN_A_YEAR){
    printf("The month entered (%d) is not valid!\n", month);
    PRINT_NEWLINE;
    return FALSE;
  }

  // is the day of the month valid?
  int leap_year;
  leap_year = is_leap_year(year);
  if (day < 1 || day > days_in_month(month, leap_year)){
    printf("The day entered (%d) is not valid!\n", day);
    PRINT_NEWLINE;
    return FALSE;
  }

  // everything checks out
  return TRUE;
}

int main(){
  int month, day, year;

  // grab the date and validate until the date is valid
  while(1){
    get_user_input(&month, &day, &year);
    if (validate_date(month, day, year)){
      break;
    }
  }

  // is this a leap year?
  int leap_year = is_leap_year(year);

  // output
  if (leap_year){
    printf("Year %d is a leap year.\n", year);
    PRINT_NEWLINE;
    printf("Year %d has %d days.\n", year, DAYS_IN_LEAP_YEAR);
  } else {
    printf("Year %d is not a leap year.\n", year);
    PRINT_NEWLINE;
    printf("Year %d has %d days.\n", year, DAYS_IN_YEAR);
  }
  PRINT_NEWLINE;

  printf("Month %d has %d days.\n", month, days_in_month(month, leap_year));
  PRINT_NEWLINE;
  printf("Day of year = %d\n", day_in_year(day, month, leap_year));
  PRINT_NEWLINE;

  return 0;
}

