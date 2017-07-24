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
    /* the first element index for the left and right */
    uint32_t left_start = 0, right_start = rotate_point;
    /* total element number of left and right */
    uint32_t left_len = rotate_point, right_len = len - left_len;

    /* if rotate_point is at the beginning or end,
     * do not need rotate at all */
    if (!left_len || !right_len) {
        return 0;
    }

    LOG("str=%s, left_len=%d, right_len = %d, left_start=%d, right_start=%d\n", pstr, left_len, right_len, left_start, right_start);
    while (left_len != right_len) {
        if (left_len > right_len) {
            /* swap right_len elements */
            for (i = 0; i < right_len; i += 1) {
                tmp = *(pstr + right_start + i);
                *(pstr + right_start + i) = *(pstr + left_start + i);
                *(pstr + left_start + i) = tmp;
            }
            left_len -= right_len;
            left_start += right_len;
            LOG("str=%s, left_len=%d, right_len = %d, left_start=%d, right_start=%d\n", pstr, left_len, right_len, left_start, right_start);
        } else {
            right_start_tmp = right_start + (right_len - left_len);
            for (i = 0; i < left_len; i += 1) {
                tmp = *(pstr + left_start + i);
                *(pstr + left_start + i) = *(pstr + right_start_tmp + i);
                *(pstr + right_start_tmp + i) = tmp;
            }
            right_len -= left_len;
            LOG("str=%s, left_len=%d, right_len = %d, left_start=%d, right_start=%d\n", pstr, left_len, right_len, left_start, right_start);
        }
    }

    /* left_len equals to right_len, just swap data */
    for (i = 0; i < left_len; i += 1) {
        tmp = *(pstr + left_start + i);
        *(pstr + left_start + i) = *(pstr + right_start + i);
        *(pstr + right_start + i) = tmp;
    }
    LOG("str=%s, left_len=%d, right_len = %d, left_start=%d, right_start=%d\n", pstr, left_len, right_len, left_start, right_start);

    return 0;
}
