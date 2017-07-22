/******************************************************************************************
 * This is a test file for search_anagram function
 * Author: huhao
 * Date: 2017.07.22
 * Modification record:
 *
 ******************************************************************************************/

#include <string.h>
#include "search_anagram.h"

int main(int argc, char *argv[])
{
    char *dict[20] = {
        "abcdefg", "hijk", "lmnop", "qrst", "uvwxyz",
        "bcdefga", "ijkh", "mnopl", "rstq", "vwxyzu",
        "cdefgab", "jkhi", "noplm", "stqr", "wxyzuv",
        "efgabcd", "khij", "oplmn", "tqsr", "xyzuvw"
    };

    char *dict_null[5] = {
        NULL, NULL, NULL, NULL, NULL
    };

    char *dict_tops[7] = {
        "Tops", "tips", "oops", "sTop", "1", "2", "pots"
    };

    char *dict_empty[5] = {
        "", "", "", "", ""
    };

    search_anagram(dict, 20);
    search_anagram(dict_null, 5);
    search_anagram(dict_tops, 7);
    search_anagram(dict_empty, 5);

    return 0;
}
