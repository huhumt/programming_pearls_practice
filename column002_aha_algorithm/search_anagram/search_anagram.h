/*****************************************************************************************
 * This header file is an interface to use search_anagram function
 * Author: huhao
 * Date: 2017.07.22
 * Modification record:
 *
 *****************************************************************************************/

#ifndef _SEARCH_ANAGRAM_H_
#define _SEARCH_ANAGRAM_H_

#include <stdio.h>
#include <stdint.h>

#ifdef _DEBUG_MODE_EN
    #define LOG    printf
#else
    #define LOG
#endif /* _DEBUG_MODE_EN */

/* according to Oxford Dictionary website, there are about 200,000 English words */
#define MAX_WORD_NUM      (400000)
#define MAX_LETTER_NUM    (26)

/********************************************************************************
 * Description: find anagrams in given dictionary
 * Parameters:
 *     dict: array of pointer of given dictionary
 *     len: length of array, how many elements in it
 * Return: 0 if normal, -n if abnormal
 ********************************************************************************/
int search_anagram(char *dict[], uint32_t len);

#endif /* _SEARCH_ANAGRAM_H_ */
