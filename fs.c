#include <stdio.h>
#include <stdlib.h>

#include "Chaos.h"

// Filesystem operations

// void fs.copy(str filepath1, str filepath2)

int fp_copy(char *src, char *dst)
{
    FILE *fp_src;
    FILE *fp_dst;

    char ch;

    fp_src = fopen(src, "r");
    fp_dst = fopen(dst, "w");

    if (fp_src == NULL)
    {
       printf("Unable to open source file.\n");
       return 1;
    }
    else if (fp_dst == NULL) {
        printf("Unable to create destination file.\n"); 
        return 1;
    }

    while ((ch = fgetc(fp_src)) != EOF)
        fputc(ch, fp_dst);
    
    fclose(fp_src);
    fclose(fp_dst);

    return 0;
}

char *copy_param_names[] = {
    "fp_1",
    "fp_2"
};
unsigned copy_params_type[] = {
    K_STRING,
    K_STRING
};
unsigned copy_params_secondary_type[] = {
    K_ANY
};
unsigned short copy_params_length = (unsigned short) sizeof(copy_params_type) / sizeof(unsigned);
int KAOS_EXPORT Kaos_copy()
{
    char* fp_1 = kaos.getVariableString(copy_param_names[0]);
    char* fp_2 = kaos.getVariableString(copy_param_names[1]);
    fp_copy(fp_1, fp_2);
    free(fp_1);
    free(fp_2);
    return 0;
}
