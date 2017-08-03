/************************************************************************************
 * This source file is an implementation of seven segment display
 * Author: huhao
 * Date: 2017.07.31
 * Modification record:
 *
 ************************************************************************************/

#include "seven_segment.h"

static inline uint8_t SET_BIT(uint8_t num, uint8_t which_bit)
{
    if (which_bit > 7) {
        return num;
    } else {
        return (num | (1 << which_bit));
    }
}

static int seven_segment_dispaly_digit(uint8_t digit)
{
    uint8_t tmp = 0;

    if (digit > 9) {
        LOG("Can only display digits from 0 to 9\n");
        return -5;
    } else {
        switch (digit) {
        case 0:
            tmp = SET_BIT(tmp, 0);
            tmp = SET_BIT(tmp, 2);
            tmp = SET_BIT(tmp, 3);
            tmp = SET_BIT(tmp, 4);
            tmp = SET_BIT(tmp, 5);
            tmp = SET_BIT(tmp, 6);
            break;
        case 1:
            tmp = SET_BIT(tmp, 4);
            tmp = SET_BIT(tmp, 6);
            break;
        case 2:
            tmp = SET_BIT(tmp, 0);
            tmp = SET_BIT(tmp, 1);
            tmp = SET_BIT(tmp, 2);
            tmp = SET_BIT(tmp, 4);
            tmp = SET_BIT(tmp, 5);
            break;
        case 3:
            tmp = SET_BIT(tmp, 0);
            tmp = SET_BIT(tmp, 1);
            tmp = SET_BIT(tmp, 2);
            tmp = SET_BIT(tmp, 4);
            tmp = SET_BIT(tmp, 6);
            break;
        case 4:
            tmp = SET_BIT(tmp, 1);
            tmp = SET_BIT(tmp, 3);
            tmp = SET_BIT(tmp, 4);
            tmp = SET_BIT(tmp, 6);
            break;
        case 5:
            tmp = SET_BIT(tmp, 0);
            tmp = SET_BIT(tmp, 1);
            tmp = SET_BIT(tmp, 2);
            tmp = SET_BIT(tmp, 3);
            tmp = SET_BIT(tmp, 6);
            break;
        case 6:
            tmp = SET_BIT(tmp, 0);
            tmp = SET_BIT(tmp, 2);
            tmp = SET_BIT(tmp, 3);
            tmp = SET_BIT(tmp, 4);
            tmp = SET_BIT(tmp, 5);
            tmp = SET_BIT(tmp, 6);
            break;
        case 7:
            tmp = SET_BIT(tmp, 2);
            tmp = SET_BIT(tmp, 4);
            tmp = SET_BIT(tmp, 6);
            break;
        case 8:
            tmp = SET_BIT(tmp, 0);
            tmp = SET_BIT(tmp, 1);
            tmp = SET_BIT(tmp, 2);
            tmp = SET_BIT(tmp, 3);
            tmp = SET_BIT(tmp, 4);
            tmp = SET_BIT(tmp, 5);
            tmp = SET_BIT(tmp, 6);
            break;
        case 9:
            tmp = SET_BIT(tmp, 0);
            tmp = SET_BIT(tmp, 1);
            tmp = SET_BIT(tmp, 2);
            tmp = SET_BIT(tmp, 3);
            tmp = SET_BIT(tmp, 4);
            tmp = SET_BIT(tmp, 6);
            break;
        default:
            break;
        }
    }
    return (int) tmp;
}

int seven_segment_dispaly(uint16_t num)
{
    uint8_t mod, segment;
    uint8_t i, bit_shift;

    do {
        mod = num % 10;
        segment = (uint8_t) seven_segment_dispaly_digit(mod);
        LOG("mod is %d, segment is %d, bit on is:", mod, segment);
        for (i = 0; i < 8; i += 1) {
            bit_shift = 1 << i;
            if (segment & bit_shift) {
                LOG(" %d", i);
            }
        }
        LOG("\n");
        num /= 10;
    } while (num > 0);
    return 0;
}
