# Snack Register

## Overview

The program uses three integer variables to store the quantities of chips, juice, and cookies. The prices are stored as integer values in cents to avoid problems with floating-point calculations.

The program calculates the total cost using:

* Chips: 125 cents each
* Juice: 150 cents each
* Cookies: 75 cents each

The total is calculated in cents and then divided by `100.0` when printed so that the result is displayed in dollars with two decimal places.

The program:

1. Reads three quantities using `scanf`.
2. Calculates the total cost in cents.
3. Converts the result to dollars.
4. Prints the formatted total.

## Skills Demonstrated

* Variables and data types
* User input with scanf
* Arithmetic operations
* Integer and floating-point calculations

## Compile and Run

gcc -std=c11 -Wall -Wextra 01-early-program/snack_register.c -o snack_register
./snack_register

## Example

SAMPLE INPUT:

2 3 4

SAMPLE OUTPUT:

$8.75

## What I Learned

One issue I had to be careful about was how the total cost was converted from cents to dollars. The calculation stores the total as an integer number of cents, so dividing by `100` as an integer would produce an incorrect result for some values.

To fix this issue I used: cents / 100.0

instead of: cents / 100

Using `100.0` makes the division a floating-point calculation and allows `printf` to correctly display the total with two decimal places.
