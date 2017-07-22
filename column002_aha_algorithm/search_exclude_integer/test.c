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
    uint32_t i, j, random_num;
    const uint32_t kMAX_UINT32 = (1 << 31);
    const uint32_t kRANDOM_NUM_SIZE = 6000000;
    const uint32_t kSEARCH_ARRAY_SIZE = 10000;
    uint32_t search_array[kSEARCH_ARRAY_SIZE];
    uint32_t zero_num_counter = 0;

    memset(search_array, 0, sizeof(search_array));

    LOG("Begin to generate %lu random data\n", kRANDOM_NUM_SIZE);
    fd_src = fopen(psrc_name, "wb");

    for (i = 0; i < kRANDOM_NUM_SIZE; i += 1) {
        random_num = generate_random_number(0, kMAX_UINT32);
        if (random_num == 0) { // count how many zeros
            zero_num_counter += 1;
        }
        fwrite(&random_num, 4, 1, fd_src);
    }
    fclose(fd_src);
    LOG("Success generate random a.txt file\n");

    search_exclude_uint32(psrc_name, search_array, kSEARCH_ARRAY_SIZE);

    fd_src = fopen(psrc_name, "rb");
    for (i = 0; i < kRANDOM_NUM_SIZE; i += 1) {
        fread(&random_num, 4, 1, fd_src);
        for (j = 0; j < kSEARCH_ARRAY_SIZE; j += 1) {
            if (random_num == search_array[j]) {
                LOG("Error: find same integer with the file\n");
                fclose(fd_src);
                return -2;
            } else {
                // everything is ok, have a rest
            }
        }
    }

    LOG("Pass the test, congratulations\n");
    LOG("Totally have %lu 0 in %s\n", zero_num_counter, psrc_name);

    return 0;
}
