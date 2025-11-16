#include <stdio.h>

int main (void)
{
    /* OPTION 1
    char ch = '\0';
    FILE* fp = NULL;
    if (fp = fopen ("someFile.c", "rw"))
    {
        ch = getc (fp);
        while (ch != EOF)
        {
            putc (ch, fp);
            ch = getc (fp);
        }
    }
    fclose (fp);
    */
    /* OPTION 2 */
    char ch = 'd';
    putc (ch, stdout);

    return 0;
}