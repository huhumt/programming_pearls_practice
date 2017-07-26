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

    /* rotate_point is at the beginning/ending, do not need rotate */
    if (rotate_point == 0 || rotate_point >= len) {
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

static int reverse_string(char *psrc, char *pdst, uint32_t len)
{
    uint32_t num;
    char tmp, *psrc_tmp;

    if (psrc == NULL || pdst == NULL) {
        LOG("Must be char array to store string\n");
        return -5;
    }

    if (psrc == pdst) { // use the same array to store reverse string
        num = len / 2;
    } else { // use different arrary
        num = len;
    }

    psrc_tmp = psrc + len - 1; // end of the string
    while (num) {
        /* swap data, use tmp to avoid psrc and pdst is the same */
        tmp = *pdst;
        *pdst = *psrc_tmp;
        *psrc_tmp = tmp;

        /* move pointer */
        psrc_tmp -= 1;
        pdst += 1;
        num -= 1;
    }

    return 0;
}

/* We can describe the problem as transfer ab to ba.
 * ba = (a'b')' while a' = reverse(a), so we can solve the problem easily */
int rotate_vector_method2(char *pstr, uint32_t len, uint32_t rotate_point)
{
    /* rotate_point is at the beginning/ending, do not need rotate */
    if (rotate_point == 0 || rotate_point >= len) {
        return 0;
    }

    /* get left part reversed, ie a' */
    if (reverse_string(pstr, pstr, rotate_point) < 0) {
        return -5;
    }
    /* get right part reversed, ie b' */
    if (reverse_string(pstr + rotate_point, pstr + rotate_point, len - rotate_point) < 0) {
        return -5;
    }
    /* get the whole string reversed, ie (a'b')' */
    if (reverse_string(pstr, pstr, len) < 0) {
        return -5;
    }
    return 0;
}
