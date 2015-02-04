/*
 * Copyright (c) 2006-2015 David Schor (david@zigwap.com), ZigWap LLC
 * 
 * License: MIT
 */

const char a_next_char_size[256] = 
{
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 
    2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 
    4, 4, 4, 4, 4, 4, 4, 4, 1, 1, 1, 1, 1, 1, 1, 1
};
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

static a_cp a_internal_to_next_cp(const char **s)
{
#if 1
    const unsigned char *p = (const unsigned char*)*s;
    const int size = a_size_chr_cstr(p);
    
    *s += size;
    switch (size)
    {
        case 1:
            return *p;
        case 2:
            return ((*p & 0x1F) << 6) | (p[1] & 0x3F);
        case 3:
            return ((*p & 0x0F) << 12) | ((p[1] & 0x3F) << 6) | (p[2] & 0x3F);
        case 4:
            return ((*p & 0x07) << 18) | ((p[1] & 0x3F) << 12) | ((p[2] & 0x3F) << 6) | (p[3] & 0x3F);
        default:
            return -1;
    }
#else
    const unsigned char *p = (const unsigned char*)*s;
    unsigned char c = *p;
    if (c < 0x80)
    {
        *s += 1;
        return c;
    }
    if ((c & 0xE0) == 0xC0/*&& (p[1] & 0xC0) == 0x80*/)
    {
        *s += 2;
        return ((c & 0x1F) << 6) | (p[1] & 0x3F);
    }
    if ((c & 0xF0) == 0xE0/* && (p[1] & 0xC0) == 0x80 && (p[2] & 0xC0) == 0x80*/)
    {
        *s += 3;
        return ((c & 0x0F) << 12) | ((p[1] & 0x3F) << 6) | (p[2] & 0x3F);
    }
    if ((c & 0xF8) == 0xF0/* && (p[1] & 0xC0) == 0x80 && (p[2] & 0xC0) == 0x80 && (p[3] & 0xC0) == 0x80*/)
    {
        *s += 4;
        return ((c & 0x07) << 18) | ((p[1] & 0x3F) << 12) | ((p[2] & 0x3F) << 6) | (p[3] & 0x3F);
    }
    return -1;
#endif
}
a_cp a_next_cp_cstr(const char **s)
{
    assert(s != NULL);
    PASSTHROUGH_ON_FAIL(s != NULL, 0);
    return a_internal_to_next_cp(s);
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