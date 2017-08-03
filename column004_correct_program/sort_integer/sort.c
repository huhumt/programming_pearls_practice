/*********************************************************************************
 * This source file is an implementation of sort method
 * Author: huhao
 * Date: 2017.08.03
 * Modification record:
 *
 **********************************************************************************/

#include "sort.h"

/****************************************************************************
 * Description: rotate array by 180 degree, ie. [1, 2, 3, 4] -> [4, 3, 2, 1]
 * Parameters:
 *     array: input array, also used to store data after rotated
 *     array_size: how many elements in the array
 * Return: 0 if normal, -n if abnormal
 *****************************************************************************/
static int reverse_array(uint32_t array[], uint32_t array_size)
{
    uint32_t i, tmp, len = array_size / 2;

    for (i = 0; i < len; i += 1) {
        tmp = array[i];
        array[i] = array[array_size - 1 - i];
        array[array_size - 1 - i] = tmp;
    }
    return 0;
}

int sort_method1(uint32_t array[], uint32_t array_size, sort_order_e order)
{
    uint32_t i, tmp, start, end;
    uint32_t max, min;
    uint32_t max_index, min_index;

    start = 0;
    end = array_size - 1;

    while (start < end) {
        /* initial with start value */
        max_index = start;
        min_index = start;
        max = array[max_index];
        min = array[min_index];

        /* search for max and min value in the array
         * and record relatived index */
        for (i = start; i <= end; i += 1) {
            if (array[i] > max) {
                max = array[i];
                max_index = i;
            }

            if (array[i] < min) {
                min = array[i];
                min_index = i;
            }
        }

        if (order == ASCENDING_ORDER) {
            /* if max value appears in the left of min value first swap their
             * position to make sure max value is on the right of min value */
            if (max_index < min_index) {
                tmp = array[max_index];
                array[max_index] = min;
                array[min_index] = tmp;

                tmp = max_index;
                max_index = min_index;
                min_index = tmp;
            }

            /* rotate array by 180 degree to make sure min value is at the beginning
             * and max value is at the ending */
            reverse_array(&array[start], min_index - start + 1);
            reverse_array(&array[max_index], end - max_index + 1);
        } else {
            /* if max value appears in the left of min value first swap their
             * position to make sure max value is on the right of min value */
            if (max_index > min_index) {
                tmp = array[max_index];
                array[max_index] = min;
                array[min_index] = tmp;

                tmp = max_index;
                max_index = min_index;
                min_index = tmp;
            }

            /* rotate array by 180 degree to make sure min value is at the beginning
             * and max value is at the ending */
            reverse_array(&array[start], max_index - start + 1);
            reverse_array(&array[min_index], end - min_index + 1);
        }

        LOG("\tarray is:");
        for (i = 0; i < array_size; i += 1) {
            LOG(" %u", array[i]);
        }
        LOG("\n");

        start += 1;
        end -= 1;
    }

    return 0;
}
