/*************************************************************************************
 * This header file is an interface to use rotate_vector function
 * Author: huhao
 * Date: 2017.07.21
 * Modification record:
 *
 **************************************************************************************/

#ifndef _ROTATE_VECTOR_H_
#define _ROTATE_VECTOR_H_

#include <stdint.h>

#ifdef _DEBUG_MODE_EN
    #define LOG    printf
#else
    #define LOG
#endif /* _DEBUG_MODE_EN */

/********************************************************************
 * Description: rotate vector by rotate_point
 * Parameters:
 *     pstr: pointer to input string
 *     len: length of input string
 *     rotate_point: rotate by this point
 * Return: 0 if normal, -n if abnormal
 ********************************************************************/
int rotate_vector(char *pstr, uint32_t len, uint32_t rotate_point);

#endif /* _ROTATE_VECTOR_H_ */
