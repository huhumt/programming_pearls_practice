/**************************************************************************************
 * This source file is a test file for find excluded integer from given file
 * Author: huhao
 * Date: 2017.07.18
 * Modification record:
 *
 **************************************************************************************/

#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "search_exclude_integer.h"

/************************************************************************
 * Description: generate random number ranges from [low_range, hi_range)
 *              low_range is included while hi_range is not
 * Parameters:
 *     low_range: low range of random number
 *     hi_range: high range of random number
 * return: random number in range of [low_range, hi_range)
 *************************************************************************/
static uint32_t generate_random_number(uint32_t low_range, uint32_t hi_range)
{
    uint8_t i, rand8[4];
    uint32_t rand32 = 0;
    static uint8_t rand_initialized = 0;

    if (low_range >= hi_range) { // invalid input parameter
        return 0;
    }

    if (!rand_initialized) {
        srand(time(NULL));
        rand_initialized = 1;
    }

    /* rand() function can generate random number in [0, 32767)
     * so we need 4 uint8_t random number to generate uint32_t random number */
    for (i = 0; i < 4; i += 1) {
        rand8[i] = rand() % 0xff;
        rand32 |= rand8[i];
        rand32 <<= 8;
    }

    /* re-range number in range of [low_range, hi_range) */
    return (rand32 % (hi_range - low_range) + low_range);
}

int main(int argc, char *argv[])
{
    LOG("begin to run........\n");
    char *psrc_name = "./a.txt";
    FILE *fd_src;
    uint32_t i, tmp;

    fd_src = fopen(psrc_name, "wb");
    for (i = 4000000UL; i >= 1; i -= 1) {
        if (100 == i) {
            tmp = 0;
        } else {
            tmp = i;
        }
        fwrite(&tmp, 4, 1, fd_src);
    }
    fclose(fd_src);

    tmp = search_exclude_uint32_method2(psrc_name);
    LOG("Pass the test, missing data is %lu, congratulations\n", tmp);
    return 0;
}
