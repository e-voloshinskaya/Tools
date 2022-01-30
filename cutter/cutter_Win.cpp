#include <iostream>
#include <stdio.h>
#include <malloc.h>

int main(int argc, char const *argv[])
{
    int cut = 0;
    char name_inp[260];

    //scanf_s("%d", &cut);
    strcpy_s(name_inp, argv[1]);
    cut = atoi(argv[2]);


    FILE* input;
    fopen_s(&input, name_inp, "rb"); if (!input) { perror(name_inp); exit(1); }
    fseek(input, 0L, SEEK_END);
    int sz = ftell(input);
    rewind(input);
    unsigned char* input_data;
    input_data = (unsigned char*)malloc(sz);

    fread(input_data, 1, sz, input);
    
    FILE* output;

    fopen_s(&output, "left", "wb");
    fwrite(&input_data[0], 1, cut, output);
    fclose(output);
    fopen_s(&output, "right", "wb");
    fwrite(&input_data[cut], 1, sz - cut, output);

    fclose(input);
    fclose(output);

    
    free(input_data);
}