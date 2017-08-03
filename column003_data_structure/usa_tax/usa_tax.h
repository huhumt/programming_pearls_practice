/******************************************************************************************
 * This header file is an interface to use usa tax calculator program
 * Author: huhao
 * Date: 2017.07.31
 * Modification record:
 *
 *
 *****************************************************************************************/

#ifndef _USA_TAX_H_
#define _USA_TAX_H_

#include <stdio.h>
#include <stdint.h>

#ifdef _DEBUG_MODE_EN
#define LOG    printf
#else
#define LOG
#endif /* _DEBUG_MODE_EN */

/**********************************************************************************
 * Description: this function is used to calculate tax based on your income
 * Parameters:
 *     income: you monthly income
 * Return: the amount you will be taxed
 ***********************************************************************************/
float usa_tax_calculator(uint32_t income);

#endif /* _USA_TAX_H_ */
