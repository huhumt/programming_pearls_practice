/***************************************************************************************
 * This header file is an interface to use seven segment dispaly
 * Author: huhao
 * Date: 2017.07.31
 * Modification record:
 *
 ***************************************************************************************/

#ifndef _SEVEN_SEGMENT_H_
#define _SEVEN_SEGMENT_H_

#include <stdio.h>
#include <stdint.h>

#ifdef _DEBUG_MODE_EN
#define LOG    printf
#else
#define LOG
#endif /* _DEBUG_MODE_EN */

int seven_segment_dispaly(uint16_t num);

#endif /* _SEVEN_SEGMENT_H_ */
