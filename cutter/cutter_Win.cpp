#include <iostream>
#include <cstring>
//#include <stdio.h>
//#include <malloc.h>

int main(int argc, char const *argv[])
{
    if (!strcmp(argv[1], "-h")) {
        printf("This program cuts the contents of a file [filename]\n  in two parts, according to the input integer parameter [cut_n].\
                \n  The two resulting files are compiled as follows:");
        printf("The first file contains the first [cut_n] consecutive bytes of the source file. ");
        printf("The second file contains all the remaining bytes of the source file taken consecutively starting from the sixth byte of the source file.\
                \n\nSyntax: [command name] [filename] [cut_n (unsigned integer number)].\n");
        exit(0);
    }
    // first condition - if arg[2] contains symbols apart from digits
    if ((argc != 3) || (strspn(argv[2], "1234567890") != strlen(argv[2]))) {
        printf("Incorrect input.\n  Syntax: [command name] [filename] [cut_n (unsigned integer number)].\n");
        printf("  Try 'cutter.exe -h' for more information.\n");
        exit(1);
    }

    char name_inp[260];
    char name_out[260];
    strcpy_s(name_inp, argv[1]);
    int cut_n = atoi(argv[2]);
    printf("Your input:  filename = '%s', cut_n = %d.\n", name_inp, cut_n);
    printf("  Try 'cutter.exe -h' for more information.\n");

    errno_t err;
    FILE* input;
    err = fopen_s(&input, name_inp, "rb");
    if (err) { perror(name_inp); exit(1); } // can't open file

    fseek(input, 0L, SEEK_END);
    int sz = ftell(input);
    rewind(input);

    unsigned char* input_data;
    input_data = (unsigned char*)malloc(sz);
    fread(input_data, 1, sz, input);
    
    FILE* output;

    char* point = strrchr(name_inp, '.');
    strncpy_s(name_out, name_inp, point - name_inp);
    strcat_s(name_out, 260, ".001");

    fopen_s(&output, name_out, "wb");
    fwrite(&input_data[0], 1, cut_n, output);
    fclose(output);

    char* one = strrchr(name_out, '1');
    strncpy_s(name_out, name_out, one - name_out);
    strcat_s(name_out, 260, "2");
    fopen_s(&output, name_out, "wb");
    fwrite(&input_data[cut_n], 1, sz - cut_n, output);

    fclose(input);
    fclose(output);

    
    free(input_data);
}