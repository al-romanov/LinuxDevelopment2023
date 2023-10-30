#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int close_files(FILE *infile, FILE *outfile)
{
}

int main(int argc, char *argv[])
{
    if (argc != 3) {
        fputs("Usage: move <infile> <outfile>", stderr);
        return 1;
    }
    char *infile_name = argv[1];
    FILE *infile = fopen(infile_name, "r");
    if (!infile) {
        fputs("Couldn't open file ", stderr);
        fputs(infile_name, stderr);
        fputs("\n", stderr);
        return 2;
    }
    char *outfile_name = argv[2];
    FILE *outfile = fopen(outfile_name, "w");
    if (!outfile) {
        fputs("Couldn't open file ", stderr);
        fputs(outfile_name, stderr);
        fputs("\n", stderr);
        fclose(infile);
        return 2;
    }
    enum { BUF_SIZE = 1024 }; // moving by 1KB
    void *buffer = malloc(BUF_SIZE);
    int exit_status = 0;
    do {
        size_t chars_read = fread(buffer, 1, BUF_SIZE, infile);
        if (ferror(infile)) {
            fputs("Failed to read from ", stderr);
            fputs(infile_name, stderr);
            fputs("\n", stderr);
            exit_status = 3;
            break;
        }
        size_t chars_written = fwrite(buffer, 1, chars_read, outfile);
        if (chars_written != chars_read && ferror(outfile)) {
            fputs("Failed to write to ", stderr);
            fputs(outfile_name, stderr);
            fputs("\n", stderr);
            exit_status = 4;
            break;
        }
    } while (!feof(infile));
    fclose(infile);
    fclose(outfile);
    if (exit_status) {
        int remove_status = remove(outfile_name);
        if (remove_status) {
            fputs("Couldn't remove file ", stderr);
            fputs(infile_name, stderr);
            fputs("\n", stderr);
            return 6;
        }
        return exit_status;
    }
    int remove_status = remove(infile_name);
    if (remove_status) {
        fputs("Couldn't remove file ", stderr);
        fputs(infile_name, stderr);
        fputs("\n", stderr);
        return 6;
    }
    return 0;
}
