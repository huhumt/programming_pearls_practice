/*****************************************************************************************
 * Self-Printing Program
 *
 * Write a program that, when run, will print out its source code.
 * This source code, in turn, should compile and print out itself.
 * (Fun fact: a program that prints itself is called a quine.)
 ********************************************************************************************/

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static void print_file(char* filename)
{
    char* pbuf;
    uint32_t file_size;
    FILE* fd;

    fd = fopen(filename, "r");
    if (fd == NULL) {
        printf("fail to open file\n");
    }

    fseek(fd, 0, SEEK_END);
    file_size = ftell(fd);
    rewind(fd);

    pbuf = (char*)calloc(file_size, sizeof(char));
    if (pbuf == NULL) {
        printf("fail to allocate memory\n");
    }

    fread(pbuf, sizeof(char), file_size, fd);
    fclose(fd);

    while (file_size > 0) {
        printf("%c", *pbuf);
        pbuf += 1;
        file_size -= 1;
    }
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        print_file("./puz014.c");
    } else {
        print_file(argv[1]);
    }

    return 0;
}
