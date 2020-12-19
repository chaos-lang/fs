#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
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


// I/O

// num fs.open(str filepath, str mode)

char *open_param_names[] = {
    "filepath",
    "mode"
};
unsigned open_params_type[] = {
    K_STRING,
    K_STRING
};
unsigned open_params_secondary_type[] = {
    K_ANY,
    K_ANY
};
unsigned short open_params_length = (unsigned short) sizeof(open_params_type) / sizeof(unsigned);
int KAOS_EXPORT Kaos_open()
{
    char* filepath = kaos.getVariableString(open_param_names[0]);
    char* mode = kaos.getVariableString(open_param_names[1]);

    FILE *fp = fopen(filepath, mode);
    free(filepath);
    free(mode);

    if (fp == NULL)
        kaos.raiseError("Unable to open the file");

    kaos.returnVariableInt((intptr_t) fp);
    return 0;
}

// void fs.close(num file_descriptor)

char *close_param_names[] = {
    "file_descriptor"
};
unsigned close_params_type[] = {
    K_NUMBER
};
unsigned close_params_secondary_type[] = {
    K_ANY
};
unsigned short close_params_length = (unsigned short) sizeof(close_params_type) / sizeof(unsigned);
int KAOS_EXPORT Kaos_close()
{
    long long file_descriptor_int = kaos.getVariableInt(close_param_names[0]);
    fclose((FILE* ) file_descriptor_int);
    return 0;
}

// str fs.read(num file_descriptor)

char *read_param_names[] = {
    "file_descriptor"
};
unsigned read_params_type[] = {
    K_NUMBER
};
unsigned read_params_secondary_type[] = {
    K_ANY
};
unsigned short read_params_length = (unsigned short) sizeof(read_params_type) / sizeof(unsigned);
int KAOS_EXPORT Kaos_read()
{
    long long file_descriptor_int = kaos.getVariableInt(close_param_names[0]);

    FILE *fp = (FILE* ) file_descriptor_int;

    fseek(fp, 0, SEEK_END);
    long fsize = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    char *text = malloc(fsize + 1);
    fread(text, 1, fsize, fp);

    text[fsize] = 0;

#if defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__)
    remove_char_from_string(text, '\r');
#endif
    kaos.returnVariableString(text);
    free(text);
    return 0;
}

// void fs.write(num file_descriptor, str text)

char *write_param_names[] = {
    "file_descriptor",
    "text"
};
unsigned write_params_type[] = {
    K_NUMBER,
    K_STRING
};
unsigned write_params_secondary_type[] = {
    K_ANY,
    K_ANY
};
unsigned short write_params_length = (unsigned short) sizeof(write_params_type) / sizeof(unsigned);
int KAOS_EXPORT Kaos_write()
{
    long long file_descriptor_int = kaos.getVariableInt(close_param_names[0]);
    char *text = kaos.getVariableString(write_param_names[1]);
    FILE *fp = (FILE* ) file_descriptor_int;
    fprintf(fp, "%s", text);
    free(text);
    return 0;
}


// Filesystem Operations

// void fs.move(str oldpath, str newpath)

char *move_param_names[] = {
    "oldpath",
    "newpath"
};
unsigned move_params_type[] = {
    K_STRING,
    K_STRING
};
unsigned move_params_secondary_type[] = {
    K_ANY,
    K_ANY
};
unsigned short move_params_length = (unsigned short) sizeof(move_params_type) / sizeof(unsigned);
int KAOS_EXPORT Kaos_move()
{
    int ret;

    char* old_path = kaos.getVariableString(move_param_names[0]);
    char* new_path = kaos.getVariableString(move_param_names[1]);

    ret = rename(old_path, new_path);
    free(old_path);
    free(new_path);
    if (ret != 0)
        kaos.raiseError("Error when renaming the file.");

    return 0;
}

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
        sprintf(err, "Cannot access '%s'", path);
        kaos.raiseError(err);
    } else if (info.st_mode & S_IFDIR) {
        kaos.returnVariableBool(true);
    } else {
        kaos.returnVariableBool(false);
    }
    free(path);

    return 0;
}

// bool fs.is_file(str path)

char *is_file_param_names[] = {
    "path"
};
unsigned is_file_params_type[] = {
    K_STRING
};
unsigned is_file_params_secondary_type[] = {
    K_ANY
};
unsigned short is_file_params_length = (unsigned short) sizeof(is_file_params_type) / sizeof(unsigned);
int KAOS_EXPORT Kaos_is_file()
{
    char* path = kaos.getVariableString(is_file_param_names[0]);

    FILE *fp;
    fp = fopen(path, "r");
    if (fp == NULL) {
        char err[100];
        sprintf(err, "Unable to access '%s'", path);
        kaos.raiseError(err);
        return -1;
    }
    fclose(fp);

    struct stat info;
    stat(path, &info);
    free(path);
    if (S_ISREG(info.st_mode)) {
        kaos.returnVariableBool(true);
    } else {
        kaos.returnVariableBool(false);
    }

    return 0;
}


int KAOS_EXPORT KaosRegister(struct Kaos _kaos)
{
    kaos = _kaos;

    // I/O
    kaos.defineFunction("open", K_STRING, K_ANY, open_param_names, open_params_type, open_params_secondary_type, open_params_length, NULL, 0);
    kaos.defineFunction("close", K_VOID, K_ANY, close_param_names, close_params_type, close_params_secondary_type, close_params_length, NULL, 0);
    kaos.defineFunction("read", K_STRING, K_ANY, read_param_names, read_params_type, read_params_secondary_type, read_params_length, NULL, 0);
    kaos.defineFunction("write", K_VOID, K_ANY, write_param_names, write_params_type, write_params_secondary_type, write_params_length, NULL, 0);

    // Filesystem Operations
    kaos.defineFunction("move", K_VOID, K_ANY, move_param_names, move_params_type, move_params_secondary_type, move_params_length, NULL, 0);
    kaos.defineFunction("copy", K_VOID, K_ANY, copy_param_names, copy_params_type, copy_params_secondary_type, copy_params_length, NULL, 0);
    kaos.defineFunction("is_dir", K_STRING, K_ANY, is_dir_param_names, is_dir_params_type, is_dir_params_secondary_type, is_dir_params_length, NULL, 0);
    kaos.defineFunction("is_file", K_STRING, K_ANY, is_file_param_names, is_file_params_type, is_file_params_secondary_type, is_file_params_length, NULL, 0);

    return 0;
}
