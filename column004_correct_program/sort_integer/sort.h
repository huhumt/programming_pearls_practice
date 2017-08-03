/*************************************************************************************
 * This header file is an interface to use sort function
 * Author: huhao
 * Date: 2017.08.03
 * Modification record:
 *
 ************************************************************************************/

#ifndef _SORT_H_
#define _SORT_H_

#include <stdio.h>
#include <stdint.h>

#ifdef _DEBUG_MODE_EN
#define LOG    printf
#else
#define LOG
#endif /* _DEBUG_MODE_EN */

typedef enum {
    ASCENDING_ORDER,
    DESCENDING_ORDER,
} sort_order_e;

int sort_method1(uint32_t array[], uint32_t array_size, sort_order_e order);

#endif /* _SORT_H_ */
