#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "Chaos.h"

void remove_char_from_string(char *str, char c)
{
    int i = 0;
    int len = strlen(str) + 1;

    for (i=0; i<len; i++) {
        if (str[i] == c) {
            strncpy(&str[i], &str[i+1], len - i);
        }
    }
}

// File Operations

// void fs.copy(str src_filepath, str dst_filepath)

char *copy_param_names[] = {
    "src_filepath",
    "dst_filepath"
};
unsigned copy_params_type[] = {
    K_STRING,
    K_STRING
};
unsigned copy_params_secondary_type[] = {
    K_ANY,
    K_ANY
};
unsigned short copy_params_length = (unsigned short) sizeof(copy_params_type) / sizeof(unsigned);
int KAOS_EXPORT Kaos_copy()
{
    char* src_filepath = kaos.getVariableString(copy_param_names[0]);
    char* dst_filepath = kaos.getVariableString(copy_param_names[1]);

    FILE *fp_src;
    FILE *fp_dst;

    fp_src = fopen(src_filepath, "r");
    free(src_filepath);
    if (fp_src == NULL) {
        kaos.raiseError("Unable to open the source file");
    }

    fp_dst = fopen(dst_filepath, "w");
    free(dst_filepath);
    if (fp_dst == NULL) {
        kaos.raiseError("Unable to create the destination file.");
    }

    char ch;
    while ((ch = fgetc(fp_src)) != EOF)
        fputc(ch, fp_dst);

    fclose(fp_src);
    fclose(fp_dst);
    return 0;
}

// bool fs.is_dir(str path)

char *is_dir_param_names[] = {
    "path"
};
unsigned is_dir_params_type[] = {
    K_STRING
};
unsigned is_dir_params_secondary_type[] = {
    K_ANY
};
unsigned short is_dir_params_length = (unsigned short) sizeof(is_dir_params_type) / sizeof(unsigned);
int KAOS_EXPORT Kaos_is_dir()
{
    char* path = kaos.getVariableString(is_dir_param_names[0]);

    struct stat info;
    if (stat(path, &info) != 0) {
        char err[100];
        sprintf(err, "Cannot acces '%s'\n", path);
        kaos.raiseError(err);
    } else if (info.st_mode & S_IFDIR) {
       kaos.returnVariableBool(true);
    } else {
        kaos.returnVariableBool(false);
    }

    return 0;
}

// str fs.read(str filepath)

char *read_param_names[] = {
    "filepath"
};
unsigned read_params_type[] = {
    K_STRING
};
unsigned read_params_secondary_type[] = {
    K_ANY
};
unsigned short read_params_length = (unsigned short) sizeof(read_params_type) / sizeof(unsigned);
int KAOS_EXPORT Kaos_read()
{
    char* filepath = kaos.getVariableString(read_param_names[0]);

    FILE *fp = fopen(filepath, "rb");
    free(filepath);

    if (fp == NULL)
        kaos.raiseError("Unable to open the file");

    fseek(fp, 0, SEEK_END);
    long fsize = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    char *text = malloc(fsize + 1);
    fread(text, 1, fsize, fp);
    fclose(fp);

    text[fsize] = 0;

#if defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__)
    remove_char_from_string(text, '\r');
#endif
    kaos.returnVariableString(text);
    free(text);
    return 0;
}

// void fs.rename(str oldpath, str newpath)

char *rename_param_names[] = {
    "oldpath",
    "newpath"
};
unsigned rename_params_type[] = {
    K_STRING,
    K_STRING
};
unsigned rename_params_secondary_type[] = {
    K_ANY,
    K_ANY
};
unsigned short rename_params_length = (unsigned short) sizeof(rename_params_type) / sizeof(unsigned);
int KAOS_EXPORT Kaos_rename()
{
    int ret;

    char* oldpath = kaos.getVariableString(rename_param_names[0]);
    char* newpath = kaos.getVariableString(rename_param_names[1]);

    ret = rename(oldpath, newpath);
    if (ret != 0)
        kaos.raiseError("Error when renaming the file.");

    return 0;
}

int KAOS_EXPORT KaosRegister(struct Kaos _kaos)
{
    kaos = _kaos;

    // File Operations
    kaos.defineFunction("copy", K_VOID, K_ANY, copy_param_names, copy_params_type, copy_params_secondary_type, copy_params_length, NULL, 0);
    kaos.defineFunction("is_dir", K_STRING, K_ANY, is_dir_param_names, is_dir_params_type, is_dir_params_secondary_type, is_dir_params_length, NULL, 0);
    kaos.defineFunction("read", K_STRING, K_ANY, read_param_names, read_params_type, read_params_secondary_type, read_params_length, NULL, 0);
    kaos.defineFunction("rename", K_VOID, K_ANY, rename_param_names, rename_params_type, rename_params_secondary_type, rename_params_length, NULL, 0);

    return 0;
}
