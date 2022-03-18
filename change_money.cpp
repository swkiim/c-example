#include <stdio.h>

int main()
{
    int money, price, changes;
    printf("Inserted Coin : ");
    scanf("%d", &money);
    printf("Price is : ");
    scanf("%d", &price);

    changes = money - price;
    printf("Change : %d\n\n", changes);

    int coin100s = changes / 100;
    changes = changes % 100;

    int coin10s = changes / 10;
    changes = changes % 10;

    printf("100 Coins : %d ea\n", coin100s);
    printf("10 Coins : %d ea\n", coin10s);

    return 0;
}