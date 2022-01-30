/* Формат ввода в командной строке: [команда] [файл] [количество значений в строке]
Имя файла не должно содержать русские буквы. Если оно содержит пробелы, при вводе необходимо заключить его в двойные кавычки.
Отсутствие расширения обрабатывает корректно, добавляет .asm. Если расширения нет, но точка в названии есть, как и винда, считает вторую часть расширением.
Параметр 3 может принимать любые целые значения. Если оно меньше или равно нулю,
а также больше размера файла, то информация выведется в одну строку.
*/
#include <iostream>
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>

int main(int argc, char const* argv[])
{
    if (!strcmp(argv[1], "-h")) {
        printf("This command translates the contents of a file [filename]\n  into a set of bytes in format:\n ");
        printf("\t\tdb\t#33 #40 #9F\n");
        printf("\t\tdb\t#0A #79 #AE\n");
        printf("Groups like #NN represent a byte. Their number in a line depends on the second argument [string length].\n");
        printf("Syntax: [command name] [filename] [string length (integer number)].\n");
        printf("!!!  [string length] can be any integer value. If it is\n\t- less than or equal to zero;\
                \n\t- larger than the file size,\n  then the information will be displayed in one line.\
                \nIf [string length] has incorrect format, it will be translated to 0\n  (if a string doesn't contain numbers) or some number.\n");
        exit(0);
    }
    if (argc != 3) {
        printf("Incorrect input.\n  Syntax: [command name] [filename] [string length (integer number)].\n");
        printf("  Try 'bin2asm.exe -h' for more information.\n");
        exit(1);
    }
    int str_size = atoi(argv[2]);
    char name_inp[260];
    char name_out[260];
    int count = 1;
    //strcpy(name_inp, argv[1]);
    strcpy_s(name_inp, argv[1]); // got arguments from console
    printf("Your input:  filename = '%s', str_length = %d.\n", name_inp, str_size);
    printf("  Try 'bin2asm.exe -h' for more information.\n");

    errno_t err;
    FILE* input_file;
    //FILE** pinput = &input;
    //input = fopen(name_inp, "rb");
    err = fopen_s(&input_file, name_inp, "rb");
    if (err) { perror(name_inp); exit(1); } // opened file
    
    fseek(input_file, 0L, SEEK_END);
    int sz = ftell(input_file);
    rewind(input_file); // got size (sz) of the file

    unsigned char* data = (unsigned char*)malloc(sz);
    fread(data, 1, sz, input_file);
    fclose(input_file); //read data

    // filling name_out
    char* point = strrchr(name_inp, '.');
    // position: [point - name_inp], also a number of symb-s before '.' 
    //strncpy(name_out, name_inp, point - name_inp); //copy in to out
    strncpy_s(name_out, name_inp, point - name_inp);
    //strcat(name_out, ".asm"); // add .asm
    strcat_s(name_out, ".asm");

    FILE* output;
    //FILE** poutput = &output;
    //output = fopen("result", "wb");
    fopen_s(&output, name_out, "w");

    //fprintf(output, "Atoi -> %d\n", str_size);
    for (int i = 0; i < sz; i++)
    {
        if (count == 1)
            fprintf(output, "\t\tdb\t");
        fprintf(output, "#%02X", data[i]);

        if ((i != sz - 1) && (count != str_size))
            fprintf(output, ", ");
        count++;
        if (count == str_size + 1)
        {
            fprintf(output, "\n");
            count = 1;
        }
        //printf("%d ", input_data[i]); //вывод тех же символов с переводом в числа и обратно
        //int sym = input_data[i];
        //fwrite(&sym, sizeof(int), 1, output);
    }

    fclose(output);
    free(data);
    return 0;
}
