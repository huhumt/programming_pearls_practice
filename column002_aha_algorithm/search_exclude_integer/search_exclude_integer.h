/**************************************************************************************
 * This header file is an interface to search an integer that isn't in the file
 * Author: huhao
 * Date: 2017.07.21
 * Modification record:
 *
 ***************************************************************************************/

#ifndef _SEARCH_EXCLUDE_INTEGER_H_
#define _SEARCH_EXCLUDE_INTEGER_H_

#include <stdint.h>

#ifdef _DEBUG_MODE_EN
    #define LOG    printf
#else
    #define LOG
#endif /* _DEBUG_MODE_EN */

/**************************************************************************************
 * Description: find integers that are not in the file
 * Parameters:
 *     pfile_name: pointer to the file name that include some uint32_t integers
 *     parray: pointer to the array to store integers that aren't in the file
 *     array_size: how many excluded integers do you want to search
 *                 if (array_size = 1), we only find one then quit
 * Return: 0 if normal, -n if abnormal
 **************************************************************************************/
int search_exclude_uint32(char *pfile_name, uint32_t *parray, uint32_t array_size);

#endif /* _SEARCH_EXCLUDE_INTEGER_H_ */
