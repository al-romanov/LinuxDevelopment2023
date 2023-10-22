#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        fprintf(stderr, "Usage: %s REGEX SUBSTITUTION STRING\n", argv[0]);
        return -1;
    }
    const char *regex_str = argv[1];
    size_t substitution_str_length = strlen(argv[2]);
    char *substitution_str = calloc(substitution_str_length + 1, sizeof(*substitution_str));
    strcpy(substitution_str, argv[2]);
    const char *input_str = argv[3];
    regex_t regex;
    int regcomp_error = regcomp(&regex, regex_str, REG_EXTENDED);
    if (regcomp_error)
    {
        enum
        {
            MAX_ERROR_LENGTH = 1024
        };
        char *error_str = calloc(MAX_ERROR_LENGTH, sizeof(*error_str));
        regerror(regcomp_error, &regex, error_str, MAX_ERROR_LENGTH);
        fprintf(stderr, "%s\n", error_str);
        free(error_str);
        return -2;
    }
    size_t str_length;
    enum
    {
        MAX_BAGS = 10
    };
    regmatch_t bags[MAX_BAGS];
    if (regexec(&regex, input_str, MAX_BAGS, bags, 0) != 0)
    {
        puts(input_str);
        return 0;
    }
    int number_bags = 0;
    while (number_bags < MAX_BAGS && bags[number_bags].rm_so >= 0)
    {
        ++number_bags;
    }

    // Replace all '\\' with '\' and bags to  it's content
    size_t i = 0;
    while (substitution_str[i])
    {
        if (substitution_str[i] == '\\')
        {
            ++i;
            if (substitution_str[i] == '\\')
            {
                strcpy(substitution_str + i, substitution_str + i + 1);
                --substitution_str_length;
            }
            else if (substitution_str[i] >= '0' && substitution_str[i] <= '9')
            {
                int bag_number = substitution_str[i] - '0';
                if (bag_number >= number_bags)
                {
                    fprintf(stderr, "Failed to find group with number %d\n", bag_number);
                    return -3;
                }
                regoff_t offset = bags[bag_number].rm_so;
                regoff_t bag_length = bags[bag_number].rm_eo - bags[bag_number].rm_so;
                substitution_str = realloc(substitution_str, substitution_str_length + bag_length + 1);
                strcpy(substitution_str + i - 1 + bag_length, substitution_str + i + 1);
                strncpy(substitution_str + i - 1, input_str + offset, bag_length);
                substitution_str_length += bag_length - 2;
            }
        }
        ++i;
    }
    printf("%.*s%s%s\n", bags[0].rm_so, input_str, substitution_str, input_str + bags[0].rm_eo);
    regfree(&regex);
    return 0;
}