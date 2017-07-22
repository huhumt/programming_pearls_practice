/**************************************************************************************
 * This source file is a test file for bitmap sort implement
 * Author: huhao
 * Date: 2017.07.18
 * Modification record:
 *
 **************************************************************************************/

#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "bitmap_sort.h"

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
    char *pdst_name = "./b.txt";
    FILE *fd_src, *fd_dst;
    uint32_t i, random_num;
    static uint32_t random_num_pre = 0;

    LOG("argc = %d\n", argc);
    switch(argc) {
    default:
    case 1:
        break;
    case 2:
        pdst_name = argv[1];
        break;
    case 3:
        psrc_name = argv[1];
        pdst_name = argv[2];
        break;
    }

    LOG("Begin to generate 10,000,000 random data\n");
    fd_src = fopen(psrc_name, "wb");

    for (i = 0; i < 100; i += 1) {
        random_num = generate_random_number(0, MAX_SUPPORT_SIZE);
        if (i % 10 == 0) {
            printf("\n");
        }
        printf("    %07lu", random_num);
    }
    printf("\n\n");

    for (i = 0; i < MAX_SUPPORT_SIZE; i += 1) {
        //random_num = generate_random_number(0, MAX_SUPPORT_SIZE);
        random_num = 9999999 - i;
        fwrite(&random_num, 4, 1, fd_src);
    }
    fclose(fd_src);
    LOG("Success generate random a.txt file\n");

    bitmap_sort(psrc_name, pdst_name, MAX_SUPPORT_SIZE);

    /* check for data in b.txt */
    fd_dst = fopen(pdst_name, "rb");
    if (fd_dst != NULL) {
        LOG("Success open %s\n", pdst_name);
    } else {
        LOG("Fail to open %s\n", pdst_name);
        return -5;
    }

    for (i = 0; i < MAX_SUPPORT_SIZE; i += 1) {
        fread(&random_num, 4, 1, fd_dst);
        /* not the first loop, but current number is smaller than previous, error */
        if (random_num_pre && random_num_pre >= random_num) {
            LOG("Sort number failed\n");
            fclose(fd_dst);
            return -2;
        }
        random_num_pre = random_num;
    }
    fclose(fd_dst);
    LOG("Pass test, sort number success\n");

    return 0;
}
