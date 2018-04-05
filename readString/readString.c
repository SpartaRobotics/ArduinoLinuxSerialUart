#include <stdio.h>
#include <string.h>

int main ()
{
    char str[] ="1,2,3,4,5";
    char *token;
    char *rest = str;
    int val;

    while ((token = strtok_r(rest, ",", &rest)))
    {
        val = atoi(token);
        //printf("%s\n", token);
        printf("%d\n", val);
    }

    return 0;
}