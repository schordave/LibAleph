/*
 * Copyright (c) 2006-2015 David Schor (david@zigwap.com), ZigWap LLC
 * 
 * License: MIT
 */

static a_cp a_internal_to_prev_cp(const char **s)
{
    return a_internal_char_to_cp(
                a_internal_to_prev(s));
}

static char *a_internal_to_prev(const char **s)
{
#if 1
    const char *t = *s - 1;
    
    (void)(((*t-- & 0xC0) == 0x80)
            && ((*t-- & 0xC0) == 0x80)
                && ((*t-- & 0xC0) == 0x80));
    
    *s = t + 1;
    return (char*)*s;
#else
    const char *t;
    
    for (t = *s - 1; ; --t)
    {
        if ((*t & 0xC0) != 0x80)
        {
            *s = t;
            break;
        }
    }
    
    return (char*)t;
#endif
}
char *a_prev(char **s)
{
    assert(s != NULL);
    PASSTHROUGH_ON_FAIL(s != NULL, NULL);
    return a_internal_to_prev((const char**)s);
}
char *a_prev_cstr(const char **s)
{
    assert(s != NULL);
    PASSTHROUGH_ON_FAIL(s != NULL, NULL);
    return a_internal_to_prev(s);
}

a_cp a_prev_cp(char **s)
{
    assert(s != NULL);
    PASSTHROUGH_ON_FAIL(s != NULL, 0);
    return a_prev_cp_cstr((const char **)s);
}
a_cp a_prev_cp_cstr(const char **s)
{
    assert(s != NULL);
    PASSTHROUGH_ON_FAIL(s != NULL, 0);
    return a_internal_to_prev_cp(s);
}