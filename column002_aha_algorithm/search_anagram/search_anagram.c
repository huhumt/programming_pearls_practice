/***************************************************************************************
 * This header file is an implementation for search_anagram
 * Author: huhao
 * Date: 2017.07.22
 * Modification record:
 *
 ***************************************************************************************/

#include <string.h>
#include "search_anagram.h"

/****************************************************************
 * Description: get status of certain bit of number
 * Parameters:
 *     num: the number need to be checked
 *     which_bit: which bit need to be checked
 * Return: 1-bit enabled, 0-bit disabled
 ****************************************************************/
static inline uint8_t GET_BIT(uint8_t num, uint8_t which_bit)
{
    if (which_bit < 8) {
        return (num & (1 << which_bit));
    } else {
        return 0;
    }
}

/******************************************************************
 * Description: set certain bit to enabled
 * Parameters:
 *     num: the number need to be set bit
 *     which_bit: which bit need to be set enabled
 * Return: the number after setting bit
 *******************************************************************/
static inline uint8_t SET_BIT(uint8_t num, uint8_t which_bit)
{
    if (which_bit < 8) { // only applied to uint8_t type
        return (num | (1 << which_bit));
    } else { // invalid to left shift more than 7 bit
        return (num);
    }
}

/**************************************************************************************
 * Description: summary how many time each alphabet appear
 * Parameters:
 *     psrc: pointer to input string
 *     alphabet_map[]: array to store alphabet_map
 *     len: lenght of alphabet_map, generally 26. For there are 26 letters in English
 * Return: 0 if normal, -n if abnormal
 **************************************************************************************/
static int generate_alphabet_map(char *psrc, uint8_t alphabet_map[], uint8_t len)
{
    char tmp;
    uint8_t index;

    if (psrc == NULL) {
        return -5;
    }

    do { // if empty string, can exit abnormal
        tmp = *psrc;
        if (tmp >= 'A' && tmp <= 'Z') {
            /* lowercase all the letters first */
            tmp += 32;
        } else if (tmp >= 'a' && tmp <= 'z') {
            // do nothing
        } else { // not valid letter
            return -5;
        }
        index = tmp - 'a';
        alphabet_map[index] += 1;
        psrc += 1; // move pointer to next
    } while (*psrc != '\0');

    return 0;
}

/* interface function, refer to .h file to use it */
int search_anagram(char *dict[], uint32_t len)
{
    uint32_t i, j, index;
    uint8_t k, offset, anagram_flag;
    uint8_t alphabet_map1[MAX_LETTER_NUM];
    uint8_t alphabet_map2[MAX_LETTER_NUM];
    uint8_t bitmap_ignore[MAX_WORD_NUM / 8];

    if (len > MAX_WORD_NUM) {
        LOG("Error, no more than %lu words in Oxford Dictionary\n", MAX_WORD_NUM);
        return -5;
    } else {
        LOG("There are %lu words in the dictionary\n", len);
    }

    memset(bitmap_ignore, 0, sizeof(bitmap_ignore));
    LOG("Anagrams list below:\n");
    for (i = 0; i < len - 1; i += 1) {
        /* check whether this element has been recorded as anagram */
        index = i / 8;
        offset = (uint8_t) (i % 8);
        if (GET_BIT(bitmap_ignore[index], offset)) {
            break;
        } else {
            anagram_flag = 0;
            memset(alphabet_map1, 0, MAX_LETTER_NUM);
        }

        if (generate_alphabet_map(dict[i], alphabet_map1, MAX_LETTER_NUM) < 0) {
            /* non-alphabet found, invalid string */
            break;
        } else {
            // currently we do nothing here
        }

        for (j = i + 1; j < len; j += 1) {
            /* check whether this element has been recorded as anagram */
            index = j / 8;
            offset = (uint8_t) (j % 8);
            if (GET_BIT(bitmap_ignore[index], offset)) {
                continue;
            } else {
                memset(alphabet_map2, 0, MAX_LETTER_NUM);
            }

            if (generate_alphabet_map(dict[j], alphabet_map2, MAX_LETTER_NUM) < 0) {
                /* non-alphabet found, invalid string */
                continue;
            } else {
                for (k = 0; k < MAX_LETTER_NUM; k += 1) {
                    if (alphabet_map1[k] == alphabet_map2[k]) { // same letter
                        // current do nothing here
                    } else { // different letter
                        break;
                    }
                }
                if (k == MAX_LETTER_NUM) { // find anagram
                    if (anagram_flag) { // not the first time
                        LOG(" %s", dict[j]);
                    } else { // first anagram found
                        LOG("\n    %s %s", dict[i], dict[j]);
                        anagram_flag = 1;
                        /* if anagram found, set flag to ignore check for another time */
                        index = i / 8;
                        offset = (uint8_t) (i % 8);
                        bitmap_ignore[index] = SET_BIT(bitmap_ignore[index], offset);
                    }
                    /* if anagram found, set flag to ignore check for another time */
                    index = j / 8;
                    offset = (uint8_t) (j % 8);
                    bitmap_ignore[index] = SET_BIT(bitmap_ignore[index], offset);
                }
            }
        }
    }
    LOG("\n\n");

    return 0;
}
