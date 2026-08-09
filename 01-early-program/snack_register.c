#include <stdio.h>

int main(void)
{
    int chips, juice, cookies;
    scanf("%d %d %d", &chips, &juice, &cookies);
    
    int cents = (chips * 125) + (juice * 150) + (cookies * 75);
    printf("Total cost: $%.2f\n", cents / 100.0);
    
    return 0;
}