/*******************************************************************************************************
 * Challenge - Factorial Challenge
 *
 * Write a program that determines the number of trailing zeros at the end of X! (X factorial)
 * where X is an arbitrary number.
 * For instance, 5! is 120, so it has one trailing zero
 * (How can you handle extremely values, such as 100!?)
 ********************************************************************************************************/

#include <stdint.h>
#include <stdio.h>

static uint16_t find_trailing_zero_num(uint16_t num)
{
    uint16_t i, tmp;
    uint16_t mod2 = 0, mod5 = 0;

    /* 0! = 1, 1 ! = 1 without trailing zero */
    if (num == 0 || num == 1) {
        return 0;
    }

    for (i = 2; i <= num; i += 1) {
        tmp = i;
        while (tmp % 5 == 0) {
            mod5 += 1;
            tmp /= 5;
        }

        while (tmp % 2 == 0) {
            mod2 += 1;
            tmp /= 2;
        }
    }

    if (mod2 > mod5) {
        return mod5;
    } else {
        return mod2;
    }
}

static uint16_t find_trailing_zero_num2(uint16_t num)
{
    uint16_t i, zero_cnt = 0;

    if (num < 5) {
        return 0;
    }

    for (i = 5; i <= num; i *= 5) {
        zero_cnt += num / i;
    }

    return zero_cnt;
}

static void print_factorial_zero_num(uint16_t num)
{
    uint16_t zero_num = find_trailing_zero_num(num);
    uint16_t zero_num2 = find_trailing_zero_num2(num);
    printf("%d! has %d <-> %d trailing zeros.\n", num, zero_num, zero_num2);
    if (zero_num != zero_num2) {
        printf("----------------------ther must be something wrong!--------------------\n");
    }
}

int main(int argc, char* argv[])
{
    uint16_t i;

    for (i = 0; i <= 1000; i += 1) {
        print_factorial_zero_num(i);
    }

    return 0;
}
