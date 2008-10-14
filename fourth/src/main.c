/*
 * Julian O'Brien
 * ECE Applications
 * Assignment #3
 * Calendar
 */

#include "stdio.h"

#define TRUE 1
#define FALSE 0

#define MONTHS_IN_A_YEAR 12

//#define JANUARY           1
//#define FEBRUARY          2
//#define MARCH             3
//#define APRIL             4
//#define MAY               5
//#define JUNE              6
//#define JULY              7
//#define AUGUST            8
//#define SEPTEMBER         9
//#define OCTOBER           10
//#define NOVEMBER          11
//#define DECEMBER          12

#define JANUARY_DAYS      31
#define FEBRUARY_DAYS     28
#define MARCH_DAYS        31
#define APRIL_DAYS        30
#define MAY_DAYS          31
#define JUNE_DAYS         30
#define JULY_DAYS         31
#define AUGUST_DAYS       31
#define SEPTEMBER_DAYS    30
#define OCTOBER_DAYS      31
#define NOVEMBER_DAYS     30
#define DECEMBER_DAYS     31

//#define MONDAY            1
//#define TUESDAY           2
//#define WEDNESDAY         3
//#define THURSDAY          4
//#define FRIDAY            5
//#define SATURDAY          6
//#define SUNDAY            7

#define DAYS_IN_YEAR      365
#define DAYS_IN_LEAP_YEAR 366

#define LEAP_YR_TEST_1    1600
#define LEAP_YR_TEST_2    400
#define LEAP_YR_TEST_3    100
#define LEAP_YR_TEST_4    4

int is_leap_year(year){
  if (0 == (year % LEAP_YR_TEST_1)) return FALSE;
  if (0 == (year % LEAP_YR_TEST_2)) return TRUE;
  if (0 == (year % LEAP_YR_TEST_3)) return FALSE;
  if (0 == (year % LEAP_YR_TEST_4)) return TRUE;
  return FALSE;
}

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

//enum days {
//  monday      = MONDAY,
//  tuesday     = TUESDAY,
//  wednesday   = WEDNESDAY,
//  thursday    = THURSDAY,
//  friday      = FRIDAY,
//  saturday    = SATURDAY,
//  sunday      = SUNDAY
//};

void get_user_input(int *month, int *day, int *year){
  printf("Enter Date (mm dd yyyy): ");
  scanf("%d %d %d", month, day, year);
}

int main(){
  int month, day, year;

  get_user_input(&month, &day, &year);

  int leap_year = is_leap_year(year);

  if (leap_year){
    printf("Year %d is a leap year.", year);
    printf("Year %d has %d days.", year, DAYS_IN_LEAP_YEAR);
  } else {
    printf("Year %d is not a leap year.", year);
    printf("Year %d has %d days.", year, DAYS_IN_YEAR);
  }

  return 0;
}
