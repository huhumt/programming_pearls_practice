/*******************************************************************************************
 * This source file is used to test rotate_vector function
 * Author: huhao
 * Date: 2017.07.22
 * Modification record:
 *
 *******************************************************************************************/

#include <string.h>
#include <sys/time.h>
#include "rotate_vector.h"

static uint32_t get_us(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1e6 + tv.tv_usec);
}

int main(int argc, char *argv[])
{
    char test_data[11] = "abcdefghij";
    char test_data_method2[11] = "zyxwvutsrq";
    uint32_t i, j;

    for (i = 0; i < 10; i += 1) {
        LOG("Before rotate: str=%s, len=%d, rotate_point=%d\n", test_data, 10, i);
        rotate_vector(test_data, 10, i);
        LOG("After rotate:  str=%s, len=%d, rotate_point=%d\n\n", test_data, 10, i);

        LOG("Before rotate: str=%s, len=%d, rotate_point=%d\n", test_data_method2, 10, i);
        rotate_vector_method2(test_data_method2, 10, i);
        LOG("After rotate:  str=%s, len=%d, rotate_point=%d\n\n", test_data_method2, 10, i);
    }
    return 0;
}
