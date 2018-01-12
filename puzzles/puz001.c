#include <stdio.h>

#define TOTAL_ELEMENTS (sizeof(array) / sizeof(array[0]))
int array[] = {1, 2, 3, 4 ,5, 6, 7};

int main()
{
    int d;

    /* what sizeof return type is size_t
     * in some compiler, it maybe unsigned int */
    //  for (d = -1; d <= (TOTAL_ELEMENTS - 2); d++) {
    for (d = -1; d <= (int)(TOTAL_ELEMENTS - 2); d++) {
        printf("%d\n", array[d + 1]);
    }

    return 0;
}
