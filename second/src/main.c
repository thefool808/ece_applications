/*
 * Julian O'Brien
 * ECE Applications
 * Assignment #2
 */

#include "stdio.h"
#include "math.h"

// this is a 4x4 table
// 4 rows and 4 columns
#define ROW_COUNT 4
#define COL_COUNT 4

//
// Table Types
//

// a place to store each piece of data in a row
// and the function to print that data
// NOTE: Callbacks may not be the best choice here.
//       I chose to use them mainly because I wanted to try
//       them.
typedef struct {
  // a pointer to the cell data
  const void *pdata;
  // the function to print the cell
  // function takes a pointer to the data
  // and the cell padding
  void (*print)(const void *pdata, const int padding);
} cell;

// a row is an array of cells
typedef struct {
  cell cells[COL_COUNT];
} row;

// a table is an array of rows
// and an array of ints that contain each column's padding
typedef struct {
  row rows[ROW_COUNT];
  int column_paddings[COL_COUNT];
} table;

//
// cell printing callback functions
//

// print a floating point number
void print_f(const void *_f, const int padding){
  // cast the void pointer to a float pointer
  const float *f = (const float *) _f;
  printf("%*.2f", padding, *f);
}

// print an integer
void print_i(const void *_i, const int padding){
  // cast the void pointer to an int pointer
  const int *i = (const int *) _i;
  printf("%*d", padding, *i);
}

// print a string
void print_s(const void *_s, const int padding){
  // cast the void pointer to a char pointer
  const char *s = (const char *) _s;
  printf("%*s", padding, s);
}

// print a row heading
// (print a left justified string)
void print_row_heading(const void *_s, const int padding){
  // cast the void pointer to a char pointer
  const char *s = (const char *) _s;
  printf("%-*s", padding, s);
}

// table printing function
void print_table(const table tbl){
  int i, j;
  for (i = 0; i < ROW_COUNT; i++){
    row r;
    r = tbl.rows[i];
    for (j = 0; j < COL_COUNT; j++){
      cell c;
      c = r.cells[j];
      c.print(c.pdata, tbl.column_paddings[j]);
    }
    // add a newline to the end of a row
    printf("\n");
  }
}

//
// calculation functions
//

// convert currency by exchane_rate
float calc_currency(const int original_amount, const float exchange_rate){
  return original_amount * exchange_rate;
}

// calculate the amount of tax on an income
float calc_tax(const float income, const float tax_rate){
  return income * tax_rate;
}

// calculate the amount of remaining income after taxes
float calc_after_tax(const float income, const float tax_rate){
  return income - calc_tax(income, tax_rate);
}

// calculate the amount of product that can be bought with an amount of money
// NOTE: This will always round down!
//       Since when can you buy 11 products @ $1.50(ea.) with $16.00?
int calc_amount_of_product(const float money, const float cost_of_product){
  return floor(money / cost_of_product);
}

// input function
// ask the user for their income and return it
void retrieve_income(float *income){
  printf("Enter an income in dollars ");
  scanf("%f", income);
}

// main
int main(){
  // setup the values used for calculations
  const float DollarToPoundRate = 0.498331;
  const float DollarToEuroRate = 0.722126;

  const float UsTaxRate = 0.20;
  const float GerTaxRate = 0.45;
  const float GbTaxRate = 0.30;

  const float UsBigMacCost = 1.50;
  const float GerBigMacCost = 1.99;
  const float GbBigMacCost = 0.99;

  // grab the income in dollars
  float us_income;
  retrieve_income(&us_income);

  //
  // run the necessary calculations
  //

  // US
  float us_after_tax = calc_after_tax(us_income, UsTaxRate);
  int   us_big_macs = calc_amount_of_product(us_after_tax, UsBigMacCost);

  // Germany
  float ger_income = calc_currency(us_income, DollarToEuroRate),
        ger_after_tax = calc_after_tax(ger_income, GerTaxRate);
  int   ger_big_macs = calc_amount_of_product(ger_after_tax, GerBigMacCost);

  // Great Britian
  float gb_income = calc_currency(us_income, DollarToPoundRate),
        gb_after_tax = calc_after_tax(gb_income, GbTaxRate);
  int   gb_big_macs = calc_amount_of_product(gb_after_tax, GbBigMacCost);

  //
  // setup the table
  //

  // column headings
  const char *Col1Heading = "";
  const char *Col2Heading = "Income";
  const char *Col3Heading = "After Tax";
  const char *Col4Heading = "Macs Purchased";

  // column paddings
  table tbl;
  tbl.column_paddings[0] = 10;
  tbl.column_paddings[1] = 9;
  tbl.column_paddings[2] = 12;
  tbl.column_paddings[3] = 17;

  // add the header row to the table
  tbl.rows[0].cells[0].pdata = Col1Heading;
  tbl.rows[0].cells[0].print = print_s;
  tbl.rows[0].cells[1].pdata = Col2Heading;
  tbl.rows[0].cells[1].print = print_s;
  tbl.rows[0].cells[2].pdata = Col3Heading;
  tbl.rows[0].cells[2].print = print_s;
  tbl.rows[0].cells[3].pdata = Col4Heading;
  tbl.rows[0].cells[3].print = print_s;

  // add the US row
  const char *Row1Heading = "US";
  tbl.rows[1].cells[0].pdata = Row1Heading;
  tbl.rows[1].cells[0].print = print_row_heading;
  tbl.rows[1].cells[1].pdata = &us_income;
  tbl.rows[1].cells[1].print = print_f;
  tbl.rows[1].cells[2].pdata = &us_after_tax;
  tbl.rows[1].cells[2].print = print_f;
  tbl.rows[1].cells[3].pdata = &us_big_macs;
  tbl.rows[1].cells[3].print = print_i;

  // add the Germany row
  const char *Row2Heading = "Germany";
  tbl.rows[2].cells[0].pdata = Row2Heading;
  tbl.rows[2].cells[0].print = print_row_heading;
  tbl.rows[2].cells[1].pdata = &ger_income;
  tbl.rows[2].cells[1].print = print_f;
  tbl.rows[2].cells[2].pdata = &ger_after_tax;
  tbl.rows[2].cells[2].print = print_f;
  tbl.rows[2].cells[3].pdata = &ger_big_macs;
  tbl.rows[2].cells[3].print = print_i;

  // add the English row
  const char *Row3Heading = "English";
  tbl.rows[3].cells[0].pdata = Row3Heading;
  tbl.rows[3].cells[0].print = print_row_heading;
  tbl.rows[3].cells[1].pdata = &gb_income;
  tbl.rows[3].cells[1].print = print_f;
  tbl.rows[3].cells[2].pdata = &gb_after_tax;
  tbl.rows[3].cells[2].print = print_f;
  tbl.rows[3].cells[3].pdata = &gb_big_macs;
  tbl.rows[3].cells[3].print = print_i;

  // print the table
  print_table(tbl);

  return 0;
}
