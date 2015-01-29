/*
 * Copyright (c) 2006-2015 David Schor (david@zigwap.com), ZigWap LLC
 * 
 * License: MIT
 */
char *a_prev(const char **s)
{
    const char *t;
    assert(s != NULL);
    PASSTHROUGH_ON_FAIL(s != NULL, NULL);
    for (t = *s - 1; ; --t)
    {
        if ((*t & 0xC0) != 0x80)
        {
            *s = t;
            break;
        }
    }
    
    return (char*)t;
}

a_cp a_prev_cp(const char **s)
{
    assert(s != NULL);
    PASSTHROUGH_ON_FAIL(s != NULL, 0);
    return a_to_cp(a_prev(s));
}