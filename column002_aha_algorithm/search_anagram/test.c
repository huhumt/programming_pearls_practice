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

    search_anagram(dict, 20);

    return 0;
}
