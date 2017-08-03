/************************************************************************************
 * This header file is an interface to use binary search algorithm
 * Author: huhao
 * Date: 2017.08.03
 * Modification record:
 *
 ***********************************************************************************/

#ifndef _BINARY_SEARCH_H_
#define _BINARY_SEARCH_H_

#include <stdio.h>
#include <stdint.h>

#ifdef _DEBUG_MODE_EN
#define LOG    printf
#else
#define LOG
#endif /* _DEBUG_MODE_EN */

/*************************************************************************************
 * Description: standard binary search program, search given element index in array
 * Parameters:
 *     array: array in sorted asending order
 *     array_size: total elements in array
 *     element: element need to be searched in array
 *     position: index for element in array
 * Return: 0 if normal, -1 if not found
 **************************************************************************************/
int binary_search_standard(uint32_t array[], uint32_t array_size, uint32_t element, uint32_t *position);

/*************************************************************************************
 * Description: some different with standard search, if element appears in array for
 *     more than once, find the first one rather than middest one.
 * Parameters:
 *     array: array in sorted asending order
 *     array_size: total elements in array
 *     element: element need to be searched in array
 *     position: index for element in array
 * Return: 0 if normal, -1 if not found
 **************************************************************************************/
int binary_search_first_appear(uint32_t array[], uint32_t array_size, uint32_t element, uint32_t *position);

#endif /* _BINARY_SEARCH_H_ */
