/*******************************************************************************************
 * This source file is used to test rotate_vector function
 * Author: huhao
 * Date: 2017.07.22
 * Modification record:
 *
 *******************************************************************************************/

#include <string.h>
#include "rotate_vector.h"

int main(int argc, char *argv[])
{
    char test_data[11] = "abcdefghij";
    uint32_t i, j;

    for (i = 0; i < 10; i += 1) {
        LOG("Before rotate: index=%d, str=%s, len=%d, rotate_point=%d\n", i, test_data, 10, i);
        rotate_vector(test_data, 10, i);
        LOG("After rotate:  index=%d, str=%s, len=%d, rotate_point=%d\n\n", i, test_data, 10, i);
    }
    return 0;
}
