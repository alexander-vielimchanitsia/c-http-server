#include <string.h>
#include "utils.h"

/*
 * combines two paths into dest
 */
void path_combine(char *dest, char *path1, char *path2)
{
    // TODO: make it stable
    strcpy(dest, path1);
    strcat(dest, path2);
}
