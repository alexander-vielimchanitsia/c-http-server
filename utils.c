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

void reverse(char *s)
{
    int temp, i, j;
    for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
        temp = s[j];
        s[j] = s[i];
        s[i] = temp;
    }
}

/* convests int to string */
void itoa(int n, char *s)
{
    int i, sign;
    if ((sign = n) < 0)
        n = -n;
    i = 0;
    do {
        s[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}
