#include <stdio.h>
#include <string.h>

#include <dlfcn.h>

typedef int (*remove_proto)(const char *);

int remove(const char *name)
{
    if (strstr(name, "PROTECT")) {
        return 0;
    }
    remove_proto std_remove = dlsym(RTLD_NEXT, "remove");
    return std_remove(name);
}