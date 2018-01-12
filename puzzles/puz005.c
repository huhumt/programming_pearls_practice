#include <stdint.h>
#include <stdio.h>
#include <string.h>

void swap(char* x, char* y)
{
    char temp;

    temp = *x;
    *x = *y;
    *y = temp;
}

int permutation(char* str, uint8_t left, uint8_t right)
{
    uint8_t i;

    if (str == NULL) {
        return -1;
    }

    if (left == right)
        printf("%s\n", str);
    else {
        for (i = left; i <= right; i += 1) {
            swap(str + left, str + i);
            permutation(str, left + 1, right);
            swap(str + left, str + i);
        }
    }

    return 0;
}

int print_all_permutation(char* str, uint8_t length)
{
    if (str == NULL) {
        return -1;
    }

    if (length < 2) {
        printf("%s\n", str);
    } else {
        permutation(str, 0, length - 1);
    }

    return 0;
}

int main(int argc, char* argv[])
{
    char str1[] = "cat";
    char str2[] = "1233";

    print_all_permutation(str1, strlen(str1));
    print_all_permutation(str2, strlen(str2));

    return 0;
}
