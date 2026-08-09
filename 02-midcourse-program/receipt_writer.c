/*
Name: Calvin Hu
Date: 7/23/2026
Purpose: Read item quantities and write receipt.txt.
Fixed prices:
Coffee $3.00, Sandwich $7.50, Cookie $2.00
Tax 8.875%, discount 10% when subtotal > $50.00
*/

#include <stdio.h>

double calculateSubtotal(int coffeeQty, int sandwichQty, int cookieQty);
double calculateTax(double subtotal);
double calculateDiscount(double subtotal);
double calculateFinalTotal(double subtotal, double tax, double discount);

int main(void)
{
    int coffeeQty = 0;
    int sandwichQty = 0;
    int cookieQty = 0;

    /* TODO 1: Read three integer quantities in this order:
       coffee, sandwich, cookie.
    */

    printf("Coffee quantity:\n");
    scanf("%d", &coffeeQty);

    printf("Sandwich quantity:\n");
    scanf("%d", &sandwichQty);

    printf("Cookie quantity:\n");
    scanf("%d", &cookieQty);

    /* TODO 2: Call all four calculation functions. */

    double subtotal = calculateSubtotal(coffeeQty, sandwichQty, cookieQty);
    double tax = calculateTax(subtotal);
    double discount = calculateDiscount(subtotal);
    double finalTotal = calculateFinalTotal(subtotal, tax, discount);

    /* TODO 3: Open receipt.txt with "w" and check for NULL. */

    FILE *fp = fopen("receipt.txt", "w");

    if (fp == NULL) {
        printf("Error: could not open receipt.txt\n");
        return 1;
    }

    /* TODO 4: Use fprintf() to include these labels:
       Coffee
       Sandwich
       Cookie
       Subtotal
       Tax
       Discount
       Final total
    */

    fprintf(fp, "Coffee: %d\n", coffeeQty);
    fprintf(fp, "Sandwich: %d\n", sandwichQty);
    fprintf(fp, "Cookie: %d\n", cookieQty);
    fprintf(fp, "Subtotal: $%.2f\n", subtotal);
    fprintf(fp, "Tax: $%.2f\n", tax);
    fprintf(fp, "Discount: $%.2f\n", discount);
    fprintf(fp, "Final total: $%.2f\n", finalTotal);

    /* TODO 5: Close the file and print a saved message. */

    fclose(fp);

    printf("Receipt saved to receipt.txt\n");

    return 0;
}

double calculateSubtotal(int coffeeQty, int sandwichQty, int cookieQty)
{
    /* TODO */

    double subtotal = 0.00;

    subtotal = (coffeeQty * 3.00)
             + (sandwichQty * 7.50)
             + (cookieQty * 2.00);

    return subtotal;
}

double calculateTax(double subtotal)
{
    /* TODO */

    double tax = 0.00;

    tax = subtotal * 0.08875;

    return tax;
}

double calculateDiscount(double subtotal)
{
    /* TODO */

    double discount = 0.00;

    if (subtotal > 50.00) {
        discount = subtotal * 0.10;
    }

    return discount;
}

double calculateFinalTotal(double subtotal, double tax, double discount)
{
    /* TODO */

    double finalTotal = 0.00;

    finalTotal = subtotal + tax - discount;

    return finalTotal;
}