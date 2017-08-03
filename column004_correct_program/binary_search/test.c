/**************************************************************************************
 * This source file is a test file for binary search implementation
 * Author: huhao
 * Date: 2017.07.31
 * Modification record:
 *
 **************************************************************************************/

#include "binary_search.h"
#include <string.h>

int main(int argc, char* argv[])
{
    uint32_t i, test_array[100], position;
    int ret;

    memset(test_array, 0, sizeof(test_array));
    for (i = 0; i < 10; i += 1) {
        test_array[i] = i + 1;
    }

    for (i = 0; i < 10; i += 1) {
        ret = binary_search_standard(test_array, 10, i, &position);
        if (ret < 0) {
            LOG("%u is not found in array\n", i);
        } else {
            LOG("%u is successfully found in %u\n", i, position);
        }

        ret = binary_search_first_appear(test_array, 9, i + 1, &position);
        if (ret < 0) {
            LOG("%u is not found in array\n", i + 1);
        } else {
            LOG("%u is successfully found in %u\n", i + 1, position);
        }
    }

    return 0;
}
