#include <cs50.h>
#include <stdio.h>

bool card_validity(long long n);
void print_brand(long long ccn);
bool checksum(long long n);
void print_brand(long long ccn);


int main(void)
{
    long long credit_card_number;
    do
    {
        credit_card_number = get_long_long("Enter Credit card number :");
    }
    while (credit_card_number < 0);

    if (card_validity(credit_card_number) == true)
    {
        print_brand(credit_card_number);
    }
    else
    {
        printf("INVALID\n");
    }
}


bool card_validity(long long n)
{
    long long ccn = n;
    int len = 0;
    for (len = 0; n != 0; n /= 10, len++);
    return (len == 13 || len == 15 || len == 16) && checksum(ccn);
}

bool checksum(long long n)
{
    int sum = 0;
    int digit = 0;
    int i;
    for (i = 0; n != 0; i++, n /= 10)
    {
        if (i % 2 == 0)
        {
            sum += n % 10;
        }
        else
        {
            digit = 2 * (n % 10);
            sum += (digit / 10) + (digit % 10);
        }

    }
    return (sum % 10) == 0;

}




void print_brand(long long ccn)
{

    if ((ccn > 34e13 && ccn < 35e13) || (ccn > 37e13 && ccn < 38e13))
    {
        printf("AMEX\n");
    }
    else if (ccn > 51e14 && ccn < 56e14)
    {
        printf("MASTERCARD\n");
    }
    else if ((ccn > 4e12 && ccn < 5e12) || (ccn > 4e15 && ccn < 5e15))
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }

}



