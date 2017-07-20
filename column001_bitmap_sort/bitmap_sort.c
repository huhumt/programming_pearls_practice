/*********************************************************************************************
 * This source file is an implement of bitmap sort
 * Author: huhao
 * Data: 2017.07.18
 * Modification record:
 *
 *********************************************************************************************/

#include <stdio.h>
#include <string.h>
#include "bitmap_sort.h"

/****************************************************************
 * Description: get status of certain bit of number
 * Input:
 *     num: the number need to be checked
 *     which_bit: which bit need to be checked
 * return: 1-bit enabled, 0-bit disabled
 ****************************************************************/
static inline uint8_t GET_BIT(uint8_t num, uint8_t which_bit)
{
    if (which_bit < 8) {
        return (num & (1 << which_bit));
    } else {
        return 0;
    }
}

static inline uint8_t SET_BIT(uint8_t num, uint8_t which_bit)
{
    if (which_bit < 8) { // only applied to uint8_t type
        return (num | (1 << which_bit));
    } else { // invalid to left shift more than 7 bit
        return (num);
    }
}

int bitmap_sort(char *psrc_name, char *pdst_name, uint32_t num_size)
{
    uint32_t i, index, tmp;
    uint8_t j, offset;
    FILE *fd_src, *fd_dst;
    /* totally MAX_SUPPORT_SIZE data, each data takes a bit in bitmap_array
     * but each element in bitmap_array is a byte(8 bits)
     * so totally (MAX_SUPPORT_SIZE / 8) elements in bitmap_array */
    const uint32_t kARRAY_SIZE = MAX_SUPPORT_SIZE / 8;
    uint8_t bitmap_array[kARRAY_SIZE];

    memset(bitmap_array, 0, kARRAY_SIZE);
    fd_src = fopen(psrc_name, "rb");
    if (fd_src != NULL) {
        LOG("Success open %s\n", psrc_name);
    } else {
        LOG("Fail to open %s\n", psrc_name);
        return -5;
    }

    for (i = 0; i < num_size; i += 1) {
        fread(&tmp, 4, 1, fd_src); // read a uint32_t data
        index = tmp / 8;
        offset = tmp % 8;
        if (GET_BIT(bitmap_array[index], offset)) { // have recored data already
            LOG("Dupicated data found, error\n");
            fclose(fd_src);
            return -4;
        } else {
            bitmap_array[index] = SET_BIT(bitmap_array[index], offset);
        }
    }
    LOG("Sucess generate bitmap array\n");

    fclose(fd_src);
    fd_dst = fopen(pdst_name, "wb");
    if (fd_dst != NULL) {
        LOG("Success open %s\n", pdst_name);
    } else {
        LOG("Fail to open %s\n", pdst_name);
        return -5;
    }

    for (i = 0; i < kARRAY_SIZE; i += 1) { // check bitmap_array
        for (j = 0; j < 8; j += 1) { // check each bit of bitmap_array element
            if (GET_BIT(bitmap_array[i], j)) { // the num exists
                tmp = i * 8 + j;
                fwrite(&tmp, 4, 1, fd_dst);
            } else { // not exist
                // currently do nothing here
            }
        }
    }
    fclose(fd_dst);
    LOG("Success sort a.txt to b.txt\n");

    return 0;
}
