/*******************************************************************************************
 * This source file is an implementation for searching excluded integers in given file.
 * Author: huhao
 * Date: 2017.07.21
 * Modification record:
 *
 *****************************************************************************************/

#include <stdio.h>
#include <string.h>
#include "search_exclude_integer.h"

/****************************************************************
 * Description: get status of certain bit of number
 * Parameters:
 *     num: the number need to be checked
 *     which_bit: which bit need to be checked
 * Return: 1-bit enabled, 0-bit disabled
 ****************************************************************/
static inline uint8_t GET_BIT(uint8_t num, uint8_t which_bit)
{
    if (which_bit < 8) {
        return (num & (1 << which_bit));
    } else {
        return 0;
    }
}

/******************************************************************
 * Description: set certain bit to enabled
 * Parameters:
 *     num: the number need to be set bit
 *     which_bit: which bit need to be set enabled
 * Return: the number after setting bit
 *******************************************************************/
static inline uint8_t SET_BIT(uint8_t num, uint8_t which_bit)
{
    if (which_bit < 8) { // only applied to uint8_t type
        return (num | (1 << which_bit));
    } else { // invalid to left shift more than 7 bit
        return (num);
    }
}

/* interface function, refer to .h file to use it */
int search_exclude_uint32(char *pfile_name, uint32_t *parray, uint32_t array_size)
{
    FILE *fd_src;
    uint32_t i, tmp;
    uint32_t num_size, counter = 0;

    fd_src = fopen(pfile_name, "rb");
    if (fd_src != NULL) {
        LOG("Success open file %s\n", pfile_name);
    } else {
        LOG("Fail to open file %s\n", pfile_name);
        return -5;
    }

    /* move file pointer to the end, then get the file length by byte,
     * for we store uint32_t data, need devide the length by sizeof(uint32_t).
     * After getting the data size, we must set the file pointer to the beginning. */
    fseek(fd_src, 0, SEEK_END);
    num_size = ftell(fd_src) / sizeof(uint32_t);
    rewind(fd_src);
    LOG("There are %lu data in %s\n", num_size, pfile_name);

#ifdef _SOLUTION_ONE

    /*************************************************************************
     * In this solution, we have ample main memory, refer to column 1,
     * we can build a huge bitmap with 2^32 bits(2^29 bytes) to record
     * all the included and excluded integers, then we can put
     * array_size integers to parray to accomplish the task
     *************************************************************************/
    const uint32_t kARRAY_SIZE = 1 << (32 - 3);
    /* It takes too much memory here, I can't even test it on my computer */
    uint8_t bitmap_array[kARRAY_SIZE];
    uint32_t index;
    uint8_t j, offset;

    memset(bitmap_array, 0, sizeof(bitmap_array));

    for (i = 0; i < num_size; i += 1) {
        fread(&tmp, 4, 1, fd_src); // read a uint32_t data
        index = tmp / 8;
        offset = tmp % 8;
        if (GET_BIT(bitmap_array[index], offset)) { // have recored data already
            LOG("Dupicated data found, error\n");
            fclose(fd_src);
            return -4;
        } else { // first time to detect the data, record it in bitmap
            bitmap_array[index] = SET_BIT(bitmap_array[index], offset);
        }
    }
    LOG("Success generate bitmap array\n");
    fclose(fd_src);

    for (i = 0; i < kARRAY_SIZE; i += 1) { // check bitmap_array
        for (j = 0; j < 8; j += 1) { // check each bit of bitmap_array element
            if (GET_BIT(bitmap_array[i], j)) { // the num is included in the file
                // currently do nothing here
            } else { // the num is excluded from the file
                tmp = i * 8 + j;
                *parray = tmp;
                parray += 1; // move pointer to the next, I never use "++" or "--"
                counter += 1; // find one more data excluded from the file
                if (counter >= array_size) { // have collected enough data for the array
                    LOG("Success find %lu excluded data\n", counter);
                    return 0;
                } else { // still in collecting data
                    // currently we do nothing here
                }
            }
        }
    }

    /* if do not exit before searched all the bitmap, indicate not enough excluded data
     * but we do not treat it as an error, return 0 as normal */
    LOG("Not enough excluded data, only find %lu\n", counter);
    return 0;

#else

    /***********************************************************************************
     * In this situation, we only have hundred bytes of memory.
     **********************************************************************************/

    /* Each byte can be [0x00, 0xff], totally 256 possibility
     * so need 256 bits(32 bytes) for each, uint32_t has 4 byte */
    uint8_t bitmap[4][32];
    uint8_t k, m, n, m_data;
    uint16_t loop1, loop2, loop3;
    uint8_t index, offset;
    uint32_t zero_num_counter = 0;

    memset(bitmap, 0, sizeof(bitmap));

    for (i = 0; i < num_size; i += 1) {
        fread(&tmp, 4, 1, fd_src);
        for (m = 0; m < 4; m += 1) {
            m_data = (uint8_t) ((tmp >> (8 * m)) & 0xff);
            index = m_data / 8;
            offset = m_data % 8;
            bitmap[m][index] = SET_BIT(bitmap[m][index], offset);
        }
    }

    for (m = 0; m < 4; m += 1) { // check bitmap
        for (n = 0; n < 32; n += 1) {
            for (k = 0; k < 8; k += 1) {
                if (GET_BIT(bitmap[m][n], k)) { // this byte is recorded
                    // do nothing currently
                } else { // this byte hasn't been recorded
                    m_data = 8 * n + k;
                    for (loop1 = 0; loop1 < 256; loop1 += 1) {
                        for (loop2 = 0; loop2 < 256; loop2 += 1) {
                            for (loop3 = 0; loop3 < 256; loop3 += 1) {
                                switch (m) {
                                case 0:
                                    tmp = (((uint32_t) loop1) << 24) + (((uint32_t) loop2) << 16)
                                        + (((uint32_t) loop3) << 8) + (uint32_t) m_data;
                                    break;
                                case 1:
                                    tmp = (((uint32_t) loop1) << 24) + (((uint32_t) loop2) << 16)
                                        + ((uint32_t) loop3) + (((uint32_t) m_data) << 8);
                                    break;
                                case 2:
                                    tmp = (((uint32_t) loop1) << 24) + (((uint32_t) loop2) << 8)
                                        + ((uint32_t) loop3) + (((uint32_t) m_data) << 16);
                                    break;
                                case 3:
                                    tmp = (((uint32_t) loop1) << 16) + (((uint32_t) loop2) << 8)
                                        + ((uint32_t) loop3) + (((uint32_t) m_data) << 24);
                                    break;
                                default:
                                    break;
                                }
                                if (tmp == 0) {
                                    zero_num_counter += 1;
                                }
                                *parray = tmp;
                                parray += 1;
                                counter += 1;
                                if (counter >= array_size) { // have collected enough data for the array
                                    LOG("Success find %lu excluded data with %lu 0\n", counter, zero_num_counter);
                                    fclose(fd_src);
                                    return 0;
                                } else { // still in collecting data
                                    // currently we do nothing here
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    fclose(fd_src);
    /* if do not exit before searched all the bitmap, indicate not enough excluded data
     * but we do not treat it as an error, return 0 as normal */
    LOG("Not enough excluded data, only find %lu with %lu 0\n", counter, zero_num_counter);
    return 0;

#endif /* _SOLUTION_ONE */
}

uint32_t search_exclude_uint32_method2(char *pfile_name)
{
    FILE *fd_src;
    uint32_t i, tmp, num_size;
    uint32_t left_counter, right_counter;
    uint32_t midpoint;

    fd_src = fopen(pfile_name, "rb");
    if (fd_src == NULL) {
        LOG("Fail to open file %s\n", pfile_name);
        return -5;
    }
    fseek(fd_src, 0, SEEK_END);
    num_size = ftell(fd_src) / sizeof(uint32_t);
    rewind(fd_src);

    midpoint = ((uint32_t) 1) << 31;
    /* read data, compare left part and right part devided by midpoint
     * there must be some data missing in the smaller part
     * if any part has 0 data, it means we find the missing data */
    do {
        /* initial counter and midpoint */
        left_counter = 0;
        right_counter = 0;

        /* read data from file and counter left/right part */
        for (i = 0; i < num_size; i += 1) {
            fread(&tmp, 4, 1, fd_src);
            if (tmp < midpoint) {
                left_counter += 1;
            } else {
                right_counter += 1;
            }
        }
        rewind(fd_src);

        /* there must be some data missing in the part with less data */
        tmp = midpoint / 2;
        if (left_counter > right_counter) {
            midpoint += tmp;
        } else {
            midpoint -= tmp;
        }
    } while (left_counter && right_counter);

    fclose(fd_src);

    /* for we devide data by format of [left_index, midpoint) and [midpoint, right_index)
     * it means left is included while right is excluded */
    if (left_counter == 0) {
        return midpoint - 1;
    } else {
        return midpoint;
    }
}
