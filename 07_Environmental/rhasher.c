#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <rhash.h>

#include "config.h"

#ifdef READLINE
#include <readline/readline.h>
#endif

typedef struct HashInfo
{
    int algorithm;
    int view;
} HashInfo;

int get_hash_info(const char *hash, HashInfo *info)
{
    const char *hash_names[] = {
        "MD5", "SHA1", "TTH"};
    int algorithms[] = {RHASH_MD5, RHASH_SHA1, RHASH_TTH};
    for (unsigned long i = 0; i < sizeof(hash_names) / sizeof(*hash_names); ++i)
    {
        size_t hash_name_len = strlen(hash_names[i]);
        if (!strncmp(hash, hash_names[i], hash_name_len))
        {
            info->algorithm = algorithms[i];
            info->view = RHPR_HEX;
            return 0;
        }
        char *lower_case_hash_name = calloc(hash_name_len + 1, sizeof(*lower_case_hash_name));
        if (!lower_case_hash_name)
        {
            fputs("Out of memory!\n", stderr);
            return 1;
        }
        for (unsigned long j = 0; hash_names[i][j]; ++j)
        {
            lower_case_hash_name[j] = tolower(hash_names[i][j]);
        }
        if (!strncmp(hash, lower_case_hash_name, hash_name_len))
        {
            info->algorithm = algorithms[i];
            info->view = RHPR_BASE64;
            free(lower_case_hash_name);
            return 0;
        }
        free(lower_case_hash_name);
    }
    fputs("Wrong hash name!\n", stderr);
    return -1;
}

int main()
{
    char *input = NULL;
    rhash_library_init();
#ifndef READLINE
    size_t len = 0;
    while (getline(&input, &len, stdin) != -1)
#else
    while ((input = readline(NULL)) != NULL)
#endif
    {
        char *EOL = strstr(input, "\n");
        if (EOL)
        {
            *EOL = '\0';
        }
        HashInfo info;
        if (get_hash_info(input, &info))
        {
            if (input)
            {
                free(input);
                input = NULL;
            }
            continue;
        }
        free(input);
        input = NULL;
#ifndef READLINE
        if (getline(&input, &len, stdin) == 1)
#else
        if ((input = readline(NULL)) == NULL)
#endif
        {
            break;
        }
        EOL = strstr(input, "\n");
        if (EOL)
        {
            *EOL = '\0';
        }
        char *whitespace = strstr(input, " ");
        if (whitespace)
        {
            *whitespace = '\0';
        }
        unsigned char digest[64];
        char output[130];
        int res = 0;
        char *pure_input = input;
        if (input[0] == '\"')
        {
            pure_input += 1;
            res = rhash_msg(info.algorithm, pure_input, strlen(pure_input), digest);
        }
        else
        {
            res = rhash_file(info.algorithm, pure_input, digest);
        }
        if (res < 0)
        {
            fprintf(stderr, "Hashing error: %s!\n", strerror(errno));
        }
        else
        {
            rhash_print_bytes(output, digest, rhash_get_digest_size(info.algorithm), info.view);
            puts(output);
        }
        free(input);
        input = NULL;
    }
    free(input);
    return 0;
}
