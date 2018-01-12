/*********************************************************************************************
 * Programming Challenges - Number Base Conversion
 *
 * Write a program that accepts a base ten (non-fractional) number at the command line
 * and outputs the binary representation of that number.
 ********************************************************************************************/

#include <stdio.h>
#include <stdint.h>
#include <string.h>

static void complement_code(uint8_t *parray, uint8_t len)
{
    uint8_t i;

    for (i = 0; i < len; i += 1) {
        *(parray + i) = !(*(parray + i));
    }

    for (i = 0; i < len; i += 1) {
        if (*(parray + i) == 0) {
            *(parray + i) = 1;
            return;
        } else {
            *(parray + i) = 0;
        }
    }
}

static void dec2bin(int32_t num)
{
    uint8_t bin_array[32];
    uint8_t i, j, len = 0;
    uint8_t negetive_num = 0;

    memset(bin_array, 0, sizeof(bin_array));
    printf("decimal to binary %d=0b", num);
    if (num == 0) {
        printf("0\n");
        return;
    }

    if (num < 0) {
        negetive_num = 1;
        num = -num;
    }

    do {
        bin_array[len] = num % 2;
        num /= 2;
        len += 1;
    } while (num > 0);

    if (negetive_num == 1) {
        complement_code(bin_array, 32);
        len = 32;
    } else {
        if (len % 4 != 0) {
            len = (1 + len / 4) * 4;
        }
    }

    j = 0;
    for (i = len; i > 0; i -= 1) {
        printf("%d", bin_array[i - 1]);
        j += 1;
        if (j >= 4) {
            j = 0;
            printf(" ");
        }
    }
    printf("\n");
}

int main(int argc, char *argv[])
{
    uint16_t i;

    for (i = 0; i <= 1024; i += 1) {
        dec2bin(i);
        dec2bin(-i);
    }

    return 0;
}
