/*
 * Copyright (c) 2006-2015 David Schor (david@zigwap.com), ZigWap LLC
 * 
 * License: MIT
 */
char *a_next(char **s)
{
    assert(s != NULL);
    PASSTHROUGH_ON_FAIL(s != NULL, NULL);
    return (*s = *s + a_size_chr_cstr(*s));
}
char *a_next_cstr(const char **s)
{
    assert(s != NULL);
    PASSTHROUGH_ON_FAIL(s != NULL, NULL);
    return (char*)(*s = *s + a_size_chr_cstr(*s));
}
char *a_gnext(char **s)
{
    return a_gnext_cstr((const char **)s);
}
char *a_gnext_cstr(const char **s)
{
    a_cp this, next;
    do
    {
        this = a_next_cp_cstr(s);
        next = a_peek(*s);
    } while (next && !a_grapheme_break_table[A_GCB(this)][A_GCB(next)]);
    
    return (char*)*s;
}
a_cp a_next_cp(char **s)
{
    return a_next_cp_cstr((const char **)s);
}
a_cp a_next_cp_cstr(const char **s)
{
    assert(s != NULL);
    PASSTHROUGH_ON_FAIL(s != NULL, 0);
    return a_internal_critical_to_next_cp(s);
}

a_cp a_peek(const char *s)
{
    assert(s != NULL);
    PASSTHROUGH_ON_FAIL(s != NULL, 0);
    return a_to_cp(s);
}

a_cp a_peek_prev(const char *s)
{
    return a_to_cp(a_prev(&s));
}