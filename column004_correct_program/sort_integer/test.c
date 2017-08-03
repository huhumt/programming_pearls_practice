/**************************************************************************************
 * This source file is a test file for sort array
 * Author: huhao
 * Date: 2017.07.31
 * Modification record:
 *
 **************************************************************************************/

#include "sort.h"

int main(int argc, char* argv[])
{
    uint32_t i;
    uint32_t test_array1[10] = {200, 10, 8, 6, 3, 22, 4, 11, 10000, 44};
    uint32_t test_array2[13] = {200, 10, 8, 6, 3, 22, 4, 11, 10000, 44, 6, 3, 3};

    LOG("Before sort data is:");
    for (i = 0; i < 10; i += 1) {
        LOG(" %u", test_array1[i]);
    }
    LOG("\n");

    sort_method1(test_array1, 10, ASCENDING_ORDER);

    LOG("After sort data is:");
    for (i = 0; i < 10; i += 1) {
        LOG(" %u", test_array1[i]);
    }
    LOG("\n");

    LOG("Before sort data is:");
    for (i = 0; i < 13; i += 1) {
        LOG(" %u", test_array2[i]);
    }
    LOG("\n");

    sort_method1(test_array2, 13, DESCENDING_ORDER);

    LOG("After sort data is:");
    for (i = 0; i < 13; i += 1) {
        LOG(" %u", test_array2[i]);
    }
    LOG("\n");

    return 0;
}
