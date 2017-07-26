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

#define HALF_MAX_UINT32    (((uint32_t) 1) << 31)

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
    uint32_t num_size;

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
    uint32_t i, tmp, counter = 0;
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
            LOG("Duplicated data found, error\n");
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
                counter += 1; // find one more data excluded from the file
                if (counter >= array_size) { // have collected enough data for the array
                    LOG("Success find %lu excluded data\n", counter);
                    return 0;
                } else { // still in collecting data
                    parray += 1; // move pointer to the next, I never use "++" or "--"
                }
            }
        }
    }

    /* if do not exit before searched all the bitmap, indicate not enough excluded data
     * but we do not treat it as an error, return 0 as normal */
    LOG("Not enough excluded data, only find %lu\n", counter);
    return 0;

#else


#endif /* _SOLUTION_ONE */
}

uint32_t search_exclude_uint32_method2(char *pfile_name)
{
    FILE *fd_src;
    uint32_t i, tmp, num_size;
    uint32_t left_counter, right_counter;
    uint32_t midpoint, search_len;

    fd_src = fopen(pfile_name, "rb");
    if (fd_src == NULL) {
        LOG("Fail to open file %s\n", pfile_name);
        return -5;
    }
    fseek(fd_src, 0, SEEK_END);
    num_size = ftell(fd_src) / sizeof(uint32_t);
    rewind(fd_src);
    LOG("Totally has %lu data\n", num_size);

    midpoint = HALF_MAX_UINT32;
    search_len = HALF_MAX_UINT32;
    /* read data, compare left part and right part devided by midpoint
     * there must be some data missing in the smaller part
     * if any part has 0 data, it means we find the missing data */
    while (1) {
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

            if (left_counter > HALF_MAX_UINT32 || right_counter > HALF_MAX_UINT32) {
                LOG("Too much duplicated data, exit\n");
                fclose(fd_src);
                return -5;
            }
        }
        rewind(fd_src);
        LOG("Search range, %lu:%lu, left_counter=%lu, right_counter=%lu\n", midpoint - search_len, midpoint, left_counter, right_counter);

        /* for we devide data by format of [left_index, midpoint) and [midpoint, right_index)
         * it means left is included while right is excluded */
        if (left_counter == 0) {
            fclose(fd_src);
            return midpoint - 1;
        } else if(right_counter == 0) {
            fclose(fd_src);
            return midpoint;
        } else {
            /* there must be some data missing in the part with less data */
            search_len >>= 1;
            if (left_counter > right_counter) {
                midpoint += search_len;
            } else {
                midpoint -= search_len;
                /* search for all data and no data missing */
                if (left_counter == 1 && right_counter == 1) {
                    fclose(fd_src);
                    LOG("No missing uint32_t data in the file\n");
                    return 0;
                }
            }
        }
    }
}
