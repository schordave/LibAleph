#include "aleph.h"
#include <stdio.h>

int main()
{
    a_gc;
    a_str *emails, *e;
    const char *email_list = "<foo@example.com> <bar@gmail.com> <baz@hotmail.com> <qux@yahoo.com>"
                             " <foo@example.com> <bar@gmail.com> <baz@hotmail.com> <qux@yahoo.com>"
                             " <foo@example.com> <bar@gmail.com> <baz@hotmail.com> <qux@yahoo.com>"
                             " <foo@example.com> <bar@gmail.com> <baz@hotmail.com> <qux@yahoo.com>";
    
    emails = a_split(email_list, ' ');
    for (e = emails; *e; ++e)
        printf("=> %s\n", a_(a_substr_between_cstr(*e, "<", ">", 0)));
    
    a_free_vec(emails);
    a_gc_done();
    return 0;
}