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

static char    *a_internal_critical_cp_to_char(a_cp cp, char *buffer);
static a_cp     a_internal_critical_char_to_cp(const char *s);
/*static a_cp   a_internal_critical_to_next(const char **s);*/
static a_cp     a_internal_critical_to_next_cp(const char **s);
static char    *a_internal_critical_to_prev(const char **s);
static a_cp     a_internal_critical_to_prev_cp(const char **s);

/*
 * const char * -> a_cp
 */
static a_cp a_internal_critical_char_to_cp(const char *s)
/*
 * this code is called from just about every function for
 * just about every operation, performance is very important.
 */
{
#if 0
    const unsigned char *p = (const unsigned char*)s;
    unsigned char c = *p;
    switch (a_next_char_size[c])
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
            return 0;
    }
#else
    unsigned char c = *s;
    
    if (c < 0x80)
        return c;
    if ((c & 0xE0) == 0xC0/*&& (s[1] & 0xC0) == 0x80*/)
        return ((c & 0x1F) << 6) | (s[1] & 0x3F);
    if ((c & 0xF0) == 0xE0/* && (s[1] & 0xC0) == 0x80 && (s[2] & 0xC0) == 0x80*/)
        return ((c & 0x0F) << 12) | ((s[1] & 0x3F) << 6) | (s[2] & 0x3F);
    if ((c & 0xF8) == 0xF0/* && (s[1] & 0xC0) == 0x80 && (s[2] & 0xC0) == 0x80 && (s[3] & 0xC0) == 0x80*/)
        return ((c & 0x07) << 18) | ((s[1] & 0x3F) << 12) | ((s[2] & 0x3F) << 6) | (s[3] & 0x3F);
    return -1;
#endif
}

static char *a_internal_critical_cp_to_char(a_cp cp, char *b)
{
    unsigned int c = (unsigned int)cp;
    
    if (c < 0x80)
        b[0] = (char)c, b[1] = '\0';
    else if (c < 0x0800)
        b[0] = (char)(0xC0 | (c >> 6)), 
        b[1] = (char)(0x80 | (c & 0x3F)),
        b[2] = '\0';
    else if (c < 0x10000)
        b[0] = (char)(0xE0 | (c >> 12)),
        b[1] = (char)(0x80 | ((c >> 6) & 0x3F)),
        b[2] = (char)(0x80 | (c & 0x3F)),
        b[3] = '\0';
    else if (c < 0x110000)
        b[0] = (char)(0xF0 | (c >> 18)),
        b[1] = (char)(0x80 | ((c >> 12) & 0x3F)),
        b[2] = (char)(0x80 | ((c >> 6) & 0x3F)),
        b[3] = (char)(0x80 | (c & 0x3F)),
        b[4] = '\0';
    else
        b[0] = '\0';
    
    return b;
}


static a_cp a_internal_critical_to_next_cp(const char **s)
{
#if 1
    const unsigned char *p = (const unsigned char*)*s;
    switch (a_size_chr_cstr(p))
    {
        case 1:
            *s += 1;
            return *p;
        case 2:
            *s += 2;
            return ((*p & 0x1F) << 6) | (p[1] & 0x3F);
        case 3:
            *s += 3;
            return ((*p & 0x0F) << 12) | ((p[1] & 0x3F) << 6) | (p[2] & 0x3F);
        case 4:
            *s += 4;
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

static a_cp a_internal_critical_to_prev_cp(const char **s)
{
    return a_internal_critical_char_to_cp(
                a_internal_critical_to_prev(s));
}

static char *a_internal_critical_to_prev(const char **s)
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