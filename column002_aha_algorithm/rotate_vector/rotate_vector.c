/****************************************************************************************
 * This source file is an implementation of rotate vector
 * Author: huhao
 * Date: 2017.07.21
 * Modification record:
 *
 ****************************************************************************************/

#include "rotate_vector.h"

/* interface function, refer to .h file for usage */
int rotate_vector(char *pstr, uint32_t len, uint32_t rotate_point)
{
    char tmp;
    uint32_t i, right_start_tmp;
    uint32_t left_start = 0, right_start = rotate_point;
    uint32_t left_len = rotate_point;
    uint32_t right_len = len - left_len;

    while (left_len != right_len) {
        if (left_len > right_len) { // move right to left
            for (i = 0; i < right_len; i += 1) {
                tmp = *(pstr + right_start + i);
                *(pstr + right_start + i) = *(pstr + left_start + i);
                *(pstr + left_start + i) = tmp;
                left_len -= right_len;
                left_start += right_len;
            }
        } else { // move left to right
            right_start_tmp = right_start + (right_len - left_len);
            for (i = 0; i < left_len; i += 1) {
                tmp = *(pstr + left_start + i);
                *(pstr + left_start + i) = *(pstr + right_start_tmp + i);
                *(pstr + right_start_tmp + i) = tmp;
            }
            right_len -= left_len;
        }
    }

    /* left_len equals to right_len, just swap data */
    for (i = 0; i < left_len; i += 1) {
        tmp = *(pstr + left_start + i);
        *(pstr + left_start + i) = *(pstr + right_start + i);
        *(pstr + right_start + i) = tmp;
    }
}
