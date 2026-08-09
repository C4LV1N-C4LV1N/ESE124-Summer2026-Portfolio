# Receipt Writer

## Overview

The Snack Register program reads the quantities of coffee, sandwiches, and cookies purchased by the user and calculates the total cost. It calculates the subtotal, applies an 8.875% tax, applies a 10% discount when the subtotal is greater than $50.00, and saves the receipt to receipt.txt.

## Skills Demonstrated

* Functions and modular program design
* File input/output using fopen, fprintf, and fclose
* Arithmetic calculations and conditional statements
* Formatted output using printf and fprintf

## Compile and Run

gcc -std=c11 -Wall -Wextra receipt_writer.c -o receipt_writer
./receipt_writer

## Example

Normal Example
Input:

Coffee quantity:
5
Sandwich quantity:
6
Cookie quantity:
4

The resulting receipt.txt contains:

Coffee: 5
Sandwich: 6
Cookie: 4
Subtotal: $67.00
Tax: $5.95
Discount: $6.70
Final total: $66.25


Edge Case (Quanities are 0)

Coffee quantity:
0
Sandwich quantity:
0
Cookie quantity:
0

The receipt contains:

Coffee: 0
Sandwich: 0
Cookie: 0
Subtotal: $0.00
Tax: $0.00
Discount: $0.00
Final total: $0.00

## Design and Testing

The program was designed using separate functions for each calculation. calculateSubtotal() determines the purchase subtotal, while separate functions calculate the tax, discount, and final total. This modular design makes each calculation easier to test and understand.
I tested the program with normal quantities, zero quantities, and purchases above $50.00 to verify that the tax and discount calculations worked correctly. I also checked that receipt.txt was created and contained the expected formatted results.
