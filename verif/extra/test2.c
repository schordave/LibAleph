#include "aleph.h"
#include <stdio.h>

int main(void)
{
    a_cp cp;
    char chr[5], name[A_NAME_MAX_SIZE];
    
    printf("List of chess symbols: ");
    for (cp = A_MIN_CP; cp <= A_MAX_CP; ++cp)
        if (a_ifind_cstr_cstr(a_name_cp(cp, name), "chess") != A_EOS)
            printf("%s ", a_to_utf8(cp, chr));
    puts("");
    return 0;
}