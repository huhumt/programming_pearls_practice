/**************************************************************************************
 * This source file is a test file for usa tax calculator impletation
 * Author: huhao
 * Date: 2017.07.31
 * Modification record:
 *
 **************************************************************************************/

#include "usa_tax.h"

int main(int argc, char *argv[])
{
    float tax;
    tax = usa_tax_calculator(3201);
    LOG("income=%u, tax=%f\n", 3201, tax);
    return 0;
}
