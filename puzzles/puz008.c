/*****************************************************************************************************
 * Challenges - String Search Challenge
 *
 * Write a program that takes two arguments at the command line, both strings.
 * The program checks to see whether or not the second string is a substring of the first
 * One caveat: any * in the second string can match zero or more characters in the first string
 * so if the input were "abcd" and the substring were "a*c", then it would count as a substring
 * Also, include functionality to allow an asterisk to be taken literally if preceded by a \
 * and a \ is taken literally except when preceding an asterisk.
 *****************************************************************************************************/

#include <stdint.h>
#include <stdio.h>

static void compare_string(char* str1, char* str2)
{
    char* pstr1_tmp = str1;
    char* pstr2_tmp = str2;
    uint8_t star_mode_on = 0;
    uint16_t start_index = 0;

    if (str1 == NULL || str2 == NULL) {
        printf("invalid string of NULL.\n");
    }

    while (*pstr1_tmp != '\0') {
        if (*pstr2_tmp == '*') {
            star_mode_on = 1;
            pstr2_tmp += 1;
        } else if (*pstr2_tmp == '\\' && *(pstr2_tmp + 1) == '*') {
            star_mode_on = 1;
            pstr2_tmp += 2;
        } else {
            if (*pstr2_tmp == *pstr1_tmp) {
                if (start_index == 0) {
                    start_index = pstr1_tmp - str1;
                }
                pstr2_tmp += 1;
            } else {
                if (star_mode_on == 0) {
                    start_index = 0;
                    pstr2_tmp = str2;
                }
            }
            pstr1_tmp += 1;
        }

        if (*pstr2_tmp == '\0') {
            printf("%s is substring to %s, start_index=%d, end_index=%d\n", str2, str1, start_index, pstr1_tmp - str1);
            return;
        }
    }
    printf("%s is not substring to %s\n", str2, str1);
}

int main(int argc, char* argv[])
{
    char* str1 = "abcbdcfedcba";
    char* str2 = "skjflaksjf;alkjf;ajfdlkaj";

    compare_string(str1, str2);

    return 0;
}
