#include "aleph.h"
#include <stdio.h>

int main()
{
    a_str a = a_new(u8"Hello World!");
    
    puts(a);
    
    a_free(a);
    return 0;
}
