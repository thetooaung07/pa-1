//
// Created by aungthet on 2/6/24.
//



#include <stdio.h>
#include <limits.h>
#include "string.h"


int main ( void )
{
char a [5] = "abcd";
char *b = a;
strcpy(a, "aaaaa");
    printf("%s\n", a);
}