/****************************************************************************************************
 * Challenges - Pascal's Triangle Challenge
 *
 * Write a program to compute the value of a given position in Pascal's Triangle (See image).
 * The way to compute any given position's value is to add up the numbers
 * to the position's right and left in the preceding row. For instance,
 * to compute the middle number in the third row, you add 1 and 1;
 * the sides of the triangle are always 1 because you only add the number
 * to the upper left or the upper right (there being no second number on the other side).
 *******************************************************************************************************/

#include <stdio.h>
#include <stdint.h>

static uint32_t get_current_val(uint8_t line, uint8_t index)
{
    if (line == 0) {
        return 1;
    }

    if (index == 0 || index == line) {
        return 1;
    }

    return get_current_val(line - 1, index - 1) + get_current_val(line - 1, index);
}

void print_pascal_triangle(uint8_t line)
{
    uint8_t i, j;

    if (line == 0) {
        return;
    }

    for (i = 0; i < line; i += 1) {
        for (j = 0; j < line - 1 - i; j += 1) {
            printf("    ");
        }

        for (j = 0; j < i + 1; j += 1) {
            printf("%4d    ", get_current_val(i, j));
        }
        printf("\n");
    }
}

int main(int argc, char *argv[])
{
    print_pascal_triangle(15);

    return 0;
}
