/************************************************************************************
 * This source file is an implementation for binary search
 * Author: huhao
 * Date: 2017.08.03
 * Modification record:
 *
 *
 *************************************************************************************/

#include "binary_search.h"

int binary_search_standard(uint32_t array[], uint32_t array_size, uint32_t element, uint32_t* position)
{
#if 0

    uint32_t midpoint, search_range, midpoint_shift;

    /* initial midpoint and search range */
    midpoint = array_size / 2;
    search_range = array_size / 2;

    /* if array_size equals to 1 and array contains element,
     * using do...while will get right result */
    do {
        midpoint_shift = (search_range + 1) / 2;
        search_range /= 2;
        if (element < array[midpoint]) { // element must be on the left part
            midpoint -= midpoint_shift;
        } else if (element > array[midpoint]) { // element is on the right part
            midpoint += midpoint_shift;
        } else { // element found
            *position = midpoint;
            return 0;
        }
    } while(search_range);

    /* when search_range equals to 0, midpoint is at the beginning/ending
     * of the array, need to check for last time */
    if (element == array[midpoint]) {
        *position = midpoint;
        return 0;
    } else {
        return -1; // element is not contained in the array
    }

#else

    uint32_t left_index, right_index, midpoint;

    /* iniialize variables */
    left_index = 0;
    right_index = array_size - 1;
    midpoint = (left_index + right_index) / 2;

    while (left_index < right_index) {
        if (element < array[midpoint]) { // element is on the left part
            if (midpoint > 0) {
                right_index = midpoint - 1; // move right index left by half
            } else {
                right_index = 0;
            }
        } else if (element > array[midpoint]) { // element is on the right part
            if (midpoint < array_size - 1) {
                left_index = midpoint + 1; // move left index right by half
            } else {
                left_index = array_size - 1;
            }
        } else { // element found
            *position = midpoint;
            return 0;
        }
        midpoint = (left_index + right_index) / 2; // update midpoint
    }

    /* when left_index = right_index, need compare it with element */
    if (element == array[midpoint]) {
        *position = midpoint;
        return 0;
    } else {
        return -1; // element is not contained in the array
    }

#endif
}

int binary_search_first_appear(uint32_t array[], uint32_t array_size, uint32_t element, uint32_t* position)
{
    int ret;
    uint32_t position_tmp;

    /* first to find position using standard method */
    ret = binary_search_standard(array, array_size, element, &position_tmp);
    if (ret < 0) { // element is not in the array
        return ret;
    }

    *position = position_tmp; // position_tmp can be 0, so first given the found position
    while (position_tmp) {    // compare forward array element
        if (array[position_tmp] == element) {
            *position = position_tmp;
            position_tmp -= 1; // move pointer to left
        } else {               // find the first appearance of element
            return 0;
        }
    }

    return 0; // actually never run to here, just for no synaptic warning
}
