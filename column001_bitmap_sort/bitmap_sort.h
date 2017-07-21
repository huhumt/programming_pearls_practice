/********************************************************************************************
 * This header file is an interface to use bitmap sort
 * Author: huhao
 * Date: 2017.07.18
 * Modification record:
 *
 ********************************************************************************************/

#ifndef _BITMAP_SORT_H_
#define _BITMAP_SORT_H_

#include <stdint.h>

#define MAX_SUPPORT_SIZE    (10000000)

#ifdef _DEBUG_MODE_EN
    #define LOG    printf
#else
    #define LOG
#endif /* _DEBUG_MODE_EN */

/******************************************************************
 * Description: sort disk data by bitmap
 * Parameters:
 *     *psrc_name: pointer to input disk file name
 *     *pdst_name: pointer to file name you want to save on disk
 *     num_size: how many valid data stored in psrc_name
 *               no more than MAX_SUPPORT_SIZE
 * Return: 0 if normal, -n if abnormal
 ******************************************************************/
int bitmap_sort(char *psrc_name, char *pdst_name, uint32_t num_size);

#endif /* _BITMAP_SORT_H_ */
