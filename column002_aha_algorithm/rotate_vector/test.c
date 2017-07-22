/*******************************************************************************************
 * This source file is used to test rotate_vector function
 * Author: huhao
 * Date: 2017.07.22
 * Modification record:
 *
 *******************************************************************************************/

#include "rotate_vector.h"

int main(int argc, char *argv[])
{
    struct {
        uint32_t len;
        uint32_t rotate_point;
        char pstr[10];
    } test_data[10];
    uint8_t i, j;

    for (i = 0; i < 10; i += 1) {
        for (j = 0; j < 10; j += 1) {
            test_data[i].pstr[j] = 'a' + i + j;
        }
        test_data[i].len = 10;
        test_data[i].rotate_point = i;
        LOG("Before rotate: index=%d, str=%s, len=%d, rotate_point=%d\n", i, test_data[i].pstr, test_data[i].len, test_data[i].rotate_point);
        rotate_vector(test_data[i].pstr, test_data[i].len, test_data[i].rotate_point);
        LOG("After rotate:  index=%d, str=%s, len=%d, rotate_point=%d\n\n", i, test_data[i].pstr, test_data[i].len, test_data[i].rotate_point);
    }
    return 0;
}
