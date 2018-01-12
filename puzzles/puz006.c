/*******************************************************************************************************
 * Integer to english number conversion
 * Write a program that takes an integer and displays the English name of that value.
 * You should support both positive and negative numbers
 * in the range supported by a 32-bit integer (approximately -2 billion to 2 billion).
 * Examples:
 *     10 -> ten
 *     121 -> one hundred twenty one
 *     1032 -> one thousand thirty two
 *     11043 -> eleven thousand forty three
 *     1200000 -> one million two hundred thousand
 ******************************************************************************************************/

#include <stdint.h>
#include <stdio.h>

/* basic number unit including:
 *     zero, one, two, three, four five, six, seven, eight, nine, ten
 *     eleven, tweleve, thirdteen, fourteen, fifteen, sixteen, elevnteen ,eighteen, nineteen
 *     twenty, thirty, fourty, fifty, sixty, seventy, eighty, ninety
 *     hundred, thousand, million, billion, trillion */
static int32_t basic_num[] = {
    1000000000, 1000000, 1000, 100,
    90, 80, 70, 60, 50, 40, 30, 20,
    19, 18, 17, 16, 15, 14, 13, 12, 11, 10,
    9, 8, 7, 6, 5, 4, 3, 2, 1
};

static char* basic_num_name[] = { "billion", "million", "thousand", "hundred",
    "ninety", "eighty", "seventy", "sixty", "fifty", "fourty", "thirty", "twenty",
    "nineteen", "eighteen", "seventeen", "sixteen", "fifteen", "fourteen", "thirteen", "twelve", "eleven",
    "ten", "nine", "eight", "seven", "six", "five", "four", "three", "two", "one" };

static int search_num_in_array(int32_t num, uint8_t length, uint8_t unit_index)
{
    uint8_t i;
    int32_t div;

    if (num == 0) {
        return 0;
    } else if (num < 20) {
        for (i = length - 1; i >= unit_index; i -= 1) {
            if (num == basic_num[i]) {
                printf("%s ", basic_num_name[i]);
                return 0;
            }
        }
    }

    div = num / basic_num[unit_index];
    num -= div * basic_num[unit_index];

    if (div > 0 && basic_num[unit_index] >= 20) {
        if (basic_num[unit_index] >= 100) {
            search_num_in_array(div, length, 0);
        }
        printf("%s ", basic_num_name[unit_index]);
    }
    search_num_in_array(num, length, unit_index + 1);
}

int print_num_name(int32_t num)
{
    uint8_t len;

    printf("%d: ", num);

    if (num == 0) {
        printf("zero\n");
        return 0;
    }

    if (num < 0) {
        printf("negetive ");
        num = -num;
    }

    len = sizeof(basic_num) / sizeof(basic_num[0]);
    search_num_in_array(num, len, 0);
    printf("\n");
}

int main(int argc, char* argv[])
{
    print_num_name(10);
    print_num_name(121);
    print_num_name(1032);
    print_num_name(11043);
    print_num_name(1200000);
    return 0;
}
