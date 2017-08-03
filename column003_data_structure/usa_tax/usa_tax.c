/****************************************************************************************
 * This source file is an implementation to calculate tax based on your monthly income
 * Author: huhao
 * Date: 2017.07.31
 * Modification record:
 *
 *
 *
 *****************************************************************************************/

#include "usa_tax.h"

/**********************************************************************************
 * Description: find index for element in ascending sorted array data
 * Parameters:
 *     array: array to store data
 *     array_size: element numbers in array
 *     element: elment need to find index
 * Return: index for element in array
 **********************************************************************************/
static uint8_t find_index(uint32_t array[], uint8_t array_size, uint32_t element)
{
    uint8_t i;

    for (i = 0; i < array_size; i += 1) {
        if (element <= array[i]) {
            return i;
        }
    }
    return (array_size - 1);
}

float usa_tax_calculator(uint32_t income)
{
    const uint8_t kARRAY_SIZE = 57;
    uint8_t i, index, tax_rate[kARRAY_SIZE];
    uint16_t inc, tax_base[kARRAY_SIZE];
    uint32_t tax_level[kARRAY_SIZE];

    tax_rate[0] = 0;
    tax_base[0] = 0;
    tax_level[0] = 2200;

    for (i = 1; i < kARRAY_SIZE; i += 1) {
        tax_rate[i] = 14 + (i - 1);
        if (i > 1) {
            inc += 5;
        } else {
            inc = 70;
        }
        tax_base[i] = tax_base[i - 1] + inc;
        tax_level[i] = tax_level[i - 1] + 500;
    }
    LOG("tax = %u + .%u * (income - %lu)\n", tax_base[56], tax_rate[56], tax_level[56]);

    index = find_index(tax_level, kARRAY_SIZE, income);
    if (index == 0) {
        return 0.0f;
    } else {
        return (tax_base[index] + tax_rate[index] * 0.01f * (income - tax_level[index - 1]));
    }
}
